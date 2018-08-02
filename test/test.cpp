#include <iostream>
#include <string>

#include <ophidian/design/DesignBuilder.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <ophidian/placement/Library.h>
#include <ophidian/standard_cell/StandardCells.h>
#include "placer/Floorplanner.h"
#include "placer/Placer.h"
#include "util/util.h"
#include "placer/WireLength.h"

std::string pinDirection(ophidian::standard_cell::StandardCells &, ophidian::standard_cell::Pin &);
bool isInput(ophidian::circuit::Netlist &, ophidian::circuit::Pin &);
bool isOutput(ophidian::circuit::Netlist &, ophidian::circuit::Pin &);
void testCellSize(ophidian::design::Design & design);
int cellsSite(ophidian::design::Design & design);

int main(int argc, char** argv)
{
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::string;
    using ophidian::circuit::Cell;
    using ophidian::circuit::Net;
    string verilog;
    string def;
    string lef;
    if(argc == 4)
    {
        verilog = argv[1];
        def = argv[2];
        lef = argv[3];
    } else {
        cerr << "invalid parrameters, use ./hellow_world verilog def lev" << endl;
        return -1;
    }
    cout << "Hello World!" << endl;

    ophidian::design::ICCAD2015ContestDesignBuilder builder{lef, def, verilog};

    auto & myDesign = builder.build();
    WireLength wireLength(myDesign);
    Floorplanner floorplanner(myDesign);
    floorplanner.setUtilization(1.0);
    floorplanner.setFloorplanRatio(2.0);
    floorplanner.create();
    std::cout << cellsSite(myDesign) << std::endl << designUtil::reportRows(myDesign) << std::endl;

    double estimate = wireLength.estimate();
    std::cout << "WireLength " << estimate << std::endl;
    Placer placer(myDesign);
    placer.place();

    estimate = wireLength.estimate();
    std::cout << "WireLength " << estimate << std::endl;
    return 0;
} 


void testCellSize(ophidian::design::Design & design)
{
    auto & stdCells = design.standardCells();
    std::string cellName = "DFFSR";
    auto cell = stdCells.find(ophidian::standard_cell::Cell(), cellName);

    auto multiBox = design.library().geometry(cell);
    for (auto boxIter = multiBox.begin(); boxIter != multiBox.end(); boxIter++) {
        std::cout << boxIter->min_corner().x() << " " << boxIter->max_corner().x() << std::endl; 
    }
}


int cellsSite(ophidian::design::Design & design)
{
    using Cell = ophidian::circuit::Cell;
    auto & netlist = design.netlist();
    auto site = design.floorplan().find("core");
    float siteWidth = floorplanUtil::siteWidth(design, site);
    int cellSite = 0;

    for (auto cellIter = netlist.begin(Cell()); cellIter != netlist.end(Cell()); cellIter++) {
        float cellWidth = cellUtil::cellWidth(*cellIter, design.libraryMapping(), design.library());
        int sites = cellWidth / siteWidth;
        cellSite += sites;
    }

    return cellSite;
}
