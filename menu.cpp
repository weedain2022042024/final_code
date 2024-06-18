#include "menu.h"
#include <windows.h>
#include <iostream>
#include <vector>

void displayMenu(const std::vector<std::string>& options, int currentSelection) {
    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    std::cout << "\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t==========================================\n";
    std::cout << "\t\t\t\t\t   사용하고자 하는 기능을 선택하세요:\n";
    std::cout << "\t\t\t\t\t==========================================\n";
    std::cout << "\n";

    for (int i = 0; i < options.size(); ++i) {
        if (i == currentSelection) {
            std::cout << "\t\t\t\t\t\t\t" << "> " << options[i] << " <\n";
        }
        else {
            std::cout << "\t\t\t\t\t\t\t" << options[i] << "\n";
        }
    }

    std::cout << "\n\n\n";
    std::cout << "\t\t\t\t\t" << std::string(consoleWidth / 2 - options[currentSelection].length() / 2, ' ') << "> " << options[currentSelection] << " <\n";
}
