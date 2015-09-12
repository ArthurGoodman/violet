#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

class Vector {
    static const int InitialCapacity = 128;

    int _size, _capacity;
    byte *_data;

public:
    Vector();
    Vector(const Vector &v);
    Vector(const vector<byte> &v);

    ~Vector();

    byte *allocate(int count);
    bool free(int count);
    void release();

    bool enoughSpace(int count) const;

    byte *data() const;
    int size() const;
    int capacity() const;
};

#endif // VECTOR_H
