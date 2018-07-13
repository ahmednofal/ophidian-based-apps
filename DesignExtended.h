#ifndef DESIGN_EXTENDED_H
#define DESIGN_EXTENDED_H

#include <ophidian/design/Design.h>

class Placer : public ophidian::design::Design {

    using Cell=ophidian::circuit::Cell;

public:
    Placer();
    ~Placer();

    int cellWidth(const Cell &);
    int cellHeight(const Cell &);
    int dyeWidth();
    int dyeHeight();
};

#endif
