#ifndef CODING_PRACTICE_BINARY_TREE_H_
#define CODING_PRACTICE_BINARY_TREE_H_

#include <iostream>

class BSTNode {
  public:
    BSTNode(int value) : value_(value) {}
    ~BSTNode() { 
      left_ = nullptr;
      right_ = nullptr;
    }

    void SetValue(int val) { value_ = val; }
    int GetValue() { return value_; }

    void SetLeft(BSTNode* child) { left_ = child; }
    void SetRight(BSTNode* child) { right_ = child; }
    BSTNode* GetLeft() { return left_; }
    BSTNode* GetRight() { return right_; }

    void PrintTree() {
      std::cout << "Node: " << value_ << "\n";
      std::cout << "Left: ";
      if (left_ != nullptr) left_->PrintTree();
      std::cout << "\nRight: ";
      if (right_ != nullptr) right_->PrintTree();
      std::cout << "\n";
    }

  private:
    int value_;
    BSTNode* left_ = nullptr;
    BSTNode* right_ = nullptr;
};


#endif // CODING_PRACTICE_BINARY_TREE_H_
