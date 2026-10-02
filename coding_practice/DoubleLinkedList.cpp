#include "DoubleLinkedList.h"

// Reverse a double linked list, first try.
Node* Reverse(Node* start) {
  // Empty list.
  if (start == nullptr) return start;

  // Single node double linked list.
  if (start->GetNext() == nullptr) return start;

  Node* itr = start;
  Node* temp_next {};

  while (itr != nullptr) {
    temp_next = itr->GetNext();
    itr->SetNext(itr->GetPrev());
    itr->SetPrev(temp_next);
    if (temp_next != nullptr) itr = itr->GetPrev();
    else break;
  }

  return itr;
}

// Reverse a double linked list recursively.
void ReverseRecursive(Node* start) {
  if (start == nullptr) return;

  Node* next = start->GetNext();
  start->SetNext(start->GetPrev());
  start->SetPrev(next);
  ReverseRecursive(start->GetPrev());
}

// Insert a node at the head of the given list.
Node* InsertHead(Node* head, Node* toadd) {
  // We are not at the beginning of the list.
  while (head->GetPrev() != nullptr) {
    head = head->GetPrev();
  }

  // At beginning.
  head->SetPrev(toadd);
  toadd->SetNext(head);

  return toadd;
}

// Delete the node at the head of the given list.
Node* DeleteHead(Node* head) {
  // We are not at the beginning of the list.
  while (head->GetPrev() != nullptr) {
    head = head->GetPrev();
  }

  // At beginning.
  Node* temp_next = head->GetNext();
  head->SetNext(nullptr);
  temp_next->SetPrev(nullptr);
  return temp_next;
}

// Insert a node at the end of the given list.
Node* InsertTail(Node* head, Node* toadd) {
  Node* itr = head;

  // Find the end of the list unless we are already there.
  while (itr->GetNext() != nullptr) {
    itr = itr->GetNext();
  }

  // At the end of the list.
  itr->SetNext(toadd);
  toadd->SetPrev(itr);
  
  return head;
}

// Delete the node at the end of the list.
Node* DeleteTail(Node* head) {
  Node* itr = head;

  // Find the end of the list unless we are already there.
  while (itr->GetNext() != nullptr) {
    itr = itr->GetNext();
  }

  // At the end of the list.
  Node* temp_prev = itr->GetPrev();
  itr->SetPrev(nullptr);
  temp_prev->SetNext(nullptr);

  return head;
}

// Insert the given node before a provided position.
// Head will always be the first node in the list.
// I assume if the pos does not exist we insert at the head.
Node* InsertBefore(Node* head, Node* pos, Node* toadd) {
  // Find the node to insert before.
  Node* itr = head;
  while (itr != pos) {
    itr = itr->GetNext();
    if (itr == nullptr) return InsertHead(head, toadd);
  }

  // Now insert the node.
  Node* prev = itr->GetPrev();
  // If we are at the current head of the list.
  if (prev == nullptr) return InsertHead(itr, toadd);

  prev->SetNext(toadd);
  toadd->SetPrev(prev);
  toadd->SetNext(itr);
  itr->SetPrev(toadd);

  return head;
}

// Insert the given node after a provided position.
// Head will always be the first node in the list.
// I assume that if pos does not exist it adds the node to the tail.
Node* InsertAfter(Node* head, Node* pos, Node* toadd) {
  // Find the node to insert after.
  Node* itr = head;
  while (itr != pos) {
    itr = itr->GetNext();
    if (itr == nullptr) return InsertTail(head, toadd);
  }

  // Now insert the node.
  Node* next = itr->GetNext();
  // If we are at the current tail of the list.
  if (next == nullptr) return InsertTail(itr, toadd);

  next->SetPrev(toadd);
  toadd->SetNext(next);
  toadd->SetPrev(itr);
  itr->SetNext(toadd);

  return head;
}

// Delete the node in the given position.
// Head will always be the first node in the list.
Node* DeleteNode(Node* head, Node* todel) {
  // Find the node.
  Node* itr = head;

  while (itr != todel) {
    itr = itr->GetNext();
    // Does not exist in the list.
    if (itr == nullptr) return head;
  }

  Node* temp_prev = itr->GetPrev();
  Node* temp_next = itr->GetNext();

  // Deleting the head.
  if (temp_prev == nullptr) {
    itr->SetNext(nullptr);
    temp_next->SetPrev(nullptr);
    return temp_next;
  }

  // Deleting the tail.
  else if (temp_next == nullptr) {
    itr->SetPrev(nullptr);
    temp_prev->SetNext(nullptr);
    return head;
  }

  // Deleting elsewhere in the list.
  itr->SetPrev(nullptr);
  itr->SetNext(nullptr);
  temp_prev->SetNext(temp_next);
  temp_next->SetPrev(temp_prev);

  return head;
}

int main(int argc, char* argv[]) {
  Node node1(1);
  Node node2(2);
  Node node3(3);
  Node node4(4);

  Node node5(5);

  node1.SetNext(&node2);
  node2.SetNext(&node3);
  node3.SetNext(&node4);
  node4.SetPrev(&node3);
  node3.SetPrev(&node2);
  node2.SetPrev(&node1);

  node1.PrintList();
  std::cout << "\n";
/*
  Node* new_head = Reverse(&node1);
  std::cout << "\n";
  new_head->PrintList();
*/
/*
  ReverseRecursive(&node1);
  node4.PrintList();
*/

  std::cout << "\nInserting at the head of the list\n";
  Node* head = InsertHead(&node1, &node5);
  head->PrintList();
  std::cout << "\n";

  std::cout << "\nDeleting the head of the list\n";
  head = DeleteHead(head);
  head->PrintList();
  std::cout << "\n";

  std::cout << "\nInserting at the tail of the list\n";
  head = InsertTail(&node1, &node5);
  head->PrintList();
  std::cout << "\n";

  std::cout << "\nDeleting the tail of the list\n";
  head = DeleteTail(head);
  head->PrintList();
  std::cout << "\n";

  std::cout << "\nInserting before node 3\n";
  head = InsertBefore(head, &node3, &node5);
  head->PrintList();
  std::cout << "\n";

  std::cout << "\nDeleting node 5\n";
  head = DeleteNode(head, &node5);
  head->PrintList();
  std::cout << "\n";

  Node node6(6);

  std::cout << "\nInserting before node 5\n";
  head = InsertBefore(head, &node5, &node6);
  head->PrintList();
  std::cout << "\n";

  std::cout << "\nInserting after node 2\n";
  head = InsertAfter(head, &node2, &node5);
  head->PrintList();
  std::cout << "\n";

  return 0;
}
