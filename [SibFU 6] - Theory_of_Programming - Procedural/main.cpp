#include "Header.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "usage: #.exe in_file out_file" << endl;
        exit(1);
    }
    ifstream ifst(argv[1]);
    if (!ifst.is_open()) {
        cout << "No input file found or could not open!" << endl;
        system("pause");
        return 1;
    }
    if (ifst.peek() == std::ifstream::traits_type::eof())
    {
        cout << "File is empty!" << endl << endl;
        system("pause");
        return 1;
    }
    ofstream ofst(argv[2]);
    if (!ofst.is_open()) {
        cout << "No output file found or could not open!" << endl;
        system("pause");
        return 1;
    }
    Container *list = new Container();

    initContainer(list);
    inContainer(list, ifst);
    ofst << "Container filled." << endl;
    cout << "Container filled." << endl;
    outContainer(list, ofst);
    sort(list);
    ofst << "Container sorted." << endl;
    cout << "Container sorted." << endl;
    outContainer(list, ofst);
    ofst << "Output filtered." << endl;
    cout << "Output filtered." << endl;
	if (outFilter(list, ofst))
	{
		cout << "Error of writing";
	}
    clearContainer(list);
    ofst << "Container cleared." << endl;
    cout << "Container cleared." << endl;
    outContainer(list, ofst);
    cout << "Done!" << endl;
    system("pause");
    return 0;
}