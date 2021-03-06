#include <iostream>
#include <memory>

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


template <class T, class E = T>
struct MyAllocator {
    using value_type = T;

    using Traits = std::allocator_traits<MyAllocator<T, E>>;

    MyAllocator() {}

    MyAllocator(MyAllocator<E>& my_alloc){}

    template<class U, class M = U>
    MyAllocator(const MyAllocator<U, M>& other) {}

    T* allocate(std::size_t n) {
        return reinterpret_cast<T*>(E:: operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        E::operator delete (reinterpret_cast<E*>(p), n * sizeof(T));
    }
};


int main()
{
    MyAllocator<A> allocator;
    // auto sp = std::make_shared<A>();
    auto sp = std::allocate_shared<A> (allocator);

    return 0;
}
