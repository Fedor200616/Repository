#include <iostream>

class MyClass {
public:
    static int count;

    MyClass() {
        count++;
    }

    void showCount() {
        std::cout << "Создано объектов: " << count << std::endl;
    }
};

int MyClass::count = 0;

int main() {
    MyClass a, b, c;
    MyClass::showCount(); // выведет 3
}