#include <iostream>
#include "Map.h"
#include "Trie.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

Map::Map() : docArray(NULL) {
}

Map::~Map() {
    if (docArray != NULL) {
        for (int i = 0; i < lineCounter; i++) {
            delete [] docArray[i];
        }

        delete [] docArray;
        delete [] wordCounterArray;
    }
}

int Map::countLines(const char * filename) {
    //metrisi twn arithmo twn keimenwn
    FILE * myReadFile = NULL; //https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    myReadFile = fopen(filename, "r");
    if (myReadFile != NULL) {
        char * output = NULL;
        size_t len = 0;
        int nread, id;
        lineCounter = 0;

        while ((nread = getline(&output, &len, myReadFile)) != -1) {
            // cout<<output<<endl;
            char str[len] = {0}; //https://stackoverflow.com/questions/632846/clearing-a-char-array-c
            sscanf(output, "%d %[^\n]", &id, str); //https://stackoverflow.com/questions/11391870/sscanf-writing-to-a-character-array              
            // Tsekarisma twn id        
            if (id != lineCounter) {
                cout << "Provlima me ta Ids tou keimenou, prepei to prwto keimeno na ksekinaei me 0 kai na sunexizei se auksousa seira" << endl;
                if (output != NULL) {
                    free(output);
                }
                fclose(myReadFile);
                return 0;
            }
            // tsekarisma tou keimenou, me paradoxi oti den prepei na einai keno, prepei na exei toulaxiston mia leksi(megethous>0)
            if (strlen(str) < 1) { //http://www.cplusplus.com/reference/cstring/strlen/
                cout << "Mikro arxeio keimenoy, ta keimena tou arxeiou prepei na exoun toulaxiston 1 leksi(megethous toulaxiston 1 xaraktira)" << endl;
                if (output != NULL) {
                    free(output);
                }
                fclose(myReadFile);
                return 0;
            }
            lineCounter++;
            free(output);
            output = NULL;
        }
        if (output != NULL) {
            free(output);
        }
        fclose(myReadFile);
    } else {
        cout << "Not found the File or is empty" << endl;
        return 0;
    }
    //cout << "Line counter " << lineCounter << endl; //for debug 
    return lineCounter;
}

bool Map::readFile(const char * fileName) {
    if (countLines(fileName) == 0) { //metrima twn keimenwn sto arxeio kai elegxos lathwn 
        return false;
    }
    //edw apothikeyw ta keimena
    docArray = new char * [lineCounter]; //http://www.cplusplus.com/forum/beginner/26264/

    //apothikeuw poses lekseis exei to kathe keimeno
    wordCounterArray = new int [lineCounter]();

    FILE * myReadFile; //https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    myReadFile = fopen(fileName, "r");
    if (myReadFile != NULL) {
        char * output = NULL;
        size_t len = 0;
        int nread, id;

        while ((nread = getline(&output, &len, myReadFile)) != -1) { //diavasma tou arxeioy ana grammi
            char str[len];
            sscanf(output, "%d %[^\n]", &id, str); // https://stackoverflow.com/questions/11391870/sscanf-writing-to-a-character-array              
            docArray[id] = new char [strlen(str) + 1];
            strcpy(docArray[id], str); //perasma kathe keimenou stin antistixi thesi sto pinaka 

            //spasimo tou keimenou se leksis
            char * pch; //http://www.cplusplus.com/reference/cstring/strtok/
            pch = strtok(str, " \n"); //http://www.cplusplus.com/forum/beginner/8388/
            while (pch != NULL) {
                wordCounterArray[id] += 1; //enimerwsi tou pinaka pou arithmei poses lekseis exei to kathe keimenou
                pch = strtok(NULL, " \n");
            }
            free(output);
            output = NULL;
        }
        if (output != NULL) {
            free(output);
        }
        fclose(myReadFile);
        avgdlCalculator(); //ipologismos tou avgdl
    } else {
        cout << "cant open the file" << endl;
        return false;
    }
    return true;
}

void Map::print() {
    for (int i = 0; i < lineCounter; i++) {
        cout << docArray[i] << endl;
    }
}

void Map::avgdlCalculator() { // to meso plithos twn leksewn apo ola ta keimena
    int totalWords = 0;
    for (int i = 0; i < lineCounter; i++) {
        totalWords += wordCounterArray[i];
    }
    //cout << "totalWords= " << totalWords << endl;
    avgDL = (double) totalWords / lineCounter;
    //cout << "avgDL= " << avgDL << endl;
}

char** Map::getDocArray() {
    return docArray;
}

int Map::getLineCounter() {
    return lineCounter;
}

int* Map::getWordCounterArray() {
    return wordCounterArray;
}

double Map::getAvgDL() {
    return avgDL;
}