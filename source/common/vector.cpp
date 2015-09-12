#include "vector.h"

#include <cstdlib>
#include <memory>
#include <cmath>

Vector::Vector()
    : _size(0), _capacity(0), _data(0) {
}

Vector::Vector(const Vector &v)
    : _size(0), _capacity(0), _data(0) {
    allocate(v.size());
    memcpy(_data, v.data(), _size);
}

Vector::Vector(const vector<byte> &v)
    : _size(0), _capacity(0), _data(0) {
    allocate(v.size());
    memcpy(_data, v.data(), _size);
}

Vector::~Vector() {
    release();
}

byte *Vector::allocate(int count) {
    if (count <= 0)
        return 0;

    if (!enoughSpace(count)) {
        int newCapacity = _capacity;

        if (!newCapacity)
            newCapacity = InitialCapacity;

        newCapacity *= pow(2, max(0.0, ceil(log2(double(_size + count) / newCapacity))));

        byte *newData = (byte *)realloc(_data, newCapacity);

        if (!newData)
            return 0;

        _capacity = newCapacity;
        _data = newData;
    }

    _size += count;

    return _data + _size - count;
}

bool Vector::free(int count) {
    if (count <= 0)
        return false;

    if (_size >= count)
        _size -= count;
    else
        _size = 0;

    return true;
}

void Vector::release() {
    if (_data)
        ::free(_data);

    _size = 0;
    _capacity = 0;
    _data = 0;
}

bool Vector::enoughSpace(int count) const {
    return _size + count <= _capacity;
}

byte *Vector::data() const {
    return _data;
}

int Vector::size() const {
    return _size;
}

int Vector::capacity() const {
    return _capacity;
}
