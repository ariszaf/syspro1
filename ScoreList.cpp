#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "ScoreList.h"
#include "Map.h"


using namespace std;

ScoreList::ScoreList() {
    scoreListHeadPtr=NULL;
}

ScoreList::~ScoreList() {
}

void ScoreList::updateScore(double theDocId, double score) {
    if (scoreListHeadPtr == NULL) { // an den yparxei lista, dimioyrgia
        scoreListHeadPtr = new ScoreListNode();
        scoreListHeadPtr->documentId = theDocId;
        scoreListHeadPtr->score = score;
        scoreListHeadPtr->next = NULL;
    } else { // an yparxei lista tote enimerwsi tis uparxousas 
        ScoreListNode* tempScoreListPtr = scoreListHeadPtr;
        bool exist = false;
        while (tempScoreListPtr != NULL) {  // tsekarisma an eidi iparxei komvos me to sugkekrimeno id, diladi an exei eidi arxisei na tou ipologizetai score
            if (tempScoreListPtr->documentId == theDocId) {
                tempScoreListPtr->score += score;
                exist = true;
            }
            tempScoreListPtr = tempScoreListPtr->next;
        }
        if (exist == false) {               // neo komvos se periptwsi pou to sigkekrimeno arxeio den exei arxisei na tou katagrafetai to score sti lista
            ScoreListNode* newDok = new ScoreListNode();
            newDok->documentId = theDocId;
            newDok->score = score;
            newDok->next = scoreListHeadPtr;
            scoreListHeadPtr = newDok;
        }
    }
}

void ScoreList::print(Map* map,int k) {
    ScoreListNode* tempScoreListNodePtr = scoreListHeadPtr;

    int row = 1;
    while (tempScoreListNodePtr != NULL && row<=k) {
        int documId = tempScoreListNodePtr->documentId;
        cout << row << ".( " << documId << ")" << "[" << tempScoreListNodePtr->score << "] " << map->getDocArray()[documId] << endl;
        tempScoreListNodePtr = tempScoreListNodePtr->next;
        row++;
    }

}
//!!!
//Pigi algorithmou https://gist.github.com/hnguyen091188/efa43431593f2370007e
void ScoreList::mergeSort(ScoreListNode*& head) {
    if (head->next != NULL) //check the condition if this is the last node, do nothing
    {
        ScoreListNode* head1;
        ScoreListNode* head2 = head; //assign head to head 2. Head 2 will point to second half of the linked list
        int len = getLength(head);
        for (int i = 0; i < len / 2; i++) //use for loop to increment the pointer 2 to the mid poin in linked list
        {
            head1 = head2; // assign head1 to any node head2 point to, 
            head2 = head2->next; //in order to put NULL terminate for the first half of the linked list
        }
        head1->next = NULL; //terminate first half of the linked list
        head1 = head; //reposition head1 to the beginning of linked list, also the first node of the first half
        mergeSort(head1);
        mergeSort(head2);
        head = merge(head1, head2);
    }
}

ScoreList::ScoreListNode* ScoreList::merge(ScoreListNode *head1, ScoreListNode *head2) {
    ScoreListNode* newHead;
    //Base case: return the other half if  one of them is NULL
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;

    //compare the value
    if (head1->score > head2->score) {
        newHead = head1; //assign the newHead to the Node has smaller value
        newHead->next = merge(head1->next, head2); //recall the functionto find the next Node
    } else {
        newHead = head2;
        newHead->next = merge(head1, head2->next);
    }

    return newHead;
}

int ScoreList::getLength(ScoreListNode *head) {
    ScoreListNode* cur = head;
    int i = 0;
    for (; cur != NULL; cur = cur->next) {
        i++;
    }
    return i;
}