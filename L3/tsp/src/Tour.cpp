#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

}

// Destruktor uppdaterad igen! :) :)
Tour::~Tour()
{
    if (m_front != nullptr) {
        Node* current = m_front;
        do {
            delete current;
            current = current->next;
        } while (current != m_front);
    }
}

void Tour::show() const
{
    if (m_front != nullptr) {
        Node* current = m_front;
        do {
            std::cout << current->point << std::endl;
            current = current->next;
        } while (current != m_front);
    }
}

void Tour::draw(QGraphicsScene *scene) const
{
    if (m_front != nullptr) {
        Node* current = m_front;
        do {
            current->point.drawTo(current->next->point, scene);
            current = current->next;
        } while (current != m_front);
    }
}

int Tour::size() const
{

    int size = 0;
    if (m_front != nullptr) {
        Node* current = m_front;
        do {
            size++;
            current = current->next;
        } while (current != m_front);
    }
    return size;

}

double Tour::distance() const
{
    double distance = 0;
    if (m_front != nullptr) {
        Node* current = m_front;
        do {
            distance += current->point.distanceTo(current->next->point);
            current = current->next;
        } while (current != m_front);
    }
    return distance;
}

void Tour::insertNearest(Point p)
{

    if (m_front == nullptr) {
        Node* first = new Node(p,nullptr);
        first->next = first;
        m_front = first;
    }

    else if (m_front != nullptr) {
        Node* current = m_front;
        Node* nearest = m_front;
        do {
            if (current->point.distanceTo(p) < nearest->point.distanceTo(p)) {
                nearest = current;
            }
            current = current->next;
        } while (current != m_front);

        Node* next = nearest->next;
        nearest->next = new Node(p,next);
    }
}

void Tour::insertSmallest(Point p)
{

    if (m_front == nullptr) {
        Node* first = new Node(p,nullptr);
        first->next = first;
        m_front = first;
    }

    else if (m_front != nullptr) {
        Node* current = m_front;
        Node* nearest = m_front;
        do {

            double cdist = (current->point.distanceTo(p) + current->next->point.distanceTo(p) - current->point.distanceTo(current->next->point));
            double ndist = (nearest->point.distanceTo(p) + nearest->next->point.distanceTo(p) - nearest->point.distanceTo(nearest->next->point));

            if (cdist < ndist)
            {
                nearest = current;
            }
            current = current->next;
        } while (current != m_front);

        Node* next = nearest->next;
        nearest->next = new Node(p,next);
    }
}
