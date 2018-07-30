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
#include "placer/Floorplanner.h"
#include "util/util.h"


std::string pinDirection(ophidian::standard_cell::StandardCells &, ophidian::standard_cell::Pin &);
bool isInput(ophidian::circuit::Netlist &, ophidian::circuit::Pin &);
bool isOutput(ophidian::circuit::Netlist &, ophidian::circuit::Pin &);
void rowSites(ophidian::design::Design & design);
void printSites(ophidian::design::Design & design);
void printRows(ophidian::design::Design & design);
int totalCellSites(ophidian::design::Design & design);

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

//    printf("===================\nCELLS\n===================\n");
//    for (auto iter=the_netlist.begin(Cell()); iter != the_netlist.end(Cell()); iter++) {
//        auto cell = *iter;
//        auto std_cell = the_mapping.cellStdCell(cell);
//
//        auto dimensions = the_library.geometry(std_cell);
//        auto pins = the_netlist.pins(cell);
//        auto std_pins = the_cells.pins(std_cell);
//        auto location = the_placement.cellLocation(cell);
//        double pos_x = (double) location.x();
//        double pos_y = (double) location.y();
//
//        printf("Cell: %s Type: %sPos %.2f %.2f \nCell Pins:- \n", the_netlist.name(cell).c_str(), the_cells.name(std_cell).c_str(), pos_x, pos_y);
//        for (auto pin : pins) {
//            auto net = the_netlist.net(pin);
//            cout << "\tpin: " << the_netlist.name(pin) 
//                //<< " type: " << pinDirection(the_cells, pin) 
//                << "\tbelonging to net: " << the_netlist.name(net) << endl;
//        }
//
//        printf("Std Pins:-\n");
//        for (auto pin : std_pins) {
//            printf("\tpin: %s\tdirection: %s\n", the_cells.name(pin).c_str(), pinDirection(the_cells, pin).c_str());
//        }
//
//        auto box = dimensions.begin(); 
//        int width = box->max_corner().x();
//        int height = box->max_corner().y(); 
//        printf("width/height %f, width/height %f\n", (double) width, (double) height);
//
//        printf("\n");
//    } 
//
//    printf("===================\nNETS\n===================\n");
//    for (auto iter = the_netlist.begin(Net()); iter != the_netlist.end(Net()); iter++) {
//        auto net = *iter;
//        
//        std::string name = the_netlist.name(net);
//        auto pins = the_netlist.pins(net);
//
//        printf("NET: %s\n", name.c_str());
//
//        for (auto pin : pins) {
//            std::string pin_name = the_netlist.name(pin);
//            std::string cell_name;
//            
//            if (isInput(the_netlist, pin) || isOutput(the_netlist, pin)) {
//                cell_name = "n/a";
//            }
//            else {
//                auto cell = the_netlist.cell(pin);
//                cell_name = the_netlist.name(cell);
//            }
//
//            printf("\tpin: %10s -> cell %s\n", pin_name.c_str(), cell_name.c_str());
//        }
//    }
//    
//    printf("===================\nI/O\n===================\nInput:-");
//    for (auto iter = the_netlist.begin(ophidian::circuit::Input()); iter != the_netlist.end(ophidian::circuit::Input()); iter++) {
//        auto input = *iter;
//
//        printf("\tpin: %s\n", the_netlist.name(the_netlist.pin(input)).c_str());
//    }
//
//    printf("Output:-\n");
//    for (auto iter = the_netlist.begin(ophidian::circuit::Output()); iter != the_netlist.end(ophidian::circuit::Output()); iter++) {
//        auto output = *iter;
//
//        printf("\tpin: %s\n", the_netlist.name(the_netlist.pin(output)).c_str());
//    }
//
//    printf("===================\nFLOORPLAN\n===================\n");
//    printf("Dye:-\n\torigin: %.3f %.3f\n", (double) the_floorplan.chipOrigin().x(), (double) the_floorplan.chipOrigin().y());
//    printf("\tupper right corner: %.3f %.3f\n", (double) the_floorplan.chipUpperRightCorner().x(), (double) the_floorplan.chipUpperRightCorner().y());
//    for (auto row : the_floorplan.rowsRange()) {
//        printf("\t row has %d sites\n", (int) the_floorplan.numberOfSites(row));
//    }
//
//    printf("Sites:-\n");
//    for (auto site : the_floorplan.sitesRange()) {
//        auto position = the_floorplan.siteUpperRightCorner(site);
//        auto name = the_floorplan.name(site);
//
//        printf("\t site: %s size: %.3f %.3f\n", name.c_str(), (double) position.x(), (double) position.y());
//    }

