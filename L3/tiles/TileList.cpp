#include "TileList.h"

TileList::TileList() {}

TileList::~TileList()
{
    delete[] m_tiles;
}

void TileList::addTile(Tile tile)
{
    checkResize();
    m_tiles[m_size] = tile;
    m_size++;
}

void TileList::drawAll(QGraphicsScene* scene) const
{
    for (int i = 0; i < m_size; i++) {
        m_tiles[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y) const
{
    int topTile = -1;

    for (int i = 0; i < m_size; i++) {

        if (m_tiles[i].contains(x,y)) {
            topTile = i;
        }
    }

    return topTile;
}

void TileList::raise(int x, int y)
{
    int index = indexOfTopTile(x,y);

    if (isRealIndex(x,y)) {
        Tile const raiseTile = m_tiles[index];
        remove(x,y);
        addTile(raiseTile);
    }
}

void TileList::lower(int x, int y)
{
    int index = indexOfTopTile(x,y);

    if (isRealIndex(x,y)) {
        Tile const lowerTile = m_tiles[index];
        remove(x,y);

        for (int i = m_size; i > 0; i--) {
                m_tiles[i] = m_tiles[i - 1];
            }
            m_tiles[0] = lowerTile;
            m_size++;
    }
}

void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x,y);

    if (index != -1) {

        for (int i = index; i < m_size; i++) {
            m_tiles[i] = m_tiles[i + 1];
        }
        m_size--;
    }
}

void TileList::removeAll(int x, int y)
{
    while(isRealIndex(x,y)) {
        remove(x,y);
    }
}

void TileList::checkResize() {
    if (m_size == m_capacity) {
        // out of space; resize
        Tile* DoubleCapacity = new Tile[m_capacity * 2];
        for (int i = 0; i < m_size; i++) {
            DoubleCapacity[i] = m_tiles[i];
        }
        delete[] m_tiles;   // free old array's memory
        m_tiles = DoubleCapacity;
        m_capacity *= 2;
    }
}

bool TileList::isRealIndex(int x,int y) const {
    {
        int index = indexOfTopTile(x,y);
        return (index != -1);
    }
}

