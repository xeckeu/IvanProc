#include "Header.h"

void initContainer(Container* head, Container* tail) {
    head->current = tail->current = NULL;
    head->next = tail->next = NULL;
    head->prev = tail->prev = NULL;
    head->length = tail->length = 0;
}

void inContainer(Container* head, Container* tail, ifstream& ifst) {
    Container* temp;
    int length = 0;
    while (!ifst.eof()) {
        temp = new Container();
        temp->next = NULL;
        temp->prev = NULL;
        if (!length) {
            if ((head->current = inText(ifst))) {
                tail = head;
                length++;
            }
        }
        else {
            if ((temp->current = inText(ifst))) {
                tail->next = temp;
                head->prev = temp;
                temp->prev = tail;
                temp->next = head;
                tail = temp;
                length++;
            }
        }
    }
    for (int i = 0; i < length; i++) {
        head->length = length;
        if (head->next) {
            head = head->next;
        }
    }
}

void outContainer(Container* head, ofstream& ofst) {
    ofst << "Container contains " << head->length
        << " elements." << endl << endl;
    Container* temp = head;
    for (int i = 0; i < head->length; i++) {
        ofst << i << ": \n";
        outText(temp->current, ofst);
        if (temp->next) {
            temp = temp->next;
        }
    }
}

void clearContainer(Container* head, Container* tail) {
    Container* temp = head;
    head->prev = NULL;
    head->next = NULL;
    for (int i = 0; i < head->length; i++) {
        free(temp->current);
        temp->length = 0;
        if (temp->next) {
            temp = temp->next;
            free(temp->prev);
        }
    }
    head->length = 0;
}

Text* inText(ifstream& ifst) {
    Text* C;
    int K;
    ifst >> K;
    if (K == 1) {
        C = (Text*)inAphorism(ifst);
        C->K = APHORISM;
        return C;
    }
    else if (K == 2) {
        C = (Text*)inSaying(ifst);
        C->K = SAYING;
        return C;
    }
    else if (K == 3) {
        C = (Text*)inRiddle(ifst);
        C->K = RIDDLE;
        return C;
    }
    else {
        return 0;
    }
}

void outText(Text* T, ofstream& ofst) {
    if (T->K == APHORISM) {
        outAphorism((Aphorism*)T, ofst);
    }
    else if (T->K == SAYING) {
        outSaying((Saying*)T, ofst);
    }
    else if (T->K == RIDDLE) {
        outRiddle((Riddle*)T, ofst);
    }
    else {
        ofst << "Incorrect element!" << endl;
    }
}

Aphorism* inAphorism(ifstream& ifst) {
    Aphorism* T = new Aphorism();
    ifst >> T->text;
    ifst >> T->author;
    return T;
}

void outAphorism(Aphorism* T, ofstream& ofst) {
    ofst << "[Aphorism]: " << T->text << endl;
    ofst << "[Author]: " << T->author<< endl << endl;
}

Saying* inSaying(ifstream& ifst) {
    Saying* T = new Saying();
    ifst >> T->text;
    ifst >> T->country;
    return T;
}

void outSaying(Saying* T, ofstream& ofst) {
    ofst << "[Saying]: " << T->text << endl;
    ofst << "[Country]: " << T->country << endl << endl;
}

Riddle* inRiddle(ifstream& ifst) {
    Riddle* T = new Riddle();
    ifst >> T->text;
    ifst >> T->answer;
    return T;
}

void outRiddle(Riddle* T, ofstream& ofst) {
    ofst << "[Riddle]: " << T->text << endl;
    ofst << "[Answer]: " << T->answer << endl << endl;
}