#include <iostream>
#include "Header.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "usage: lab_1_proc.exe in_file out_file" << endl;
        exit(1);
    }
    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);
    Container *head = new Container();
    Container *tail = new Container();

    initContainer(head, tail);
    inContainer(head, tail, ifst);
    ofst << "Container filled." << endl;
    cout << "Container filled." << endl;
    outContainer(head, ofst);
    ofst << "Output filtered." << endl;
    cout << "Output filtered." << endl;
    outFilter(head, ofst);
    clearContainer(head, tail);
    ofst << "Container cleared." << endl;
    cout << "Container cleared." << endl;
    outContainer(head, ofst);
    cout << "Done!" << endl;
    system("pause");
    return 0;
}