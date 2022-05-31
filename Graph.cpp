//
// Created by pedro on 22-05-2022.
//

#include "Graph.h"


bool operator<(const capacity_stops&c1,const capacity_stops&c2){
    if(c1.capacity<c2.capacity)
        return true;
    else if(c2.capacity<c1.capacity)
        return false;
    else
        return c1.stops<c2.stops;
}

bool operator>(const capacity_stops&c1,const capacity_stops&c2){
    if(c1.capacity>c2.capacity)
        return true;
    else if(c2.capacity>c1.capacity)
        return false;
    else
        return c1.stops>c2.stops;
}

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int capacity,int duration) {
    if (src<0 || src>n || dest<0 || dest>n) return;
    Edge e2({src,0,0,duration});
    nodes[dest].adj.push_back(e2);
    Edge e1({dest,0,capacity,duration});
    nodes[src].adj.push_back(e1);
    nodes[src].adj.back().symmetric_edge = &nodes[dest].adj.back();
    nodes[dest].adj.back().symmetric_edge = &nodes[src].adj.back();
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
void Graph::bfs2(int v) {
    nodes[v].unweighted_distance=0;
    for (int i=0; i<=n; i++)
        nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited && e.capacity>0) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].unweighted_distance = nodes[u].unweighted_distance+1;
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
            if(*iter>0)
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
        for(int i=0;i<=n;i++)
            nodes[i].visited=false;
        bfs(src);
        if(!nodes[sink].visited)
            break;
        max_flow += update_flows(src,sink);
    }


    return max_flow;
}
int Graph::dijkstra(int a, int b) {
    for(int i=0;i<nodes.size();i++){
        this->nodes[i].dist = 0;
        this->nodes[i].num_edges = INT32_MAX/2;
        this->nodes[i].visited=false;
    }
    this->nodes[a].dist=INT32_MAX/2;
    this->nodes[a].num_edges=0;
    nodes[a].pred_d=a;
    MinHeap<int,capacity_stops> m(nodes.size()-1,-1);
    for(int i=0;i<nodes.size();i++){
        m.insert(i,{-nodes[i].dist,nodes[i].num_edges});
    }
    while(m.getSize()>0){
        int c = m.removeMin();
        nodes[c].visited = true;
        for(Edge e:nodes[c].adj){
            if (min(nodes[c].dist,e.capacity)>nodes[e.dest].dist && e.capacity>0) {
                nodes[e.dest].dist= min(nodes[c].dist,e.capacity);
                nodes[e.dest].num_edges=nodes[c].num_edges+1;
                nodes[e.dest].pred_d=c;
                m.decreaseKey(e.dest,{-nodes[e.dest].dist,nodes[e.dest].num_edges});
            }

            else if(min(nodes[c].dist,e.capacity)==nodes[e.dest].dist && e.capacity>0){
                if(nodes[c].num_edges+1<nodes[e.dest].num_edges){
                    nodes[e.dest].dist= min(nodes[c].dist,e.capacity);
                    nodes[e.dest].num_edges=nodes[c].num_edges+1;
                    nodes[e.dest].pred_d=c;
                    m.decreaseKey(e.dest,{-nodes[e.dest].dist,nodes[e.dest].num_edges});
                }
            }

        }
    }
    return -nodes[b].dist==INT32_MAX?-1:nodes[b].dist;
}
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    int x = dijkstra(a,b);
    if(x==-1) return path;
    cout<< "Flow = "<< x<<endl;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest = nodes[dest].pred_d;
    }
    path.push_front(a);
    return path;
}
list<int> Graph::unweighted_path(int a,int b){
    int flow=INT32_MAX/2;
    list<int> path;
    bfs2(a);
    if(!nodes[b].visited)
        return path;
    int dest = b;
    while(dest!=a){
        if(nodes[dest].incoming_edge->capacity==0){
            cout << "gg";
        }
        flow=min(flow,nodes[dest].incoming_edge->capacity);
        path.push_front(dest);
        dest=nodes[dest].pred;
    }
    cout << "Flow: "<< flow<<endl;
    path.push_front(dest);
    return path;
}


int Graph::criticalPath() {

    for(int i=1;i<=n;i++){
        nodes[i].es=0;
        nodes[i].in_degree=0;
    }

    for(int i=1;i<=n;i++){
        for(auto e:nodes[i].adj){
            if(e.flow<=0)
                continue;
            auto w = e.dest;
            nodes[w].in_degree++;
        }
    }
    queue<int> s;
    for(int i=1;i<=n;i++){
        if(nodes[i].in_degree == 0)
            s.push(i);
    }

    int durMin=-1;
    while(!s.empty()){
        auto v = s.front();
        s.pop();
        if(nodes[v].es>durMin)
            durMin=nodes[v].es;
        for(auto e:nodes[v].adj){
            if(e.flow<=0)
                continue;
            auto w = e.dest;

            if(nodes[w].es<nodes[v].es+e.duration)
                nodes[w].es=nodes[v].es+e.duration;

            if(--nodes[w].in_degree == 0)
                s.push(w);
        }
    }

    return durMin;
}

void Graph::putInfoOnEdges(){
    for(int i=1;i<=n;i++){
        for(Edge&e:nodes[i].adj){
            if(e.flow>0){
                e.es=nodes[i].es;
                e.ef=e.es+e.duration;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(Edge&e1:nodes[i].adj){
            int w=e1.dest;
            if(e1.flow>0){
                if(w==n){
                    e1.fs=nodes[w].es-e1.ef;
                }
                else {
                    int es = INT32_MAX;
                    for (const Edge &e2: nodes[w].adj) {
                        if (e2.flow > 0) {
                            es = min(es, e2.es);
                        }
                    }
                    e1.fs = es - e1.ef;
                }
            }
        }
    }
}

pair<int,list<int>> Graph::getMaxWaitingTime(){
    int maxWaitingTime=0;
    list<int> waiting_nodes;
    for(int i=1;i<=n;i++){
        for(const Edge&e:nodes[i].adj){
            if(e.flow>0){
                if(e.fs>maxWaitingTime){
                    maxWaitingTime=e.fs;
                    waiting_nodes.clear();
                    waiting_nodes.push_back(e.dest);
                }
                else if (e.fs==maxWaitingTime)
                    waiting_nodes.push_back(e.dest);
            }
        }
    }
    return {maxWaitingTime,waiting_nodes};
}




