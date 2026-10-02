#ifndef CODING_PRACTICE_MIN_HEAP_H_
#define CODING_PRACTICE_MIN_HEAP_H_

#include <iostream>

class HeapNode {
  public:
    HeapNode(int key) : key_(key) {}
    ~HeapNode() = default;
  
    void SetKey(int key) { key_ = key; }
    void SetLeft(HeapNode* child) { left_ = child; }
    void SetRight(HeapNode* child) { right_ = child; }
    void SetParent(HeapNode* parent) { parent_ = parent; }

    int GetKey() { return key_; }
    HeapNode* GetLeft() { return left_; }
    HeapNode* GetRight() { return right_; }
    HeapNode* GetParent() { return parent_; }

    void Print() {
      std::cout << "Key: " << key_ << "\n";
      std::cout << "Left: ";
      if (left_ != nullptr) left_->Print();
      std::cout << "\nRight: ";
      if (right_ != nullptr) right_->Print();
      std::cout << "\n";
    }

  private:
    int key_;
    HeapNode* left_ {nullptr};
    HeapNode* right_ {nullptr};
    HeapNode* parent_ {nullptr};
};

class MinHeap {
  public:
    MinHeap(HeapNode* root) : root_(root) {}
    ~MinHeap() = default;

    void Insert(HeapNode* toadd);
    HeapNode* Delete(HeapNode* todel);
    HeapNode* GetMin();
    void Heapify(HeapNode* node);
    HeapNode* ExtractMin();
    void DecreaseKey(HeapNode* todec);

    void PrintHeap() {
      if (root_ != nullptr) root_->Print();
    }

  private:
    HeapNode* root_ {nullptr};
};

#endif // CODING_PRACTICE_MIN_HEAP_H_
