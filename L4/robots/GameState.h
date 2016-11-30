/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 * Method isSafe() is used to keep Hero from moving stupidly.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"

class GameState {
public:


    /*
     * Creates a new GameState object with standard amount of robots
     */
    GameState();

    /*
     * Creates a new GameState object with the prefered number of Robots. Creates new robot objects with a random location, and tries again if the location is not empty.
     */
    GameState(int numberOfRobots);

    /*
     * Makes copy of a GameState object. Copies hero and duplicates all robot objects
     */
    GameState(const GameState& other);

    GameState& operator= (const GameState& other);
    ~GameState();

    /*
     * Clear and redraw entire playing field
     */
    void draw(QGraphicsScene* scene) const;	// Clear and redraw entire playing field

    /*
     * Teleport hero to random location
     */
    void teleportHero();

    /*
     * Move robots one step towards hero
     */
    void moveRobots();

    /* Count colliding robots
     * Also converts robots to junk while
     * checking collisions
     */
    int countCollisions ();

    /*
     * Check if any robots are left on playing field
     */
    bool anyRobotsLeft () const;

    /*
     * Is hero in same place as robot or junk?
     */
    bool heroDead() const;

    /*
     * Can unit safely reside here?
     */
    bool isSafe (const Unit& unit) const; // Can unit safely reside here?

    /*
     * Move hero towards dir
     */
    void moveHeroTowards (const Unit& dir);

    /*
     * Return hero
     */
    Hero getHero () const;

private:
    std::vector<Robot*> robots;  // the robots


    //std::vector<Junk> junks;    // robots that have turned to junk


    Hero hero;                  // the hero

    // private helpers

    /*
     * Helper function to copy constructor and operator=
     */

    void copyOther(const GameState &other);

    /*
     * Takes the location of a unit, and returns true if it is free from robots
     */
    bool isEmpty(const Unit& unit) const;

    /*
     * Counts the robots at the location of a input unit
     */
    int countRobotsAt(const Unit& unit) const;

};

#endif // GAMESTATE_H
