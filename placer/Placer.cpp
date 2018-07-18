#include "placer/Placer.h"
#include "util/util.h"


Placer::Placer(Design & design) : 
    design(design), 
    designNetlist(design.netlist()), 
    designLibrary(design.library()), 
    designLibraryMapping(design.libraryMapping()),
    designFloorplan(design.floorplan()),
    designPlacementMapping(design.placementMapping()),
    designPlacement(design.placement())
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


float Placer::siteWidth(const ophidian::floorplan::Site & site)
{
    // this assumes that there is only one site
    auto dimensions = designFloorplan.siteUpperRightCorner(site);
    return (float) dimensions.x();
}


float Placer::siteHeight(const ophidian::floorplan::Site & site)
{
    // this assumes that there is only one site
    auto dimensions = designFloorplan.siteUpperRightCorner(site);
    return (float) dimensions.y();
}


float Placer::cellWidth(const Cell & cell)
{
   auto box = (*designPlacementMapping.geometry(cell).begin());
   return box.max_corner().x();
}

// for each row
//      get row origin
//      get site width
//      place cells untill row is filled
//      repeat untill all cell are placed
// 
// This assumes equal heights at all times
void Placer::basicPlace()
{
    auto row_iter = designFloorplan.rowsRange().begin();
    auto cell_iter = designNetlist.begin(Cell());

    float row_x = (float) designFloorplan.origin(*row_iter).x();
    float row_y = (float) designFloorplan.origin(*row_iter).y();
    int sites_in_row = designFloorplan.numberOfSites(*row_iter);
    int site_width = siteWidth(designFloorplan.site(*row_iter));
    int filled_sites_in_row = 0;

    while (cell_iter != designNetlist.end(Cell())) {
        if (filled_sites_in_row > sites_in_row) {
            row_iter++;
            sites_in_row = designFloorplan.numberOfSites(*row_iter);
            site_width = siteWidth(designFloorplan.site(*row_iter));
            row_x = (float) designFloorplan.origin(*row_iter).x();
            row_y = (float) designFloorplan.origin(*row_iter).y();
        }

        float cell_width = cellWidth(*cell_iter);
        int cell_sites = cell_width / site_width;
        float pos_x = (filled_sites_in_row + cell_sites) * site_width;
        auto location = ophidian::util::LocationDbu(pos_x, row_y);
        designPlacement.placeCell(*cell_iter, location);

        filled_sites_in_row += cell_sites;
        cell_iter++;
    }
}
