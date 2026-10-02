#ifndef CODING_PRACTICE_WEIGHTED_GRAPH_H_
#define CODING_PRACTICE_WEIGHTED_GRAPH_H_

#include <iostream>
#include <map>
#include <list>

struct Vertex {
  int value;
};

struct Edge {
  Vertex* v1;
  Vertex* v2;
  int weight;
};

class Graph {
  public:
    Graph(Vertex* start) : start_(start) {
      visited_.insert(std::make_pair(start, false));
    }

    ~Graph() {
      start_ = nullptr;
      edge_list_.clear();
      visited_.clear();
    }

    void PrintEdgeList() {
      for (auto edge : edge_list_) {
        std::cout << edge->v1->value << "-" << edge->weight << "->" << edge->v2->value << "\n";
      }
    }

    void InsertEdge(Vertex* v1, Vertex* v2, int weight);
    void RemoveEdge(Vertex* v1, Vertex* v2, int weight);

    void Djikstra();

  private:
    Vertex* start_;
    std::list<Edge*> edge_list_ {};
    std::map<Vertex*, bool> visited_ {};
};

#endif // CODING_PRACTICE_WEIGHTED_GRAPH_H_
