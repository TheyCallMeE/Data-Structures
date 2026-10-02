#include "SimpleGraph.h"

// Add an edge to the graph.
void Graph::AddEdge(Vertex* v1, Vertex* v2) {
  // First check the vertices are both valid.
  if (v1 == nullptr) return;
  if (v2 == nullptr) return;

  // Then parse the edge list to ensure the edge does not already exist, this is O(n).
  // The edges are not sorted so something like a binary search would not reduce the time complexity.
  auto edge = std::make_pair(v1, v2);

  for (auto e : edge_list_) {
    if (e.first == edge.first && e.second == edge.second) return;
  }

  // If it does not exist in the list, add it to the list.
  edge_list_.push_back(edge);

  // The beauty of using a map for the visited list is this doubles as a constant lookup time for vertices.
  // See if one of the passed vertices is not a part of the graph.
  auto it = visited_.find(v1);
  if (it == visited_.end()) visited_.insert(std::make_pair(v1, false));
  
  it = visited_.find(v2);
  if (it == visited_.end()) visited_.insert(std::make_pair(v2, false));
}

// Removes the edge between the two given vertices if it exists.
void Graph::RemoveEdge(Vertex* v1, Vertex* v2) {
  // First check the vertices are both valid.
  if (v1 == nullptr) return;
  if (v2 == nullptr) return;

  // Parse the edge list to see if it exists. If so remove it.
  auto edge = std::make_pair(v1, v2);

  auto itr = edge_list_.begin();
  while (itr != edge_list_.end()) {
    if (itr->first == edge.first && itr->second == edge.second) {
      edge_list_.erase(itr);
      return;
    }
    itr++;
  }

  // The edge does not exist.
  return;
}

// Visits all nodes on the present level before travelling to a deeper level.
void Graph::BreadthFirstTraversal(Vertex* curr_node) {
  // The route vector, clear on first entrance and add the node.
  static std::list<Vertex*> route {};
  if (curr_node == start_) {
    route.clear();
    route.push_back(curr_node);
  }

  // Gather the length of the route for comparison later.
  int route_length = route.size();

  // Set the current node to visited.
  auto visit = visited_.find(curr_node);
  if (visit != visited_.end()) visit->second = true;

  // Base cases: Either the node has no edge to travel on
  //  because there are no edges in the edge list
  //  or the only adjacent node has been visited already (cycle).
  
  // Check for existence of edge first. Add any adjacent nodes to the route that arent part of a cycle.
  for (auto v : edge_list_) {
    if (v.first == curr_node) {
      // Check for cycle.
      auto cycle = visited_.find(v.second);
      if (cycle != visited_.end()) {
        if (cycle->second != true) {
          // No cycle exists so we can add the vertex to the route and consider it visited.
          route.push_back(v.second);
          visit = visited_.find(route.back());
          if (visit != visited_.end()) visit->second = true;
        }
      }
      else return;
    }
  }

  // Now pop the current node and print it as part of the traversal
  static char space {};
  std::cout << space << route.front()->value;
  space = ' ';
  route.pop_front();
  // We have altered the previously stored route length by -1, reflect that change.
  route_length--;

  // If there are no more nodes in the route after popping we have finished traversing the graph.
  if (route.empty()) return;

  // If the route is the same size after parsing the edge list that means we have added no other vertices,
  //  ie there are no edges from this node.
  if (static_cast<int>(route.size()) == route_length) return;

  // Otherwise move to the next node.
  while (!route.empty()) {
    BreadthFirstTraversal(route.front());
  }
}

// Visits all nodes on a branch before travelling to a new branch.
void Graph::DepthFirstTraversal(Vertex* curr_node) {
  static std::list<Vertex*> route {};
  if (curr_node == start_) {
    route.clear();
    route.push_back(curr_node);
  }

  // Add the current node to the visited list.
  auto visit = visited_.find(curr_node);
  if (visit != visited_.end()) visit->second = true;

  for (auto e : edge_list_) {
    if (e.first == curr_node) {
      auto cycle = visited_.find(e.second);
      if (cycle != visited_.end()) {
        if (cycle->second != true) {
          route.push_back(e.second);
          DepthFirstTraversal(route.back());
        }
      } 
      else return;
    }
  }

  // We found no edges from the current node.
  if (route.back() == curr_node) return;

  // We are back at the curr_nodeing node, print out the route.
  if (curr_node == start_) {
    char space {};
    while (!route.empty()) {
      std::cout << space << route.front()->value;
      route.pop_front();
      space = ' ';
    }
  }

  return;
}

int main(int argc, char* argv[]) {
  Vertex v1{1};
  Vertex v2{2};
  Vertex v3{3};
  Vertex v4{4};
  Vertex v5{5};

  Graph graph(&v1);

  graph.AddEdge(&v1, &v2);
  graph.AddEdge(&v2, &v1);
  graph.AddEdge(&v1, &v3);
  graph.AddEdge(&v2, &v5);
  graph.AddEdge(&v3, &v4);
  graph.AddEdge(&v3, &v5);

  graph.PrintEdgeList();

  std::cout << "\n\n";

//  graph.RemoveEdge(&v1, &v5);

//  graph.PrintEdgeList();

//  std::cout << "\n\n";

//  graph.AddEdge(&v1, &v5);

  graph.BreadthFirstTraversal(&v1);
  //graph.DepthFirstTraversal(&v1);

  std::cout << "\n\n";

  return 0;
}
