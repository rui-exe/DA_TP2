#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <map>
#include <unordered_set>
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
        vector<int> predNodes;
        int es;
        int in_degree;
        int real_node;
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

    void addEdgev2(int src, int dest, int capacity,int duration=0);
    /**
     * Traverses the nodes until it finds the target node v
     * Time Complexity T(V,E) = O(V+E)
     * @param v target node, the function will end when this node is visited
     */
    void bfs(int v);
    /**
     * Simple alterations to the normal bfs
     * Traverses the nodes until it finds the target node v
     * Time Complexity T(V,E) = O(V+E)
     * @param v target node, the function will end when this node is visited
     */
    void bfs2(int v);
    void bfs3(int v);
    /**
     * Prints the path of a group that passes through the nodes in the list that is contained
     * on "key" of the pair
     * Time Complexity : O(n)= NrElementsInPair * Edges
     * @param group pair containing the path of a group as it's "key"
     * @param trg target node where all the groups are destined to arrive
     * and the number of the group as it's value
     */
    void print_path(pair<list<int>,int> group,int trg);
    /**
     * Algorithm that solves the max flow problem for groups that can separate from each other
     * It calculates the flow for all of edges of the augmenting paths that connect the src to the sink
     * Time Complexity: T(V,E) = O(V*E²)
     * @param src initial node where all the groups depart
     * @param sink target node where all the groups are destined to arrive
     * @return Integer indicating the max flow which will be a sum of all the groups dimension that arrive at the sink
     */
    int edmonds_karp(int src, int sink);
    /**
     * Creates a new graph containing n*(maxEdges+1) nodes, where n is the number of nodes of the original graph
     * Time Complexity: T(E,B) = O(E*B), where B is the number of the minimum transshipment's needed
     * to obtain the max flow in the original graph
     * @param maxEdges number of the minimum transshipment's needed to obtain the max flow in the original graph
     * Groups aren't allowed to be separated
     * @return returns the new graph that was created
     */
    Graph createRestrictedGraph(int maxEdges);
    /**
     * Function that prints all the pareto optimal alternatives for scenario 1.2.
     * TimeComplexity T(V,E,B) = O(E*B*log(B*V))
     */
    void showParetoOptimalPaths(int src, int trg);
    /**
     * Function that is needed for Edmonds-Karp Algorithm
     * It updates the flow of the edges of all augmenting paths until no other augmenting path exists
     * TimeComplexity (V,E) = V+E
     * @param src source node
     * @param sink  target node (sink)
     * @return returns the bottleneck flow for each augmenting path
     */
    int update_flows(int src,int sink);

    /**
     * version of dijkstra's algorithm that is needed for scenario 1.2 when we create the restricted graph
     * it calculates the max flow for each node of that graph and also the edges needed to get there.
     * TimeComplexity(V,E) = E*log(V)
     * @param a
     */
    void dijkstra2(int a);

    /**
     * calculates the path from node a to b, using the field predNods of a node which is calculated by dijkstra 2
     * TimeComplexity(V) = V , in the worst case
     * @param a source node
     * @param b target node
     * @return vector with lists containing the ordered paths that one would need to do to arrive at target node, with the max flow
     */
    vector<list<int>> dijkstra_paths2(int a,int b);
    /**
     * Normal version of dijkstra, that was modified in order to return the max distance to the target node
     * which gives us the max flow from source to the target
     * TimeComplexity(V,E) = E*log(V)
     * @param a source node
     * @param b target node
     * @return max flow from a to b without the group being able to separate
     */
    int dijkstra(int a, int b);
    /**
     * Calculates the path from node a to b, using the field pred_d of a node which is calculated by dijkstra
     * * TimeComplexity(V) = V , in the worst case
     * @param a source node
     * @param b target node
     * @return list containing the ordered path that one would need to do to arrive at target node, with the max flow
     */
    list<int> dijkstra_path(int a, int b);
    /**
     *Traverses the graph in topological order, calculate the earliest start for each activity and places it
     * on each node.
     * TimeComplexity T(V,E) = O(V+E)
     * Then it using that calculates the minimum duration for all the groups to traverse the graph
     * @return minimum duration for all the groups to traverse the graph
     */
    int criticalPath();
    /**
     * TimeComplexity T(V,E) = O(V+E)
     * Places on the edges the information such as the earliest start and earliest finish on the edges
     * instead of being on the nodes. It facilitates all the calculations we will to do in the future
     * It also calculates the free slack for each edge.
     */
    void putInfoOnEdges();
    /**
     *It traverses all edges and finds the ones with the biggest free slack, which means that the target node
     * of those edges will be the nodes where the group will have to wait the maximum amount of time for another group
     * TimeComplexity T(E) = O(E)
     * @return pair containing the max waiting time as its key and the nodes where that time is waited as it's value
     */
    pair<int,list<int>> getMaxWaitingTime();
    /**
     * Corrects the path by simply adding the extra capacity to the node 0, which is our source.
     * @param src source node
     * @param trg target node (sink)
     * @param extra extra capacity to be added
     * @return
     */
    int correctRoute(int src,int trg,int extra);

    vector<list<int>> dijkstra_paths_backtrack(int a,int b,int bottleneck,int maxEdges,int nrEdges=0);
};

#endif
