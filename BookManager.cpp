#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std ���

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
    // ��� ������ 3���� �ʱ�ȭ
    BorrowManager() : quantity(3) {}

    // å�� �̸��� ����, ��� ����Ʈ�� ���� �޼���
    void initializeStock(Book book)
    {
        stock[book.title + ":" + book.author] = quantity;
    }

    // å �뿩 ���� ���� ��� �޼���
    void displayStock(const string& TitleAndAuthor)
    {
        auto it = stock.find(TitleAndAuthor);
        if (it != stock.end())
        {
            cout << it->second << "���� ��� �����Ƿ� �뿩�� �����մϴ�.\n" << endl;
        }
        else
        {
            cout << "��� �����Ƿ� �뿩�� �Ұ����մϴ�." << endl;
        }
    }

    // å �뿩 �޼���
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
                cout << endl << author << " ������ " << title << " å�� �뿩 ó�� �Ͽ����ϴ�. ���� ���� " << it->second << "�� �Դϴ�." << endl;
            }
            else
            {
                cout << endl << title << " å�� ��� �����ϴ�. ��� Ȯ���ϼ���." << endl;
            }
        }
        else
        {
            cout << endl << title << " å�� ��Ͽ� �������� �ʾ� �뿩 ó���� �� �����ϴ�." << endl;
        }
    }

    // å �ݳ� �޼���
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
                cout << endl << author << " ������ " << title << " å�� �ݳ� �Ǿ����ϴ�. ���� ���� " << it->second << "�� �Դϴ�." << endl;
            }
            else
            {
                cout << endl << author << " ������ " << title << " å�� ��� 3������ �̹� ���� �� �ֽ��ϴ�. �ݳ� ó���� �� �����ϴ�." << endl;
            }
        }
        else
        {
            cout << title << "\n å�� ��Ͽ� �������� �ʾ� �ݳ��� �� �����ϴ�." << endl;
        }
    }
};

class BookManager 
{
private:
    vector<Book> books; // å ��� ����
    BorrowManager borrowManager; // å �뿩 Ŭ���� ����
public:
    // å �߰� �޼���
    void addBook(const string& title, const string& author)
    {
        books.push_back(Book(title, author));
        borrowManager.initializeStock(Book(title, author));
        cout << "\nå�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // ��� å ��� �޼���
    void displayAllBooks() const
    {
        if (books.empty())
        {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++)
        {
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // å�� �����̳� ���ڷ� �˻� �޼���
    // å�� �ִ��� �˻��� ����ϰ� �ش� å�� ��� ����մϴ�.
    void searchByTitleOrAuthor(const string& search)
    {
        for (Book book : books)
        {
            if (book.title == search || book.author == search)
            {
                cout << endl << book.author << " ������ " << book.title << " å�� �ֽ��ϴ�." << endl;
                borrowManager.displayStock(book.title + ":" + book.author);
                return;
            }
        }
        cout << search << " å�� �����ϴ�." << endl;
    }

    // å�� �����̳� ���ڸ� ��� ���� key�� ��ȯ �޼���
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

    // �뿩���� Ŭ������ å �뿩 �޼��� ȣ��
    // BorrowManager Ŭ������ ����� �����մϴ�.
    void borrowBook(const string& key)
    {
        string searchKey = MakeSearchKey(key);
        if (!searchKey.empty())
        {
            borrowManager.borrowBook(searchKey);
        }
    }

    // �뿩���� Ŭ������ å �ݳ� �޼��� ȣ��
    // BorrowManager Ŭ������ ����� �����մϴ�.
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

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å �˻�" << endl;
        cout << "4. å �뿩" << endl;
        cout << "5. å �ݳ�" << endl;
        cout << "6. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����

        while (true)
        {
            cin >> choice;

            if (cin.fail() || !(1 <= choice && choice <= 6))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
                continue;
            }
            break;
        }

        if (choice == 1)
        {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
        }
        else if (choice == 2)
        {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3�� ����: å �˻� �� �뿩 ���� ���� ���
            // �Է��� å�� �뿩 ���� ���ο� ���� ��� Ȯ���� ����մϴ�.
            cout << "\nå�� �����̳� ���ڷ� �˻��ϼ���: ";

            string search;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, search);
            manager.searchByTitleOrAuthor(search);
        }
        else if (choice == 4)
        {
            // 4�� ����: å �뿩
            // ����ڰ� �Է��� å�� �뿩 ó���ϰ�, ���� ��� ����մϴ�.

            cout << "\n�뿩�Ͻ� å�� �����̳� ���ڸ� �Է��ϼ���: ";

            string input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);
            manager.borrowBook(input);
        }
        else if (choice == 5)
        {
            // 5�� ����: å �ݳ�
            // ����ڰ� �Է��� å�� �ݳ� ó���ϰ�, ���� ��� ����մϴ�.
            cout << "\n�ݳ��Ͻ� å�� �����̳� ���ڸ� �Է��ϼ���: ";

            string input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);
            manager.returnBook(input);
        }
        else if (choice == 6)
        {
            // 6�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else
        {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}