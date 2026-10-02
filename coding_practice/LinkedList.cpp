#include "LinkedList.h"

#include <list>

// Reverse the order of a given linked list.
Node* Reverse(Node* head) {
  // This is my first attempt, is there a better recursive method?
  // Initialize iterator pointers.
  Node* prev = head;
  Node* next = nullptr;
  Node* nextnext = nullptr;

  // Edge case, single node linked list.
  if (head->Next() == nullptr) return head;
  else next = head->Next();
  nextnext = next->Next();

  // Reverse the list.

  // Know that the head's next pointer has to be set to null.
  prev->SetNext(nullptr);

  while (next != nullptr) {
    next->SetNext(prev);
    prev = next;
    next = nextnext;
    if (nextnext != nullptr) nextnext = nextnext->Next();
  }

  return prev;
}

// A recursive version of the reverse function.
// Assumes I can change the function signature and control the argument values.
//  Prev needs to be a nullptr on the first pass for this to work.
void ReverseRecursive(Node* head, Node* prev) {
  // Base condition.
  if (head == nullptr) return;

  Node* temp = head->Next();
  head->SetNext(prev);
  prev = head;
  head = temp;
  ReverseRecursive(head, prev);
}

Node* ReverseRecursive(Node* head) {
  // Base condition.
  if (head == nullptr || head->Next() == nullptr) return head;

  Node* new_head = ReverseRecursive(head->Next());

  head->Next()->SetNext(head);
  head->SetNext(nullptr);
  return new_head;
}


// Print the middle element of a given linked list.
// If there are an even number, print the second of the middle two elements.
void Middle(Node* head) {
  // First idea was to traverse the whole list once to find the length and then traverse to the middle.
  //  Would be O(n) but not very creative.

  // Better idea, have two pointers, one that increments by 2 and one that increments by 1.
  //  Therefore, when the faster pointer hits the end the slower one will be halfway behind it, ie the middle.

  Node* fast = head;
  Node* slow = head;

  while (fast != nullptr && fast->Next() != nullptr) {
    fast = fast->Next()->Next();
    slow = slow->Next();
  }

  // Print the middle.
  slow->Print();
}

// Delete the middle element of a given linked list.
// If there are an even number, print the second of the middle two elements.
void DeleteMiddle(Node* head) {
  // First idea was to traverse the whole list once to find the length and then traverse to the middle.
  //  Would be O(n) but not very creative.

  // Better idea, have two pointers, one that increments by 2 and one that increments by 1.
  //  Therefore, when the faster pointer hits the end the slower one will be halfway behind it, ie the middle.
  //  To delete we then need an even slower pointer that is the previous of the slow pointer.

  Node* fast = head;
  Node* slow = head;
  Node* slow_prev = head;

  while (fast != nullptr && fast->Next() != nullptr) {
    fast = fast->Next()->Next();
    slow_prev = slow;
    slow = slow->Next();
  }

  // Delete the middle.
  slow_prev->SetNext(slow->Next());

  // For completeness.
  slow->SetNext(nullptr);
}

// Given a linked list, delete all the nodes which sum up to zero.
Node* DeleteZeroSum(Node* head) {
  // First idea is to use a stack, adding node pointers to it in such a way that they can be manipulated.
  std::list<Node*> stack {};

  // Edge case single node.
  if (head->Next() == nullptr) {
    // The node has a value of zero.
    if (head->GetValue() == 0) return nullptr;
    return head;
  }

  Node* itr = head;
  int sum {};

  while (itr != nullptr) {
    // Add the next node to the stack.
    stack.push_back(itr);
    sum += itr->GetValue();
    
    // If the sum is zero.
    if (sum == 0) {
      // At the end of the list.
      if (itr->Next() == nullptr) return nullptr;
      stack.push_back(itr->Next());
      itr = itr->Next();

      // For completeness delete all the next pointers of the nodes to be removed.
      while (stack.front() != itr) {
        stack.front()->SetNext(nullptr);
        stack.pop_front();
      }
    }

    // Check each node in the stack up to this point to see if they match the sum.
    auto stack_itr = stack.begin();
    while (*stack_itr != itr) {
      // There is a zero sum between this node and the current node in the overall iteration.
      if ((*stack_itr)->GetValue() == sum) {
        // At the end of the list.
        if (itr->Next() == nullptr) {
          (*stack_itr)->SetNext(nullptr);
          return *stack_itr;
        }
        stack.push_back(itr->Next());
        itr = itr->Next();
        (*stack_itr)->SetNext(stack.back());
        
        // Could theoretically leave all the following out and would achieve a correct result.
        // For completeness delete all the next pointers of the nodes to be removed before this node.
        while (stack.front() != *stack_itr) {
          stack.front()->SetNext(nullptr);
          stack.pop_front();
        }
        
        // Delete the nodes between this node and current node in the overall iteration, excluding this node.
        stack_itr++;
        while (*stack_itr != stack.back()) {
          stack.erase(stack_itr);
          // Does this place the iterator at the next element or the previous one?
          // No it does not move the iterator, have to do it myself. Cannot increment as it does not exist in the stack.
          stack_itr = stack.begin();
          stack_itr++;
        }

        break;
      }
      stack_itr++;
    }

    itr = itr->Next();
  }

  return stack.front();
}

