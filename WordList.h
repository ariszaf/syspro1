#ifndef WORDLIST_H
#define WORDLIST_H
#include "PostingList.h"
#include "ScoreList.h"
#include "Map.h"

class WordList {
private:
    class WordListNode {
    public:
        char* word;
        PostingList* postingListHeadPtr;
        WordListNode * next;
    };
public:
    WordList();
    ~WordList();
    void insertWord(char*, PostingList*);
    WordListNode* wordListHeadPtr;
    void scoreFinder(ScoreList*,Map* ); 

};

#endif /* WORDLIST_H */