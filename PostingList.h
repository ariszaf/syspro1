#ifndef POSTINGLIST_H
#define POSTINGLIST_H

class PostingList {
private:
    class PostingListNode {
    public:
        int id;
        int wordCounter;
        PostingListNode * next;        
    };
public:
    PostingList(char * word);
    ~PostingList();
    void insertDataToPostingList(PostingList*, int,int );
    void returnDataFromSpecificNode(PostingList*,int,int*,int*); 
    void returnWordCounterFromSpecificNode(PostingList*,int,int*); 
    double idfFinder(int,int);
    PostingListNode * firstNode;
    int docCounter;
    double idf;
    char * word;
};

#endif /* POSTINGLIST_H */

