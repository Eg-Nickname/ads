#include <cassert>
#include <cstdlib> // std::rand(), RAND_MAX, std::srand()
#include <ctime>
#include <iostream>
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
class RandomBinaryTree {
    BSTNode<T>* root;

    public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyślny
    ~RandomBinaryTree() { delete root; }  // trzeba wyczyścić (rekurencyjnie)
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
    // void remove(const T& item); // na razie nie usuwamy elementów
    //  Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }

    T calc_total_rec() const;
    T calc_total_rec(BSTNode<T>* node) const;
    T calc_total_iter() const;

    // T* find_min() const;
    // T* find_max() const;
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    // void iter_inorder();   // trudne
    // void iter_postorder(); // trudne
    void bfs(); // przejście poziomami (wszerz)
    void display() { display(root, 0); }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T>* insert(BSTNode<T>* node, const T& item); // zwraca nowy korzeń
    BSTNode<T>* search(BSTNode<T>* node, const T& item) const;
    void preorder(BSTNode<T>* node);
    void inorder(BSTNode<T>* node);
    void postorder(BSTNode<T>* node);
    void display(BSTNode<T>* node, int level);
    virtual void visit(BSTNode<T>* node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

// Druga wersja display() z rysowaniem krawędzi drzewa (Maksymilian Brzozowski).
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T>* node, int level) {
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
BSTNode<T>* RandomBinaryTree<T>::insert(BSTNode<T>* node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    std::srand(
        std::time(nullptr)); // use current time as seed for random generator
    if (std::rand() % 2) {   // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}

template <typename T>
BSTNode<T>* RandomBinaryTree<T>::search(BSTNode<T>* node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    }
    T* ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr) {
        ptr = search(node->right, item);
    }
    return ptr;
}

template <typename T>
void RandomBinaryTree<T>::bfs() {
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
void RandomBinaryTree<T>::inorder(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::preorder(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::postorder(BSTNode<T>* node) {
    if (node == nullptr)
        return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

template <typename T>
void RandomBinaryTree<T>::iter_preorder() {
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
// ===============================
template <typename T>
T RandomBinaryTree<T>::calc_total_rec() const {
    return this->calc_total_rec(this->root);
}

template <typename T>
T RandomBinaryTree<T>::calc_total_rec(BSTNode<T>* node) const {
    if (node == nullptr)
        return T();
    return this->calc_total_rec(node->left) +
           this->calc_total_rec(node->right) + node->value;
}

template <typename T>
T RandomBinaryTree<T>::calc_total_iter() const {
    if (root == nullptr)
        return T();
    std::queue<BSTNode<T>*> Q; // wskaźniki do wezłów
    BSTNode<T>* node = root;
    Q.push(node);
    T sum = T{};
    while (!Q.empty()) {
        node = Q.front(); // podglądamy
        Q.pop();          // usuwamy z kolejki
        // calc sum
        sum += node->value;

        if (node->left != nullptr)
            Q.push(node->left); // pierwsze wyjdzie lewe, potem prawe
        if (node->right != nullptr)
            Q.push(node->right);
    }
    return sum;
}