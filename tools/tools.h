
#include <string>
#include <vector>


class Tools{
    public:
    std::string itos(int);
    std::string invert(std::string);
    std::string padString(std::string, int);
    int stoi9(std::string num);
    std::vector<std::string> strToVec(std::string, char);
    std::string trimRepetitions(std::string);
    std::vector<std::vector<std::string>> filterVecVec(std::vector<std::vector<std::string>>, int index, std::string orAnd_, std::string possibilities);

    bool isNum(std::string);
    bool isDatum(std::string);



    private:
    // no private stuff for tools
};