// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <set>
#include <queue>
#include <pqueue.h>
#include <algorithm>

using namespace std;

bool depthFirstSearch_help(BasicGraph& graph, Vertex* start, Vertex* end, vector<Node*>& path)
{
    start->visited = true;
    start->setColor(GREEN);

    if (start == end) {
        path.push_back(start);
        return true;
    }
    else {
        for (Node* node : graph.getNeighbors(start)) {
            if (!node->visited) {
                if (depthFirstSearch_help(graph,  node, end, path)) {
                    path.push_back(start);
                    return true; // is it ok to ignore a return?
                }
            }
        }
        start->setColor(RED); //Dismissed
        return false;
    }
}

vector<Node*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    vector<Node*> path;
    graph.resetData(); //Prev. paths' have to be removed...
    depthFirstSearch_help(graph,  start, end, path);
    return path;
}


vector<Node*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    vector<Vertex*> path;
    graph.resetData(); //still important...
    queue<Node*> NodesToVisit;
    NodesToVisit.push(start);

    while (!NodesToVisit.empty()) {
        Vertex* current = NodesToVisit.front();
        current->visited = true;
        current->setColor(GREEN); //Visited

        if (current == end) {
            while (current != nullptr) {
                path.push_back(current);
                current = current->previous;
            }
            return path;
        }

        NodesToVisit.pop();

        for (Node* node : graph.getNeighbors(current)) {
            if (!node->visited) {
                node->previous = current;
                NodesToVisit.push(node);
                node->setColor(YELLOW); //Processing
            }

        }
    }
    return path;
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end)
{
    vector<Vertex*> path;
    graph.resetData();
    PriorityQueue<Vertex*> openset; // The set of nodes to be evaluated, starting with our location
    openset.enqueue(start, 0.0);
    start->previous = nullptr;

    while (!openset.isEmpty()) { // While we havnt check all possible paths
        Vertex* current = openset.dequeue();
        current->visited = true;
        current->setColor(GREEN); //Visited

        if (current == end) {
            while (current != nullptr) {
                path.push_back(current);
                current = current->previous;
            }
            return path;
        }

        for (Edge* edge : graph.getEdgeSet(current)) {
            Vertex* neighbour;
            neighbour = edge->finish;

            if (neighbour->visited)
                continue;

            bool open = false;

            for (Edge* e : neighbour->arcs) {
                if (e->visited) {
                    open = true;
                    break;
                }
            }

            edge->visited = true;
            graph.getEdge(neighbour, current)->visited = true; // from the other side as well.

            double temp_cost = current->cost + edge->cost;

            if (!open) {
                neighbour->previous = current;
                neighbour->cost = temp_cost;
                openset.enqueue(neighbour, temp_cost);
                neighbour->setColor(YELLOW);

            } else if (temp_cost < neighbour->cost) {
                neighbour->previous = current;
                neighbour->cost = temp_cost;
                openset.changePriority(neighbour, temp_cost);
            }
        }
    }
    return path;
}


vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end)
{
    graph.resetData(); // Important...!!!
    vector<Vertex*> path;
    PriorityQueue<Vertex*> openset; // The set of nodes to be evaluated.

    openset.enqueue(start, 0.0);
    start->previous = nullptr;

    while (!openset.isEmpty()) {
        Vertex* current = openset.dequeue();
        current->visited = true;
        current->setColor(GREEN); //Visited

        if (current == end) {
            while (current != nullptr) {
                path.push_back(current);
                current = current->previous;
            }
            return path;
        }

        for (Edge* edge : graph.getEdgeSet(current)) {
            Vertex* neighbour;
            neighbour = edge->finish;

            if (neighbour->visited)
                continue;

            bool open = false;

            for (Edge* e : neighbour->arcs) {
                if (e->visited) {
                    open = true;
                    break;
                }
            }

            edge->visited = true;
            graph.getEdge(neighbour, current)->visited = true; // Visited from both sides.

            double temp_cost = current->cost + edge->cost;
            double priority_cost = temp_cost + neighbour->heuristic(end);

            if (!open) {
                neighbour->previous = current;
                neighbour->cost = temp_cost;
                openset.enqueue(neighbour, priority_cost);
                neighbour->setColor(YELLOW);

            } else if (temp_cost < neighbour->cost) {
                neighbour->previous = current;
                neighbour->cost = temp_cost;
                openset.changePriority(neighbour, priority_cost);
            }
        }
    }
    return path;
}
