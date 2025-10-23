// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <algorithm>
#include <cassert> // assert()
#include <cstddef>
#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <stdexcept>
#include <utility>

template <typename T> class ArrayList {
    T* tab;
    std::size_t msize; // najwieksza mozliwa liczba elementow
    std::size_t last;  // pierwsza wolna pozycja

    public:
    ArrayList(std::size_t s = 10) : msize(s), last(0) {
        assert(s > 0);
        tab = new T[s];
        assert(tab != nullptr);
    } // default constructor

    ~ArrayList() { delete[] tab; } // destruktor

    ArrayList(const ArrayList& other) {
        this->msize = other.msize;
        this->last = other.last;
        this->tab = new T[msize];
        // Copy elements from other
        if (other.tab != nullptr) {
            std::copy(other.tab, other.tab + other.last, this->tab);
        } else {
            // Or we could ignore this and just leave our list empty
            this->last = 0;
            throw std::invalid_argument("Copied ArrayList has nullptr");
        }
    } // copy constructor
    // usage:   ArrayList<int> list2(list1);

    ArrayList(ArrayList&& other) {
        this->msize = other.msize;
        this->last = other.last;
        this->tab = other.tab;
        other.tab = nullptr;
        other.last = 0;
        other.msize = 0;
    } // move constructor NIEOBOWIAZKOWE
    // usage:   ArrayList<int> list2(std::move(list1));

    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            // We have to realocate space to fit other data
            if (this->msize < other.last) {
                delete[] this->tab;
                // New alloc with size of other tab
                this->tab = new T[other.msize];
                this->msize = other.msize;
            }
            std::copy(other.tab, other.tab + other.last, this->tab);
            this->last = other.last;
        }
        return *this;

    } // copy assignment operator, return *this
    // usage:   list2 = list1;

    ArrayList& operator=(ArrayList&& other) {
        if (this != &other) {
            this->msize = other.msize;
            this->last = other.last;
            this->tab = other.tab;
            other.tab = nullptr;
            other.last = 0;
            other.msize = 0;
        }
        return *this;
    } // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const {
        return last == 0;
    } // checks if the container has no elements

    bool full() const {
        return last == msize;
    } // checks if the container is full

    std::size_t size() const { return last; } // liczba elementow na liscie

    std::size_t max_size() const {
        return msize;
    } // najwieksza mozliwa liczba elementow

    void push_front(const T& item) {
        if (this->last < this->msize) {
            std::copy_backward(this->tab, this->tab + this->last,
                               this->tab + this->last + 1);
            this->tab[0] = item;
        } else {
            // TODO resize or throw error
        }
    } // dodanie na poczatek

    void push_front(T&& item) {
        if (this->last < this->msize) {
            std::copy_backward(this->tab, this->tab + this->last,
                               this->tab + this->last + 1);
            this->tab[0] = std::move(item);
        } else {
            // TODO resize or throw error
        }
    } // dodanie na poczatek NIEOBOWIAZKOWE

    void push_back(const T& item) {
        if (this->last < msize) {
            this->tab[this->last] = item;
            this->last += 1;
        } else {
            // TODO resize or throw exception out of bounds
            throw std::out_of_range("Not enough capacity");
        }
    } // dodanie na koniec

    void push_back(T&& item) {
        // std::cout << "MOVE OPERATOR" << std::endl;
        if (this->last < msize) {
            this->tab[this->last] = std::move(item);
            this->last += 1;
        } else {
            // TODO resize or throw exception out of bounds
            throw std::out_of_range("Not enough capacity");
        }
    } // dodanie na koniec NIEOBOWIAZKOWE

    T& front() {
        if (this->empty()) {
            throw std::out_of_range("Empty list");
        }
        return this->tab[0];
    } // zwraca poczatek, nie usuwa, error dla pustej listy

    T& back() {
        if (this->empty()) {
            throw std::out_of_range("Empty list");
        }
        return this->tab[last - 1];
    } // zwraca koniec, nie usuwa, error dla pustej listy

    void pop_front() {
        if (last == 0) {
            throw std::out_of_range("Popping empty list");
        }
        std::copy(this->tab + 1, this->tab + last, this->tab);
        this->last -= 1;
    } // usuwa poczatek, error dla pustej listy

    void pop_back() {
        if (last == 0) {
            throw std::out_of_range("Popping empty list");
        }
        this->last -= 1;
    } // usuwa koniec, error dla pustej listy

    void clear() {
        // Można wyzerować istniejące elementy jeśli dane były by wrażliwe ale w
        // większości przypadków koszty tego nie są uzasadnione
        this->last = 0;
    } // czyszczenie listy z elementow

    void display() {
        std::cout << this << std::endl;
    } // lepiej zdefiniowac operator<<

    void reverse() {
        auto len = this->size();
        for (std::size_t i = 0; i < len / 2; i++) {
            std::swap(this->tab[i], this->tab[this->size() - 1 - i]);
        }
    } // odwracanie kolejnosci

    void sort() {
        std::sort(this->tab, this->tab + this->last);
    } // sortowanie listy

    void
    merge(ArrayList& other); //  merges two sorted lists into one NIEOBOWIAZKOWE

    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](std::size_t pos) {
        if (pos < this->msize) {
            return this->tab[pos];
        }
        throw std::out_of_range("Invalid list position");
    } // podstawienie L[pos]=item, odczyt L[pos]

    const T& operator[](std::size_t pos) const {
        if (pos < this->msize) {
            return this->tab[pos];
        }
        throw std::out_of_range("Invalid list position");
    } // dostep do obiektu const

    void erase(std::size_t pos) {
        // erase only if pos in tab
        if (pos < last) {
            std::copy(this->tab + pos + 1, this->tab + this->last,
                      this->tab + pos);
            this->last -= 1;
        }
    } // usuniecie elementu na pozycji pos

    int index(const T& item) {
        for (std::size_t i = 0; i < this->last; i++) {
            if (this->tab[i] == item) {
                return i;
            }
        }
        return -1;
    } // jaki index na liscie (-1 gdy nie ma)

    void insert(std::size_t pos, const T& item) {
        if (pos == 0) {
            this->push_front(item);
        } else if (pos == this->size()) {
            this->push_back(item);
        } else {
            if (pos > this->last) {
                throw std::out_of_range("Inserion out of bounds");
            } else if (this->last == this->msize) {
                // TODO throw exception or resize
                throw std::out_of_range("Not enought capcity to insert");
            } else {
                std::copy_backward(this->tab + pos, this->tab + this->last,
                                   this->tab + this->last + 1);
                this->tab[pos] = item;
            }
        }
    } // inserts item before pos

    void insert(std::size_t pos, T&& item) {
        if (pos == 0) {
            this->push_front(item);
        } else if (pos == this->size()) {
            this->push_back(item);
        } else {
            if (pos > this->last) {
                throw std::out_of_range("Inserion out of bounds");
            } else if (this->last == this->msize) {
                // TODO throw exception or resize
                throw std::out_of_range("Not enought capcity to insert");
            } else {
                std::copy_backward(this->tab + pos, this->tab + this->last,
                                   this->tab + this->last + 1);
                this->tab[pos] = std::move(item);
            }
        }
    } // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    bool operator==(const ArrayList<T>& rhs) const {
        // If lists have different element count they cant be equal
        if (this->last != rhs.last) {
            return false;
        }
        for (std::size_t i = 0; i < this->last; i++) {
            if (this->tab[i] != rhs.tab[i]) {
                return false;
            }
        }
        return true;
    } // used for assertions if lists are equal

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (std::size_t i = 0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";                 // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
