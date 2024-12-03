#include <iostream>

template <typename T>
class MySharedPtr {
private:
    T* ptr;              // Pointer to the managed object
    int* ref_count;      // Pointer to the reference count

public:
    // Constructor
    explicit MySharedPtr(T* p = nullptr) 
        : ptr(p), ref_count(new int(1)) {
        if (ptr) {
            std::cout << "Resource acquired.\n";
        }
    }

    // Copy Constructor
    MySharedPtr(const MySharedPtr& other) 
        : ptr(other.ptr), ref_count(other.ref_count) {
        if (ptr) {
            ++(*ref_count); // Increment the reference count
        }
    }

    // Move Constructor
    MySharedPtr(MySharedPtr&& other) noexcept 
        : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;         // Transfer ownership
        other.ref_count = nullptr;
    }

    // Destructor
    ~MySharedPtr() {
        release();
    }

    // Assignment Operator (Copy)
    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();               // Release current ownership
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ptr) {
                ++(*ref_count);      // Increment the reference count
            }
        }
        return *this;
    }

    // Assignment Operator (Move)
    MySharedPtr& operator=(MySharedPtr&& other) noexcept {
        if (this != &other) {
            release();               // Release current ownership
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;     // Transfer ownership
            other.ref_count = nullptr;
        }
        return *this;
    }

    // Dereference operator
    T& operator*() const { return *ptr; }

    // Member access operator
    T* operator->() const { return ptr; }

    // Get the current reference count
    int use_count() const {
        return (ref_count ? *ref_count : 0);
    }

private:
    // Release the current ownership
    void release() {
        if (ptr && ref_count) {
            --(*ref_count);          // Decrement the reference count
            if (*ref_count == 0) {   // If no more references
                std::cout << "Resource released.\n";
                delete ptr;          // Delete the managed object
                delete ref_count;    // Delete the reference count
            }
        }
        ptr = nullptr;
        ref_count = nullptr;
    }
};

int main() {
    // Create a shared pointer
    MySharedPtr<int> sp1(new int(42));
    std::cout << "sp1 use_count: " << sp1.use_count() << '\n';

    {
        MySharedPtr<int> sp2 = sp1; // Copy constructor
        std::cout << "sp2 use_count: " << sp2.use_count() << '\n';

        MySharedPtr<int> sp3;
        sp3 = sp2; // Copy assignment
        std::cout << "sp3 use_count: " << sp3.use_count() << '\n';

        // sp2 and sp3 go out of scope here
    }

    std::cout << "sp1 use_count after sp2/sp3 destroyed: " << sp1.use_count() << '\n';

    // sp1 goes out of scope here, releasing the resource
    return 0;
}
