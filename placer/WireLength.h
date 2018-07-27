#ifndef WIRE_LENGTH_H
#define WIRE_LENGTH_H

#include <ophidian/design/Design.h>
#include <ophidian/interconnection/Flute.h>
#include <ophidian/interconnection/SteinerTree.h>
#include <ophidian/entity_system/EntitySystem.h>
#include <ophidian/entity_system/Aggregation.h>
#include <ophidian/entity_system/Composition.h>
#include <vector>


class WireLength
{
    using Design=ophidian::design::Design;
    using Netlist = ophidian::circuit::Netlist;
    using Cell = ophidian::circuit::Cell;
    using Net = ophidian::circuit::Net;
    using Output = ophidian::circuit::Output;
    using Flute = ophidian::interconnection::Flute;
    using Pin = ophidian::circuit::Pin;
    using Pins = ophidian::entity_system::Association <Net, Pin>::Parts;
    using Point = ophidian::geometry::Point;

    private:
        Design & design;
        Netlist & netlist;
        bool isIO(Pin&);
        std::vector<Point> pinsPositions(Pins&);
        
    public:
        WireLength(ophidian::design::Design & design);
        ~WireLength();
        double estimate();

};

#endif
