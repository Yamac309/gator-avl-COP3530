#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include "AVL.h"

using namespace std;

// Checks if the ID is valid, it must be exactly 8 digits long
bool isValidID(string id) {
    if (id.length() != 8) return false;

    // make sure every character is a digit
    for (int i = 0; i < id.length(); i++) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

// Checks if the name is valid. It can only contain letters and spaces
bool isValidName(string name) {
    if (name.length() == 0) return false;

    for (int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return false;
    }
    return true;
}

int main() {
    // Creates the AVL tree object
    AVL tree;

    // Reads the number of commands
    int n;
    cin >> n;
    cin.ignore();

    // Process each command
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);  // Reads the full command line

        // Prints inorder traversal
        if (line == "printInorder") {
            vector<string> names = tree.printInorder();
            for (int j = 0; j < names.size(); j++) {
                if (j > 0) cout << ", ";
                cout << names[j];
            }
            cout << endl;
        }

        // Prints preorder traversal
        else if (line == "printPreorder") {
            vector<string> names = tree.printPreorder();
            for (int j = 0; j < names.size(); j++) {
                if (j > 0) cout << ", ";
                cout << names[j];
            }
            cout << endl;
        }

        // Prints postorder traversal
        else if (line == "printPostorder") {
            vector<string> names = tree.printPostorder();
            for (int j = 0; j < names.size(); j++) {
                if (j > 0) cout << ", ";
                cout << names[j];
            }
            cout << endl;
        }

        // Prints the number of levels in the tree
        else if (line == "printLevelCount") {
            cout << tree.levelCount() << endl;
        }

        // Inserts the command
        else if (line.find("insert") == 0) {
            // Finds the quoted name
            int q1 = line.find('"');
            int q2 = line.find('"', q1 + 1);

            // If quotes are missing, command is invalid
            if (q1 == string::npos || q2 == string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }

            // Extract the name between quotes
            string name = line.substr(q1 + 1, q2 - q1 - 1);

            // Extracts the ID after the name
            string rest = line.substr(q2 + 1);
            string id;
            stringstream ss(rest);
            ss >> id;

            // Validates the name and ID before inserting
            if (!isValidName(name) || !isValidID(id)) {
                cout << "unsuccessful" << endl;
            } else {
                // Try inserting into the AVL tree
                if (tree.insert(name, id)) {
                    cout << "successful" << endl;
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        }

        // Searches for command
        else if (line.find("search") == 0) {
            // Search by name
            if (line.find('"') != string::npos) {
                int q1 = line.find('"');
                int q2 = line.find('"', q1 + 1);

                // Checks for invalid format
                if (q1 == string::npos || q2 == string::npos) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // Extracts the name
                string name = line.substr(q1 + 1, q2 - q1 - 1);
                vector<string> ids = tree.searchName(name);

                // If no ID is found, prints unsuccessful
                if (ids.size() == 0) {
                    cout << "unsuccessful" << endl;
                } else {
                    // Print all matching IDs
                    for (int k = 0; k < ids.size(); k++) {
                        cout << ids[k] << endl;
                    }
                }
            }

            // Searches by ID
            else {
                string cmd, id;
                stringstream ss(line);
                ss >> cmd >> id;

                string found;
                if (isValidID(id) && tree.searchID(id, found)) {
                    cout << found << endl;
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        }

        // Removes inorder command
        else if (line.find("removeInorder") == 0) {
            string cmd;
            int index;
            stringstream ss(line);
            ss >> cmd >> index;

            if (tree.removeInorder(index)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        }

        // Remove by ID command
        else if (line.find("remove") == 0) {
            string cmd, id;
            stringstream ss(line);
            ss >> cmd >> id;

            if (isValidID(id) && tree.removeID(id)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        }

        // For any unrecognized commands
        else {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}