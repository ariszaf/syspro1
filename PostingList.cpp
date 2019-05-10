#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <math.h>
#include "PostingList.h"


using namespace std;

PostingList::PostingList(char * word) {
    this->word = new char[strlen(word) + 1];
    strcpy(this->word, word);
    firstNode = NULL;
}

void PostingList::insertDataToPostingList(PostingList* postingListPtr, int id, int lineCounter) {
    if (postingListPtr->firstNode == NULL) { // stin periptwsi pou den yparxei komvos                          
        PostingListNode* thefirstNode = new PostingListNode();
        thefirstNode->next = NULL;
        thefirstNode->id = id;
        thefirstNode->wordCounter = 1;
        postingListPtr->firstNode = thefirstNode;
        postingListPtr->docCounter = 1;
        postingListPtr->idf = idfFinder(lineCounter, postingListPtr->docCounter);
    } else {
        PostingListNode* postingListNodeTempPtr = postingListPtr->firstNode;
        while (postingListNodeTempPtr != NULL) { // 
            //an petyxei oti yparxei eidi kataxwrisi tis leksis gia to idio keimeno tote apla enimerwnei ton komvo, px stin periptwsi pou sinantame mia leksi panw apo mia fora sto idio keimeno
            if (postingListNodeTempPtr->id == id) { //se periptwsi pou afora enimerwsi komvoy , otan prokeite gia to idio doc id
                postingListNodeTempPtr->wordCounter++;
                break;
            }
            else if (postingListNodeTempPtr->next == NULL) { // diaforetika neos komvos afou prokeite gia pliroforia diaforetikou doc id      
                postingListPtr->docCounter++; 
                PostingListNode* newNode = new PostingListNode();
                newNode->next = NULL;
                newNode->id = id;
                newNode->wordCounter = 1;
                postingListNodeTempPtr->next = newNode;
                postingListPtr->idf = idfFinder(lineCounter, postingListPtr->docCounter);
                break;
            }
            postingListNodeTempPtr = postingListNodeTempPtr->next;
        }
    }
}

PostingList::~PostingList() {
    PostingListNode* tempPostingListNotePtr = this->firstNode;
    while (tempPostingListNotePtr != NULL) {
        PostingListNode* t = tempPostingListNotePtr;
        tempPostingListNotePtr = tempPostingListNotePtr->next;
        delete t;
    }
    delete []  this->word;
}

double PostingList::idfFinder(int N, int numOfDocs) {
    double result, m, n, e;
    m = N - numOfDocs + 0.5;
    n = numOfDocs + 0.5;
    e = m / n;

    result = log10(e);
    return result;
}

void PostingList::returnDataFromSpecificNode(PostingList* postingListPtr, int position, int* theId, int* theWordCounter) {
    PostingListNode* tempPostingListNotePtr = postingListPtr->firstNode;
    int currentPosition = 0;
    while (tempPostingListNotePtr != NULL) {

        if (currentPosition == position) {
            *theId = tempPostingListNotePtr->id;
            *theWordCounter = tempPostingListNotePtr->wordCounter;
            return;
        }

        currentPosition++;
        tempPostingListNotePtr = tempPostingListNotePtr->next;
    }

    *theId = -1;
    *theWordCounter = -1;
}

void PostingList::returnWordCounterFromSpecificNode(PostingList* postingListPtr, int docid, int* theWordCounter) {
    PostingListNode* tempPostingListNotePtr = postingListPtr->firstNode;
    while (tempPostingListNotePtr != NULL) {

        if (tempPostingListNotePtr->id == docid) {
            *theWordCounter = tempPostingListNotePtr->wordCounter;
            return;
        }
        tempPostingListNotePtr = tempPostingListNotePtr->next;
    }
    *theWordCounter = -1;
}