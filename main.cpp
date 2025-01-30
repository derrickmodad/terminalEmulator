/*
Task scheduler program through pseudo terminal
Created 5/17/24 - modad

5/18 - issue: fileName check after taking command is failing
              if only command is supplied, program crashes
              program should catch and ask for fileName
       potentially solved: changed method to catch no fileName

5/19 - issue: insert function double prints "i: " on first line
       fixed: add cin.ignore() to catch no fileName and clear buffer

//5/21 - checking git push

ideas:
//add task function?
//or maybe task class?
//task --
//  title
//  description
//  date created
//  date edited (if)
//  date completed


add a validating function template so all input can be validated
    i.e. usernames can have spaces put within them and after them so they will technically be new users
    make a validating tool that prevents this


*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void firstRun();
void terminal();
void print(string, int);
void insert(string);
void edit(string);
void newFile(string);
int user();
void createUser(string, int);
void help();
void daemonLog();

string userName; //global variable so all functions can access the current user
bool isAdmin;

int main() {
    firstRun();
    terminal();
    return 0;
}

void firstRun() {
    //this is where the user file will be created
    //  (the file that holds all users)
    //also where the main account will be loaded

    ifstream check("userList.txt");
    if (!check.good()) {
        ofstream createUserFile("userList.txt");
        createUserFile << "S-admin|admin";
        createUserFile.close();
        userName = "admin";
        isAdmin = true;
    } else {
        char c;
        while (check.get(c)) {
            if (c != '|')
                userName.push_back(c);
            else 
                break;
        }
        check.close();
    }
}

void terminal() {
    string input;
    cout << "terminal> ";
    getline(cin, input);

    if (input.substr(0, 3) == "new" || input == "new") {
        if (input.length() == 4 || input[4] == ' ' || input.length() == 3) {
            cout << " -- please specify a filename: ";
            cin >> input;
            newFile(input);
        } else
            newFile(input.substr(4));
    } else if (input.substr(0, 5) == "print" || input == "print") {
        if (input.length() == 6 || input[6] == ' ' || input.length() == 5) {
            cout << " -- please specify a filename: ";
            cin >> input;
            print(input, 0);
        } else
            print(input.substr(6), 0);
    } else if (input == "help") {
        help();
    } else if (input.substr(0, 6) == "insert" || input == "insert") {
        if (input.length() == 7 || input[7] == ' ' || input.length() == 6) { //look at this, this shit is wack
            cout << " -- please specify a filename: ";
            cin >> input;
            cin.ignore();
            insert(input);
        } else
            insert(input.substr(7));
    } else if (input.substr(0, 11) == "create user" || input == "create user") {
        if (input.length() == 12 || input[12] == ' ' || input.length() == 11) {
            createUser("fill", 0);
        } else {
            createUser(input.substr(12), 1); 
        }
    } else if (input == "whoami") {
        cout << "user: " << userName << endl;
        terminal();
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
        getline(file, buffer);
        if (buffer != userName) {
            cout << " -- insufficient privileges to read document" << endl;
            terminal();
        }
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
        if (buffer != ":wq")
            content.push_back(buffer);
    } while (buffer != ":wq");

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
        outputFile << userName;
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
         << "print (fileName)" << endl
         << "exit\n" << endl;
    terminal();
}

void createUser(string uName, int fromMain) {
    if (!fromMain) {
        cout << " -- please specify a username: ";
        getline(cin, uName);
    }

    ifstream fromUserList("userList.txt");
    string buffer;
    vector<string> users;

    if (!fromUserList.good()) {
        cout << " -- error creating user" << endl;
        terminal();
    }

    while (getline(fromUserList, buffer)) {
        users.push_back(buffer);
    }

    //something here for checking if username has already been used

    //then if passing, prompt for password

    //then append to file


    //fromUserList.clear();  //clears eof marker
    //fromUserList.seekg(0); //reset stream position to beginning of file

}

int user() {
    //File for users:
    //admins will have regex: A-username (not case sensitive)
    //standard users are    : S-username (not case sensitive)


    string uname, pass;
    cout << "username: ";
    getline(cin, uname);
    cout << "password: ";
    getline(cin, pass);


    return 1;
}