#ifndef DESIGN_EXTENDED_H
#define DESIGN_EXTENDED_H

#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/placement/Library.h>

class Placer : public ophidian::design::Design {

    using Design=ophidian::design::Design;
    using Cell=ophidian::circuit::Cell;

public:
    Placer();
    ~Placer();

    int cellWidth(const Cell &);
    int cellHeight(const Cell &);
    int dyeWidth();
    int dyeHeight();
    void area(Design & );
    void place_1st_cell(Cell & );
};

#endif
