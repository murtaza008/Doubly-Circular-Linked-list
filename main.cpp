#include <iostream>
using namespace std;

// Node structure for the doubly circular linked list
struct Node {
    int data;
    Node* prev;
    Node* next;

    // Constructor to create a new node
    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Doubly Circular Linked List class
class DoublyCircularLinkedList {
private:
    Node* head;

public:
    // Constructor to initialize the head of the list
    DoublyCircularLinkedList() {
        head = nullptr;
    }

    // Function to add a node at the end of the list
    void append(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;  // Points to itself
            newNode->prev = head;  // Points to itself
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
            newNode->next = head;
            head->prev = newNode;  // Connect the last node back to head
        }
    }

    // Function to delete a node by value
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;

        // If the node to delete is the head
        if (head->data == value) {
            if (head->next == head) {  // Only one node in the list
                delete head;
                head = nullptr;
            } else {
                Node* last = head->prev;
                head = head->next;
                head->prev = last;
                last->next = head;
                delete temp;
            }
            return;
        }

        // Traverse the list to find the node to delete
        do {
            if (temp->data == value) {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Value not found." << endl;
    }

    // Function to display the list forward
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(head)" << endl;  // Indicating circular nature
    }

    // Function to display the list backward
    void displayBackward() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head->prev;
        do {
            cout << temp->data << " -> ";
            temp = temp->prev;
        } while (temp != head->prev);
        cout << "(head)" << endl;  // Indicating circular nature
    }

    // Function to search for a value in the list
    bool search(int value) {
        if (head == nullptr) {
            return false;
        }
        Node* temp = head;
        do {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    // Destructor to clean up memory
    ~DoublyCircularLinkedList() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        do {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        head = nullptr;
    }
};

// Main function to test the list
int main() {
    DoublyCircularLinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    cout << "List displayed forward: ";
    list.displayForward();

    cout << "List displayed backward: ";
    list.displayBackward();

    cout << "Searching for 20: " << (list.search(20) ? "Found" : "Not Found") << endl;

    list.deleteByValue(20);
    cout << "List after deleting 20 (forward): ";
    list.displayForward();

    cout << "List after deleting 20 (backward): ";
    list.displayBackward();

    return 0;
}
