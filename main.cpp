/*
 * Copyright 2017 Ophidian
   Licensed to the Apache Software Foundation (ASF) under one
   or more contributor license agreements.  See the NOTICE file
   distributed with this work for additional information
   regarding copyright ownership.  The ASF licenses this file
   to you under the Apache License, Version 2.0 (the
   "License"); you may not use this file except in compliance
   with the License.  You may obtain a copy of the License at
   http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing,
   software distributed under the License is distributed on an
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
   KIND, either express or implied.  See the License for the
   specific language governing permissions and limitations
   under the License.
 */

#include <iostream>
#include <string>

#include <ophidian/design/DesignBuilder.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <ophidian/placement/Library.h>
#include <ophidian/standard_cell/StandardCells.h>

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

    auto & the_cells = myDesign.standardCells();
    auto & the_netlist = myDesign.netlist();
    auto & the_placement = myDesign.placement();
    auto & the_floorplan = myDesign.floorplan();
    auto & the_library = myDesign.library();
    auto & the_mapping = myDesign.libraryMapping();

    for (auto iter=the_netlist.begin(Cell()); iter != the_netlist.end(Cell()); iter++) {
        auto cell = *iter;
        auto std_cell = the_mapping.cellStdCell(cell);

        auto dimensions = the_library.geometry(std_cell);
        auto pins = the_netlist.pins(cell);
        auto std_pins = the_cells.pins(std_cell);

        printf("Cell: %s Type: %s \nCell Pins:- \n", the_netlist.name(cell).c_str(), the_cells.name(std_cell).c_str());
        for (auto pin : pins) {
            auto net = the_netlist.net(pin);
            cout << "\tpin: " << the_netlist.name(pin) 
                //<< " type: " << pinDirection(the_cells, pin) 
                << "\tbelonging to net: " << the_netlist.name(net) << endl;
        }

        printf("Std Pins:-\n");
        for (auto pin : std_pins) {
            printf("\tpin: %s\tdirection: %s\n", the_cells.name(pin).c_str(), pinDirection(the_cells, pin).c_str());
        }

        auto box = dimensions.begin(); 
        int width = box->max_corner().x();
        int height = box->max_corner().y(); 
        printf("width/height %f, width/height %f\n", (double) width, (double) height);

        printf("\n");
    } 

    printf("===============NETS===============\n");
    for (auto iter = the_netlist.begin(Net()); iter != the_netlist.end(Net()); iter++) {
        auto net = *iter;
        
        std::string name = the_netlist.name(net);
        auto pins = the_netlist.pins(net);

        printf("NET: %s\n", name.c_str());

        for (auto pin : pins) {
            std::string pin_name = the_netlist.name(pin);
            std::string cell_name;
            
            if (isInput(the_netlist, pin) || isOutput(the_netlist, pin)) {
                cell_name = "n/a";
            }
            else {
                auto cell = the_netlist.cell(pin);
                cell_name = the_netlist.name(cell);
            }

            printf("\tpin: %10s -> cell %s\n", pin_name.c_str(), cell_name.c_str());
        }
    }
    
    printf("===============I/O===============\nInput:-");
    for (auto iter = the_netlist.begin(ophidian::circuit::Input()); iter != the_netlist.end(ophidian::circuit::Input()); iter++) {
        auto input = *iter;

        printf("\tpin: %s\n", the_netlist.name(the_netlist.pin(input)).c_str());
    }

    printf("Output:-\n");
    for (auto iter = the_netlist.begin(ophidian::circuit::Output()); iter != the_netlist.end(ophidian::circuit::Output()); iter++) {
        auto output = *iter;

        printf("\tpin: %s\n", the_netlist.name(the_netlist.pin(output)).c_str());
    }

    printf("===============FLOORPLAN===============\n");
    printf("Dye:-\n\torigin: %.3f %.3f\n", (double) the_floorplan.chipOrigin().x(), (double) the_floorplan.chipOrigin().y());
    printf("\tupper right corner: %.3f %.3f\n", (double) the_floorplan.chipUpperRightCorner().x(), (double) the_floorplan.chipUpperRightCorner().y());
    for (auto row : the_floorplan.rowsRange()) {
        printf("\t row has %d sites\n", (int) the_floorplan.numberOfSites(row));
    }

    printf("Sites:-\n");
    for (auto site : the_floorplan.sitesRange()) {
        auto position = the_floorplan.siteUpperRightCorner(site);
        auto name = the_floorplan.name(site);

        printf("\t site: %s size: %.3f %.3f\n", name.c_str(), (double) position.x(), (double) position.y());
    }

    return 0;
}


std::string pinDirection(ophidian::standard_cell::StandardCells & cells, ophidian::standard_cell::Pin & pin)
{
    using ophidian::standard_cell::PinDirection;

    std::string direction;

    switch (cells.direction(pin)) {
        case PinDirection::INPUT:
            direction = "input";
            break;
        case PinDirection::OUTPUT:
            direction = "ouput";
            break;
        case PinDirection::INOUT:
            direction = "input/output";
            break;
        case PinDirection::NA:
            direction = "N/A";
            break;
    }

    return direction;
}
            
bool isInput(ophidian::circuit::Netlist & netlist, ophidian::circuit::Pin & pin)
{
    std::string pin_name = netlist.name(pin);
    for (auto iter = netlist.begin(ophidian::circuit::Input()); iter != netlist.end(ophidian::circuit::Input()); ++iter) {
        auto input = *iter;
        if (netlist.name(netlist.pin(input)) == pin_name)
            return true;
    }
    return false;
}

bool isOutput(ophidian::circuit::Netlist & netlist, ophidian::circuit::Pin & pin)
{
    std::string pin_name = netlist.name(pin);
    for (auto iter = netlist.begin(ophidian::circuit::Output()); iter != netlist.end(ophidian::circuit::Output()); ++iter) {
        auto output = *iter;
        if (netlist.name(netlist.pin(output)) == pin_name)
            return true;
    }
    return false;
}
