#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "Trie.h"
#include "PostingList.h"
#include "WordList.h"
#include "ScoreList.h"

using namespace std;

Trie::Trie() {
    root = NULL;
}

void Trie::insertWord(char* newWord, int id, int lineCounter) {
    if (newWord != NULL) { // se periptwsi pou i eisodos einai leksi(kai oxi null eisodos)  
        // cout << "word: " << newWord << endl;
        int len = strlen(newWord); //megethos leksis
        Node*temp = root;
        for (int i = 0; i < len; i++) { // gia kathe xaraktira tis leksis
            if (root == NULL) { // To trie einai keno opote i eisagogi tha ginei stin arxi
                while (i < len) { // gia kathe xaraktira                                
                    Node* newCharacter = new Node(); // dimioyrgia tou komvou
                    newCharacter->postingListHeadPtr = NULL;
                    newCharacter->character = newWord[i]; // enimerwsi tou xaraktira tou komvou  
                    if (i == 0) { //stin periptwsi pou einai o prwtos xaraktiras tha prepei na sindethei me to root
                        root = newCharacter;
                    } else {
                        temp->nextWordCharacter = newCharacter; //enimerwsi tou nextWordCharacter , na deixnei sto komvo pou molis ftiaxtike       
                    }
                    temp = newCharacter; //enimerwsi tou voithitikou temp deikti na deixnei ston trexon komvo pou dimiourgithike 
                    i++; //sunexizetai i idia diadikasia kai sto epomeno xaraktira                      
                }
                if (temp->postingListHeadPtr == NULL) {
                    PostingList* postingList = new PostingList(newWord); //dimioyrgia posting List 
                    temp->postingListHeadPtr = postingList;
                }
                temp->postingListHeadPtr->insertDataToPostingList(temp->postingListHeadPtr, id, lineCounter);
                break; //afou valame tin prwti leksi sto trie tote kanoume break kathws tin exoume isagei olokliri mesw tou eswterikou while 
            } else {
                while (temp != NULL) { //mexri na tsekaroume olous tou komvous                     
                    if (temp->character == newWord[i]) { //se periptwsi pou o xaraktiras einai idios ksekiname tin akolouthi diadikasia
                        while (i < len) { //  oxi perisoteres epanalipseis apo to megethos tis leksi   
                            if (temp->nextWordCharacter != NULL) { //An yparxei epomenos xaraktiras 
                                if (i == len - 1) { //an exoume ftasei ston telefteo xaraktira tis ipopsifias leksis tote stamatame kai enimerwnoume oti einai to telos tis leksis  
                                    if (temp->postingListHeadPtr == NULL) {
                                        PostingList* postingList = new PostingList(newWord); //dimioyrgia posting List 
                                        temp->postingListHeadPtr = postingList;
                                    }
                                    temp->postingListHeadPtr->insertDataToPostingList(temp->postingListHeadPtr, id, lineCounter);
                                    break;
                                } else if (temp->nextWordCharacter->character == newWord[i + 1]) { //afou yparxei epomenos xaraktiras,an einai idios me to epomeno gramma tis lekseis pou isixthei
                                    temp = temp->nextWordCharacter;
                                    i++;
                                } else { //an o epomenos xaraktiras den einai idios tote spaei i alisida
                                    temp = temp->nextWordCharacter; //o deiktis temp deixni ston epomeno xaraktira wste na skanaristei ayto to epipedo
                                    break; //break to trexon while, tha skanaristei to epipedo pou deixnei pleon o temp
                                }
                            } else if (temp->nextWordCharacter == NULL) { //an den yparxei epomenos xaraktiras stin diakladwsi
                                i++; //auksisi tou i, kathws o elegxos exei ginei gia ton i,   
                                while (i < len) { //dimiourgia kai topothetisi to ena katw apo ta ala twn ipolipomenwn xaraktirwn
                                    Node* newCharacter = new Node();
                                    newCharacter->postingListHeadPtr = NULL;
                                    newCharacter->character = newWord[i];
                                    temp->nextWordCharacter = newCharacter;
                                    temp = newCharacter;
                                    i++;
                                }
                                if (temp->postingListHeadPtr == NULL) {
                                    PostingList* postingList = new PostingList(newWord); //dimioyrgia posting List 
                                    temp->postingListHeadPtr = postingList;
                                }
                                temp->postingListHeadPtr->insertDataToPostingList(temp->postingListHeadPtr, id, lineCounter);
                                break; // meta to telos tis diadikasias ginetai break , kai kleinei i diadikasia mias kai to i =len opote den tha mpei oute sti kentriki for
                            }
                        }
                        break;
                    } else if (temp->nextListCharacter == NULL) { //se periptwsi pou exoume ftasei sto trexon epipedo sto telefteo komvo sigoura den yparxei yparxei o xaraktiras  
                        Node* newCharacter = new Node();
                        newCharacter->postingListHeadPtr = NULL;
                        newCharacter->character = newWord[i];
                        temp->nextListCharacter = newCharacter;
                        temp = newCharacter;
                        i++;
                        while (i < len) {
                            Node* newCharacter = new Node();
                            newCharacter->postingListHeadPtr = NULL;
                            newCharacter->character = newWord[i];
                            temp->nextWordCharacter = newCharacter;
                            temp = newCharacter;
                            i++;
                        }
                        if (temp->postingListHeadPtr == NULL) {
                            PostingList* postingList = new PostingList(newWord); //dimioyrgia posting List 
                            temp->postingListHeadPtr = postingList;
                        }
                        temp->postingListHeadPtr->insertDataToPostingList(temp->postingListHeadPtr, id, lineCounter);
                        break;
                    } else { //afou den exoume ftasei sto telefteo komvo ,topothetoume to temp ston epomeno komvo tou epipedou  
                        temp = temp->nextListCharacter;
                    }
                }
            }
        }
    }
}

