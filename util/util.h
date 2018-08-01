#ifndef UTIL_H
#define UTIL_H
#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/geometry/Models.h>
#include <ophidian/placement/Library.h>
#include <string>
#include <cstdlib>
namespace cellUtil{
    using Design=ophidian::design::Design;
    using Cell=ophidian::circuit::Cell;
    class Height;
    class Width;


    float cellWidth(const Cell &,ophidian::circuit::LibraryMapping &, ophidian::placement::Library &  );
    float cellHeight(const Cell &,ophidian::circuit::LibraryMapping & ,ophidian::placement::Library & );

    ophidian::geometry::Box  cellDim(const Cell &,ophidian::circuit::LibraryMapping &, ophidian::placement::Library &);
};

namespace floorplanUtil {
    using Design = ophidian::design::Design;
    using Point = ophidian::util::LocationDbu;
    using Cell = ophidian::circuit::Cell;
    using Floorplan = ophidian::floorplan::Floorplan;
   using string = std::string;
    using Site = ophidian::floorplan::Site;
    
    Point chipDiemnsions(Design & design);
    Point siteDimensions(Design & design, Site & site);
    float chipHeight(Design & design);
    float chipWidth(Design & design);
    float siteWidth(Design & design, Site & site);
    float siteHeight(Design & design, Site & site);
    float cellsArea(Design & design);
}
#endif
