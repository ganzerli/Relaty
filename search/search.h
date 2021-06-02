#include <vector>
#include <string>

class Search{
    public:
        void loadContentAndIndexFromPath(std::string);
        std::vector<std::string> searchRelations(std::string);
        std::vector<std::string> searchDate(std::string);
        std::vector<std::vector<std::string>> fromRelations(std::string);
        std::vector<std::vector<std::string>> wordInConceptRel(std::string, std::vector<std::vector<std::string>>);
        std::vector<std::string> searchWord(std::string);
    private:
    std::vector<char> CONTENT;
    std::vector<char> INDEX;
};