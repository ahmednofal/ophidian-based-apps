#ifndef FLOOR_PLANNER_H
#define FLOOR_PLANNER_H

#include <ophidian/design/Design.h>

class Floorplanner
{
    using Design=ophidian::design::Design;
    using Point = ophidian::util::LocationDbu;
    using Row = ophidian::floorplan::Row;
    using Site = ophidian::floorplan::Site;

public:
    Floorplanner(Design & design);
    void create();
    void setUtilization(float utilization);
    void setFloorplanRatio(float ratio);

private:
    Design & mDesign;
    Site mCoreSite;
    int mRowCount;
    int mSiteCount;
    float mSiteWidth;
    float mSiteHeight;
    float mSiteRatio;
    float mRowRatio;
    float mChipArea;
    float mFloorplanArea;

    float mUtilization;
    float mFloorplanRatio;
    float mCellsArea;

    void printVals();
};

#endif
