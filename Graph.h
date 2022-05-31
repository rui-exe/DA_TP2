#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include "minHeap.h"

using namespace std;

typedef struct{
    int capacity;
    int stops;
}capacity_stops;


class Graph {

public:

    struct Edge {
        int dest;   // Destination node // A double weight
        int flow;
        int capacity;
        int duration;
        int es;
        int ef;
        int fs;
        Edge* symmetric_edge;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;
        int unweighted_distance;
        int pred;
        int dist;
        int pred_d;
        int peopleInGroup;
        int es;
        int lf;
        int in_degree;
        int out_degree;
        int num_edges;
        Edge* incoming_edge;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented


    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capacity,int duration=0);
    void bfs(int v);
    void bfs2(int v);
    void print_path(pair<list<int>,int> group);

    int edmonds_karp(int src, int sink);


    int update_flows(int src,int sink);
    int dijkstra(int a, int b);
    list<int> dijkstra_path(int a, int b);
    /**
     * Function that invokes the bfs function and returns the best path with less stops made from node a to b.
     * @param a int representing the starting node we want to calculate the best path from
     * @param b int representing the final node we want to calculate the best path to
     * @return list of integers that represent the best path from node a to node b
     */
    list<int> unweighted_path(int a,int b);
    int criticalPath();
    void putInfoOnEdges();
    pair<int,list<int>> getMaxWaitingTime();
};

#endif
