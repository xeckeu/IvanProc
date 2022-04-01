#ifndef CONTAINER_H
#define CONTAINER_H

#include <fstream>
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

struct Aphorism {
    Key K;
    string text;
    string author;
};
Aphorism* inAphorism(ifstream& ifst);
void outAphorism(Aphorism* T, ofstream& ofst);

struct Saying {
    Key K;
    string text;
    string country;
};
Saying* inSaying(ifstream& ifst);
void outSaying(Saying* T, ofstream& ofst);

struct Riddle {
    Key K;
    string text;
    string answer;
};
Riddle* inRiddle(ifstream& ifst);
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
#endif //CONTAINER_H