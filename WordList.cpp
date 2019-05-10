#include "WordList.h"
#include "ScoreList.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

WordList::WordList() {
    wordListHeadPtr = NULL;
}

WordList::~WordList() {
}

void WordList::insertWord(char* newWord, PostingList* postingListHeadPtr) {
    if (wordListHeadPtr == NULL) {
        wordListHeadPtr = new WordListNode();
        wordListHeadPtr->next = NULL;
    } else {
        WordListNode* nextWord = new WordListNode();
        nextWord->next = wordListHeadPtr;
        wordListHeadPtr = nextWord;
    }
    wordListHeadPtr->postingListHeadPtr = postingListHeadPtr;
    wordListHeadPtr->word = newWord;
}

void WordList::scoreFinder(ScoreList* scoreList,Map* map) {
    int theDocId;
    int theWordCounter;
    double score;
    WordListNode* tempWordListNodeptr=wordListHeadPtr;
    while (tempWordListNodeptr != NULL) {
        if (tempWordListNodeptr->postingListHeadPtr != NULL) {
            for (int i = 0; i < tempWordListNodeptr->postingListHeadPtr->docCounter; i++) {
                //enimrwsi tou doc id kai tou wordcounter kathe keimenou 
                tempWordListNodeptr->postingListHeadPtr->returnDataFromSpecificNode(tempWordListNodeptr->postingListHeadPtr, i, &theDocId, &theWordCounter);
                //score calculator
                score = tempWordListNodeptr->postingListHeadPtr->idf * ((theWordCounter * (1.2 + 1) / (theWordCounter + 1.2 * (1 - 0.75 + (0.75 * (map->getWordCounterArray()[theDocId] / map->getAvgDL()))))));
                scoreList->updateScore(theDocId,score);
            }
        }
        tempWordListNodeptr = tempWordListNodeptr->next;
    }
}