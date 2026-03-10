/*
* Name: Wadan Mehraban
 * Date: March 9, 2026
 * Purpose: Lab - Pointers, Vectors, & RAII.
 */


#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Book Class ---
//holding the book info
class Book {
private:
    string title;
    string auth; // that is author
    double cost; //

public:
    // simple constructor for private data
    Book(string t, string a, double c) {
        title = t;
        auth = a;
        cost = c;
    }

    void showBook() const { //
        cout << "Book: " << title << " by " << auth << " ($" << cost << ")" << endl;
    }
};

// --- Inventory Class ---
// this is for the manager class
class Inventory {
private:
    //adding the pointers here
    vector<Book*> bookList;

public:
    // Destructor part of the assignment
    ~Inventory() {
        cout << "--- Destructor: Cleaning up books from heap ---" << endl;
        for (int i = 0; i < (int)bookList.size(); i++) {
            delete bookList[i];
        }
        bookList.clear();
    }
// functoin to add a new book pointer to our vector
    void add(Book* b) {
        bookList.push_back(b);
    }

    void printAll() const {
        if (bookList.empty()) {
            cout << "Nothing in stock yet." << endl;
        }
        else {
            for (int i = 0; i < (int)bookList.size(); i++) {
                cout << i << ". ";
                bookList[i]->showBook(); // using -> for the pointer
            }
        }
    }

    void remove(int idx) {
        if (idx >= 0 && idx < (int)bookList.size()) {
            delete bookList[idx]; // free memory first
            bookList.erase(bookList.begin() + idx);
            cout << "Removed book at index " << idx << endl;
        }
        else {
            cout << "Error: Index out of bounds." << endl;
        }
    }
};

int main() {
    Inventory myStore; //creating inventory object on the stack
    int userIn = 0;
// writing menu loop
    while (userIn != 4) {
        cout << "\n1) Add Book\n2) Show All\n3) Remove\n4) Exit\n> ";
        cin >> userIn;

        if (userIn == 1) {
            string t, a;
            double p;

            cout << "Title: ";
            cin.ignore(); // skip newline from cin
            getline(cin, t);
            cout << "Author: ";
            getline(cin, a);
            cout << "Price: ";
            cin >> p;

            // Make the new book on the heap and pass pointer
            Book* temp = new Book(t, a, p);
            myStore.add(temp);
        }
        else if (userIn == 2) {
            myStore.printAll();
        }
        else if (userIn == 3) {
            int toDelete;
            cout << "Index to delete: ";
            cin >> toDelete;
            myStore.remove(toDelete);
        }
    }

    // myStore goes out of scope here, calling destructor automatically
    return 0;
}