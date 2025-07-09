#include <iostream>
using namespace std;

// Node definition
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Doubly Circular Linked List class
class DoublyCircularLinkedList {
private:
    Node* head;

public:
    // Constructor
    DoublyCircularLinkedList() {
        head = nullptr;
    }

    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node();
        newNode->data = value;

        if (head == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        } else {
            Node* tail = head->prev;

            tail->next = newNode;
            newNode->prev = tail;

            newNode->next = head;
            head->prev = newNode;
        }
    }

    // Insert at beginning
    void insertAtBeginning(int value) {
        insertAtEnd(value);      // Insert at end first
        head = head->prev;       // Move head to the new node
    }

    // Delete by value
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;

        do {
            if (current->data == value) {
                if (current->next == current) {
                    // Only one node
                    delete current;
                    head = nullptr;
                } else {
                    Node* prevNode = current->prev;
                    Node* nextNode = current->next;

                    prevNode->next = nextNode;
                    nextNode->prev = prevNode;

                    if (current == head)
                        head = nextNode;

                    delete current;
                }
                return;
            }
            current = current->next;
        } while (current != head);

        cout << "Value not found." << endl;
    }

    // Search for value
    bool search(int value) {
        if (head == nullptr)
            return false;

        Node* current = head;

        do {
            if (current->data == value)
                return true;
            current = current->next;
        } while (current != head);

        return false;
    }

    // Display forward
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;
        do {
            cout << current->data << " <-> ";
            current = current->next;
        } while (current != head);

        cout << "(Back to Head)" << endl;
    }

    // Display backward
    void displayBackward() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* tail = head->prev;
        Node* current = tail;

        do {
            cout << current->data << " <-> ";
            current = current->prev;
        } while (current != tail);

        cout << "(Back to Tail)" << endl;
    }

    // Destructor
    ~DoublyCircularLinkedList() {
        if (head == nullptr)
            return;

        Node* current = head->next;
        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
    }
};

// Main function to test
int main() {
    DoublyCircularLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtBeginning(5);

    cout << "Forward: ";
    list.displayForward();

    cout << "Backward: ";
    list.displayBackward();

    list.deleteByValue(20);
    list.displayForward();

    if (list.search(5))
        cout << "5 found in the list." << endl;
    else
        cout << "5 not found." << endl;

    return 0;
}
