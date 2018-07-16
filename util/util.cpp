#include <util.h>

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

