#include <string>
#include <vector> 

using namespace std;


class TImpl;
using TImplPtr = unique_ptr<TImpl>;


class TImpl
{
    public:
        virtual ~TImpl() = default;
        virtual void Parse(const string& str, vector<string>& res) = 0;
};


class ImplOne: public TImpl
{
    public:
        virtual void Parse(const string& str, vector<string>& res) override;
};

class ImplTwo: public TImpl
{
    public:
        virtual void Parse(const string& str, vector<string>& res) override;
};

// other implementations ...


class TParser {
    TImplPtr impl;
public:
    TParser(TImplPtr r): impl(move(r)) {}

    void newParser(TImplPtr r) {
        impl = move(r);
    }

    void Parse(const string& str, vector<string>& res) {
        impl->Parse(str, res);
    }
};


template<typename ConcreteImpl>
size_t Do(string text)
{
    TParser* parser = new TParser(make_unique<ConcreteImpl>());
    vector<string> tokens;
    parser->Parse(text, tokens);
 
    size_t c = 0;
    for (const string& word: tokens) {
        if (word.size() > 5) {
            ++c;
        }
    }
    return c;
}
