#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book
{
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BorrowManager
{
protected:
    unordered_map<string, int> stock;

private:
    int quantity;

public:
    // 재고 개수를 3개로 초기화
    BorrowManager() : quantity(3) {}

    // 책의 이름과 저자, 재고를 리스트에 저장 메서드
    void initializeStock(Book book)
    {
        stock[book.title + ":" + book.author] = quantity;
    }

    // 책 대여 가능 여부 출력 메서드
    void displayStock(const string& TitleAndAuthor)
    {
        auto it = stock.find(TitleAndAuthor);
        if (it != stock.end())
        {
            cout << it->second << "개의 재고가 있으므로 대여가 가능합니다.\n" << endl;
        }
        else
        {
            cout << "재고가 없으므로 대여가 불가능합니다." << endl;
        }
    }

    // 책 대여 메서드
    void borrowBook(const string& TitleAndAuthor)
    {
        auto it = stock.find(TitleAndAuthor);
        size_t pos = TitleAndAuthor.find(":");
        string author = TitleAndAuthor.substr(pos + 1);
        string title = TitleAndAuthor.substr(0, pos);

        if (it != stock.end())
        {
            if (it->second > 0)
            {
                it->second--;
                cout << endl << author << " 저자의 " << title << " 책을 대여 처리 하였습니다. 현재 재고는 " << it->second << "권 입니다." << endl;
            }
            else
            {
                cout << endl << title << " 책의 재고가 없습니다. 재고를 확인하세요." << endl;
            }
        }
        else
        {
            cout << endl << title << " 책이 목록에 존재하지 않아 대여 처리할 수 없습니다." << endl;
        }
    }

    // 책 반납 메서드
    void returnBook(const string& TitleAndAuthor)
    {
        auto it = stock.find(TitleAndAuthor);
        size_t pos = TitleAndAuthor.find(":");
        string author = TitleAndAuthor.substr(pos + 1);
        string title = TitleAndAuthor.substr(0, pos);

        if (it != stock.end())
        {
            if (it->second < 3)
            {
                it->second++;
                cout << endl << author << " 저자의 " << title << " 책이 반납 되었습니다. 현재 재고는 " << it->second << "권 입니다." << endl;
            }
            else
            {
                cout << endl << author << " 저자의 " << title << " 책의 재고가 3권으로 이미 가득 차 있습니다. 반납 처리할 수 없습니다." << endl;
            }
        }
        else
        {
            cout << title << "\n 책이 목록에 존재하지 않아 반납할 수 없습니다." << endl;
        }
    }
};

class BookManager 
{
private:
    vector<Book> books; // 책 목록 저장
    BorrowManager borrowManager; // 책 대여 클래스 선언
public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author)
    {
        books.push_back(Book(title, author));
        borrowManager.initializeStock(Book(title, author));
        cout << "\n책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const
    {
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++)
        {
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // 책의 제목이나 저자로 검색 메서드
    // 책이 있는지 검색해 출력하고 해당 책의 재고를 출력합니다.
    void searchByTitleOrAuthor(const string& search)
    {
        for (Book book : books)
        {
            if (book.title == search || book.author == search)
            {
                cout << endl << book.author << " 저자의 " << book.title << " 책이 있습니다." << endl;
                borrowManager.displayStock(book.title + ":" + book.author);
                return;
            }
        }
        cout << search << " 책이 없습니다." << endl;
    }

    // 책의 제목이나 저자를 재고 관리 key로 반환 메서드
    string MakeSearchKey(const string& search)
    {
        for (Book book : books)
        {
            if (book.title == search || book.author == search)
            {
                return book.title + ":" + book.author;
            }
        }
        return "";
    }

    // 대여관리 클래스의 책 대여 메서드 호출
    // BorrowManager 클래스의 기능을 연결합니다.
    void borrowBook(const string& key)
    {
        string searchKey = MakeSearchKey(key);
        if (!searchKey.empty())
        {
            borrowManager.borrowBook(searchKey);
        }
    }

    // 대여관리 클래스의 책 반납 메서드 호출
    // BorrowManager 클래스의 기능을 연결합니다.
    void returnBook(const string& key)
    {
        string searchKey = MakeSearchKey(key);
        if (!searchKey.empty())
        {
            borrowManager.returnBook(searchKey);
        }
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
        cout << "3. 책 검색" << endl;
        cout << "4. 책 대여" << endl;
        cout << "5. 책 반납" << endl;
        cout << "6. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장

        while (true)
        {
            cin >> choice;

            if (cin.fail() || !(1 <= choice && choice <= 6))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
                continue;
            }
            break;
        }

        if (choice == 1)
        {
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
        else if (choice == 2)
        {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3번 선택: 책 검색 및 대여 가능 여부 출력
            // 입력한 책의 대여 가능 여부와 현재 재고를 확인해 출력합니다.
            cout << "\n책의 제목이나 저자로 검색하세요: ";

            string search;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, search);
            manager.searchByTitleOrAuthor(search);
        }
        else if (choice == 4)
        {
            // 4번 선택: 책 대여
            // 사용자가 입력한 책을 대여 처리하고, 현재 재고를 출력합니다.

            cout << "\n대여하실 책의 제목이나 저자를 입력하세요: ";

            string input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);
            manager.borrowBook(input);
        }
        else if (choice == 5)
        {
            // 5번 선택: 책 반납
            // 사용자가 입력한 책을 반납 처리하고, 현재 재고를 출력합니다.
            cout << "\n반납하실 책의 제목이나 저자를 입력하세요: ";

            string input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);
            manager.returnBook(input);
        }
        else if (choice == 6)
        {
            // 6번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else
        {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}