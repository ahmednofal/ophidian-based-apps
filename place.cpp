#include <place.h>

void area(Design & design)
{
    auto & designStandardCells = design.standardCells();
    auto & designNetlist = design.netlist();
    auto & designLibraryMapping = design.libraryMapping();
    auto & designLibrary = design.library();

    for (auto iter=designNetlist.begin(Cell()); iter != designNetlist.end(Cell()); iter++)

    {
        auto currentStdCell = designLibraryMapping.cellStdCell(*iter);

    }
}
Design place(Design & currentDesign)
{
   // We are going to be doing constructive placement
   // 1- Choose the first cell in the internal data structure format of the ophidian library
   // Bla() : Lvalue which is function definition  
   auto cell = new Cell();
   place_1st_cell(*cell);
   // 2- Use the legal function to constraint the placement range
   // 3- Place the cell randomly
   // 4- Traverse the netlist for the connected cells
   // 5- place the cells one by one closer to their connected cell, closer: shorter wire length using the manhattan distance
   //
   //
   // 6- Till u reach the last cell of the netlist
   //
}

void place_1st_cell(Cell & cell)
{
    
}


