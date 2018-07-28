#include "placer/WireLength.h"

WireLength::WireLength(ophidian::design::Design & design) :
    design(design),
    netlist(design.netlist())
{
}

double WireLength::estimate()
{
    double total = 0;
    auto & treeCreator = Flute::instance();

    for (auto netIter = netlist.begin(Net()); netIter != netlist.end(Net()); netIter++) {
        auto pins = netlist.pins(*netIter);
        auto locations = pinsPositions(pins);
        auto tree = treeCreator.create<std::vector<Point>>(locations);                      // maybe save them for later use
        total += tree->length();
    }

    return total;
}


bool WireLength::isIO(Pin & pin)
{
    using Input = ophidian::circuit::Input;
    using Output = ophidian::circuit::Output;

    return (netlist.input(pin) == Input() && netlist.output(pin) == Output());
}


std::vector<WireLength::Point> WireLength::pinsPositions(Pins & pins)
{
    auto placement = design.placement();
    std::vector<WireLength::Point> positions;
    for (auto pin : pins) {
        if (!isIO(pin)) {
            auto cell = netlist.cell(pin);
            auto cellPosition = placement.cellLocation(cell);
            auto point = Point((double) cellPosition.x(), (double) cellPosition.y());
            positions.push_back(point);
        }
    }
    return positions;
}


WireLength::~WireLength()
{
}
