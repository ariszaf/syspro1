#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include "Map.h"
#include "Trie.h"

using namespace std;
bool isNumber(char *number);                            
void menuPanel(Map* map, Trie* trie,int k);         

int main(int argc, char** argv) {
    int K;                                  //posa apotelesmata to poly tha gyrisei gia kathe query                                
    char *fileName;
  
    //elegxos orismatwn
    if (argc < 3) {                        
        cout << "Too few arguments .. " << endl;
        return 1;
    } else if (argc > 5) {
        cout << "Too many arguments supplied ... " << endl;
        return 1;
    } else if (argc == 3) {                  // se periptwsi pou valei mono 2 orismata tote apaiteitai na xei valei san orisma to onoma tou arxeiou, prepei na proigeite to flag -i
        if (strcmp(argv[1], "-i") == 0) {            
            fileName = argv[2];
            K=5;
            cout << "the filename is " << fileName << " and the K is " << K << endl;
        } else {
            cout << "Invalid parameters .. " << endl;
            return 1;
        }
    } else if (argc == 5) {                 // dinetai i dunatotita ta flags na exoun diaforetiki seira  , diladi mporei na valei to -i san prwto flag i san deytero, to idio kai me to -k  
        if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-k") == 0 && isNumber(argv[4])) {  // ektos twn alwn elexete kai an k einai arithmos 
            fileName = argv[2];
            K = atoi(argv[4]);
            cout << "the filename is " << fileName << " and the K is " << K << endl;
        } else if (strcmp(argv[1], "-k") == 0 && isNumber(argv[2]) && strcmp(argv[3], "-i") == 0) {
            fileName = argv[4];
            K = atoi(argv[2]);
            cout << "the filename is " << fileName << " and the K is " << K << endl;
        } else {
            cout << "Invalid parameters .. " << endl;
            return 1;
        }
    } else {
        cout << "Invalid parameters .. " << endl;
        return 1;
    }
    if(K==0){
        K=5;
    }      
    
    Map* map = new Map();                   
    if (!map->readFile(fileName)) {     //diavasma tou arxeiou, prin to perasma twn keimenwn se enan pinaka ginetai elegxos gia lathi sto keimeno
        delete map;
        return 1;
    }

    Trie* trie = new Trie();
    trie->insertDoc(map);

    menuPanel(map, trie, K);

    delete map;
    delete trie;

    return 0;
}

void menuPanel(Map* map, Trie* trie, int k) {
    char* operation = NULL;
    int numOfWords;

    do {
        numOfWords = 0;
        char *line = NULL;
        cout << "----------Menu Panel----------" << endl; 
        cout << "/search" << endl;
        cout << "/df" << endl;
        cout << "/df word" << endl;
        cout << "/tf id word" << endl;
        cout << "/exit" << endl;
        printf("# ");
        size_t len = 0;
        ssize_t read;
        read = getline(&line, &len, stdin);
        //cout << line << endl;
        char *newline = strchr(line, '\n');    //https://stackoverflow.com/questions/16677800/strtok-not-discarding-the-newline-character 
        if (newline)
            *newline = 0;

        char* str = new char [strlen(line) + 1];
        strcpy(str, line);

        char * pch;
        pch = strtok(str, " \n");
        if (operation != NULL) {
            delete [] operation;
        }
        operation = new char [strlen(pch) + 1];
        strcpy(operation, pch);         //i prwti leksi einai to operation pou zitaei o xristis, opote tin apothikeyw sti metavliti operation

        while (pch != NULL) {
            pch = strtok(NULL, " \n");
            if (pch != NULL) {      //metrisi twn leksewn
                numOfWords++;
            }
        }
        
        cout << "Operation:" << operation << endl;

        if (strcmp(operation, "/search") == 0) {
            if (numOfWords == 0) {
                cout << "apaitite toulaxiston mia leksi gia na ektelestei to search" << endl;
            } else {
                if (numOfWords > 10) {
                    cout << "Panw apo 10 lekseis, tha upologistei me vasi tis prwtes 10  " << endl;
                }
                trie->Search(map,line,k);
            }
        } else if (strcmp(operation, "/df") == 0) {
            if (numOfWords == 0) {
                trie->df();
            } else if (numOfWords == 1) {
                char * dfword;
                dfword = strtok(line, " \n");
                dfword = strtok(NULL, " \n");
                trie->df(map, dfword);
            } else {
                cout << "I entoli df pernei to polu mia leksi" << endl;
            }
        } else if (strcmp(operation, "/tf") == 0) {
            if (numOfWords == 2) {
                int id, i;
                i = 0;
                char *word;
                char *tfWords;
                tfWords = strtok(line, " \n"); //http://www.cplusplus.com/forum/beginner/8388/
                while (tfWords != NULL) {
                    tfWords = strtok(NULL, " \n");
                    if (i == 0) {
                        if (isNumber(tfWords) == false) {
                            cout << "pliktrologiste swsta to ID" << endl;
                            break;
                        }
                        id = atoi(tfWords);
                    }
                    if (i == 1) {
                        word = new char [strlen(tfWords) + 1];
                        strcpy(word, tfWords);
                    }
                    i++;
                }
                trie->tf(map, id, word);
            } else {
                cout << "I entoli tf prepei na exei 2 lekseis" << endl;
            }
        } else if(strcmp(operation, "/exit") == 0){
            cout<<"Exit from program" <<endl;
        }
        else {
            cout << "Wrong operation" << endl;
        }        
        
        if (line != NULL) {
            free(line);
        }
        delete [] str;
    } while (strcmp(operation, "/exit") != 0); // otan pataei exit vgazei to pio panw error, diorthose t
      delete [] operation;
}

bool isNumber(char *number) //https://stackoverflow.com/questions/29248585/c-checking-command-line-argument-is-integer-or-not
{
    int i = 0;
    //checking for negative numbers
    if (number[0] == '-') {
        i = 1;
        cout << "please not negative numbers" << endl;
        return false;
    }
    for (; number[i] != 0; i++) {
        if (!isdigit(number[i])) {
            cout << "please enter right the number after flag -k" << endl;
            return false;
        }
    }
    return true;
}
