#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool isIssued;

public:
    Book(int id, string title, string author)
        : id(id), title(title), author(author), isIssued(false) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }

    void issueBook() { isIssued = true; }
    void returnBook() { isIssued = false; }
};

class LibraryManager {
private:
    vector<Book> books;
    int bookCounter;

public:
    LibraryManager() : bookCounter(0) {}

    void addBook() {
        string title, author;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, author);
        books.push_back(Book(++bookCounter, title, author));
        cout << "Book added successfully!\n";
    }

    void searchBook() {
        string keyword;
        cout << "Enter book title or author to search: ";
        cin.ignore();
        getline(cin, keyword);

        bool found = false;
        for (const auto &book : books) {
            if (book.getTitle().find(keyword) != string::npos ||
                book.getAuthor().find(keyword) != string::npos) {
                cout << "ID: " << book.getId() << ", Title: " << book.getTitle()
                     << ", Author: " << book.getAuthor()
                     << ", Issued: " << (book.getIsIssued() ? "Yes" : "No") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No book found with the given keyword.\n";
        }
    }

    void issueBook() {
        int id;
        cout << "Enter book ID to issue: ";
        cin >> id;

        for (auto &book : books) {
            if (book.getId() == id) {
                if (book.getIsIssued()) {
                    cout << "Book is already issued.\n";
                } else {
                    book.issueBook();
                    cout << "Book issued successfully!\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;

        for (auto &book : books) {
            if (book.getId() == id) {
                if (!book.getIsIssued()) {
                    cout << "Book is not issued.\n";
                } else {
                    book.returnBook();
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
    }

    void generateReports() {
        cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(30) << "Author" << setw(10) << "Issued" << endl;
        cout << string(75, '-') << endl;

        for (const auto &book : books) {
            cout << left << setw(5) << book.getId() << setw(30) << book.getTitle()
                 << setw(30) << book.getAuthor() << setw(10)
                 << (book.getIsIssued() ? "Yes" : "No") << endl;
        }
    }
};

int main() {
    LibraryManager library;
    int choice;

    do {
        cout << "\nLibrary Manager Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Generate Reports\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;
        case 2:
            library.searchBook();
            break;
        case 3:
            library.issueBook();
            break;
        case 4:
            library.returnBook();
            break;
        case 5:
            library.generateReports();
            break;
        case 6:
            cout << "Exiting Library Manager. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
