#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    Tour();
    ~Tour();
    void show() const;
    void draw(QGraphicsScene* scene) const;
    int size() const;
    double distance() const;
    void insertNearest(const Point p);
    void insertSmallest(const Point p);

private:
    Node* m_front = nullptr;
};

#endif // TOUR_H
