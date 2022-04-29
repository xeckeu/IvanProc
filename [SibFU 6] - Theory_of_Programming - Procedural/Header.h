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
void outText(Text* C, ofstream& ofst);
int textCounter(Text* T);

struct Aphorism {
    Key K;
    string text;
    string author;
    int mark;
};
Aphorism* inAphorism(ifstream& ifst);
void outAphorism(Aphorism* T, ofstream& ofst);
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

struct Container {
    int length;
    Text* current;
    Container* prev;
    Container* next;
};

void initContainer(Container* head, Container* tail);
void inContainer(Container* head, Container* tail, ifstream& ifst);
void outContainer(Container* head, ofstream& ofst);
void clearContainer(Container* head, Container* tail);
void sort(Container* head);
void outFilter(Container* head, ofstream& ofst);

#endif //CONTAINER_H