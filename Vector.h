#ifndef GRAPHS_3TH_PROJECT_VECTOR_H
#define GRAPHS_3TH_PROJECT_VECTOR_H

class Vector {
private:
    int size;
    int capacity;
    int *array;
public:
    Vector();

    Vector(const Vector &other);

    Vector(Vector &&other);

    int get(int i);

    void set(int i, int v);

    void push_back(int v);

    void pop_back();

    int Size() const;

    Vector &operator=(const Vector &other);

    Vector &operator=(Vector &&other);

    ~Vector();
};

#endif //GRAPHS_3TH_PROJECT_VECTOR_H