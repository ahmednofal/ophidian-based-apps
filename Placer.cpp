#include <Placer.h>
#include <util.h>

float Placer::calcArea()
{
    auto & designNetlist = this->design.netlist();
    auto & designLibraryMapping = this->design.libraryMapping();
    auto & designLibrary = this->design.library();

    float area;
    for (auto iter=designNetlist.begin(Cell()); iter != designNetlist.end(Cell()); iter++)

    {
        auto cellWidth = cellUtil::cellWidth(*iter, designLibraryMapping, designLibrary);
        auto cellHeight = cellUtil::cellHeight(*iter, designLibraryMapping, designLibrary);
        area+= cellHeight * cellWidth;
    }

    return area;
}
void Placer::place(Design & currentDesign)
{
   // We are going to be doing constructive placement
   // 1- Choose the first cell in the internal data structure format of the ophidian library
   // Bla() : Lvalue which is function definition  
   auto cell = new Cell();
   this->place1stCell(*cell );
   // 2- Use the legal function to constraint the placement range
   // 3- Place the cell randomly
   // 4- Traverse the netlist for the connected cells
   // 5- place the cells one by one closer to their connected cell, closer: shorter wire length using the manhattan distance
   //
   //
   // 6- Till u reach the last cell of the netlist
   //
}

void place1stCell(Cell & cell)
{
    
}


