#pragma once
#include <iostream>

class Cellule
{
private:
    int index;
    int x;
    int y;
    bool val;
public:
    Cellule(int index, bool val, int X_max);
    void afficher() const;
    int return_index() const;
    int return_x() const;
    int return_y() const;
    int return_state() const;
    void change_state(bool u);
};