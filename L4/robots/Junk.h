/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H



//#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(Robot c);

    virtual Junk* clone() const;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const override;

    virtual void moveTowards(const Unit &u);

    virtual bool attacks(const Unit &u) const;

    virtual bool isJunk() const override;
};

#endif // JUNK_H
