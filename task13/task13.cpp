#include <iostream>
#include <map>
#include <chrono>
#include <string>
#include <vector>


const uint64_t NUM_IT = 1000000;


// first example
void withoutHint(std::map<std::string, int>& m) {
    auto start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < NUM_IT; ++i) {
        std::string key = "some key " + std::to_string(i);
        m.insert(std::pair<std::string, int>(key, i % 10));
    }
    auto end = std::chrono::steady_clock::now();
    auto timeDiff = end - start;
    std::cout << "time without hint = " 
              << std::chrono::duration <double, std::milli> (timeDiff).count()
              << " ms" << std::endl;
}


void withHint(std::map<std::string, int>& m) {
    auto start = std::chrono::steady_clock::now();
    auto it = m.begin();
    for (uint64_t i = 0; i < NUM_IT; ++i) {
        std::string key = "some key " + std::to_string(i);
        it = m.insert(it, std::pair<std::string, int>(key, i % 10));
    }
    auto end = std::chrono::steady_clock::now();
    auto timeDiff = end - start;
    std::cout << "time with hint = " 
              << std::chrono::duration <double, std::milli> (timeDiff).count()
              << " ms" << std::endl;
}
// end first example


// second example
void init(std::map<int, int>& m) {
    for (uint64_t i = 0; i <= 2 * NUM_IT; i += 2) {
        m[i] = 2;
    }
}


void withoutHint2(std::map<int, int>& m) {
    auto start = std::chrono::steady_clock::now();
    for (uint64_t i = 1; i <= 2 * NUM_IT + 1; i += 2) {
        m.insert(std::pair<int, int>(i, i % 10));
    }
    auto end = std::chrono::steady_clock::now();
    auto timeDiff = end - start;
    std::cout << "time without hint = " 
              << std::chrono::duration <double, std::milli> (timeDiff).count()
              << " ms" << std::endl;
}


void withHint2(std::map<int, int>& m) {
    auto start = std::chrono::steady_clock::now();
    auto it = m.begin();
    for (uint64_t i = 1; i <= 2 * NUM_IT + 1; i += 2) {
        it = m.insert(++it, std::pair<int, int>(i, i % 10));
    }
    auto end = std::chrono::steady_clock::now();
    auto timeDiff = end - start;
    std::cout << "time with hint = " 
              << std::chrono::duration <double, std::milli> (timeDiff).count()
              << " ms" << std::endl;
}
// end second example


int main(int argc, char **argv) {
    std::map<std::string, int> m1 = { {"some key ", 5} };
    std::map<std::string, int> m2 = { {"some key ", 5} };

// first example
    withoutHint(m1);
    withHint(m2);

// second example
    std::map<int, int> m3 = { {0, 0} };
    std::map<int, int> m4 = { {0, 0} };
    init(m3);
    init(m4);
    std::cout << "after init" << std::endl;
    withoutHint2(m3);
    withHint2(m4);    
    return 0;
}