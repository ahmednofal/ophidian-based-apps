
#ifndef PLACE_H
#define PLACE_H

#include <ophidian/placement/Placement.h>
#include <ophidian/design/Design.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/placement/Library.h>

using Design=ophidian::design::Design;
using Cell=ophidian::circuit::Cell;

void area(Design & );
void place_1st_cell(Cell & );


#endif
