#include <iostream>
#include <memory>
using namespace std;
template <typename T>
class ownUniqPtr {
    public: 

        ownUniqPtr(ownUniqPtr&)  = delete;
        ownUniqPtr& operator=(ownUniqPtr&) = delete; 

         // Constructor
        explicit ownUniqPtr(T* ptr = nullptr) : _ptr(ptr) {}

         // Destructor
         ~ownUniqPtr() {
                cout<<"destructor called"<<endl;
                delete _ptr;
            }

        // Move constructor
    ownUniqPtr(ownUniqPtr&& other) noexcept {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    // Move assignment operator
    ownUniqPtr& operator=(ownUniqPtr&& other) noexcept {
        if (this != &other) {
            delete _ptr;
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }

     T& operator*() const {
        return *_ptr;
    }

    private:
        T* _ptr;

};

int main()
{
    float var =30.5;
    //unique_ptr<int> ptr(new int(var));
    //unique_ptr<int> ptr1= make_unique<int>(var);

    ownUniqPtr<float> ptr(new float(var));
    // ownUniqPtr ptr2 = ptr; // error assignment
    //ownUniqPtr ptr3(ptr); //error copy constructor

    ownUniqPtr<float> ptr4 = move(ptr);
    // if(*ptr == nullptr)
    //     cout<<"success"<<endl;
    cout<<"value::"<< *ptr4<<endl;


}
