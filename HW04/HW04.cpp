#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;
    int availableCopies;

    Book(const string& title, const string& author)
        : title(title), author(author), availableCopies(3) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    // 책 제목으로 검색
    void searchByTitle(const string& title) const {
        for (const Book& book : books) {
            if (book.title == title) {
                cout << "검색 결과: " << book.title << " by " << book.author << endl;
                return;
            }
        }
        cout << "해당 제목의 책을 찾을 수가 없습니다." << endl;
    }

    // 작가 이름으로 검색
    void searchByAuthor(const string& author) const {
        bool found = false;
        for (const Book& book : books) {
            if (book.author == author) {
                if (!found) {
                    cout << "작가 [" << author << "]의 책 목록:" << endl;
                    found = true;
                }
                cout << "- " << book.title << endl;
            }
        }
        if (!found) {
            cout << "해당 작가의 책을 찾을 수가 없습니다." << endl;
        }
    }

    // 책 이름으로 대여
    void borrowByTitle(const string& title) {
        for(Book& book : books) {
            if (book.title == title) {
                if (book.availableCopies > 0) {
                    book.availableCopies--;
                    cout << "책 \"" << book.title << "\" 을(를) 대여했습니다. 남은 재고: " << book.availableCopies << endl;
                }
                else {
                    cout << "현재 \"" << book.title << "\" 의 재고가 없습니다." << endl;
                }
                return;
            }
        }
        cout << "해당 제목의 책을 찾을 수 없습니다." << endl;
    }

    // 작가 이름으로 대여
    void borrowByAuthor(const string& author) {
        bool found = false;
        for (Book& book : books) {
            if (book.author == author) {
                found = true;
                cout << "- " << book.title << " (재고: " << book.availableCopies << ")";
                if (book.availableCopies > 0) {
                    book.availableCopies--;
                    cout << " -> 대여 완료. 남은 재고: " << book.availableCopies << endl;
                }
                else {
                    cout << " -> 대여 불가 (재고 없음)" << endl;
                }
            }
        }
        if (!found) {
            cout << "해당 작가의 책을 찾을 수 없습니다." << endl;
        }
    }

    // 책 이름으로 반납
    void returnBook(const string& title) {
        for (Book& book : books) {
            if (book.title == title) {
                if (book.availableCopies < 3) {
                    book.availableCopies++;
                    cout << "책 \"" << book.title << "\" 을(를) 반납했습니다. 현재 재고: " << book.availableCopies << endl;
                }
                else {
                    cout << "해당 책은 반납이 필요하지 않습니다. (재고 가득)" << endl;
                }
                return;
            }
        }
        cout << "해당 제목의 책을 찾을 수 없습니다." << endl;
    }
};

int main() {
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 종료" << endl; // 프로그램 종료
        cout << "4. 제목으로 책 검색" << endl; // 책 제목 입력받아 책 검색
        cout << "5. 작가로 책 검색" << endl; // 작가 이름 입력받아 책 검색
        cout << "6. 제목으로 책 대여" << endl; // 제목 입력받아 책 대여
        cout << "7. 작가로 책 대여" << endl; // 작가 이름 입력받아 책 대여
        cout << "8. 책 반납" << endl; // 제목 입력받아 반납
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else if (choice == 4) {
            // 4번 선택 : 책 제목 입력받아 책 검색
            // 현재 책 목록 중에서 제목이 일치하는 책을 찾아 출력
            string title;
            cout << "검색할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            manager.searchByTitle(title);
        }
        else if (choice == 5) {
            // 5번 선택 : 작가 이름 입력받아 책 검색
            // 현재 책 목록 중에서 작가 이름이 일치하는 책을 찾아 출력
            string author;
            cout << "검색할 작가 이름: ";
            cin.ignore();
            getline(cin, author);
            manager.searchByAuthor(author);
        }
        else if (choice == 6) {
            // 6번 선택 : 제목 입력받아 책 대여
            // 책 목록 중에서 제목이 일치하는 책의 재고를 -1
            string title;
            cout << "대여할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            manager.borrowByTitle(title);
        }
        else if (choice == 7) {
            // 7번 선택 : 작가 이름 입력받아 책 대여
            // 책 목록 중에서 작가 이름이 일치하는 책의 재고를 -1
            string author;
            cout << "대여할 책 작가 이름: ";
            cin.ignore();
            getline(cin, author);
            manager.borrowByAuthor(author);
        }
        else if (choice == 8) {
            // 8번 선택 : 제목 입력받아 책 반납
            // 책 목록 중에서 제목이 일치하는 책의 재고를 +1
            string title;
            cout << "반납할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            manager.returnBook(title);
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
