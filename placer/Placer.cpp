#include <placer/Placer.h>
#include <util/util.h>


Placer::Placer(Design & design) : 
    design(design), 
    designNetlist(design.netlist()), 
    designLibrary(design.library()), 
    designLibraryMapping(design.libraryMapping()),
    designFloorplan(design.floorplan()),
    designPlacementMapping(desgin.placementMapping())
{
}


float Placer::calcCoreArea()
{
    for (auto iter=designNetlist.begin(Cell()); iter != designNetlist.end(Cell()); iter++)
    {
        auto cellWidth = cellUtil::cellWidth(*iter, designLibraryMapping, designLibrary);
        auto cellHeight = cellUtil::cellHeight(*iter, designLibraryMapping, designLibrary);
        this->area+= cellHeight * cellWidth;
    }
    return area;
}


void Placer::place(Design & currentDesign)
{
   // We are going to be doing constructive placement
   // 1- Choose the first cell in the internal data structure format of the ophidian library
   // Bla() : Lvalue which is function definition  

   auto fstCell = this->design.netlist().begin(Cell()); 
   this->place1stCell(*fstCell);
   auto x = fstCell+1;
   for (auto iter = fstCell+1; iter != this->designNetlist.end(Cell()); iter++)
   {
        
   }
   // 2- Use the legal function to constraint the placement range
   // 3- Place the cell randomly
   // 4- Traverse the netlist for the connected cells
   // 5- place the cells one by one closer to their connected cell, closer: shorter wire length using the manhattan distance
   //
   //
   // 6- Till u reach the last cell of the netlist
   //
}

void Placer::place1stCell(const Cell & cell)
{
    auto location = ophidian::util::LocationDbu(0,0);
    this->design.placement().placeCell(cell, location);

}


float Placer::siteWidth()
{
    // this assumes that there is only one site
    auto site = (* designFloorplan.sitesRange().begin());
    auto dimensions = designFloorplan.siteUpperRightCorner(site);
    return (float) dimensions.x();
}


float Placer::siteHeight()
{
    // this assumes that there is only one site
    auto site = (* designFloorplan.sitesRange().begin());
    auto dimensions = designFloorplan.siteUpperRightCorner(site);
    return (float) dimensions.y();
}


float Placer::cellWidth(Cell & cell)
{
   auto box = (*designPlacementMapping.geometry(cell).begin());
   return box.max_corner().x();
}

void Placer::basicPlace()
{
    float site_width = siteWidth();
    float site_height = siteHeight();
    float pos_x = 0;
    float pos_y = 0;

    for (auto iter = designNetlist.begin(Cell()); iter != designNetlist.end(Cell()); ++iter) {
        auto cell = *iter;
        float cell_width = cellWidth(cell);

    }
}

