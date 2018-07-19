#include "placer/Placer.h"
#include "util/util.h"
#include <math.h>


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

Placer::~Placer()
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
    int site_height = siteHeight(designFloorplan.site(*row_iter));
    int filled_sites_in_row = 0;

    printf("site width: %d site height: %d\n", site_width, site_height);

    while (cell_iter != designNetlist.end(Cell())) {
        float cell_width = (float) cellUtil::cellWidth(*cell_iter, designLibraryMapping, designLibrary);
        float cell_height = (float) cellUtil::cellHeight(*cell_iter, designLibraryMapping, designLibrary);
        int cell_sites = ceil(cell_width / (float) site_width);

        if ((cell_sites + filled_sites_in_row) > sites_in_row) {
            row_iter++;
            row_x = (float) designFloorplan.origin(*row_iter).x();
            row_y = (float) designFloorplan.origin(*row_iter).y();

            sites_in_row = designFloorplan.numberOfSites(*row_iter);
            site_width = siteWidth(designFloorplan.site(*row_iter));

            filled_sites_in_row = 0;
        }

        float pos_x = (filled_sites_in_row) * site_width + row_x;
        auto location = ophidian::util::LocationDbu(pos_x, row_y);
        designPlacement.placeCell(*cell_iter, location);

        // printf("cell_width: %.2f cell_height: %.2f\t cell_sites: %d\t filled_sites_in_row: %d\n", cell_width, cell_height, cell_sites, filled_sites_in_row);
        filled_sites_in_row += cell_sites;
        cell_iter++;
    }
}


void Placer::printLocations()
{
    printf("==================================\nLOCATIONS\n==================================\n");
    for (auto cell_iter = designNetlist.begin(Cell()); cell_iter != designNetlist.end(Cell()); cell_iter++)
    {
        std::string name = designNetlist.name(*cell_iter);
        float x = (float) designPlacement.cellLocation(*cell_iter).x();
        float y = (float) designPlacement.cellLocation(*cell_iter).y();
        printf("Cell: %s\t (%.3f, %.3f)\n", name.c_str(), x, y);
    }
    printf("==================================\n");
}
