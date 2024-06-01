#include "bst.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		throw invalid_argument("ERROR INVALID FORMATTING");
	}

	Tree tree;
	
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);

	string line, com, val1, val2;

	while (getline(input, line)) {
		if (line.length() == 0) continue;

		stringstream ss(line);
		getline(ss, com, ' ');

		if (com == "i" && getline(ss, val1, ' ')) {
			tree.root = tree.AVLinsert(tree.root, val1);

		} else if (com == "r") {
			if (getline(ss, val1, ' ') && getline(ss, val2, ' ')) {
				
				output << to_string(tree.wordRange(val1, val2)) << endl;
			}
		}
	}
	tree.printTree(tree.root, 0);
	input.close();
	output.close();
}
