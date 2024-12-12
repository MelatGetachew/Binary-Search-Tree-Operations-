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

int treeHeight(TreeNode* root) {
    if (root == nullptr) return -1;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int findLevel(TreeNode* root, int value, int level = 1) {
    if (root == nullptr) return -1; 
    if (root->value == value) return level;

    if (value < root->value) {
        return findLevel(root->left, value, level + 1);
    } else {
        return findLevel(root->right, value, level + 1);
    }
}

TreeNode* findMin(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteByCopying(TreeNode* root, int value) {
    if (root == nullptr) return root;

    if (value < root->value) {
        root->left = deleteByCopying(root->left, value);
    } else if (value > root->value) {
        root->right = deleteByCopying(root->right, value);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            TreeNode* temp = findMin(root->right);
            root->value = temp->value;
            root->right = deleteByCopying(root->right, temp->value);
        }
    }
    return root;
}

TreeNode* deleteByMerging(TreeNode* root, int value) {
    if (root == nullptr) return root;

    if (value < root->value) {
        root->left = deleteByMerging(root->left, value);
    } else if (value > root->value) {
        root->right = deleteByMerging(root->right, value);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            TreeNode* temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }
            temp->right = root->right;
            TreeNode* newRoot = root->left;
            delete root;
            return newRoot;
        }
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

void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
}

void preOrder(TreeNode* root) {
    if (root) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
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
    TreeNode* tree1 = nullptr; // Tree for deletion by merging
    TreeNode* tree2 = nullptr; // Tree for deletion by copying
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert an element\n";
        cout << "2. Delete an element (By Copying)\n";
        cout << "3. Delete an element (By Merging)\n";
        cout << "4. Search for an element\n";
        cout << "5. In-order Traversal (Both Trees)\n";
        cout << "6. Pre-order Traversal (Both Trees)\n";
        cout << "7. Post-order Traversal (Both Trees)\n";
        cout << "8. Display Tree Height (Both Trees)\n";
        cout << "9. Display Level of a Node\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                tree1 = insert(tree1, value);
                tree2 = insert(tree2, value);
                break;
            case 2:
                cout << "Enter the value to delete (By Copying): ";
                cin >> value;
                tree2 = deleteByCopying(tree2, value);
                break;
            case 3:
                cout << "Enter the value to delete (By Merging): ";
                cin >> value;
                tree1 = deleteByMerging(tree1, value);
                break;
            case 4:
                cout << "Enter the value to search: ";
                cin >> value;
                if (search(tree1, value)) {
                    cout << "Element found in the tree.\n";
                } else {
                    cout << "Element not found in the tree.\n";
                }
                break;
            case 5:
                cout << "In-order Traversal of Tree 1 (Merging): ";
                inOrder(tree1);
                cout << "\nIn-order Traversal of Tree 2 (Copying): ";
                inOrder(tree2);
                cout << endl;
                break;
            case 6:
                cout << "Pre-order Traversal of Tree 1 (Merging): ";
                preOrder(tree1);
                cout << "\nPre-order Traversal of Tree 2 (Copying): ";
                preOrder(tree2);
                cout << endl;
                break;
            case 7:
                cout << "Post-order Traversal of Tree 1 (Merging): ";
                postOrder(tree1);
                cout << "\nPost-order Traversal of Tree 2 (Copying): ";
                postOrder(tree2);
                cout << endl;
                break;
            case 8:
                cout << "Height of Tree 1 (Merging): " << treeHeight(tree1) << endl;
                cout << "Height of Tree 2 (Copying): " << treeHeight(tree2) << endl;
                break;
            case 9:
                cout << "Enter the value to find its level: ";
                cin >> value;
                int level;
                level = findLevel(tree1, value);
                if (level == -1) {
                    cout << "Node not found in Tree 1.\n";
                } else {
                    cout << "Level of the node in Tree 1: " << level << endl;
                }

                level = findLevel(tree2, value);
                if (level == -1) {
                    cout << "Node not found in Tree 2.\n";
                } else {
                    cout << "Level of the node in Tree 2: " << level << endl;
                }
                break;
            case 10:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}