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

void Graph::addEdgev2(int src, int dest, int capacity,int duration){
    if (src<0 || src>n || dest<0 || dest>n) return;
    nodes[src].adj.push_back({dest,0,capacity,duration});
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
void Graph::bfs3(int v) {
    nodes[v].unweighted_transposed_distance=0;
    for (int i=0; i<=n; i++)
        nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited && e.capacity==0) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].unweighted_transposed_distance = nodes[u].unweighted_transposed_distance+1;
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


void Graph::print_path(pair<list<int>,int> group,int trg){
    int i = group.first.back();
    if(i==trg){
        cout << "Caminho do grupo com " << group.second << " pessoas: ";
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
            print_path(new_group,trg);
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

Graph Graph::createRestrictedGraph(int maxEdges){
    Graph restrictedGraph(n*(maxEdges+1),true);

    for(int u=1;u<=n*(maxEdges+1);u++){
        restrictedGraph.nodes[u].real_node=((u-1)/(maxEdges+1))+1;
    }

    for(int u=1;u<=n;u++){
        for(Edge e:nodes[u].adj){
            if(e.capacity>0) {
                int v = e.dest;
                for (int b = 0; b <= maxEdges; b++) {
                    if (b + 1 <= maxEdges) {
                        restrictedGraph.addEdgev2((u - 1) * (maxEdges + 1) + 1 + b,
                                                  ((v - 1) * (maxEdges + 1) + 1 + b) + 1, e.capacity);
                    }
                }
            }
        }
    }

    return restrictedGraph;
}


Graph Graph::originalGraph(){
    Graph originalGraph(n);
    for(int i=1;i<=n;i++){
        originalGraph.nodes[i].unweighted_distance = nodes[i].unweighted_distance;
        originalGraph.nodes[i].unweighted_transposed_distance = nodes[i].unweighted_transposed_distance;
        originalGraph.nodes[i].maxCapacity=INT32_MIN/2;
        for(const Edge&e:nodes[i].adj) {
            if(e.capacity>0) {
                originalGraph.addEdgev2(i, e.dest, e.capacity, 0);
                originalGraph.nodes[i].maxCapacity=max(originalGraph.nodes[i].maxCapacity,e.capacity);
            }
        }
    }
    return originalGraph;
}
void Graph::showParetoOptimalPaths(int src, int trg){
    bfs2(src);
    int minEdges=nodes[trg].unweighted_distance;
    bfs3(trg);
    dijkstra(src,trg);
    unsigned maxEdges = nodes[trg].num_edges;
    Graph restrictedGraph = createRestrictedGraph(maxEdges);
    restrictedGraph.dijkstra2((src-1)*(maxEdges+1)+1 );
    int lastCapacity=INT32_MIN/2;
    for(int i=minEdges;i<=maxEdges;i++){
        int dest = (trg-1)*(maxEdges+1)+1 +i; //node (dest,i) of restrictedGraph
        int currentCapacity = restrictedGraph.nodes[dest].dist;
        if(currentCapacity>lastCapacity){
            Graph originalGraph = this->originalGraph();
            lastCapacity = currentCapacity;
            cout << "Encaminhamento com  " << i - 1 << " transbordos - " << "fluxo = " << currentCapacity << endl;
            for(int k=1;k<=n;k++){
                if(k!=trg) {
                    originalGraph.nodes[k].visited = originalGraph.nodes[k].unweighted_distance +
                                                     originalGraph.nodes[k].unweighted_transposed_distance > i;

                    originalGraph.nodes[k].visited = originalGraph.nodes[k].visited || originalGraph.nodes[k].maxCapacity<currentCapacity;
                    for (auto iter = originalGraph.nodes[k].adj.begin();iter!=originalGraph.nodes[k].adj.end();iter++) {
                        if (iter->capacity<currentCapacity) {
                            auto previous_iter = --iter;
                            originalGraph.nodes[k].adj.erase(++iter);
                            iter=previous_iter;
                        }
                    }
                }
                else
                    originalGraph.nodes[k].visited=false;
            }
            int nodesMarkVisited=1;
            while(nodesMarkVisited>0){
                nodesMarkVisited=0;
                for(int k=1;k<=n;k++){
                    if(!originalGraph.nodes[k].visited && k!=trg) {
                        bool unvisitableNode = true;
                        for (auto iter = originalGraph.nodes[k].adj.begin();iter!=originalGraph.nodes[k].adj.end();iter++) {
                            if (!originalGraph.nodes[iter->dest].visited) {
                                unvisitableNode = false;
                            }
                            else{
                                auto previous_iter = --iter;
                                originalGraph.nodes[k].adj.erase(++iter);
                                iter=previous_iter;
                            }
                        }
                        if (unvisitableNode) {
                            originalGraph.nodes[k].visited = true;
                            nodesMarkVisited++;
                        }
                    }
                }
            }

            vector<list<int>> paths = originalGraph.dijkstra_paths_backtrack(src, trg,currentCapacity,i);
            for(int j=0;j<paths.size();j++) {
                cout << "Path " << j+1 << endl;
                list<int> path = paths[j];
                for (auto iter = path.begin(); iter != path.end(); iter++) {
                    if (*iter != *--path.end())
                        cout << "No " << *iter<< ", ";
                    else
                        cout << "No " << *iter;
                }
                cout << endl;
                cout << endl;
            }
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
       }
    }
}
void Graph::dijkstra2(int a){
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
                nodes[e.dest].predNodes.clear();
                nodes[e.dest].predNodes.push_back(c);
                m.decreaseKey(e.dest,{-nodes[e.dest].dist,nodes[e.dest].num_edges});
            }

            else if(min(nodes[c].dist,e.capacity)==nodes[e.dest].dist && e.capacity>0){
                if(nodes[c].num_edges+1<nodes[e.dest].num_edges){
                    nodes[e.dest].dist= min(nodes[c].dist,e.capacity);
                    nodes[e.dest].num_edges=nodes[c].num_edges+1;
                    nodes[e.dest].predNodes.clear();
                    nodes[e.dest].predNodes.push_back(c);
                    m.decreaseKey(e.dest,{-nodes[e.dest].dist,nodes[e.dest].num_edges});
                }
                else if(nodes[e.dest].num_edges==nodes[c].num_edges+1){
                    nodes[e.dest].predNodes.push_back(c);
                }
            }

        }
    }
}

