#include <iostream>
#include "prioqueue.h"
#include "prioqueue.cpp"
#include <list>
#include <limits>
#include <vector>

void shortestPath(int src, int n, int m, std::list<Node> *graph);


int
main(void)
{
    int n;
    int m;
    int start_vertex;

    std::cin >> n;
    std::cin >> m;

    std::list<Node> *adj = new std::list<Node>[n];

    float weight;
    int v1, v2;

    for (int i = 0; i < m; i++)
    {
        std::cin >> v1 >> v2 >> weight;
        if (weight < 0)
            continue;
        adj[v1-1].push_back(Node(weight, v2-1));
    }

    std::cin >> start_vertex;

    auto start_s = clock();
    shortestPath(start_vertex, n, m, adj);
    auto stop_s = clock();
    std::cerr << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000 << "ms" << std::endl;

    return 0;
}

void
shortestPath(int src, int n, int m, std::list<Node> *graph)
{
    Queue queue(n);

    std::vector<float> distances(n, std::numeric_limits<float>::max());
    distances[src-1] = 0;
    queue.insert(src-1, 0);

    while (!queue.isEmpty())
    {
        auto current_vertex = queue.pop();
        auto edges = graph[current_vertex];

        for (auto edge : edges)
        {
            auto dest = edge.value;
            if (distances[dest] > distances[current_vertex] + edge.priority )
            {
                distances[dest] = distances[current_vertex] + edge.priority;
                queue.insert(dest, distances[dest]);
            }
        }

    }

    for (int i = 0; i < n; i++)
    {
        std::cout << i+1 << " " << distances[i] << std::endl;
    }
}

//initialize graph
//initialize pq
//pq.insertAll(graph.getVertices())
//
//while (pq is not empty) {
//  vertex = pq.remove()
//  edges = vertex.getEdges()
//
//  for all edges {
//    destination = edge.getDestination()
//    newDistance = edge.getLength() + vertex.getDistance()
//    if (newDistance < destination.getDistance()) {
//      destination.setShortestDistance(newDistance)
//      pq.update(destination)
//    }
//  }
//}
