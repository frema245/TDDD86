/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Robot.h"
#include "constants.h"
#include <iostream>

using namespace std;

Robot::Robot() : Unit() {}

Robot::Robot(Unit c) : Unit(c) {}

Robot* Robot::clone() const {
    return new Robot(*this);
}

void Robot::draw(QGraphicsScene *scene) const {

    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));

}

bool Robot::isJunk() const {
    return false;
}
