#include <iostream>
using namespace std;


struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};


TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}


bool search(TreeNode* root, int value) {
    if (root == nullptr) return false;
    if (value == root->value) return true;
    if (value < root->value) {
        return search(root->left, value);
    }
    return search(root->right, value);
}



void preOrder(TreeNode* root) {
    if (root) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}



void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
}



void postOrder(TreeNode* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->value << " ";
    }
}


int main() {
    TreeNode* root = nullptr;
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert an element\n";
        cout << "2. Search for an element\n";
        cout << "3. Pre-order Traversal\n";
        cout << "4. In-order Traversal\n";
        cout << "5. Post-order Traversal\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter the value to search: ";
                cin >> value;
                if (search(root, value)) {
                    cout << "Element found in the tree.\n";
                } else {
                    cout << "Element not found in the tree.\n";
                }
                break;
            case 3:
                cout << "Pre-order Traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case 4:
                cout << "In-order Traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 5:
                cout << "Post-order Traversal: ";
                postOrder(root);
                cout << endl;
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
