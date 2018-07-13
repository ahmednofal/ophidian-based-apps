#ifndef DESIGN_EXTENDED_H
#define DESIGN_EXTENDED_H

#include <ophidian/design/Design.h>

class DesignExtended : public ophidian::design::Design {

    using Cell=ophidian::circuit::Cell;

public:
    DesignExtended();
    ~DesignExtended();

    int cellWidth(const Cell &);
    int cellHeight(const Cell &);
    int dyeWidth();
    int dyeHeight();
};

#endif
