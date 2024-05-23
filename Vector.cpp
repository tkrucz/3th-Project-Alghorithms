#include "Vector.h"
#include "iostream"

using namespace std;

Vector::Vector() : size(0), array(nullptr), capacity(1) {
    array = new int[capacity];
};

Vector::Vector(const Vector &other) :
        size(other.size), array(other.array) {
}

int Vector::get(int i) {
    return array[i];
}

void Vector::push_back(int v) {
    if (size == capacity) {
        capacity = capacity * 2;
        int *tmp = new int[capacity];
        for (int i = 0; i < size; i++)
            tmp[i] = array[i];
        delete[] array;
        array = tmp;
    }
    array[size] = v;
    size += 1;
}

int Vector::Size() const {
    return size;
}

Vector &Vector::operator=(const Vector &other) {
    int *tmp = new int[other.size];
    for (int i = 0; i < other.size; i++)
        tmp[i] = other.array[i];
    delete array;
    size = other.size;
    array = tmp;
    return *this;
}

Vector &Vector::operator=(Vector &&other) {
    delete[] array;
    array = other.array;
    size = other.size;
    other.size = 0;
    other.array = nullptr;
    return *this;
}

Vector::~Vector() {
    if (array != nullptr)
        delete[] array;
}