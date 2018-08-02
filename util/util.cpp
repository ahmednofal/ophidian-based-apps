#include "util/util.h"
#include <iostream>
using string = std::string;

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


string header(string title)
{
    string hashs = "############################";
    return hashs + "\n " + title + "\n" + hashs + "\n";
}


string designUtil::reportRows(Design & design)
{
    auto floorplan = design.floorplan();
    
    bool isEven = true;
    int rowNumber = 0;
    string report = "";
    auto site = floorplan.find("core");
    int siteWidth = floorplanUtil::siteWidth(design, site);

    report += header("ROWS");
    for (auto row : floorplan.rowsRange()) {
       auto sitesInRow = floorplan.numberOfSites(row); 
       auto origin = floorplan.origin(row);
       string orinetation = (isEven) ? "N" : "FS";

       report += "ROW ROW_" + std::to_string(rowNumber) + " core " + std::to_string((int) origin.x()) 
           + " " + std::to_string((int) origin.y()) + " " + orinetation + " DO " 
           + std::to_string(sitesInRow) + " BY 1 STEP " + std::to_string(siteWidth) + " 0;\n";

       rowNumber += 1;
       isEven = !isEven;
    }

    return report;
}
