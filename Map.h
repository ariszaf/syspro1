#ifndef MAP_H
#define MAP_H

class Map {
public:
    Map();          
    ~Map(); 
    bool readFile(const char * filename);
    void print();
    void avgdlCalculator();
    char** getDocArray() ;
    int getLineCounter() ;
    int* getWordCounterArray() ;
    double getAvgDL() ;
private:
    char **docArray;    //http://www.cplusplus.com/forum/beginner/26264/
    int lineCounter;
    double avgDL;
    int *wordCounterArray;
    int countLines(const char * filename);
};

#endif /* MAP_H */

