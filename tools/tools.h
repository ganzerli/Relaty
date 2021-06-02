
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


    private:
    // no private stuff for tools
};