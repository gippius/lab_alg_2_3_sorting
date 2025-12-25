#include "app/menu.hpp"

#ifdef _WIN32
  #include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    runMenu();
    return 0;
}
