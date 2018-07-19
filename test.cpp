#include <iostream>
#include <string>

#include <ophidian/design/DesignBuilder.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <ophidian/placement/Library.h>
#include <ophidian/standard_cell/StandardCells.h>
#include "placer/Placer.h"

std::string pinDirection(ophidian::standard_cell::StandardCells &, ophidian::standard_cell::Pin &);
bool isInput(ophidian::circuit::Netlist &, ophidian::circuit::Pin &);
bool isOutput(ophidian::circuit::Netlist &, ophidian::circuit::Pin &);

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
    
    Placer placer(myDesign);
    placer.printLocations();
    placer.basicPlace();
    printf("After placing\n");
    placer.printLocations();

    return 0;
} 