// katastrofi mesw anadromis

Trie::~Trie() {
    df_traverse_delete(root);
}

void Trie::insertDoc(Map* map) {
    char **b = new char * [map->getLineCounter()];
    int size;

    for (int i = 0; i < map->getLineCounter(); i++) { // antigrafi tou pinaka me ta keimena se alo pinaka b, o logos i strtok pou aliwnei ena keimeno opote theloume na prostateysoume ton arxiko pinaka me ta keimena 
        size = strlen(map->getDocArray()[i]);
        b[i] = new char[size + 1];
        strcpy(b[i], map->getDocArray()[i]);
    }

    //eisagwgi kathe leksis twn keimenwn sto trie 
    for (int id = 0; id < map->getLineCounter(); id++) {
        char * pch; //http://www.cplusplus.com/reference/cstring/strtok/
        pch = strtok(b[id], " \t\n"); //http://www.cplusplus.com/forum/beginner/8388/
        while (pch != NULL) {
            insertWord(pch, id, map->getLineCounter());
            pch = strtok(NULL, " \t\n");
        }
    }

    for (int i = 0; i < map->getLineCounter(); i++) {
        delete [] b[i];
    }
    delete [] b;
}

void Trie::Search(Map* map, char * query, int k) {
    WordList* theWordList = new WordList();
    // theWordList voithitiki domi, apothikeyw onoma leksis kai to dikti pou deixnei stin posting list, na antlisw tin plirofories tis posting list kai na upologisw metepita to score
    char * pch;
    pch = strtok(query, " \n"); //http://www.cplusplus.com/forum/beginner/8388/
    int wordcount = 0;
    while (pch != NULL && wordcount < 10) { //mono oi 10 prwtes lekseis metexoun stin anazitisi
        pch = strtok(NULL, " \n");
        if (pch != NULL) {
            theWordList->insertWord(pch, GetPostingListHeadPtr(pch));
        }
        wordcount++;
    }

    ScoreList* scoreList = new ScoreList();
    theWordList->scoreFinder(scoreList, map);
    if (scoreList->scoreListHeadPtr != NULL) { //Sinthiki elegxou giati uparxei periptwsi i lista twn score na einai keni, i moni periptwsi einai oloi oi oroi anazitiseis na min uparxoun sto trie
        scoreList->mergeSort(scoreList->scoreListHeadPtr); //taksinomisi me merge sort
        scoreList->print(map, k);

    } else {
        cout << "I anazitisi den vrike kapoio egrafo" << endl;
    }
}

