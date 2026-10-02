#ifndef CODING_PRACTICE_SIMPLE_GRAPH_H_
#define CODING_PRACTICE_SIMPLE_GRAPH_H_

#include <iostream>
#include <list>
#include <map>

struct Vertex {
  int value;
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

    void AddEdge(Vertex* v1, Vertex* v2);
    void RemoveEdge(Vertex* v1, Vertex* v2);

    void BreadthFirstTraversal(Vertex* curr_node);
    void DepthFirstTraversal(Vertex* curr_node);

    void PrintEdgeList() {
      for (auto edge : edge_list_) {
        std::cout << "Edge: " << edge.first->value << ", " << edge.second->value << "\n";
      }
    }

  private:
    Vertex* start_ {nullptr};
    std::list<std::pair<Vertex*, Vertex*>> edge_list_ {};
    std::map<Vertex*, bool> visited_ {};
};

#endif // CODING_PRACTICE_SIMPLE_GRAPH_H_
