#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <tuple>


static std::stringstream m_stream;


struct Printer
{

    std::string str() const
    {
        std::string s = std::move(m_stream.str());
        m_stream.str("");
        return s;
    }

    template<typename T>
    Printer& format(const T& el)
    {
        m_stream << el;
        return *this;
    }

    template<typename T>
    Printer& format(const std::vector<T>& vect)
    {
        m_stream << "[ ";
        if (not vect.empty())
        {
            for (auto it = vect.begin(); it != --vect.end(); it++)
            {
                this->format(*it);
                m_stream << ", ";
            }
            this->format(*(--vect.end()));
        }
        m_stream << " ]";
        return *this;
    }

    template<typename T>
    Printer& format(const std::set<T>& set)
    {
        m_stream << "{ ";
        if (not set.empty())
        {
            for (auto it = set.begin(); it != --set.end(); it++)
            {
                this->format(*it);
                m_stream << ", ";
            }
            this->format(*(--set.end()));
        }
        m_stream << " }";
        return *this;
    }

    template<typename T, typename M>
    Printer& format(const std::pair<T, M>& pr)
    {
        m_stream << "(";
        this->format(pr.first);
        m_stream << ", ";
        this->format(pr.second);
        m_stream << ")";
        return *this;
    }

    template<typename... Args>
    Printer& format(const std::tuple<Args...> tup)
    {
        m_stream << "( ";
        std::apply
        (
            [this](auto &... x)
            {
                size_t n{0};
                (...,static_cast<void>
                            (this->format(x), m_stream << (++n != sizeof...(Args) ? ", " : "")));
            }, 
            tup
        );
        m_stream << " )";
        return *this;
    }
};


template<typename T>
std::string format(const T& t) {
    return Printer().format(t).str();
}


int main()
{
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
    std::string s1 = Printer().format(" vector: ").format(v).str();
    std::cout << s1 << std::endl;
    // // " vector: [ (1, 4), (5, 6) ]"
    std::string s2 = Printer().format(t).format(" ! ").format(0).str();
    std::cout << s2 << std::endl;

    std::vector<std::set<std::string>> v2 = { {"sdsdsd", "dfdsf"}, 
                                              {"44"}, 
                                              {"fdfdf", "dfdfdf"}};

    std::tuple< std::string, 
                std::vector<int>, 
                std::set<std::string>, 
                std::pair<std::string, int> > t2 = {"qwerty", 
                                                    {1, 2, 3}, 
                                                    {"qax", "ert", "33"}, 
                                                    {"12345", 99}};

    std::pair<std::string, double> t3 = {"qwe", 2.5};
    std::string s3 = Printer().format(v2).format(" vector:::: ").format(t2).format(2).str();
    std::cout << s3 << std::endl;
    std::cout << std::endl;
    std::cout << format(t3) << std::endl;
    std::tuple<int> t12;
    std::string s4 = Printer().format(t12).str();
    std::cout << s4 << std::endl;
    return 0;
}




