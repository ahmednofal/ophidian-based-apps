#ifndef PLACER_H
#define PLACER_H

#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/placement/Library.h>

using Design=ophidian::design::Design;
using Cell=ophidian::circuit::Cell;

class Placer : public ophidian::design::Design {


public:
    Placer(Design & );
    Placer();
    ~Placer();
    void inputDesign(Design & );
    void place(Design & );
    void place1stCell(Cell & );
private:
    int dyeWidth();
    int dyeHeight();
    float calcArea();
    Design design;

};

#endif
