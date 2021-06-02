
#include <string>

class Crypt{
    public:
    std::string shuffle(std::string);
    int findex(const char, std::string);
    std::string invert(std::string str);

    std::string encrypt(std::string);
    std::string decrypt(std::string);

    private:
    const std::string ABC = "QW)12E,./?|RTYUI-=OPxcLKJopl kH^%GFDqwefdCr[t789yui_(*jhs&$azvm<>:]}SAZXg56VBNM{+#@!3bn40";   
    std::string newAlphabet = "";   

};