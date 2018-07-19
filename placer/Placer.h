#ifndef PLACER_H
#define PLACER_H

#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/placement/Library.h>
#include <ophidian/util/Units.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <ophidian/floorplan/Floorplan.h>


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
    float area = 0;

    int dyeWidth();
    int dyeHeight();
    float calcCoreArea();
    void place1stCell(const Cell &);
    float siteWidth(const ophidian::floorplan::Site &);
    float siteHeight(const ophidian::floorplan::Site &);

    Design & design;
    ophidian::circuit::Netlist & designNetlist;  
    ophidian::placement::Library & designLibrary;
    ophidian::circuit::LibraryMapping & designLibraryMapping;
    ophidian::floorplan::Floorplan & designFloorplan;
    ophidian::placement::PlacementMapping & designPlacementMapping;
    ophidian::placement::Placement & designPlacement;
};

#endif