// Given that a linked list represents a number with each node a digit, add 1 to this number.
void AddOne(Node* head) {
  // First idea: reverse the linked list, perform the addition and respective carries, reverse back.
  
  Node* start = Reverse(head);
  Node* original_tail = start;

  // Have potential to add another node if the carry traverses the whole number, it will be local to this scope
  //  and on the stack so in this particular program I will print the number at the end and then remove reference to it.
  Node *new_digit;

  // Increment the first (least significant) digit and perform carry as necessary.
  while ((start->GetValue() + 1) == 10) {
    start->SetValue(0);
    if (start->Next() == nullptr) {
      new_digit = new Node(0);
      start->SetNext(new_digit);
      break;
    }
    start = start->Next();    
  }
  start->SetValue(start->GetValue() + 1);

  // Reverse the list back so it reads like a digit.
  start = Reverse(original_tail);

  start->PrintList();

  // Now remove the stack allocated node to avoid complications.
  start->SetNext(nullptr);
}

// Return true if the given linked list is a palindrome.
// Mine will be if the number reads the same forwards and backwards.
// I assume that the list nodes are store in contiguous memory locations, if not replace the middle pointer
//  with an integer counter.
bool IsPalindrome(Node* head) {
  // Assuming a single node is a palindrome.
  if (head->Next() == nullptr) return true;

  // Use a stack, here I use the Cpp feature std::list, which has a push front and pop front method.
  std::list<int> stack {};

  // Need to find the middle to determine when to start checking the numbers.
  //  Use the same fast and slow pointer method.
  Node* fast = head;
  Node* middle = head;
  // My first rendition had two separate loops, one to find the middle and one to check palindromic or not.
  // Optimize by doing both in one loop

  // To see if there is an even number of elements.
  bool even {false};

  // Now iterate through the linked list.
  Node* nodeitr = head;

  while (nodeitr != nullptr) {
    // Determining where the middle is.
    if (fast != nullptr && fast->Next() != nullptr) {
      fast = fast->Next()->Next();
      middle = middle->Next();
    }
    if (fast == nullptr) even = true;

    // Add the values to the stack for the first half of the list.
    if (nodeitr < middle) {
      stack.push_front(nodeitr->GetValue());
    } 

    // At the middle, if not even it can be whatever so merely continue with the loop.
    else if (nodeitr == middle) {
      if (even) {
        if (nodeitr->GetValue() != stack.front()) {
          return false;
        }
      }
    }

    // We are in the second half of the list.
    else {
      if (nodeitr->GetValue() != stack.front()) {
        return false;
      }
      stack.pop_front();
    }
    nodeitr = nodeitr->Next();
  }

  // Out of the loop means it is a palindrome.
  return true;
}

// Given a linked list, rotate counter-clockwise by k nodes.
Node* Rotate(Node* head, int k) {
  if (k == 0) return head;
  Node* curr = head;
  Node* new_head = nullptr;
  
  // Find the place to become the new tail after rotation.
  for (int i = 1; i < k; i++) {
    curr = curr->Next();
    // If k is greater than the number of nodes in the list.
    if (curr == nullptr) curr = head;
  } 

  // Assign the new head of the linked list.
  // If the rotations equate to the original linked list return such.
  if (curr->Next() == nullptr) return head;
  new_head = curr->Next();

  // Separate the tail from the new head.
  curr->SetNext(nullptr);

  // Find the end and adjoin the two separated linked lists.
  curr = new_head;
  while (curr->Next() != nullptr) {
    curr = curr->Next();
  }   
  curr->SetNext(head);

  return new_head;
}

int main(int argc, char* argv[]) {
  // Create the linked list.
  Node node1(6);
  Node node2(2);
  Node node3(3);
  Node node4(-5);
  Node node5(4);

  node1.SetNext(&node2);
  node2.SetNext(&node3);
  node3.SetNext(&node4);
  node4.SetNext(&node5);

  std::cout << "Initial list\n";
  node1.PrintList();

  // List reversal
/*
  std::cout << "Reversed list\n";
  //Node* nodeptr = Reverse(&node1);
  Node* new_head = ReverseRecursive(&node1);
  new_head->PrintList();
*/

  // List rotation
/*
  std::cout << "\nList rotated 2 times\n";
  Node* nodeptr = Rotate(&node1, 2);
  nodeptr->PrintList();
*/

  // Middle manipulation
  std::cout << "\nMiddle of the list\n";
  Middle(&node1);
/*  std::cout << "\nDeleting the middle item\nThe new list\n";
  DeleteMiddle(nodeptr);
  nodeptr->PrintList();
*/

  // Checking palindrome
  std::cout << "\nPalindrome checking\n";
  if (IsPalindrome(&node1)) std::cout << "Palindrome\n";
  else std::cout << "Not a palindrome\n";

  // Incrementing
/*
  std::cout << "\nIncrementing the number\n";
  AddOne(&node1);
*/

  // Deleting zero sums
  std::cout << "\nDeleting zero sums\n";
  Node* nodeptr = DeleteZeroSum(&node1);
  nodeptr->PrintList();

  return 0;
}
