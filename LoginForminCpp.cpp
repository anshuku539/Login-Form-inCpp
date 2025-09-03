#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class temp {
    string userName, Email, password;
    string searchName, searchPass, searchEmail;
    fstream file;
public:
    void login();
    void signUp();
    void forgot();
};

temp obj;

int main() {
    char choice;

    do {
        cout << "\n-----------------------";
        cout << "\n1- Login";
        cout << "\n2- Sign-Up";
        cout << "\n3- Forgot Password";
        cout << "\n4- Exit";
        cout << "\n\nEnter Your Choice :: ";
        cin >> choice;
        cin.ignore(); // Input buffer ko clear karne ke liye
        switch (choice) {
            case '1':
                obj.login();
                break;
            case '2':
                obj.signUp();
                break;
            case '3':
                obj.forgot();
                break;
            case '4':
                cout << "\nExiting program... Thank you!" << endl;
                break;
            default: 
                cout << "Invalid Selection...!" << endl;
        }
    } while (choice != '4'); // Loop tab tak chalega jab tak user '4' na select kare

    return 0;
}

void temp::signUp() {
    cout << "\n--- SIGN UP ---";
    cout << "\nEnter Your User Name: ";
    getline(cin, userName);
    cout << "Enter Your Email Address: ";
    getline(cin, Email);
    cout << "Enter Your Password: ";
    getline(cin, password);

    // File ko append mode mein kholna taaki purana data delete na ho
    file.open("loginData.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << userName << "*" << Email << "*" << password << endl;
        file.close();
        cout << "\nSign up successful!" << endl;
    } else {
        cout << "Error: Could not open the file!" << endl;
    }
}

void temp::login() {
    cout << "\n--- LOGIN ---" << endl;
    cout << "Enter Your User Name: ";
    getline(cin, searchName);
    cout << "Enter Your Password: ";
    getline(cin, searchPass);

    bool found = false;
    file.open("loginData.txt", ios::in);
    
    if (!file.is_open()) {
        cout << "Error: No user data found. Please sign up first." << endl;
        return;
    }

    while (getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password, '\n')) {
        if (userName == searchName) {
            found = true;
            if (password == searchPass) {
                cout << "\nAccount Login Successful...!" << endl;
                cout << "\nUsername: " << userName;
                cout << "\nEmail: " << Email << endl;
            } else {
                cout << "\nPassword is Incorrect...!" << endl;
            }
            break; // Username mil gaya, aage check karne ki zaroorat nahi
        }
    }
    file.close();

    if (!found) {
        cout << "\nUsername not found...!" << endl;
    }
}

void temp::forgot() {
    cout << "\n--- FORGOT PASSWORD ---";
    cout << "\nEnter Your UserName: ";
    getline(cin, searchName);
    cout << "Enter Your Email Address: ";
    getline(cin, searchEmail);

    bool accountFound = false;
    file.open("loginData.txt", ios::in);

    if (!file.is_open()) {
        cout << "Error: No user data found." << endl;
        return;
    }

    while (getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password, '\n')) {
        if (userName == searchName && Email == searchEmail) {
            accountFound = true;
            cout << "\nAccount Found...!" << endl;
            cout << "Your Password is: " << password << endl;
            break; 
        }
    }
    file.close();

    if (!accountFound) {
        cout << "\nAccount not found with the provided details." << endl;
    }
}


