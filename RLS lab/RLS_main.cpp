#include <iostream>
#include "RLS_head.h"
using namespace std;


int main(){
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale());

    random_init_plane();

    return 0;
}

