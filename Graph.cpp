//
// Created by pedro on 22-05-2022.
//

#include "Graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int capacity,int duration) {
    if (src<1 || src>n || dest<1 || dest>n) return ;
    Edge e2({src,0,0,duration});
    nodes[dest].adj.push_back(e2);
    Edge e1({dest,0,capacity,duration});
    e1.symmetric_edge = &nodes[dest].adj[nodes[dest].adj.size()-1];
    nodes[src].adj.push_back(e1);
    nodes[dest].adj[nodes[dest].adj.size()-1].symmetric_edge = &nodes[src].adj[nodes[src].adj.size()-1];


}

void Graph::bfs(int v) {
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto &e : nodes[u].adj) {
            int w = e.dest;
            int remaining_capacity = e.capacity-e.flow;
            if (!nodes[w].visited && remaining_capacity>0) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].pred = u;
                nodes[w].incoming_edge = &e;
            }
        }
    }
}


int Graph::update_flows(int src,int sink){
    int bottleneck=INT32_MAX/2;
    bfs(src);
    if(!nodes[sink].visited)
        return 0;
    int dest = sink;

    while(dest!=src){ //find bottleneck
        int remaining_capacity = nodes[dest].incoming_edge->capacity-
                                 nodes[dest].incoming_edge->flow;
        bottleneck = min(bottleneck,remaining_capacity);
        dest=nodes[dest].pred;
    }

    dest = sink;

    while(dest!=src){ //find bottleneck
        nodes[dest].incoming_edge->flow+=bottleneck;
        nodes[dest].incoming_edge->symmetric_edge->flow-=bottleneck;
        dest=nodes[dest].pred;
    }

    return bottleneck;
}

void Graph::print_path(int i,int peopleInGroup){
    if(i==n) {
        cout << "Fim deste grupo" <<endl;
        return;
    }
    cout << peopleInGroup << " people in node " << i << endl;
    for(const Edge &e:nodes[i].adj){
        if(e.flow>0 && peopleInGroup-e.flow>0){
            print_path(e.dest,peopleInGroup-e.flow);
        }
    }
}

int Graph::edmonds_karp(int src, int sink){
    int max_flow=0;
    while(true) {
        for(int i=1;i<=n;i++)
            nodes[i].visited=false;
        bfs(src);
        if(!nodes[sink].visited)
            break;
        max_flow += update_flows(src,sink);
    }

    print_path(src,max_flow);

    return max_flow;
}