vector<list<int>> Graph::dijkstra_paths2(int a,int b){
    int dest = b;
    vector<list<int>> answer;
    if(dest==a){
        answer.push_back(list<int>{a});
        return answer;
    }
    for(int pred:nodes[dest].predNodes) {
        vector<list<int>> paths_to_pred = dijkstra_paths2(a,pred);
        for(list<int> path_to_pred:paths_to_pred) {
            path_to_pred.push_back(dest);
            answer.push_back(path_to_pred); //path to pred + dest = path to dest
        }
    }
    return answer;
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
    cout<< "Fluxo = "<< x<<endl;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest = nodes[dest].pred_d;
    }
    path.push_front(a);
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

void Graph::putInfoOnEdges(int dest){
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
                if(w==dest){
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



int Graph::correctRoute(int src,int trg,int extra){
    //Assumes the algorithm used for exercise 2.1 was exactly before this
    nodes[0].adj.back().capacity+=extra;
    return edmonds_karp(0,trg);
}


vector<list<int>> Graph::dijkstra_paths_backtrack(int a,int b,int bottleneck,int maxEdges,int nrEdges){
    vector<list<int>> answer;
    if(a==b){
        return vector<list<int>>{{a}};
    }
    for(const Edge& e:nodes[a].adj){
        if(nodes[e.dest].visited){
            continue;
        }
        else{
            if(nodes[e.dest].unweighted_transposed_distance+nrEdges+1<=maxEdges) {
                vector<list<int>> paths = dijkstra_paths_backtrack(e.dest, b, bottleneck, maxEdges, nrEdges + 1);
                for (list<int> path: paths) {
                    path.push_front(a);
                    answer.push_back(path);
                }
            }
        }
    }
    return answer;
}


