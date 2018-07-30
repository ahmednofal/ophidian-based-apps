#include "util/util.h"

float cellUtil::cellWidth(const Cell & cell,ophidian::circuit::LibraryMapping & libraryMapping,ophidian::placement::Library & library)
{
    auto box = cellUtil::cellDim(cell, libraryMapping, library);
    return abs(box.min_corner().x() - box.max_corner().x());
}

float cellUtil::cellHeight(const Cell & cell,ophidian::circuit::LibraryMapping & libraryMapping,ophidian::placement::Library & library)
{
    auto box = cellUtil::cellDim(cell, libraryMapping, library);
    return abs(box.min_corner().y() - box.max_corner().y());
}

ophidian::geometry::Box cellUtil::cellDim(const Cell & cell,ophidian::circuit::LibraryMapping & libraryMapping, ophidian::placement::Library & library)
{
    auto stdCell = libraryMapping.cellStdCell(cell);
    auto dimensions = library.geometry(stdCell);
    return *(dimensions.begin());
}


float floorplanUtil::chipWidth(Design & design)
{
    return (float) floorplanUtil::chipDiemnsions(design).x();
}


float floorplanUtil::chipHeight(Design & design)
{
    return (float) floorplanUtil::chipDiemnsions(design).y();
}


floorplanUtil::Point floorplanUtil::chipDiemnsions(Design & design)
{
    auto floorplan = design.floorplan();
    Point dimensions_max = floorplan.chipUpperRightCorner();
    Point dimensions_min = floorplan.chipOrigin();
    return Point(dimensions_max.x() - dimensions_min.x(), dimensions_max.y() - dimensions_min.y());
}


float floorplanUtil::cellsArea(Design & design)
{
    auto & netlist = design.netlist();
    float area = 0;

    for (auto cellIter = netlist.begin(Cell()); cellIter != netlist.end(Cell()); cellIter++)
    {
        auto cellWidth = cellUtil::cellWidth(*cellIter, design.libraryMapping(), design.library());
        auto cellHeight = cellUtil::cellHeight(*cellIter, design.libraryMapping(), design.library());
        area += cellHeight * cellWidth;
    }

    return area;
}


float floorplanUtil::siteWidth(Design & design, Site & site)
{
    return (float) floorplanUtil::siteDimensions(design, site).x();
}


float floorplanUtil::siteHeight(Design & design, Site & site)
{
    return (float) floorplanUtil::siteDimensions(design, site).y();
}


floorplanUtil::Point floorplanUtil::siteDimensions(Design & design, Site & site)
{
    Floorplan & floorplan = design.floorplan();
    return floorplan.siteUpperRightCorner(site);
}
