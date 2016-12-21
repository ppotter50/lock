#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

int main () {
	string filename,pass("one"),passcheck("two"),line;
	int n=1;
	ofstream newCode("lock.cpp");

	cout << "File with sensitive information: ";
	cin >> filename;
	ifstream secret(filename.c_str());

	if (secret.fail()) {
		cout << "File does not exist!" << endl;
		return 0;
	}

	while (pass!=passcheck) {
		cout << "Type your password: ";
		cin >> pass;
		cout << "Retype your password: ";
		cin >> passcheck;

		if (pass!=passcheck) {
			cout << "Passwords do not match!" << endl;
		}
	}

	newCode << "#include <iostream>" << endl;
	newCode << "#include <fstream>" << endl;
	newCode << "#include <stdlib.h>" << endl;
	newCode << "#include <string>" << endl;
	newCode << "using namespace std;" << endl << endl;
	newCode << "int main () {" << endl;
	newCode << "	string pass(\"" << pass << "\");" << endl;
	newCode << "	string entered;" << endl;
	newCode << "	int n=0;" << endl;
	newCode << "	ofstream open(\"" << filename << "\");" << endl << endl;
	newCode << "	cout << \"Type password: \";" << endl;
	newCode << "	cin >> entered;" << endl << endl;
	newCode << "	while (n<=3) {" << endl;
	newCode << "		if (entered==pass) {" << endl;
	getline(secret,line);
	while (!secret.fail()){
		newCode << "			open << \"" << line << "\" << endl;"  << endl;
		getline(secret,line);
	}
	newCode << "			cout << \"Access Granted\" << endl;" << endl;
	newCode << "			system(\"rm lock\");" << endl;
	newCode << "			return 0;" << endl;
	newCode << "		}" << endl;
	newCode << "		else if (n<2){" << endl;
	newCode << "			cout << \"Incorrect Password\" << endl;" << endl;
	newCode << "			cout << \"Type Password: \";" << endl;
	newCode << "			cin >> entered;" << endl;
	newCode << "			n++;" << endl;
	newCode << "		}" << endl;
	newCode << "		else if (n==2) {" << endl;
	newCode << "			cout << \"Password limit exceeded. The file will be deleted\" << endl;" << endl;
	newCode << "			system(\"rm lock\");" << endl;
	newCode << "			return 0;" << endl;
	newCode << "		}" << endl;
	newCode << "	}" << endl;
	newCode << "}" << endl;

	newCode.close();
	secret.close();

	system("g++ lock.cpp -o lock");
	string remove = "rm ";
	remove = remove + filename;
	system(remove.c_str());
	system("rm lock.cpp");
	return 0;
}


