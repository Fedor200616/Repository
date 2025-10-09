#include <iostream>


int main() {
    char ch[] = "Porno";
    std::string str;
    str = ch;
    std::cout << str.c_str() << '\n';
    std::cout << str.length();
}
