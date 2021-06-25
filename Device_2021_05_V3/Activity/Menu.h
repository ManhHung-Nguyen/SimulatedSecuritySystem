#pragma once
#include "Mode.h"

class Menu : public Mode {
protected:
    void show_content(LPCHAR content) override;
    void on_number_key(int code) override;
public:
    Menu(LPCHAR main = 0, LPCHAR sub = 0) : Mode(main, sub) {}
};

class MainMenu : public Menu {
public:
    MainMenu();
    void MappingData();
};
