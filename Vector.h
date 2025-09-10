#ifndef VECTOR_H
#define VECTOR_H


template<typename T>
class Vector {
private:
    T* arr;
    int capacity;
    int length;

private:
    void resizeInternal(int newCap) {
        T* newArr = new T[newCap];
        for(int i = 0; i < length; i++){
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

public:
    Vector(){
        arr = nullptr;
        capacity = 0;
        length =0;
    }

    ~Vector() {
        delete[] arr;
    }

    // Copy constructor
    Vector(const Vector &other){
        arr = nullptr;
        capacity = 0;
        length =0;
        if (other.capacity > 0) {
            arr = new T[other.capacity];
            capacity = other.capacity;
            length = other.length;
            for (int i = 0; i < length; i++) {
                arr[i] = other.arr[i];
            }
        }
    }

    // Assignment operator
    Vector& operator=(const Vector &other) {
        if (this == &other) return *this;
        delete[] arr;
        capacity = other.capacity;
        length = other.length;
        arr = new T[capacity];
        for(int i = 0; i < length; i++){
            arr[i] = other.arr[i];
        }
        return *this;
    }

    int size() const {
        return length;
    }

    bool empty() const {
        return length == 0;
    }

    void resize(int newSize) {
        if (newSize > capacity) {
            resizeInternal(newSize);
        }
        if (newSize > length) {
            // Initialize new elements with default constructor
            for (int i = length; i < newSize; i++) {
                arr[i] = T();
            }
        }
        length = newSize;
    }

    //Εισαγωγή στοιχείου ως το τέλευταιο στοιχείο του πίνακα
    void push(const T& value) {
        if (length >= capacity) {
            int newCap = (capacity == 0) ? 1 : capacity * 2;
            resizeInternal(newCap);
        }
        arr[length++] = value;
    }

    //Διαγραφή του τέλευταιου στοιχείου του πίνακα
    bool pop() {
        if (length > 0) {
            length--;
            if (length < (capacity/2) && capacity > 1) {
                int newCap = capacity / 2;
                resizeInternal(newCap);
            }
            return true;
        }
        return false;
    }

    //Ορισμός του τελεστή []
    T& operator[](int index) {
        return arr[index];
    }

    //Ορισμός του τελεστή [] για const συναρτήσεις
    const T& operator[](int index) const {
        return arr[index];
    }

    void swap(int a,int b){
        T c = arr[a];
        arr[a] = arr[b];
        arr[b] = c;
    }

    void clear() {
        delete[] arr;
        arr = nullptr;
        capacity = 0;
        length = 0;
    }

};

#endif