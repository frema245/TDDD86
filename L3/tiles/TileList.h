#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    TileList();
    ~TileList();
    void addTile(const Tile tile); // Adds given tile to m_tiles
    void drawAll(QGraphicsScene* scene) const; // Draws all Tile objects in m_tiles in accending order
    void lower(const int x, const int y); // Moves the top tile coresponding to input coordinates to pos 0 in m_tiles
    void raise(const int x, const int y); // Moves the top tile coresponding to input coordinates to last pos in m_tiles
    void remove(const int x, const int y); // Removes the top tile coresponding to input coordinates.
    void removeAll(const int x, const int y); // Removes all tiles coresponding to input coordinates.

private:
    int m_size = 0;
    int m_capacity = 60;
    Tile* m_tiles = new Tile[m_capacity];
    bool isRealIndex(const int x,const int y) const; // Checks if index of top tile at pos (x,y) is not equals -1
    void checkResize(); // Checks if the m_tiles is full. If so, the size doubles.
    int indexOfTopTile(const int x, const int y) const; // Returns the index of the last Tile in m_tiles that corresponds to input coordinates
};

#endif // TILELIST_H
