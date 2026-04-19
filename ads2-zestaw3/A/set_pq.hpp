#ifndef SET_PQ
#define SET_PQ

// #include <concepts>

#include "list_set.hpp"
#include <stdexcept>

template <typename T>
struct QueueElement {
    int32_t priority;
    T e;

    QueueElement(int32_t p, T e) : priority(p), e(e) {}

    auto operator<=>(const QueueElement<T>& qe) const {
        return this->priority <=> qe.priority;
    }

    bool operator==(const QueueElement<T>& qe) const {
        return priority == qe.priority && qe.e == this->e;
    }
};

class SetPqTests;

template <typename T, typename U>
class SetPq {
    ListSet<QueueElement<T>> ls;
    U priority_fn;
    friend SetPqTests;

    public:
    SetPq(U priority) : priority_fn(priority) {};

    void insert(T e) { ls.insert(QueueElement(priority_fn(e), e)); }
    size_t size() { return ls.size(); }
    T pop() {
        if (this->size() > 0) {
            auto ret = ls.inner_set.front();
            ls.inner_set.pop_front();
            return ret.e;
        } else {
            throw std::out_of_range("Pq is empty");
        }
    }
};

#endif