PostingList* Trie::GetPostingListHeadPtr(char* word) {
    PostingList* postListHeadPtr = NULL;
    int len = strlen(word);
    Node*temp = root;
    for (int i = 0; i < len; i++) { // gia kathe xaraktira tis leksis
        while (temp != NULL) {
            if (temp->character == word[i]) { //se periptwsi pou o xaraktiras einai idios ksekiname tin akolouthi diadikasia
                if (i == len - 1) { // se periptwsi pou prokeite gia ton telefteo xaraktira tis leksis tote an vrike posting list simainei oti  vrethike i leksi kaio diaforetika oti den vrethike
                    if (temp->postingListHeadPtr != NULL) {
                        return temp->postingListHeadPtr;
                        break;
                    } else {
                        return postListHeadPtr;
                        break;
                    }
                }
                if (temp->nextWordCharacter != NULL) {
                    if (temp->nextWordCharacter->character == word[i + 1]) { //afou yparxei epomenos xaraktiras,an einai idios me to epomeno gramma tis lekseis pou isixthei
                        temp = temp->nextWordCharacter;
                        i++;
                    } else { //an o epomenos xaraktiras den einai idios tote spaei i alisida
                        temp = temp->nextWordCharacter; //o deiktis temp deixni ston epomeno xaraktira wste na skanaristei ayto to epipedo
                        break; //break to trexon while, tha skanaristei to epipedou pou deixnei pleon o temp
                    }
                } else if (temp->nextWordCharacter == NULL) { //an den yparxei epomenos xaraktiras stin diakladwsi
                    return postListHeadPtr;
                    break; // meta to telos tis diadikasias ginetai break , kai kleinei i diadikasia mias kai to i =len opote den tha mpei oute sti kentriki for
                }
            } else if (temp->nextListCharacter == NULL) { //se periptwsi pou exoume ftasei sto trexon epipedo sto telefteo komvo sigoura den yparxei yparxei o xaraktiras  
                return postListHeadPtr;
                break;
            } else { //afou den exoume ftasei sto telefteo komvo ,topothetoume to temp ston epomeno komvo tou epipedou  
                temp = temp->nextListCharacter;
            }
        }
    }
    return postListHeadPtr;
}

void Trie::tf(Map* map, int docid, char* query) {
    PostingList* node = GetPostingListHeadPtr(query);

    if (node == NULL) {
        cout << "0" << endl;
    } else {
        int theWordCounter = -1;

        node->returnWordCounterFromSpecificNode(node, docid, &theWordCounter);

        if (theWordCounter != -1) {
            cout << theWordCounter << endl;
        } else {
            cout << "0" << endl;
        }
    }
}

void Trie::df(Map* map, char* query) {
    PostingList* node = GetPostingListHeadPtr(query);

    if (node == NULL) {
        cout << query << " " << "0" << endl;
    } else {
        cout << query << " " << node->docCounter << endl;
    }
}

//Eyresi lisis anadromika

void Trie::df() {
    df_traverse(root);
}

void Trie::df_visit(Node * n) {
    if (n != NULL) {
        if (n->postingListHeadPtr != NULL) {
            cout << n->postingListHeadPtr->word << " " << n->postingListHeadPtr->docCounter << endl;
        }
    }
}

void Trie::df_traverse(Node * n) {
    if (n != NULL) {
        df_visit(n);
        // cout<<n->character<<endl;
        df_traverse(n->nextListCharacter);
        df_traverse(n->nextWordCharacter);
    }
}

void Trie::df_visit_delete(Node * n) {
    if (n != NULL) {
        if (n->postingListHeadPtr != NULL) {
            delete n->postingListHeadPtr;
        }
        delete n;
    }
}

void Trie::df_traverse_delete(Node * n) {
    if (n != NULL) {
        df_traverse_delete(n->nextListCharacter);
        df_traverse_delete(n->nextWordCharacter);
        df_visit_delete(n);
    }
}