//    rowSites(myDesign);
//    printRows(myDesign);
    Floorplanner floorplanner(myDesign);
    floorplanner.setUtilization(0.8);
    floorplanner.setFloorplanRatio(1.0);
    floorplanner.create();
    
    printRows(myDesign);
    printf("total cellSites %d\n", totalCellSites(myDesign));
//    the_netlist.add(ophidian::circuit::Cell(), "hello");
//    the_netlist.add(ophidian::circuit::Pin(), "you");
//    the_floorplan.add(ophidian::floorplan::Site(), "eeee", ophidian::util::LocationDbu(10.0, 10.0));
//    the_floorplan.add(ophidian::floorplan::Row(), ophidian::util::LocationDbu(40.0, 0.0), 20, the_floorplan.find("core"));
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


// useless for now
void rowSites(ophidian::design::Design & design)
{
    auto & placement = design.placement();
    auto & netlist = design.netlist();
    
    auto cellIter = netlist.begin(ophidian::circuit::Cell());

    int rowNumber = 0;
    double sites = 0;
    double width = 0;
    double siteWidth = 160;
    double rowPosition = (double) placement.cellLocation(*cellIter).y();
    width += cellUtil::cellWidth(*cellIter, design.libraryMapping(), design.library());
    cellIter++;

    while (cellIter != netlist.end(ophidian::circuit::Cell()))
    {
        width += cellUtil::cellWidth(*cellIter, design.libraryMapping(), design.library());
        double newRowPosition = (double) placement.cellLocation(*cellIter).y();
        if (newRowPosition != rowPosition) {
            rowPosition = newRowPosition;
            sites = ceil((double)placement.cellLocation(*cellIter).x() + cellUtil::cellWidth(*cellIter, design.libraryMapping(), design.library()) / siteWidth);
            printf("Row %d sites %.2f width %.2f\n", rowNumber, sites, width);
            rowNumber++;
            width = 0;
        }
        cellIter++;
    }
}


int totalCellSites(ophidian::design::Design & design)
{
    int cellSites = 0;
    auto & netlist = design.netlist();

    for (auto cellIter = netlist.begin(ophidian::circuit::Cell()); cellIter != netlist.end(ophidian::circuit::Cell()); cellIter++)
        cellSites += ceil(cellUtil::cellWidth(*cellIter, design.libraryMapping(), design.library()) / 160);

    return cellSites;
}


void printSites(ophidian::design::Design & design)
{
    printf("===================\nSITES\n===================\n");
    using string = std::string;
    auto floorplan = design.floorplan();

    for (auto siteIter = floorplan.sitesRange().begin(); siteIter != floorplan.sitesRange().end(); siteIter++) {
        auto site = *siteIter;
        string siteName = floorplan.name(site);
        double width = (double) floorplan.siteUpperRightCorner(site).x();
        double height = (double) floorplan.siteUpperRightCorner(site).y();
        printf("site %s %.2f x %.2f\n", siteName.c_str(), width, height);
    }
}


void printRows(ophidian::design::Design & design)
{
    auto floorplan = design.floorplan();

    int n = 0;
    for (auto rowIter = floorplan.rowsRange().begin(); rowIter != floorplan.rowsRange().end(); rowIter++) {
        auto row = *rowIter;
        double row_y = (double) floorplan.origin(row).y();
        double row_x = (double) floorplan.origin(row).x();
        int no_of_sites = floorplan.numberOfSites(row);

        printf("row %d contains %d sites @ (%.2f, %.2f)\n", n, no_of_sites, row_x, row_y);
        n++;
    }
}
