#include "MinHeap.h"

// Insert a node and call heapify to fix the heap.
//  Inserts the node at the bottom left of the tree, assumes the heap is a minheap before insertion.
void MinHeap::Insert(HeapNode* toadd){
  // Traverse to the bottom left.
  HeapNode* itr = root_;

  while (itr->GetLeft() != nullptr) {
    itr = itr->GetLeft();    
  }

  // Insert the node.
  toadd->SetParent(itr);
  itr->SetLeft(toadd);

  // Heapify the heap to fix it, starting with the parent of the newly inserted node.
  Heapify(itr);
}

// Delete a node and call heapify to fix the heap.
//  Replace the node to be deleted with the bottom left node, unless this is the one being deleted.
HeapNode* MinHeap::Delete(HeapNode* todel){
  if (todel == nullptr) return todel;

  HeapNode* left = todel->GetLeft();
  HeapNode* right = todel->GetRight();

  // Find the left leaf to replace the node to be deleted with.
  HeapNode* itr = root_;
  while (itr->GetLeft() != nullptr) {
    itr = itr->GetLeft();
  }
  
  HeapNode* temp = itr->GetParent();
  // Removing the link to the replacement node.
  if (temp != nullptr) temp->SetLeft(nullptr);
  itr->SetParent(todel->GetParent());
  // Changing the child of the node to be deleted's parent.
  if (todel->GetParent() != nullptr) {
    if (todel->GetParent()->GetLeft() == todel) todel->GetParent()->SetLeft(itr);
    else todel->GetParent()->SetRight(itr);
  }
  // We could be deleting the leaf nodes parent.
  if (left != itr) itr->SetLeft(left);
  itr->SetRight(right);

  // For completeness.
  todel->SetParent(nullptr);
  todel->SetLeft(nullptr);
  todel->SetRight(nullptr);

  // Now to fix the heap.
  Heapify(itr);

  // Heapify() fixes the root if it was deleted.

  return todel;
}

// The root is going to be the minimum if we have kept the heap consistent throughout.
HeapNode* MinHeap::GetMin(){
  return root_;
}

// Function to fix the heap.
void MinHeap::Heapify(HeapNode* node){
  // Base case, above the root.
  if (node == nullptr) return;

  // The root has been altered.
  if (node->GetParent() == nullptr) root_ = node;

  // Single node.
  if (node->GetLeft() == nullptr && node->GetRight() == nullptr) {
    Heapify(node->GetParent());
    return;
  }

  HeapNode* left = node->GetLeft();
  HeapNode* right = node->GetRight();

  // If the heap needs fixing.
  if (left != nullptr && node->GetKey() > left->GetKey()) {
    HeapNode* temp = node->GetParent();
    // The current node is the root.
    if (temp != nullptr) {
      if (temp->GetLeft() == node) temp->SetLeft(left);
      else temp->SetRight(left);
    }
    // Swap the two nodes.
    HeapNode* temp_right = node->GetRight();
    node->SetParent(left);
    node->SetLeft(left->GetLeft());
    if (node->GetLeft() != nullptr) {
      node->GetLeft()->SetParent(node);
    }
    node->SetRight(left->GetRight());
    if (node->GetRight() != nullptr) {
      node->GetRight()->SetParent(node);
    }
    left->SetParent(temp);
    left->SetLeft(node);
    left->SetRight(temp_right);
    // Assume the right subtree conforms to the min heap.
    Heapify(node);
  }

  else if (right != nullptr && node->GetKey() > right->GetKey()) {
    HeapNode* temp = node->GetParent();
    if (temp->GetLeft() == node) temp->SetLeft(right);
    else temp->SetRight(right);
    // Swap the two nodes.
    HeapNode* temp_left = node->GetLeft();
    node->SetParent(right);
    node->SetLeft(right->GetLeft());
    if (node->GetLeft() != nullptr) {
      node->GetLeft()->SetParent(node);
    }
    node->SetRight(right->GetRight());
    if (node->GetRight() != nullptr) {
      node->GetRight()->SetParent(node);
    }
    right->SetParent(temp);
    right->SetRight(node);
    right->SetLeft(temp_left);
    // Assume the left subtree conforms to the min heap.
    Heapify(node);
  }
  
  else {
    // Recursively work up the tree to the root.
    Heapify(node->GetParent());
    return;
  }

}

// Takes the minimum node and removes it, returning it. Then call heapify to fix the heap.
HeapNode* MinHeap::ExtractMin(){
  // We can use our delete function on the root.
  return Delete(root_);
}

// Takes a node and reduces its key by one. If this effects the heap call heapify to fix it.
void MinHeap::DecreaseKey(HeapNode* todec){
  todec->SetKey(todec->GetKey() - 1);

  // Ensure this does not effect the heap.
  Heapify(todec);
}

int main(int argc, char* argv[]) {
  HeapNode root(1);

  MinHeap heap(&root);

  HeapNode node1(16);
  HeapNode node2(6);
  HeapNode node3(70);
  HeapNode node4(2);
  HeapNode node5(35);

  node1.SetParent(&root);
  node2.SetParent(&root);
  node5.SetParent(&node2);

  root.SetLeft(&node1);
  root.SetRight(&node2);

  node2.SetRight(&node5);

  heap.PrintHeap();

  std::cout << "\n\n";

  heap.Insert(&node3);
  heap.Insert(&node4);

  heap.PrintHeap();

  std::cout << "\n\n";

  HeapNode* min = heap.GetMin();

  std::cout << "The minimum: " << min->GetKey() << "\n";

  min = heap.ExtractMin();

  std::cout << "\nThe extracted minimum: " << min->GetKey() << "\n";

  heap.PrintHeap();

  std::cout << "\nDeleting node with key 16\n";

  min = heap.Delete(&node1);

  heap.PrintHeap();

  return 0;
}
