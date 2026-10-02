#include "WeightedGraph.h"

#include <climits>

void Graph::InsertEdge(Vertex* v1, Vertex* v2, int weight) {
  // Check the vertices are both valid.
  if (v1 == nullptr) return;
  if (v2 == nullptr) return;

  // For Djikstra's we cannot allow negative and zero weights.
  if (weight < 1) return;

  // Construct an edge instance.
  Edge* edge = new Edge{v1, v2, weight};

  // Check to see that the edge does not already exist.
  for (auto e : edge_list_) {
    if (e->v1 == v1 && e->v2 == v2 && e->weight == weight) return;
  }

  // Add the edge to the edge list.
  edge_list_.push_back(edge);

  // Add the vertices to the visited list if they do not already exist.
  auto v = visited_.find(v1);
  if (v == visited_.end()) visited_.insert(std::make_pair(v1, false));
  v = visited_.find(v2);
  if (v == visited_.end()) visited_.insert(std::make_pair(v2, false));
}

void Graph::RemoveEdge(Vertex* v1, Vertex* v2, int weight) {
  // Check the vertices are both valid.
  if (v1 == nullptr) return;
  if (v2 == nullptr) return;

  // Find the edge if it exists.
  auto itr = edge_list_.begin();
  while (itr != edge_list_.end()) {
    if ((*itr)->v1 == v1 && (*itr)->v2 == v2 && (*itr)->weight == weight) {
      edge_list_.erase(itr);
      return;
    }
    itr++;
  }

  // The edge does not exist.
  return;
}

// Find the shortest path between the start node and every other node in the graph.
void Graph::Djikstra() {
  // Create a list of nodes from the visited list and give each a path weight of INT_MAX (infinity)
  //  except for the starting node which will be zero.
  // Also create a priority queue of nodes.
  std::map<Vertex*, int> distances {};
  std::list<Vertex*> priority_queue {};

  for (auto vertx : visited_) {
    if (vertx.first == start_) {
      distances.insert(std::make_pair(vertx.first, 0));
    } else {
      distances.insert(std::make_pair(vertx.first, INT_MAX));
    }
    priority_queue.push_back(vertx.first);
  }

  // Breadth First Traversal with every node in the priority queue.
  while (!priority_queue.empty()) {
    // Mark the current node as visited.
    auto visit = visited_.find(priority_queue.front());
    if (visit != visited_.end()) visit->second = true;
    else return;

    // Iterate through the current nodes edge list and compute the minimum to its adjacents.
    for (auto &edge : edge_list_) {
      if (edge->v1 == priority_queue.front()) {
        // Checking for cycles.
        auto cycle = visited_.find(edge->v2);
        if (cycle != visited_.end()) {
          if (cycle->second == false) {
            // Compute the distance.
            // The distance from the start to the current node.
            auto d_curr = distances.find(edge->v1);
            // The distance to the node we are looking at along the edge.
            auto dist = distances.find(edge->v2);
            if (d_curr != distances.end()) {
              if (dist->second > edge->weight + d_curr->second) {
                dist->second = edge->weight + d_curr->second;
              }
            }
            else return;
          }
        }
        else return;
      }
    }

    // We have concluded analysis of the current node.
    priority_queue.pop_front();
  }

  // Print the distances found.
  for (auto dist : distances) {
    std::cout << "Start to " << dist.first->value << " = " << dist.second << "\n";
  }
}

int main(int argc, char* argv[]) {
  Vertex v1{1};

  Graph graph(&v1);

  Vertex v2{2};
  Vertex v3{3};
  Vertex v4{4};
  Vertex v5{5};

  graph.InsertEdge(&v1, &v2, 6);
  graph.InsertEdge(&v1, &v3, 4);
  graph.InsertEdge(&v1, &v5, 18);
  graph.InsertEdge(&v2, &v1, 10);
  graph.InsertEdge(&v2, &v3, 12);
  graph.InsertEdge(&v3, &v4, 6);
  graph.InsertEdge(&v4, &v5, 5);
  graph.InsertEdge(&v4, &v5, 5);

  graph.PrintEdgeList();

  std::cout << "\n\n";

//  graph.RemoveEdge(&v1, &v5, 18);

//  graph.PrintEdgeList();

  graph.Djikstra();

  return 0;
}
