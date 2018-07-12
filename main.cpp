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

    
    //the_placement.
    //Cell x; 
    //Net y;
    //cout  << "Cell x" << &x << endl;
    //Still exploring the framework ...
    //We need to traverse the cells in the netlist
    //We need to traverse the nets in the netlist
    //We need to traverse the pins in the netlist 
    //All will be done using the same syntax below 
    // For the cell location acquisitionwe will be using the placement entity's member function cellLocation
    // To set the cell location we will be using the placeCell member function of the placement entity class
    // Need to import the util::locationDbu class for locations, it has x and y class member getter functions x(),y()

    for (auto iter=the_netlist.begin(Cell()); iter != the_netlist.end(Cell()); iter++) {
        auto cell = *iter;
        auto std_cell = the_mapping.cellStdCell(cell);
        auto dimensions = the_library.geometry(std_cell);
        for (auto box : dimensions) {
            cout << the_netlist.name(*iter) << " " << the_cells.name(std_cell) << " " << box.min_corner().x() << " " << box.max_corner().x() << endl;
        }
     } 

    //for (auto iter = the_netlist.begin(x); iter !=  the_netlist.end(x); iter++ )
    //{
    //    
    //    cout << "theanet reference : " << &iter << "the_netlist begin" << &the_netlist.begin(x)<<"the_netlist end" << &the_netlist.end(x)<< endl;
    //}
    //cout << "number is " << the_cells.size(x) << endl;

    /* for (auto iter : the_floorplan.sitesRange()) */
    /* { */

    /* } */
    return 0;
}
