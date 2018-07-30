#include "placer/Floorplan.h"
#include "util/util.h"

Floorplan::Floorplan(Design & design) :
    design(design),
    coreSite(design.floorplan().find("core"))
{
    chipArea = floorplanUtil::chipWidth(this->design) * floorplanUtil::chipHeight(this->design);
    siteWidth = floorplanUtil::siteWidth(this->design);
    siteHeight = floorplanUtil::siteHeight(this->design);
    cellsArea = floorplanUtil::cellsArea(this->design);
}


void Floorplan::setUtilization(int utilization)
{
    this->utilization = utilization;
}


void Floorplan::setFloorplanRatio(double ratio)
{
    floorplanRatio = ratio;
}


void Floorplan::create()
{
    auto floorplan = design.floorplan();
    floorplanArea = (int) chipArea / utilization;
    siteRatio = siteHeight / siteWidth;
    rowRatio = siteRatio / floorplanRatio;
    rowCount = ceil(sqrt(floorplanArea / (rowRatio * siteHeight * siteWidth)));
    siteCount = ceil(rowCount * rowRatio);

    for (int i = 0; i < rowCount; ++i) {
        Point rowOrigin = Point(0, siteHeight * i);
        floorplan.add(Row(), rowOrigin, siteCount, coreSite);
    }
}
