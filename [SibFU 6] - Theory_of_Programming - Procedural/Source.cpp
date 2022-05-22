#include "Header.h"

void initContainer(Container* list) {
    list->head->current = list->tail->current = NULL;
	list->head->next = list->tail->next = NULL;
	list->head->prev = list->tail->prev = NULL;
	list->size = list->size = 0;
}

void inContainer(Container* list, ifstream& ifst) {
    Node* temp=new Node;
    while (!ifst.eof()) {
        if (!list->size) {
            if ((list->head->current = inText(ifst))) {
                list->tail = list->head;
                list->size++;
            }
        }
        else {
			if ((temp-> current = inText(ifst))) {
                list->tail->next = temp;
                list->head->prev = temp;
                temp->prev = list->tail;
                temp->next = list->head;
                list->tail = temp;
                list->size++;
            }
        }
    }
   
}

void outContainer(Container* list, ofstream& ofst) {
    ofst << "Container contains " << list->size
        << " elements." << endl << endl;
    Node* temp = list->head;
    for (int i = 0; i < list->size; i++) {
        ofst << i << ": \n";
        outText(temp->current, ofst);
        if (temp->next) {
            temp = temp->next;
        }
    }
}

void clearContainer(Container* list) {
    Node* temp = list->head;
    list->head->prev = NULL;
    list->head->next = NULL;
	for (int i = 0; i < list ->size; i++) {
        free(temp->current);
        if (temp->next) {
            temp = temp->next;
            free(temp->prev);
        }
    }
    list->size = 0;
}

bool compare(Text* a, Text* b) {
    return textCounter(a) < textCounter(b);
}

void sort(Container* list) {
    if (list->size > 1) {
        Node* first = list->head;
		Node* second = list->head->next;
		Node* temp = new Node;
        for (int i = 0; i <list->size - 1; i++) {
            for (int j = 0; j < list->size - i - 1; j++) {
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

int outFilter(Container* list, ofstream& ofst) {
    Node* temp = list->head;
    for (int i = 0; i < list->size; i++) {
		if (temp->current->K == APHORISM) {
			ofst << i << ":\n";
			int ret = outAphorism((Aphorism *)temp->current, ofst);
			switch (ret)
			{
			case 0:
			{
				ofst << "[Punctuation]: " << textCounter(temp->current) << endl << endl;
				break;
			}
			default:
				return ret;
			}

         
        }
        if (temp->next) {
            temp = temp->next;
        }
		return 0;
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

int  outText(Text* T, ofstream& ofst) {
	int ret = 0;
    if (T->K == APHORISM) {
        ret = outAphorism((Aphorism*)T, ofst);
		if (ret)
			return ret;
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
	return 0;
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

int outAphorism(Aphorism* T, ofstream& ofst) 
{
	ofst << "[Aphorism]: " << T->text << endl;
	if (ofst.fail());
	{
		return 1;
	}
	ofst << "[Author]: " << T->author << endl;
	if (ofst.fail());
	{
		return 2;
	}
	ofst << "[Punctuation]: " << textCounter((Text*)T) << endl;
	if (ofst.fail());
	{
		return 3;

	}

	ofst << "[Mark]: " << T->mark << endl << endl;
	if (ofst.fail());
	{
		return 4;

	}
	return 0;

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