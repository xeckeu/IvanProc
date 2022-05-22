#ifndef CONTAINER_H
#define CONTAINER_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

enum Key {
    APHORISM,
    SAYING,
    RIDDLE
};

struct Text {
    Key K;
};
Text* inText(ifstream& ifst);
int outText(Text* C, ofstream& ofst);
int textCounter(Text* T);

struct Aphorism {
    Key K;
    string text;
    string author;
    int mark;
};
Aphorism* inAphorism(ifstream& ifst);
int outAphorism(Aphorism* T, ofstream& ofst);
int aphorismCounter(Aphorism* T);

struct Saying {
    Key K;
    string text;
    string country;
    int mark;
};
Saying* inSaying(ifstream& ifst);
void outSaying(Saying* T, ofstream& ofst);
int sayingCounter(Saying* T);

struct Riddle {
    Key K;
    string text;
    string answer;
    int mark;
};
Riddle* inRiddle(ifstream& ifst);
int riddleCounter(Riddle* T);
void outRiddle(Riddle* T, ofstream& ofst);

struct  Node 
{
		Text* current;
		Node* prev;
		Node* next;
};

struct Container 
{
	Node* head;
	Node* tail;
	int size;
};
void initContainer(Container* list);
void inContainer(Container* list, ifstream& ifst);
void outContainer(Container* list, ofstream& ofst);
void clearContainer(Container* list);
void sort(Container* list);
int outFilter(Container* list, ofstream& ofst);

#endif //CONTAINER_H