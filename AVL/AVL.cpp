#include <iostream>
using namespace std;

// Узел АВЛ-дерева
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

// Функция для получения высоты узла
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Функция для получения баланса узла
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Функция для обновления высоты узла
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Правый поворот
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левый поворот
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Вставка узла
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Дубликаты не допускаются
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    // Левый левый случай
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Правый правый случай
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Левый правый случай
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Правый левый случай
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Функция для нахождения узла с минимальным значением
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Удаление узла
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp; // Копируем содержимое
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    updateHeight(root);

    int balance = getBalance(root);

    // Левый левый случай
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Левый правый случай
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Правый правый случай
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Правый левый случай
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Функция для поиска узла
Node* search(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    
    return search(root->right, key);
}

// Функция для вывода дерева в порядке возрастания
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Вставка узлов
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Порядок обхода (inorder): ";
    inorder(root);
    cout << endl;

    // Удаление узлов
    root = deleteNode(root, 30);
    cout << "После удаления 30, порядок обхода (inorder): ";
    inorder(root);
    cout << endl;

    // Поиск узла
    Node* result = search(root, 20);
    if (result) {
        cout << "Узел с ключом 20 найден." << endl;
    } else {
        cout << "Узел с ключом 20 не найден." << endl;
    }

    return 0;
}
