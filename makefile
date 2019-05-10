all:Map.o PostingList.o Trie.o ScoreList.o WordList.o main.o main
CC = g++
OUT = main
OBJS = Map.o PostingList.o Trie.o ScoreList.o WordList.o main.o
RM = rm -f

Map.o: Map.cpp Map.h
	$(CC) -c -o Map.o Map.cpp
PostingList.o: PostingList.cpp PostingList.h
	$(CC) -c -o PostingList.o PostingList.cpp
Trie.o: Trie.cpp Trie.h
	$(CC) -c -o Trie.o Trie.cpp
ScoreList.o: ScoreList.cpp ScoreList.h
	$(CC) -c -o ScoreList.o ScoreList.cpp
WordList.o: WordList.cpp WordList.h
	$(CC) -c -o WordList.o WordList.cpp
main.o: main.cpp
	$(CC) -c -o main.o main.cpp
main: Map.o PostingList.o Trie.o ScoreList.o WordList.o main.o
	$(CC) -o main Map.o PostingList.o Trie.o ScoreList.o WordList.o main.o
clean:
	$(RM) $(OBJS) main

