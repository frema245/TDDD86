/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

using namespace std;

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {

        Robot* robot = new Robot();

        while (!isEmpty (*robot)) {
            delete robot;
            robot = new Robot();
        }

        robots.push_back(robot);
    }
    teleportHero();
}

GameState::GameState(const GameState& other) {
   copyOther(other);
}

GameState::~GameState() {
    for (auto robot : robots) {
            delete robot;
    }
}

void GameState::copyOther(const GameState &other) {
    hero = other.hero;
    for (auto robot : other.robots) {
        robots.push_back(robot->clone());
    }
}

GameState& GameState::operator= (const GameState& other) {
    if (this != &other) {
        for (auto robot : robots) {
            delete robot;
        }
        robots.clear();
        copyOther(other);
    }
    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards (hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {

        bool collision = (countRobotsAt(*robots[i]) > 1);

        if (collision && (!robots[i]->isJunk())) {
            delete robots[i];
            robots[i] = new Junk(*robots[i]);
            numberDestroyed++;
        }
        i++;
    }

    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (int i = 0; i < robots.size(); i++) {
        if (!robots[i]->isJunk()) {
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++) {
        if (robots[i]->attacks(unit)) return false;
        if (!isEmpty(unit)) return false;
    }
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}


bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);
}

int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
