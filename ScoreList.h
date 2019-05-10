#ifndef SCORELIST_H
#define SCORELIST_H
#include "Map.h"

class ScoreList {
private:

    class ScoreListNode {
    public:
        double documentId;
        double score;
        ScoreListNode * next;
    };
public:
    ScoreList();
    void updateScore(double, double);
    ~ScoreList();
    ScoreListNode* scoreListHeadPtr;
    void print(Map*,int);
    int getLength(ScoreListNode *head);
    void mergeSort(ScoreListNode*&);
    ScoreListNode* merge(ScoreListNode* head1, ScoreListNode* head2);
    ScoreListNode* getScoreListHeadPtr();
};


#endif /* SCORELIST_H */

