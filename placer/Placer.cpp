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
    mDesignPlacement(design.placement()),
    mFstSite(mDesignFloorplan.site(*mDesignFloorplan.rowsRange().begin())),
    mSiteWidth(this->siteWidth(mFstSite)),
    mSiteHeight(this->siteHeight(mFstSite))
{
}

Placer::~Placer()
{
}
void Placer::place()
{
    placeAux(&Placer::connectivityPlace);
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

void Placer::placeAux(void (Placer::*f)(ConstRowIterator & rowIter,  float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow))
{
    auto rowIter = mDesignFloorplan.rowsRange().begin();
    float rowX = (float) mDesignFloorplan.origin(*rowIter).x();
    float rowY = (float) mDesignFloorplan.origin(*rowIter).y();
    int sitesInRow = mDesignFloorplan.numberOfSites(*rowIter);
    int filledSitesInRow = 0;
    (this->*f)(rowIter,  rowX, rowY, sitesInRow,  filledSitesInRow);
}

void Placer::connectivityPlace(ConstRowIterator & rowIter, float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow)
{
   for (auto netIter = mDesignNetlist.begin(Net()); netIter != mDesignNetlist.end(Net()); netIter++)
   {
       auto netPins = mDesignNetlist.pins(*netIter);
       for (auto aPin : netPins)
       {
           auto cellToBePlaced = Cell();
           if (mDesignNetlist.output(aPin)==Output() and mDesignNetlist.input(aPin)==Input() )
           {
               cellToBePlaced = mDesignNetlist.cell(aPin);
               if (!mDesignPlacement.isFixed(cellToBePlaced))
               {
                   legallyPlace(cellToBePlaced, rowIter, rowX, rowY, sitesInRow,filledSitesInRow);
               }
           }

       }
       
    }
}
void Placer::legallyPlace(const Cell & cellToBePlaced, ConstRowIterator & rowIter,  float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow)
{

    float cellWidth = (float) cellUtil::cellWidth(cellToBePlaced, mDesignLibraryMapping, mDesignLibrary);
    float cellHeight = (float) cellUtil::cellHeight(cellToBePlaced, mDesignLibraryMapping, mDesignLibrary);
    int cellSites = ceil(cellWidth / (float) mSiteWidth);
    if (!enoughSitesInRow(cellSites, filledSitesInRow, sitesInRow)){
       goToNextRow(rowIter, rowX, rowY, sitesInRow, filledSitesInRow);
    }
    float posX = (filledSitesInRow) * mSiteWidth + rowX;
    auto location = ophidian::util::LocationDbu(posX, rowY);
    mDesignPlacement.placeCell(cellToBePlaced, location);
    filledSitesInRow += cellSites;
    mDesignPlacement.fixLocation(cellToBePlaced, true);
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
void Placer::basicPlace(ConstRowIterator & rowIter,  float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow){
    auto cellIter = mDesignNetlist.begin(Cell());
    while (cellIter != mDesignNetlist.end(Cell())) {
        legallyPlace(*cellIter, rowIter, rowX, rowY, sitesInRow, filledSitesInRow);
        cellIter++;
    }
}

void Placer::goToNextRow(ConstRowIterator & rowIter, float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow)
{
            rowIter++;
            rowX = (float) mDesignFloorplan.origin(*rowIter).x();
            rowY = (float) mDesignFloorplan.origin(*rowIter).y();
            sitesInRow = mDesignFloorplan.numberOfSites(*rowIter);
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
