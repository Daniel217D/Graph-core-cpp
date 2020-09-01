#include <iostream>
#include "../GraphCore/Graph.h"

//Выводит таблицу смежности вершин графа.
void print_adjacency_matrix(graph_tools::graph& graph) {
    int size = graph.size();
    for (int i = 0; i < size; i++) {
        std::cout << '\t' << i + 1;
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << '\t';
        auto vertex = graph.get_vertex(i);
        for (int j = 0; j < size; j++)
            std::cout << vertex.is_adjacency(graph.get_vertex(j)) << '\t';
        if (i != size - 1)
            std::cout << std::endl;
    }
}

int main()
{
    using namespace graph_tools;
    using namespace std;
    setlocale(LC_ALL, "Russian");

    std::vector<vertex> vertexes(10);
    //1
    vertexes[0].add_adjacency(vertexes[1]);
    vertexes[0].add_adjacency(vertexes[3]);
    vertexes[0].add_adjacency(vertexes[9]);
    //2
    vertexes[1].add_adjacency(vertexes[2]);
    vertexes[1].add_adjacency(vertexes[3]);
    //3
    vertexes[2].add_adjacency(vertexes[1]);
    vertexes[2].add_adjacency(vertexes[3]);
    vertexes[2].add_adjacency(vertexes[4]);
    //5
    vertexes[4].add_adjacency(vertexes[3]);
    vertexes[4].add_adjacency(vertexes[1]);
    //6
    vertexes[5].add_adjacency(vertexes[1]);
    vertexes[5].add_adjacency(vertexes[6]);
    //7
    vertexes[6].add_adjacency(vertexes[7]);
    //8
    vertexes[7].add_adjacency(vertexes[4]);
    vertexes[7].add_adjacency(vertexes[8]);
    //9
    vertexes[8].add_adjacency(vertexes[4]);
    //10
    vertexes[9].add_adjacency(vertexes[3]);

    graph graph(vertexes);
    cout << "Таблица смежности из демо: " << endl;
    print_adjacency_matrix(graph);

    return 0;
}
