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
class MyAllocStrategy {
public:
    MyAllocStrategy() {}
    ~MyAllocStrategy() {}

    void* allocate(std::size_t n) { return new T; }

    void deallocate(T* p, std::size_t n) { delete p; }
};


template <class T, class E = T>
struct MyAllocator {
    using value_type = T;

    using Traits = std::allocator_traits<MyAllocator<T, E>>;

    MyAllocator() : my_alloc(new MyAllocStrategy<E>()) {}

    MyAllocator(MyAllocStrategy<E>& my_alloc) : my_alloc(&my_alloc) {}

    template<class U, class M = U> 
    MyAllocator(const MyAllocator<U, M>& other) : my_alloc(other.my_alloc) {}

    T* allocate(std::size_t n) { 
        return reinterpret_cast<T*>(my_alloc->allocate(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) { 
        my_alloc->deallocate(reinterpret_cast<E*>(p), n);
    }

    MyAllocStrategy<E>* my_alloc;
};


int main()
{
    MyAllocator<A> allocator;
    // auto sp = std::make_shared<A>();
    auto sp = std::allocate_shared<A> (allocator);
    return 0;
}
