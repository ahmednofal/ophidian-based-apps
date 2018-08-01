#ifndef FLOOR_PLAN_H
#define FLOOR_PLAN_H

#include <ophidian/design/Design.h>

class Floorplan
{
    using Design=ophidian::design::Design;
    using Point = ophidian::util::LocationDbu;
    using Row = ophidian::floorplan::Row;
    using Site = ophidian::floorplan::Site;

public:
    Floorplan(Design & design);
    void create();
    void setUtilization(int utilization);
    void setFloorplanRatio(double ratio);

private:
    Design & design;
    Site coreSite;
    int rowCount;
    int siteCount;
    float siteWidth;
    float siteHeight;
    float siteRatio;
    float rowRatio;
    float chipArea;
    float floorplanArea;

    float utilization;
    float floorplanRatio;
    float cellsArea;
};

#endif
