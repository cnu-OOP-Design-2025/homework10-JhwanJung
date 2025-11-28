#include "MyVector.h"
#include <stdexcept>

template<typename T>
void MyVector<T>::push_back(const T& val) {
    if (length == cap) {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];
        for (size_t i = 0; i < length; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }
    data[length++] = val;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length > 0) {
        --length;
    }
}

template<typename T>
size_t MyVector<T>::size() const {
    return length;
}

template<typename T>
T& MyVector<T>::operator[](int i) {
    return data[static_cast<size_t>(i)];
}

template<typename T>
bool MyVector<T>::operator==(const MyVector<T>& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector<T>& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector<T>& other) const {
    size_t n = (length < other.length) ? length : other.length;
    for (size_t i = 0; i < n; ++i) {
        if (data[i] < other.data[i]) return true;
        if (data[i] > other.data[i]) return false;
    }
    return length < other.length;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector<T>& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector<T>& other) const {
    return !(other < *this);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector<T>& other) const {
    return !(*this < other);
}

// Iterator 구현
template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    return Iterator(ptr + n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    return Iterator(ptr - n);
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    return static_cast<int>(ptr - other.ptr);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(data + length);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    int idx = pos - begin();
    if (idx < 0) idx = 0;
    if (static_cast<size_t>(idx) > length) idx = static_cast<int>(length);
    size_t index = static_cast<size_t>(idx);

    if (length == cap) {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];
        for (size_t i = 0; i < index; ++i) {
            newData[i] = data[i];
        }
        newData[index] = value;
        for (size_t i = index; i < length; ++i) {
            newData[i + 1] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    } else {
        for (size_t i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
    }

    ++length;
    return Iterator(data + index);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    int idx = pos - begin();
    if (idx < 0 || static_cast<size_t>(idx) >= length) {
        return end();
    }
    size_t index = static_cast<size_t>(idx);
    for (size_t i = index; i + 1 < length; ++i) {
        data[i] = data[i + 1];
    }
    --length;
    return Iterator(data + index);
}

template<typename T>
void MyVector<T>::clear() {
    length = 0;
}

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >= length) {
        throw std::out_of_range("MyVector::at");
    }
    return data[i];
}

template<typename T>
T& MyVector<T>::front() {
    return data[0];
}

template<typename T>
T& MyVector<T>::back() {
    return data[length - 1];
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return cap;
}

template<typename T>
bool MyVector<T>::empty() const {
    return length == 0;
}

template class MyVector<int>;
