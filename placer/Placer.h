#ifndef PLACER_H
#define PLACER_H

#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/placement/PlacementMapping.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/placement/Library.h>
#include <ophidian/util/Units.h>
#include <ophidian/util/Range.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <ophidian/floorplan/Floorplan.h>
#include <ophidian/entity_system/EntitySystem.h>
#include <functional>

class Placer {
using Design=ophidian::design::Design;
using Cell=ophidian::circuit::Cell;
using Net=ophidian::circuit::Net;
using ConstRowIterator = ophidian::entity_system::EntitySystem <ophidian::floorplan::Row>::const_iterator;
public:
    Placer(Design & );
    Placer();
    ~Placer();
    void inputDesign(Design & );
    void place();
    void printLocations();

private:
    float mArea = 0;
    Design & mDesign;
    ophidian::circuit::Netlist & mDesignNetlist;  
    ophidian::placement::Library & mDesignLibrary;
    ophidian::circuit::LibraryMapping & mDesignLibraryMapping;
    ophidian::floorplan::Floorplan & mDesignFloorplan;
    ophidian::placement::PlacementMapping & mDesignPlacementMapping;
    ophidian::placement::Placement & mDesignPlacement;
    ophidian::floorplan::Site mFstSite;
    int mSiteWidth;
    int mSiteHeight;
    void goToNextRow(ConstRowIterator & rowIter, float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow);
    int dyeWidth();
    int dyeHeight();
    float calcCoreArea();
    void place1stCell(const Cell &);
    float siteWidth(const ophidian::floorplan::Site &);
    float siteHeight(const ophidian::floorplan::Site &);
    bool enoughSitesInRow(int, int, int);
    void placeAux(void (Placer::*f)(ConstRowIterator & rowIter,  float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow));
    void connectivityPlace(ConstRowIterator & rowIter, float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow);
    void basicPlace(ConstRowIterator & rowIter,  float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow);
    void legallyPlace(const Cell & cellToBePlaced, ConstRowIterator & rowIter,  float & rowX,  float & rowY,int & sitesInRow,  int & filledSitesInRow);
};

#endif
