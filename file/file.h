#include <vector>
#include <string>

class File{
    public:
    
    const char* PATH = "./DATA/";
    std::string vecToStr(std::vector<char>); 

    std::vector<char> getFileContent(std::string);
    bool fileCheck(std::string);
    void makeFile(std::string);

    void insertInDate(std::string, std::string , std::string);

    std::vector<char> getIndex(std::vector<char>); 
    std::vector<std::string> dataOfDay(std::string , std::vector<char>);

    private:
    // a rec0rd can begin at,or have until      999999999 chars
    // in the index will be 000000000 000000000 000000000 000
    const int MAX_N_DIGITS = 6;
    std::vector<char> standardTemplate();

    // file elabortion..
    int dayCount(std::string);
    //

    const int INDEXSIZE = 7686;
    const int FORMATSIZE = 21;
    const int CHARSOFNUMBER = 6;
  // const char* PATH = "./DATA/";
};
