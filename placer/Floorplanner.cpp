#include "placer/Floorplanner.h"
#include "util/util.h"

Floorplanner::Floorplanner(Design & design) :
    mDesign(design),
    mCoreSite(mDesign.floorplan().find("core"))
{
    mChipArea = floorplanUtil::chipWidth(this->mDesign) * floorplanUtil::chipHeight(this->mDesign);
    mSiteWidth = floorplanUtil::siteWidth(this->mDesign, mCoreSite);
    mSiteHeight = floorplanUtil::siteHeight(this->mDesign, mCoreSite);
    mCellsArea = floorplanUtil::cellsArea(this->mDesign);
}


void Floorplanner::setUtilization(float utilization)
{
    this->mUtilization = utilization;
}


void Floorplanner::setFloorplanRatio(float ratio)
{
    mFloorplanRatio = ratio;
}


void Floorplanner::create()
{
    auto & floorplan = mDesign.floorplan();
    mFloorplanArea = mCellsArea / mUtilization;
    mSiteRatio = mSiteHeight / mSiteWidth;
    mRowRatio = mSiteRatio / mFloorplanRatio;
    mRowCount = ceil(sqrt(mFloorplanArea / (mRowRatio * mSiteHeight * mSiteWidth)));
    mSiteCount = ceil(mRowCount * mRowRatio);

    printVals();
    for (int i = 0; i < mRowCount; ++i) {
        Point rowOrigin = Point(0, mSiteHeight * i);
        floorplan.add(Row(), rowOrigin, mSiteCount, mCoreSite);
    }
}


void Floorplanner::printVals()
{
    printf("chipArea: %.2f\nfpArea: %.2f\nsiteRatio %.2f\nrowRatio: %.2f\nrowCount: %d\n"
           "siteCount: %d\nsiteHeight %.2f\nsiteWidth: %.2f\n"
           "whatever %.2f\ncellsArea %.2f\n",
            mChipArea, mFloorplanArea, mSiteRatio, mRowRatio, mRowCount, mSiteCount, mSiteHeight, mSiteWidth,
            mFloorplanArea / (mRowRatio * mSiteHeight * mSiteWidth), mCellsArea);
 }
