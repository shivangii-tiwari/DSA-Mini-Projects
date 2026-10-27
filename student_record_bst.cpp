
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Student {
    int id;
    string name;
    string department;
};

struct Node {
    Student data;
    Node* left;
    Node* right;

    Node(Student s) {
        data = s;
        left = nullptr;
        right = nullptr;
    }
};

class StudentBST {
private:
    Node* root;

    Node* insertNode(Node* node, Student s, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(s);
        }

        if (s.id < node->data.id) {
            node->left = insertNode(node->left, s, inserted);
        }
        else if (s.id > node->data.id) {
            node->right = insertNode(node->right, s, inserted);
        }
        else {
            inserted = false;
        }

        return node;
    }

    Node* searchNode(Node* node, int id, int& comparisons) {
        while (node != nullptr) {
            comparisons++;

            if (node->data.id == id)
                return node;

            if (id < node->data.id)
                node = node->left;
            else
                node = node->right;
        }

        return nullptr;
    }

    Node* minimumNode(Node* node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int id, bool& deleted) {
        if (node == nullptr)
            return nullptr;

        if (id < node->data.id) {
            node->left = deleteNode(node->left, id, deleted);
        }
        else if (id > node->data.id) {
            node->right = deleteNode(node->right, id, deleted);
        }
        else {
            deleted = true;

            // Case 1: Leaf node
            if (node->left == nullptr &&
                node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: One child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Node* successor = minimumNode(node->right);
            node->data = successor->data;

            bool ignored = false;
            node->right = deleteNode(
                node->right, successor->data.id, ignored
            );
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr) return;

        inorder(node->left);
        displayStudent(node->data);
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) return;

        displayStudent(node->data);
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) return;

        postorder(node->left);
        postorder(node->right);
        displayStudent(node->data);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    StudentBST() {
        root = nullptr;
    }

    ~StudentBST() {
        destroy(root);
    }

    static void displayStudent(Student s) {
        cout << "ID: " << s.id
             << " | Name: " << s.name
             << " | Department: " << s.department << '\n';
    }

    bool insert(Student s) {
        bool inserted = false;
        root = insertNode(root, s, inserted);
        return inserted;
    }

    void search(int id) {
        int comparisons = 0;
        Node* result = searchNode(root, id, comparisons);

        if (result != nullptr) {
            cout << "\nStudent found:\n";
            displayStudent(result->data);
        }
        else {
            cout << "\nStudent not found.\n";
        }

        cout << "Comparisons made: " << comparisons << '\n';
    }

    void remove(int id) {
        bool deleted = false;
        root = deleteNode(root, id, deleted);

        if (deleted)
            cout << "Student deleted successfully.\n";
        else
            cout << "Student ID not found.\n";
    }

    void showInorder() {
        cout << "\nInorder Traversal (Sorted IDs):\n";
        if (root == nullptr) cout << "Tree is empty.\n";
        else inorder(root);
    }

    void showPreorder() {
        cout << "\nPreorder Traversal:\n";
        if (root == nullptr) cout << "Tree is empty.\n";
        else preorder(root);
    }

    void showPostorder() {
        cout << "\nPostorder Traversal:\n";
        if (root == nullptr) cout << "Tree is empty.\n";
        else postorder(root);
    }

    void loadSampleRecords() {
        vector<Student> students = {
            {105, "Aarav Sharma", "CSE"},
            {102, "Diya Verma", "AIDS"},
            {108, "Kabir Singh", "ECE"},
            {101, "Anaya Gupta", "CSE"},
            {103, "Ishaan Kumar", "AIDS"},
            {107, "Meera Patel", "ME"},
            {110, "Rohan Das", "ECE"},
            {109, "Sara Khan", "CSE"},
            {104, "Vivaan Roy", "AIDS"},
            {106, "Zoya Ali", "ME"}
        };

        for (Student s : students)
            insert(s);
    }
};

int main() {
    StudentBST bst;
    bst.loadSampleRecords();

    cout << "10 sample student records loaded.\n";

    int choice;

    do {
        cout << "\n===== STUDENT RECORD BST =====\n";
        cout << "1. Insert Student\n";
        cout << "2. Search Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Preorder Traversal\n";
        cout << "6. Postorder Traversal\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            return 0;
        }

        switch (choice) {
            case 1: {
                Student s;

                cout << "Enter enrolment ID: ";
                if (!(cin >> s.id)) {
                    cout << "Invalid ID!\n";
                    return 0;
                }

                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );

                cout << "Enter student name: ";
                getline(cin, s.name);

                cout << "Enter department: ";
                getline(cin, s.department);

                if (s.name.empty() || s.department.empty()) {
                    cout << "Name and department cannot be empty.\n";
                }
                else if (bst.insert(s)) {
                    cout << "Student inserted successfully.\n";
                }
                else {
                    cout << "Duplicate enrolment ID. "
                         << "Record not inserted.\n";
                }

                break;
            }

            case 2: {
                int id;
                cout << "Enter enrolment ID to search: ";
                cin >> id;
                bst.search(id);
                break;
            }

            case 3: {
                int id;
                cout << "Enter enrolment ID to delete: ";
                cin >> id;
                bst.remove(id);
                break;
            }

            case 4:
                bst.showInorder();
                break;

            case 5:
                bst.showPreorder();
                break;

            case 6:
                bst.showPostorder();
                break;

            case 0:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
