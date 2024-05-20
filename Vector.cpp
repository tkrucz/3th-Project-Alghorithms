#include "Vector.h"
#include "iostream"

using namespace std;

// Default constructor
Vector::Vector() : size(0), array(nullptr), capacity(1) {
    array = new int[capacity];
};

// Copy constructor
Vector::Vector(const Vector &other) :
        size(other.size), array(other.array) {
}

// Move constructor
Vector::Vector(Vector &&other) :
        size(other.size), array(other.array) {
    other.size = 0;
    other.array = nullptr;
}

// Get the value at index i
double Vector::get(int i) {
    return array[i];
}

// Set the value v at index i
void Vector::set(int i, int v) {
    array[i] = v;
}

// Set the value at the end of vector
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

// Delete the value at the end of the vector
void Vector::pop_back() {
    size -= 1;
    array[size] = 0;
}

// Get the size of the vector
int Vector::Size() const {
    return size;
}

// Copy assignment operator
Vector &Vector::operator=(const Vector &other) {
    int *tmp = new int[other.size];
    for (int i = 0; i < other.size; i++)
        tmp[i] = other.array[i];
    delete array;
    size = other.size;
    array = tmp;
    return *this;
}

// Move assignment operator
Vector &Vector::operator=(Vector &&other) {
    delete[] array;
    array = other.array;
    size = other.size;
    other.size = 0;
    other.array = nullptr;
    return *this;
}

// Destructor
Vector::~Vector() {
    if (array != nullptr)
        delete[] array;
}