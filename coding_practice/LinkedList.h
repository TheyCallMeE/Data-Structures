#ifndef CODING_PRACTICE_LINKED_LIST_H_
#define CODING_PRACTICE_LINKED_LIST_H_

#include <iostream>


// Singly-linked list node.
class Node {
  public:
    Node(int value) : value_(value) {}
    ~Node() { next_ = nullptr; }

    int GetValue() { return value_; }
    void SetValue(int val) { value_ = val; }

    void SetNext(Node* next) { next_ = next; }
    Node* Next() { return next_; }

    void Print() { 
      std::cout << "Node value: " << value_ << "\n";
    }

    void PrintList() { 
      std::cout << "Node value: " << value_ << "\n";
      if (next_ != nullptr)
        next_->PrintList();
    }

  private:
    int value_;
    Node* next_ = nullptr;
};

#endif  // CODING_PRACTICE_LINKED_LIST_H_
