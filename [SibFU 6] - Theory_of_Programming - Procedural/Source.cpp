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

bool compare(Text* a, Text* b) {
    return textCounter(a) < textCounter(b);
}

void sort(Container* head) {
    if (head->length > 1) {
        Container* first = head;
        Container* second = head->next;
        Container* temp = new Container;
        for (int i = 0; i < head->length - 1; i++) {
            for (int j = 0; j < head->length - i - 1; j++) {
                if (compare(first->current, second->current)) {
                    temp->current = first->current;
                    first->current = second->current;
                    second->current = temp->current;
                }
                second = second->next;
            }
            first = first->next;
            second = first->next;
        }
    }
}

void outFilter(Container* head, ofstream& ofst) {
    Container* temp = head;
    for (int i = 0; i < head->length; i++) {
        if (temp->current->K == APHORISM) {
            ofst << i << ":\n";
            outAphorism((Aphorism *)temp->current, ofst);
            ofst << "[Punctuation]: " << textCounter(temp->current) << endl << endl;
        }
        if (temp->next) {
            temp = temp->next;
        }
    }
}

Text* inText(ifstream& ifst) {
    Text* C;
    int K;
    string temp = "";
    getline(ifst, temp);
    if ((temp != "1") && (temp != "2") && (temp != "3")) {
        if (ifst.peek() == EOF) {
            return 0;
        }
        else {
            cout << "Invalid input data!" << endl << endl;
            system("pause");
            exit(1);
        }
    }
    else
        K = atoi(temp.c_str());

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
        ofst << "Invalid element!" << endl;
    }
}

int textCounter(Text* T){
    if (T->K == APHORISM)
        return aphorismCounter((Aphorism*)T);
    else if (T->K == SAYING)
        return sayingCounter((Saying*)T);
    else if (T->K == RIDDLE)
        return riddleCounter((Riddle*)T);
    else
        return -1;
}

Aphorism* inAphorism(ifstream& ifst) {
    Aphorism* T = new Aphorism();
    string temp;
    string nums = "9876543210";
    int mark;
    bool flag = false;
    getline(ifst, temp);
    if (!temp.empty()) {
        T->text = temp;
    }
    else {
        cout << "Invalid input data!" << endl << endl;
        system("pause");
        exit(1);
    }
    getline(ifst, temp);
    if (!temp.empty()) {
        for (auto c : temp) {
            if (!isalpha(c))
            {
                if (c != ' ' && c != '-' && c != ',' && c != '.')
                {
                    cout << "[Aphorism] Invalid Data!" << endl << endl;
                    system("pause");
                    exit(1);
                }
            }
        }
        flag = true;
    }
    if (flag)
        T->author = temp;
    getline(ifst, temp);
    if (!temp.empty() && nums.find(temp) != -1) {
        mark = atoi(temp.c_str());
        if ((mark >= 0) && (mark <= 10))
            T->mark = mark;
        else
        {
            cout << "[Mark] Invalid input data!" << endl << endl;
            system("pause");
            exit(1);
        }
    }
    return T;
}

int aphorismCounter(Aphorism* T) {
    int counter = 0;
    string punctuationMarks = ".,?!:;-_";
    for (auto m : punctuationMarks)
        counter += count(T->text.begin(), T->text.end(), m);
    return counter;
}

void outAphorism(Aphorism* T, ofstream& ofst) {
    ofst << "[Aphorism]: " << T->text << endl;
    ofst << "[Author]: " << T->author<< endl;
    ofst << "[Punctuation]: " << textCounter((Text*)T) << endl;
    ofst << "[Mark]: " << T->mark<< endl << endl;
}

Saying* inSaying(ifstream& ifst) {
    Saying* T = new Saying();
    string temp;
    string nums = "9876543210";
    int mark;
    bool flag = false;
    getline(ifst, temp);
    if (!temp.empty()) {
        T->text = temp;
    }
    else {
        cout << "Invalid input data!" << endl << endl;
        system("pause");
        exit(1);
    }
    getline(ifst, temp);
    if (!temp.empty()) {
        for (auto c : temp) {
            if (!isalpha(c))
            {
                if (c != ' ' && c != '-' && c != ',' && c != '.')
                {
                    cout << "[Saying] Invalid Data!" << endl << endl;
                    system("pause");
                    exit(1);
                }
            }
        }
        flag = true;
    }
    if (flag)
        T->country = temp;
    getline(ifst, temp);
    if (!temp.empty() && nums.find(temp) != -1) {
        mark = atoi(temp.c_str());
        if ((mark >= 0) && (mark <= 10))
            T->mark = mark;
        else
        {
            cout << "[Mark] Invalid input data!" << endl << endl;
            system("pause");
            exit(1);
        }
    }
    return T;
}

int sayingCounter(Saying* T) {
    int counter = 0;
    string punctuationMarks = ".,?!:;-_";
    for (auto m : punctuationMarks)
        counter += count(T->text.begin(), T->text.end(), m);
    return counter;
}

void outSaying(Saying* T, ofstream& ofst) {
    ofst << "[Saying]: " << T->text << endl;
    ofst << "[Country]: " << T->country << endl;
    ofst << "[Punctuation]: " << textCounter((Text*)T) << endl;
    ofst << "[Mark]: " << T->mark << endl << endl;
}

Riddle* inRiddle(ifstream& ifst) {
    Riddle* T = new Riddle();
    string temp;
    string nums = "9876543210";
    int mark;
    bool flag = false;
    getline(ifst, temp);
    if (!temp.empty()) {
        T->text = temp;
    }
    else {
        cout << "Invalid input data!" << endl << endl;
        system("pause");
        exit(1);
    }
    getline(ifst, temp);
    if (!temp.empty()) {
        for (auto c : temp) {
            if (!isalpha(c))
            {
                if (c != ' ' && c != '-' && c != ',' && c != '.')
                {
                    cout << "[Riddle] Invalid Data!" << endl << endl;
                    system("pause");
                    exit(1);
                }
            }
        }
        flag = true;
    }
    if (flag)
        T->answer = temp;
    getline(ifst, temp);
    if (!temp.empty() && nums.find(temp) != -1) {
        mark = atoi(temp.c_str());
        if ((mark >= 0) && (mark <= 10))
            T->mark = mark;
        else
        {
            cout << "[Mark] Invalid input data!" << endl << endl;
            system("pause");
            exit(1);
        }
    }
    return T;
}

int riddleCounter(Riddle* T) {
    int counter = 0;
    string punctuationMarks = ".,?!:;-_";
    for (auto m : punctuationMarks)
        counter += count(T->text.begin(), T->text.end(), m);
    return counter;
}

void outRiddle(Riddle* T, ofstream& ofst) {
    ofst << "[Riddle]: " << T->text << endl;
    ofst << "[Answer]: " << T->answer << endl;
    ofst << "[Punctuation]: " << textCounter((Text*)T) << endl;
    ofst << "[Mark]: " << T->mark << endl << endl;
}