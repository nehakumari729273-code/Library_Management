#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;
    time_t issueDate;

    Book(int id, const string &title, const string &author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = false;
        this->issueDate = 0;
    }

    void display() {
        cout << "Book ID: " << id << endl;
        cout << "Title  : " << title << endl;
        cout << "Author : " << author << endl;
        cout << "Status : " << (isIssued ? "Issued" : "Available") << endl;
        cout << "------------------------" << endl;
    }
};

class Library {
    vector<Book> books;

    void generateReceipt(const string &operation, Book &book, int fine = 0) {
        ofstream rec("receipt.txt");
        time_t now = time(0);
        char currentDateStr[100];
        strftime(currentDateStr, sizeof(currentDateStr), "%d %b %Y %H:%M:%S", localtime(&now));

        char issueDateStr[100] = "N/A";
        if (book.issueDate != 0)
            strftime(issueDateStr, sizeof(issueDateStr), "%d %b %Y", localtime(&book.issueDate));

        rec << "------------------------------\n";
        rec << "        Library Receipt       \n";
        rec << "------------------------------\n";
        rec << "Current Date : " << currentDateStr << endl;
        rec << "Operation    : " << operation << endl;
        rec << "Book ID      : " << book.id << endl;
        rec << "Title        : " << book.title << endl;
        rec << "Author       : " << book.author << endl;
        rec << "Issued Date  : " << issueDateStr << endl;
        rec << "Status       : " << (book.isIssued ? "Issued" : "Available") << endl;
        if (fine > 0)
            rec << "Fine         : ₹" << fine << endl;
        else if (operation == "Returned")
            rec << "Fine         : No fine\n";
        rec << "------------------------------\n";
        rec << " Thank you for using Library  \n";
        rec << "------------------------------\n";
        rec.close();
        cout << "Receipt generated in 'receipt.txt'.\n";
    }

public:
    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        cout << "List of Books:\n";
        for (Book &b : books)
            b.display();
    }

    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;
        for (Book &b : books) {
            if (b.id == id) {
                cout << "Book Found:\n";
                b.display();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;
        for (Book &b : books) {
            if (b.id == id) {
                if (b.isIssued) {
                    cout << "Book is already issued!\n";
                } else {
                    b.isIssued = true;
                    b.issueDate = time(0);
                    cout << "Book issued successfully!\n";
                    generateReceipt("Issued", b);
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;
        for (Book &b : books) {
            if (b.id == id) {
                if (!b.isIssued) {
                    cout << "Book is not issued.\n";
                } else {
                    b.isIssued = false;
                    time_t returnTime = time(0);
                    double seconds = difftime(returnTime, b.issueDate);
                    int days = seconds / (60 * 60 * 24);
                    int fine = 0;
                    if (days > 30) {
                        fine = (days - 30) * 100;
                        cout << "Book returned late! Fine: ₹" << fine << endl;
                    } else {
                        cout << "Book returned on time. No fine.\n";
                    }
                    char issueDateStr[100];
                    strftime(issueDateStr, sizeof(issueDateStr), "%d %b %Y", localtime(&b.issueDate));
                    cout << "Book was issued on: " << issueDateStr << endl;
                    b.issueDate = 0;
                    generateReceipt("Returned", b, fine);
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }
};

int main() {
    Library lib;
    int choice;
    do {
        cout << "\n=== Library Management Menu ===\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book (Check Fine)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.issueBook(); break;
            case 5: lib.returnBook(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);
    return 0;
}