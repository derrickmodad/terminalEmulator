/*
Task scheduler program through pseudo terminal
Created 5/17/24 - modad

5/18 - issue: fileName check after taking command is failing
              if only command is supplied, program crashes
              program should catch and ask for fileName
       potentially solved: changed method to catch no fileName

5/19 - issue: insert function double prints "i: " on first line
       fixed: add cin.ignore() to catch no fileName and clear buffer

ideas:
//add task function?
//or maybe task class?
//task --
//  title
//  description
//  date created
//  date edited (if)
//  date completed


*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void terminal();
void print(string, int);
void insert(string);
void edit(string);
void newFile(string);
void help();

int main() {
    terminal();
    return 0;
}

void terminal() {
    string input;
    cout << "terminal> ";
    getline(cin, input);

    if (input.substr(0, 3) == "new") {
        if (input.substr(4).length() < 1 || input[4] == ' ') {
            cout << " -- please specify a filename: ";
            cin >> input;
            newFile(input);
        } else
            newFile(input.substr(4));
    } else if (input.substr(0, 5) == "print") {
        if (input.substr(6).length() < 1 || input[6] == ' ') {
            cout << " -- please specify a filename: ";
            cin >> input;
            print(input, 0);
        } else
            print(input.substr(6), 0);
    } else if (input == "help") {
        help();
    } else if (input.substr(0, 6) == "insert" || input == "insert") {
        if (input.length() == 7 || input[7] == ' ' || input.length() == 6) { //look at this, this shit is wack
            cout << " -- please specify a filename: "; //something in this if is breaking the first iteration on the do while in insert
            cin >> input;
            cin.ignore();
            insert(input);
        } else
            insert(input.substr(7));
    } else if (input == "exit") {
        cout << " -- exiting" << endl;
        exit(EXIT_SUCCESS);
    } else {
        cout << " -- command not recognized\n -- type \"help\" for a list of available commands" << endl;
        terminal();
    }    
}

void print(string fileName, int arg) {
    string buffer;
    int line = 0; //for the display of line numbers
    ifstream file;
    file.open(fileName);
    if (!file.good()) {
        cout << " -- error printing file" << endl;
        terminal();
    } else {
        while (getline(file, buffer)) {
            if (arg)
                cout << ++line << ". " << buffer << endl;
            else 
                cout << buffer << endl;
        }
        terminal();
    }
}

void insert(string fileName) {
    vector<string> content;
    string buffer;
    ifstream readIn;
    ofstream writeOut;

    readIn.open(fileName);

    if (readIn.good()) {    
        while (getline(readIn, buffer))
            content.push_back(buffer);
        readIn.close();
    } else {
        cout << " -- error opening file" << endl;
        terminal();
    }
    
    do {
        cout << "i: ";    
        getline(cin, buffer);
        if (buffer != "wq")
            content.push_back(buffer);
    } while (buffer != "wq");

    //something here to allow user to exit insert without saving

    writeOut.open(fileName);
    if (writeOut.good()) {
        for (auto i : content)
            writeOut << i << endl;
        writeOut.close();
        cout << " -- saved" << endl;
    } else {
        cout << " -- error saving to file" << endl;
        //maybe something here to catch a failed save to prevent user from retyping 
    }
    terminal();
}

void edit(string fileName) {
    print(fileName, 1);
}

void newFile(string fileName) {
    ofstream outputFile;
    outputFile.open(fileName);
    if (!outputFile.good()) {
        cout << " -- error creating file" << endl;
        terminal();
    } else {
        outputFile.close();
        cout << " -- " << fileName << " created" << endl;
        terminal();
    }
}

void help() {
    cout << "\navailable commands" << endl
         << "------------------" << endl
         << "new (fileName)" << endl
         << "insert (fileName)" << endl
         << "print (fileName)\n" << endl;
    terminal();
}

/*
old code because idk if i should delete it:

if (input.length() > 1) {
        if (input.substr(0, 3) == "new") {
            if (input.substr(4).length() < 1 || input[4] == ' ') {
                cout << "please specify a filename: ";
                cin >> input;
                newFile(input);
            } else
                newFile(input.substr(4));
        } else if (input.substr(0, 5) == "print") {
            if (input.substr(6).length() < 1 || input[6] == ' ') {
                cout << "please specify a filename: ";
                cin >> input;
                print(input);
            } else
                print(input.substr(6));
        } else if (input == "help") {

        }
    } else {
        switch (toupper(input[0])) {
            case 'W':
                break;
            case 'I':
                break;
            case 'E':
                break;                
            default:
                cout << "unrecognized command - type \"help\" for a list of commands" << endl;
                terminal();
                break;
        }
    }

    while (s == 'I' || s == 'i') {
            cout << "insert: " ;
            getline(cin, input);
            if (input == "" || input == "W") {
                s = 't';
                file.open("test.txt");
                if (file.good()) {
                    cout << "saving..." << endl;
                    for (auto i : output)
                        file << i << endl;
                    file.close();
                    cout << "save successful !" << endl;
                } else 
                    cout << "error !" << endl;
            } else
                output.push_back(input);
    }
*/