#include <iostream>

class A {
public:
    // ...

    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }

    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};


template<typename T>
class MyAlloc {
public:
    MyAlloc() {}
    ~MyAlloc() {}

    void* allocate(std::size_t n) { tmp = new T; return tmp; }

    void deallocate(void* p, std::size_t n) { delete tmp; }
private:
    T* tmp;
};


template <class T, class E = T>
struct MyAllocator {
    using value_type = T;

    using Traits = std::allocator_traits<MyAllocator<T, E>>;

    MyAllocator() : my_alloc(new MyAlloc<E>()) {}

    MyAllocator(MyAlloc<E>& my_alloc) : my_alloc(&my_alloc) {}

    template<class U, class M = U> 
    MyAllocator(const MyAllocator<U, M>& other) : my_alloc(other.my_alloc) {}

    T* allocate(std::size_t n) { return (T*)my_alloc->allocate(n); }

    void deallocate(T* p, std::size_t n) { my_alloc->deallocate(p, n); }

    MyAlloc<E>* my_alloc;
};


int main()
{
    MyAllocator<A> allocator;
    // auto sp = std::make_shared<A>();
    auto sp = std::allocate_shared<A> (allocator);
    return 0;
}
