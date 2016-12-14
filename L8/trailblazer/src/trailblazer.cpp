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
    start->setColor(GREEN); //Visited

    if (start == end) {
        path.push_back(start);
        return true;
    }
    else {
        for (Node* node : graph.getNeighbors(start)) {
            if (!node->visited) {
                if (depthFirstSearch_help(graph,  node, end, path)) {
                    path.push_back(start);
                    return true; // TODO: is it ok to ignore a return?
                }
            }
        }
        start->setColor(GRAY); //Dismissed
        return false;
    }
}

vector<Node*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end)
{
    vector<Node*> path;
    graph.resetData(); //Prev. paths' have to be removed...

    depthFirstSearch_help(graph,  start, end, path);

    reverse(path.begin(), path.end());
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
            reverse(path.begin(), path.end());
            return path;
        }

        NodesToVisit.pop();

        for (Node* node : graph.getNeighbors(current)) {
            if (!node->visited) {
                node->visited = true;
                node->previous = current;
                NodesToVisit.push(node);
                node->setColor(YELLOW); //Processing
            }

        }
    }

    return path;
}

vector<Node *> findCost(BasicGraph& graph, Vertex* start, Vertex* end, bool isAStar) {

    vector<Vertex*> path;
    graph.resetData(); // Important...!!!

    PriorityQueue<Vertex*> openSet; // The set of nodes to be evaluated.

    openSet.enqueue(start, 0.0); //
    start->previous = nullptr; //

    while (!openSet.isEmpty()) { //
        Vertex* current = openSet.dequeue(); //
        current->visited = true; //
        current->setColor(GREEN); //Visited

        if (current == end) { //
            while (current != nullptr) { //
                path.push_back(current); //
                current = current->previous; //
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (Edge* edge : graph.getEdgeSet(current)) { //
            Vertex* neighbour;
            neighbour = edge->finish; //

            if (neighbour->visited) //
                continue;

            bool open = false; // No openSet --> standard

            for (Edge* e : neighbour->arcs) {
                if (e->visited) {
                    open = true; // Access to OpenSet.
                    break;
                }
            }

            edge->visited = true;
            graph.getEdge(neighbour, current)->visited = true; // Visited from both sides.

            double temp_cost = current->cost + edge->cost;

            double variable;
            if (isAStar) {
                variable = temp_cost + neighbour->heuristic(end);
            } else {
                variable = temp_cost;
            }


            if (!open) {
                neighbour->previous = current;
                neighbour->cost = temp_cost;
                openSet.enqueue(neighbour, variable);
                neighbour->setColor(YELLOW); // processed

            } else if (temp_cost < neighbour->cost) {
                neighbour->previous = current;
                neighbour->cost = temp_cost;
                openSet.changePriority(neighbour, variable);
            }
        }
    }
    return path; // Ugh....
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end)
{

    return findCost(graph, start, end, false);

}


vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end)
{

    return findCost(graph, start, end, true);

}
