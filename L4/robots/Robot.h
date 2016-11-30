/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();
    Robot(Unit c);
    virtual Robot* clone() const;

    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const;

    /*
     * Checks if this robot is actually a junk object that inherits from robot. Returns true if so.
     */
    virtual bool isJunk() const;
};

#endif // ROBOT_H
