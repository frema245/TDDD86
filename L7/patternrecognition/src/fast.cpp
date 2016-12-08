/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <map>
#include "Point.h"
#include <limits>
using namespace std;

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input12800.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("FAST Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();


    // This is our loop
    vector<pair<double, Point>> slopeVector;

    //Iterates over every point exept the last 3
    for (int i = 0; i < N-3; i++) {
        slopeVector.clear();
        Point origo = points.at(i);
        for (int j = 0; j < N; j++) {
            Point endpoint = points.at(j);
            double slope = origo.slopeTo(endpoint);
            slopeVector.push_back(pair<double, Point>(slope, endpoint));
        }

        // Sorts our vector so that the slopes accend.
        sort(slopeVector.begin(), slopeVector.end());

        // Iterates over the slopes and renders line when there are 4 or more points in a straight line.
        double prev;
        int count = 1;
        for (int e = 0; e < slopeVector.size(); e++) {

            if (slopeVector[e].first == prev) {
                count++;
            } else {
                if (count > 2) {
                    render_line(scene, origo, slopeVector[e-1].second);
                    a.processEvents();
                }
                prev = slopeVector[e].first;
                count = 1;
            }
        }

        if (count > 2) {
            render_line(scene, origo, slopeVector.back().second);
            a.processEvents();
        }

    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
