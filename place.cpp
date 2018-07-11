#include <ophidian/placement/Placement.h>
#include <ophidian/design/Design.h>
#include <ophidian/circuit/Netlist.h>

using Design=ophidian::design::Design;
using Cell=ophidian::circuit::Cell;

Design place(Design & currentDesign)
{
   // We are going to be doing constructive placement
   // 1- Choose the first cell in the internal data structure format of the ophidian library
   for 
   // 2- Use the legal function to constraint the placement range
   // 3- Place the cell randomly
   // 4- Traverse the netlist for the connected cells
   // 5- place the cells one by one closer to their connected cell, closer: shorter wire length using the manhattan distance
   //
   // 6- Till u reach the last cell of the netlist
}

void place_1st_cell(Cell & cell)
{

}
