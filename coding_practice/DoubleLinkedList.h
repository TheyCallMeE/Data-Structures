#ifndef CODING_PRACTICE_DOUBLE_LINKED_LIST_H_
#define CODING_PRACTICE_DOUBLE_LINKED_LIST_H_

#include <iostream>

class Node {
  public:
    Node(int val) : value_(val) {}
    ~Node() {
      next_ = nullptr;
      prev_ = nullptr;
    }

    int GetValue() { return value_; }
    Node* GetNext() { return next_; }
    Node* GetPrev() { return prev_; }
    
    void SetValue(int val) { value_ = val; }
    void SetNext(Node* next) { next_ = next; }
    void SetPrev(Node* prev) { prev_ = prev; }

    void PrintList() {
      std::cout << value_ << " -> ";
      if (next_ != nullptr) next_->PrintList();
    }

  private:
    int value_;
    Node* next_ {};
    Node* prev_ {};

};

#endif // CODING_PRACTICE_DOUBLE_LINKED_LIST_H_
