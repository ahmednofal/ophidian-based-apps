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

        for (auto pin : pins) {
            auto net = the_netlist.net(pin);
            cout << "pin: " << the_netlist.name(pin) << " " << the_netlist.name(net) << endl;
        }

        for (auto box : dimensions) {
            cout << the_netlist.name(cell) << " " << the_cells.name(std_cell) << " " << box.min_corner().x() << " " << box.max_corner().x() << endl;
        }
     } 
    return 0;
}


