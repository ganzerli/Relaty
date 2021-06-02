#include <vector>
#include <string>
#include <iostream>
#include <fstream> 

class Relations{

    public:
    void addRelation(std::string relationsAndConcepts);
    // opens file and retrive relations
    std::vector<std::string> relFileToVector();
    // return [0] relation, following, related relations or words
    std::vector<std::string> updateConcept(std::string,std::string,std::string,std::string);
    std::vector<std::string> relStringToVector(std::string);
    std::vector<std::vector<std::string>> getRelationsFromConcept(std::string);
    std::string findRelationsToText(std::string);

    private:
    const std::string PATH = "./DATA/RELATIONS.txt";

};