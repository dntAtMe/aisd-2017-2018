#include <iostream>
#include "prioqueue.h"
#include "prioqueue.cpp"
#include <string.h>

#include <list>
#include <limits>
#include <vector>
#include <stdlib.h>

class Edge
{
public:
    int start, end;
    float weight;
    Edge(int start, int end, float weight) : start(start), end(end), weight(weight) {}
};

void prim(int src, int n, int m, std::vector<Node> *graph);
void kruskal(int n, int m, std::vector<Edge> graph);
void randomize(int n, int m, std::vector<Node> *graph);
void unvisited(int n, int m, std::vector<Node> *graph);

int
main(int argc, char* argv[])
{


    int n;

    std::cin >> n;
    int m = n*(n-1)/2;

    std::vector<Node> *adj = new std::vector<Node>[n];

    float weight;
    int v1, v2;

    for (int i = 0; i < m; i++)
    {
        std::cin >> v1 >> v2 >> weight;
        if (weight < 0)
            continue;
        adj[v1-1].push_back( Node(weight, v2-1) );
        adj[v2-1].push_back( Node(weight, v1-1) );
    }

    auto start_s = clock();
    prim(0, n, m, adj);
    auto stop_s = clock();
    std::cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000 << "ms" << std::endl;

    start_s = clock();
    unvisited(n, m, adj);
    stop_s = clock();
    std::cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000 << "ms" << std::endl;



    if (!strcmp(argv[1], "-k"))
    {
        std::vector<Edge> graph;

        float weight;
        int v1, v2;

        for (int i = 0; i < m; i++)
        {
            std::cin >> v1 >> v2 >> weight;
            if (weight < 0)
                continue;
            graph.push_back( Edge(v1, v2, weight) );
        }

        auto start_s = clock();
        kruskal(n, m, graph);
        auto stop_s = clock();
        std::cerr << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000 << "ms" << std::endl;

    }

    return 0;
}

void
randomize(int n, int m, std::vector<Node> *graph)
{
    srand (time(NULL));
    int current = rand() % n;

    bool *visited = new bool[n];
    visited[current] = true;

    unsigned long visitedCounter = 1;
    unsigned long stepMeter = 0;

    float totalWeight = 0;

    while(visitedCounter < n)
    {
        stepMeter++;
        auto edges = graph[current];
        auto edge = edges[ (int) (rand() % edges.size()) ];
        //totalWeight += edge.priority;
        //std::cerr << current+1 << " " << edge.value+1 << std::endl;
        current = edge.value;

        if (!visited[current])
        {
            visited[current] = true;
            visitedCounter++;
        }
    }

    std::cout << stepMeter << " " << totalWeight << " " << sizeof(visited) << " ";
}

void
unvisited(int n, int m, std::vector<Node> *graph)
{
    Queue queue(m);
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    int src = 0;
    queue.insert(src, 0);

    int visitedCounter = 0;
    unsigned long stepMeter = 0;
    float totalWeight = 0;

    while (visitedCounter < n && !queue.isEmpty() )
    {
        stepMeter++;
        auto weight =  queue.prioTop();
        auto current_vertex = queue.pop();
        if (visited[current_vertex])
        {
            continue;
        }
        else
        {
            visited[current_vertex] = true;
            visitedCounter++;
            totalWeight += weight;
        }
        for (auto edge : graph[current_vertex])
        {
            if (visited[edge.value])
                continue;
            std::cerr << current_vertex << " " << edge.value << " " << edge.priority << std::endl;
            queue.insert(edge.value, edge.priority);
        }
    }

    std::cout << stepMeter << " " << totalWeight << " " << sizeof(visited) * sizeof(bool) + sizeof(queue) * sizeof(Node)<< " ";
}


class Sets
{
private:
    int *set, *rank;
    int size;
public:
    Sets(int size) : size(size)
    {
        set = new int[size];
        rank = new int[size];

        for (int i = 0; i < size; i++)
        {
            set[i] = i;
            rank[i] = 0;
        }
    }

    int find(int v)
    {
        if (v != set[v])
            set[v] = find(set[v]);
        return set[v];
    }

    void union2(int v1, int v2)
    {
        auto p1 = find(v1);
        auto p2 = find(v2);

        if (rank[p1] > rank[p2])
            set[p2] = p1;
        else
            set[p1] = p2;
        if (rank[p1] == rank[p2])
            rank[p2]++;
    }
};

void
kruskal(int n, int m, std::vector<Edge> graph)
{

    float weight = 0;

    Queue queue(m);
    for (auto i = 0; i < m; i++)
        queue.insert(i, graph[i].weight);

    Sets sets(n);

    while(!queue.isEmpty())
    {
        auto edge = graph[queue.pop()];

        auto first_set = sets.find(edge.start);
        auto second_set = sets.find(edge.end);
        if (first_set != second_set)
        {
            std::cout << edge.start << " " << edge.end << " " << edge.weight << std::endl;
            weight += edge.weight;
            sets.union2(first_set, second_set);
        }
    }
    std::cout << weight << std::endl;
}

void
prim(int src, int n, int m, std::vector<Node> *graph)
{
    Queue queue(m);
    queue.insert(src, 0);

    std::vector<float> distances(n, std::numeric_limits<float>::max());
    distances[src] = 0;

    std::vector<int> parent(n, -1);
    std::vector<bool> in_queue(n, false);

    while(!queue.isEmpty())
    {
        auto current_vertex = queue.pop();
        in_queue[current_vertex] = true;
        auto edges = graph[current_vertex];

        for (auto edge : edges)
        {
            auto v = edge.value;
            if (in_queue[v] == false &&  edge.priority < distances[v])
            {
                distances[v] = edge.priority;
                queue.insert(v, distances[v]);
                parent[v] = current_vertex;
            }
        }
    }

    float weight  = 0;

    for (int i = 1; i < n; i++)
    {
        weight += distances[i];
        std::cerr << parent[i]+1 << " " << i+1 << " " << distances[i]<< std::endl;
    }

    std::cerr << weight << std::endl;
}
