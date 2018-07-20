#include "placer/Placer.h"
#include "util/util.h"
#include <math.h>


Placer::Placer(Design & design) : 
    mDesign(design), 
    mDesignNetlist(design.netlist()), 
    mDesignLibrary(design.library()), 
    mDesignLibraryMapping(design.libraryMapping()),
    mDesignFloorplan(design.floorplan()),
    mDesignPlacementMapping(design.placementMapping()),
    mDesignPlacement(design.placement())
{
}

Placer::~Placer()
{
}

float Placer::calcCoreArea()
{
    for (auto iter=mDesignNetlist.begin(Cell()); iter != mDesignNetlist.end(Cell()); iter++)
    {
        auto cellWidth = cellUtil::cellWidth(*iter, mDesignLibraryMapping, mDesignLibrary);
        auto cellHeight = cellUtil::cellHeight(*iter, mDesignLibraryMapping, mDesignLibrary);
        mArea+= cellHeight * cellWidth;
    }
    return mArea;
}


void Placer::place()
{
    auto rowIter = mDesignFloorplan.rowsRange().begin();
    float rowX = (float) mDesignFloorplan.origin(*rowIter).x();
    float rowY = (float) mDesignFloorplan.origin(*rowIter).y();
    int sitesInRow = mDesignFloorplan.numberOfSites(*rowIter);
    int siteWidth = this->siteWidth(mDesignFloorplan.site(*rowIter));
    int siteHeight = this->siteHeight(mDesignFloorplan.site(*rowIter));
    int filledSitesInRow = 0;
   for (auto netIter = mDesignNetlist.begin(Net()); netIter != mDesignNetlist.end(Net()); netIter++)
   {
       auto netPins = mDesignNetlist.pins(*netIter);
       for (auto aPin : netPins)
       {
           auto cellToBePlaced = mDesignNetlist.cell(aPin);
           if (mDesignPlacement.isFixed(cellToBePlaced))
           {
               float cellWidth = (float) cellUtil::cellWidth(cellToBePlaced, mDesignLibraryMapping, mDesignLibrary);
               float cellHeight = (float) cellUtil::cellHeight(cellToBePlaced, mDesignLibraryMapping, mDesignLibrary);
               int cellSites = ceil(cellWidth / (float) siteWidth);
               if (!enoughSitesInRow(cellSites, filledSitesInRow, sitesInRow)){
                   goToNextRow(rowIter, rowX, rowY, sitesInRow, siteWidth, filledSitesInRow);
               }
               float posX = (filledSitesInRow) * siteWidth + rowX;
               auto location = ophidian::util::LocationDbu(posX, rowY);
               mDesignPlacement.placeCell(cellToBePlaced, location);
               filledSitesInRow += cellSites;
               mDesignPlacement.fixLocation(cellToBePlaced, true);
           }

       }
       
    }
}

void Placer::place1stCell(const Cell & cell)
{
    auto location = ophidian::util::LocationDbu(0,0);
    mDesign.placement().placeCell(cell, location);

}


float Placer::siteWidth(const ophidian::floorplan::Site & site)
{
    // this assumes that there is only one site
    auto dimensions = mDesignFloorplan.siteUpperRightCorner(site);
    return (float) dimensions.x();
}


float Placer::siteHeight(const ophidian::floorplan::Site & site)
{
    // this assumes that there is only one site
    auto dimensions = mDesignFloorplan.siteUpperRightCorner(site);
    return (float) dimensions.y();
}


// for each row
//      get row origin
//      get site width
//      place cells untill row is filled
//      repeat untill all cell are placed
// 
// This assumes equal heights at all times
void Placer::basicPlace(void (*f))
{
    auto rowIter = mDesignFloorplan.rowsRange().begin();
    auto cellIter = mDesignNetlist.begin(Cell());
    float rowX = (float) mDesignFloorplan.origin(*rowIter).x();
    float rowY = (float) mDesignFloorplan.origin(*rowIter).y();
    int sitesInRow = mDesignFloorplan.numberOfSites(*rowIter);
    int siteWidth = this->siteWidth(mDesignFloorplan.site(*rowIter));
    int siteHeight = this->siteHeight(mDesignFloorplan.site(*rowIter));
    int filledSitesInRow = 0;
    /* printf("site width: %d site height: %d\n", siteWidth, siteHeight); */
    while (cellIter != mDesignNetlist.end(Cell())) {
        float cellWidth = (float) cellUtil::cellWidth(*cellIter, mDesignLibraryMapping, mDesignLibrary);
        float cellHeight = (float) cellUtil::cellHeight(*cellIter, mDesignLibraryMapping, mDesignLibrary);
        int cellSites = ceil(cellWidth / (float) siteWidth);
        if (!enoughSitesInRow(cellSites, filledSitesInRow, sitesInRow)){
            goToNextRow(rowIter, rowX, rowY, sitesInRow, siteWidth, filledSitesInRow);
        }
        float posX = (filledSitesInRow) * siteWidth + rowX;
        auto location = ophidian::util::LocationDbu(posX, rowY);
        mDesignPlacement.placeCell(*cellIter, location);
        // printf("cellWidth: %.2f cellHeight: %.2f\t cellSites: %d\t filledSitesInRow: %d\n", cellWidth, cellHeight, cellSites, filledSitesInRow);
        filledSitesInRow += cellSites;
        cellIter++;
    }
}

void Placer::goToNextRow(ophidian::entity_system::EntitySystem <ophidian::floorplan::Row>::const_iterator & rowIter, float & rowX,  float & rowY,int & sitesInRow, int & siteWidth, int & filledSitesInRow)
{
            rowIter++;
            rowX = (float) mDesignFloorplan.origin(*rowIter).x();
            rowY = (float) mDesignFloorplan.origin(*rowIter).y();
            sitesInRow = mDesignFloorplan.numberOfSites(*rowIter);
            siteWidth = this->siteWidth(mDesignFloorplan.site(*rowIter));
            filledSitesInRow = 0;
}

bool Placer::enoughSitesInRow(int cellSites, int filledSitesInRow, int sitesInRow)
{
    return (cellSites + filledSitesInRow) <= sitesInRow;
}
void Placer::printLocations()
{
    printf("==================================\nLOCATIONS\n==================================\n");
    for (auto cell_iter = mDesignNetlist.begin(Cell()); cell_iter != mDesignNetlist.end(Cell()); cell_iter++)
    {
        std::string name = mDesignNetlist.name(*cell_iter);
        float x = (float) mDesignPlacement.cellLocation(*cell_iter).x();
        float y = (float) mDesignPlacement.cellLocation(*cell_iter).y();
        printf("Cell: %s\t (%.3f, %.3f)\n", name.c_str(), x, y);
    }
    printf("==================================\n");
}
