#ifndef UTIL_H
#define UTIL_H
#include <ophidian/design/Design.h>
#include <ophidian/placement/Placement.h>
#include <ophidian/circuit/Netlist.h>
#include <ophidian/geometry/Models.h>
#include <ophidian/placement/Library.h>
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
#endif
