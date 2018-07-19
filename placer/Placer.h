#ifndef PLACER_H
#define PLACER_H

#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/placement/PlacementMapping.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/placement/Library.h>
#include <ophidian/util/Units.h>
#include <ophidian/util/Ranges.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <ophidian/floorplan/Floorplan.h>
#include <ophidian/entity_system/EntitySystem.h>


class Placer {
using Design=ophidian::design::Design;
using Cell=ophidian::circuit::Cell;

public:
    Placer(Design & );
    Placer();
    ~Placer();
    void inputDesign(Design & );
    void place(Design & );
    void printLocations();
    void basicPlace();

private:
    float mArea = 0;
    Design & mDesign;
    ophidian::circuit::Netlist & mDesignNetlist;  
    ophidian::placement::Library & mDesignLibrary;
    ophidian::circuit::LibraryMapping & mDesignLibraryMapping;
    ophidian::floorplan::Floorplan & mDesignFloorplan;
    ophidian::placement::PlacementMapping & mDesignPlacementMapping;
    ophidian::placement::Placement & mDesignPlacement;
//entity_system::EntitySystem <Row>::const_iterator;

    void goToNextRow(entity_system::EntitySystem <Row>::const_iterator & rowIter, float & rowX,  float & rowY,int & sitesInRow, int & siteWidth, int & filledSitesInRow);
    int dyeWidth();
    int dyeHeight();
    float calcCoreArea();
    void place1stCell(const Cell &);
    float siteWidth(const ophidian::floorplan::Site &);
    float siteHeight(const ophidian::floorplan::Site &);
    bool enoughSitesInRow(int, int, int);
};

#endif
