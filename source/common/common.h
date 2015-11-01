#ifndef COMMON_H
#define COMMON_H

#include <list>
#include <vector>
using namespace std;

typedef unsigned char byte;

template <class A, class B>
list<B> &operator<<(list<B> &l, const A &e) {
    l.push_back((B)e);
    return l;
}

template <class A, class B>
list<B> *operator<<(list<B> *l, const A &e) {
    l->push_back((B)e);
    return l;
}

template <class A, class B>
vector<B> &operator<<(vector<B> &v, const A &e) {
    v.push_back((B)e);
    return v;
}

template <class A, class B>
vector<B> *operator<<(vector<B> *v, const A &e) {
    v->push_back((B)e);
    return v;
}

#endif // COMMON_H
