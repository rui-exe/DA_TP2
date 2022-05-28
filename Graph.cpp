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
        for (Edge &e : nodes[u].adj) {
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
        int capacity = nodes[dest].incoming_edge->capacity;
        nodes[dest].incoming_edge->flow+=bottleneck;
        nodes[dest].incoming_edge->symmetric_edge->flow-=bottleneck;
        dest=nodes[dest].pred;
    }

    return bottleneck;
}

void Graph::print_path(pair<list<int>,int> group){
    int i = group.first.back();
    if(i==n){
        cout << "Group with " << group.second << " people's path: ";
        for(auto iter=group.first.begin();iter!=group.first.end();iter++){
            cout << *iter << " ";
        }
        cout << endl;
    }
    for(const Edge &e:nodes[i].adj){
        if(e.flow>0){
            pair<list<int>,int> new_group;
            list<int> new_path = group.first;
            new_path.push_back(e.dest);
            new_group.first=new_path;
            new_group.second=min(group.second,e.flow);
            print_path(new_group);
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


    pair<list<int>,int> group;
    list<int>path;
    path.push_back(src);
    group.first=path;
    group.second=max_flow;
    print_path(group);
    return max_flow;
}
int Graph::dijkstra(int a, int b) {
    for(int i=1;i<nodes.size();i++){
        this->nodes[i].dist = 0;
        this->nodes[i].visited=false;
    }
    this->nodes[a].dist=INT32_MAX/2;
    nodes[a].pred_d=a;
    MinHeap<int,int> m(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        m.insert(i,-nodes[i].dist);
    }
    while(m.getSize()>0){
        int c = m.removeMin();
        nodes[c].visited = true;
        for(Edge e:nodes[c].adj){
            if (min(nodes[c].dist,e.capacity)>nodes[e.dest].dist) {
                nodes[e.dest].dist= min(nodes[c].dist,e.capacity);
                nodes[e.dest].pred_d=c;
                m.decreaseKey(e.dest,-nodes[e.dest].dist);
            }
        }
    }
    return -nodes[b].dist==INT32_MAX?-1:nodes[b].dist;
}
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    int x = dijkstra(a,b);
    if(x==-1) return path;
    cout<< "Max Flow = "<< x<<endl;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest = nodes[dest].pred_d;
    }
    path.push_front(a);
    return path;
}
list<int> Graph::unweighted_path(int a,int b){
    list<int> path;
    bfs(a);
    if(!nodes[b].visited)
        return path;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest=nodes[dest].pred;
    }
    path.push_front(dest);
    return path;
}





