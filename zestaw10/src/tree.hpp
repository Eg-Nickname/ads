#include <cassert>
#include <cstdlib> // std::rand(), RAND_MAX, std::srand()
#include <ctime>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>

// Szablon dla węzła drzewa binarnego i drzewa BST.
template <typename T>
struct BSTNode {
    // the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    // BSTNode *parent;   // używane w pewnych zastosowaniach
    //  kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {
        delete left;
        delete right;
    } // destruktor rekurencyjny
    // UWAGA Jeżeli w BSTNode będzie domyślny destruktor postaci
    // ~BSTNode() = default; lub
    // ~BSTNode() {}
    // to wtedy destruktor drzewa i metoda clear() muszą zwolnić pamięć
    // wszystkich węzłów.
};

// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class BinarySearchTree {
    BSTNode<T>* root;

    public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    BinarySearchTree(BSTNode<T>* root)
        : root(root) {} // konstruktor tworzacy drzewo z podanego węzła
    ~BinarySearchTree() { delete root; } // trzeba wyczyścić
    void clear() {
        delete root;
        root = nullptr;
    }
    bool empty() const { return root == nullptr; }
    T& top() {
        assert(root != nullptr);
        return root->value;
    } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    void remove(const T& item); // usuwanie przez złączanie
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T* iter_search(const T& item) const { // wg libavl
        for (auto node = root; node != nullptr;) {
            if (item == node->value) {
                return &(node->value);
            } else if (item < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }
    T* find_min() const;
    T* find_max() const;
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder();   // trudne
    void iter_postorder(); // trudne
    void bfs();            // przejście poziomami (wszerz)
    void display() { display(root, 0); }
    bool check_bst() {
        return this->check_bst(this->root, std::numeric_limits<T>::lowest(),
                               std::numeric_limits<T>::max());
    }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T>* insert(BSTNode<T>* node, const T& item); // zwraca nowy korzeń
    BSTNode<T>* search(BSTNode<T>* node, const T& item) const; // zwraca węzeł
    BSTNode<T>* remove(BSTNode<T>* node); // zwraca nowy korzeń poddrzewa
    void preorder(BSTNode<T>* node);
    void inorder(BSTNode<T>* node);
    void postorder(BSTNode<T>* node);
    void display(BSTNode<T>* node, int level);
    virtual void visit(BSTNode<T>* node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }

    private:
    bool check_bst(BSTNode<T>* node, T min, T max);
};

// Druga wersja display() z rysowaniem krawędzi drzewa (Maksymilian Brzozowski).
template <typename T>
void BinarySearchTree<T>::display(BSTNode<T>* node, int level) {
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::insert(BSTNode<T>* node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}
template <typename T>
void BinarySearchTree<T>::bfs() {
    if (root == nullptr)
        return;
    std::queue<BSTNode<T>*> Q; // wskaźniki do wezłów
    BSTNode<T>* node = root;
    Q.push(node);
    while (!Q.empty()) {
        node = Q.front(); // podglądamy
        Q.pop();          // usuwamy z kolejki
        visit(node);      // tu jest właściwe przetworzenie węzła
        if (node->left != nullptr)
            Q.push(node->left); // pierwsze wyjdzie lewe, potem prawe
        if (node->right != nullptr)
            Q.push(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::inorder(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void BinarySearchTree<T>::preorder(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void BinarySearchTree<T>::postorder(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

template <typename T>
void BinarySearchTree<T>::iter_preorder() {
    if (root == nullptr)
        return;
    std::stack<BSTNode<T>*> S; // wskaźniki do węzłów
    BSTNode<T>* node = root;
    S.push(node);
    while (!S.empty()) {
        node = S.top();             // podglądamy
        S.pop();                    // usuwamy ze stosu
        visit(node);                // tu jest właściwe przetworzenie węzła
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::search(BSTNode<T>* node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

// Check if correct bst
template <typename T>
bool BinarySearchTree<T>::check_bst(BSTNode<T>* node, T min, T max) {
    if (node == nullptr) {
        return true;
    }
    if (node->value < min || node->value > max) {
        return false;
    }
    return check_bst(node->left, min, node->value) &&
           check_bst(node->right, node->value, max);
}
