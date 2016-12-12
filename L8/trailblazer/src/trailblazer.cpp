// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <set>
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Vertex*> depthHelp(BasicGraph& graph, Node* node, Vertex* end, vector<Vertex*> path);

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    vector<Vertex*> build;

    path = depthHelp(graph, start, end, build);

    return path;
}

vector<Vertex*> depthHelp(BasicGraph& graph, Node* node, Vertex* end, vector<Vertex*> build ) {

    node->visited = true;
    build.push_back(node);

    for (Arc* arc: node->arcs) {
        Node* current = arc->finish;

        if (current == end) {
            cout << "CAAAAT" << endl;
            build.push_back(current);
            return build;

        } else if (!current->visited) {
            return depthHelp(graph, current, end, build);
        }
    }

    build.pop_back();

}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
