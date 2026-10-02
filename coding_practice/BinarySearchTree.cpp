#include "BinarySearchTree.h"

#include <climits>
#include <vector>

// Insert a node into the tree.
void Insert(BSTNode* root, BSTNode* toadd) {
  BSTNode* itr = root;

  if (root == nullptr) return;

  // Greater than and equal to to the right of a root node.
  // Less than to the left of a root node.

  // First time iteratively.
  BSTNode* parent = nullptr;

  while (itr != nullptr) {
    // Save the root.
    parent = itr;
    // Less than.
    if (toadd->GetValue() < itr->GetValue()) {
      itr = itr->GetLeft();
    }

    // Equal or greater than.
    else {
      itr = itr->GetRight();
    }
  }

  // We have exited the search loop, thus we are at a leaf position suitable for the new node.
  if (toadd->GetValue() < parent->GetValue()) {
    parent->SetLeft(toadd);
  }
  else {
    parent->SetRight(toadd);
  }

  return;
}

// Recursive attempt.
// The way I laid out my Binary Search Tree means that I call a method on a parent node to add a child.
// If I wanted to this function could return a BSTNode* given a value, this would then be added in main instead of here.
void InsertRecursive(BSTNode* root, BSTNode* toadd) {
  // Base case, either the root is null or the position to be added to is free.
  if (root == nullptr) return;

  // The node is less than the current root.
  if (toadd->GetValue() < root->GetValue()) {
    // Free spot to place the new node.
    if (root->GetLeft() == nullptr) {
      root->SetLeft(toadd);
      return;
    } else {
      InsertRecursive(root->GetLeft(), toadd);
    }
  }

  // The node is greater than or equal to the current root.
  else {
    // Free spot to place the new node.
    if (root->GetRight() == nullptr) {
      root->SetRight(toadd);
      return;
    } else {
      InsertRecursive(root->GetRight(), toadd);
    }
  }

  return;
}

// The following is my first attempt at binary tree delete, it fails because I default to using the 
//  left child and subtree to replace the deleted node but the rotation is incorrect as it invalidates
//  the principle of a BST. Deletion is much more difficult than I initially thought.

// Delete a given node from the tree.
BSTNode* FirstDelete(BSTNode* root, BSTNode* todel) {
  // Edge case, empty tree.
  if (root == nullptr) return root;

  // Edge case, single node tree with the root to be deleted.
  if (root == todel && root->GetLeft() == nullptr && root->GetRight() == nullptr) return nullptr;

  // Iterate through the tree until we find the node to be deleted.
  BSTNode* itr = root;
  BSTNode* parent = root;
  BSTNode* temp {};
  BSTNode* temp_right {};

  while (itr != nullptr && itr != todel) {
    parent = itr;
    if (todel->GetValue() < itr->GetValue()) {
      itr = itr->GetLeft();
    }

    else {
      itr = itr->GetRight();
    }
  }

  // If we broke the while because the node does not exist, return the original tree.
  if (itr == nullptr) return root;

  // Otherwise we have found the node to be deleted and should begin fixing the tree.
  // I default to using the left child and subtree if it exists, if not use the right child and subtree.
  // If we reach a leaf node we are done.

  // Check the special case of the root to be deleted.
  if (root == itr) {
    // As I said I will default to the left, if the right is nullptr merely return this as the new root.
    if (itr->GetRight() == nullptr) return itr->GetLeft();
    
    // Vice versa for the left being nullptr, remember we already covered both children being null of the root.
    if (itr->GetLeft() == nullptr) return itr->GetRight();

    // Set the parent to null after storing its right child.
    temp = itr->GetRight();
    root = itr->GetLeft();
    itr = itr->GetLeft();
    parent = nullptr;
  }

  else if (itr->GetLeft() != nullptr) {
    temp = itr->GetRight();
    itr = itr->GetLeft();
  }

  else if (itr->GetRight() != nullptr) {
    temp = itr->GetLeft();
    itr = itr->GetRight();
  }

  // If we reach this case we are deleting a leaf node.
  else {
    // We do not need to worry about the single node case here as that has been addressed at the start of the function.
    // The node deleted was the left child of the parent.
    if (todel->GetValue() < parent->GetValue()) {
      parent->SetLeft(nullptr);
      return root;
    } 
    // The node deleted was the right child of the parent.
    else {
      parent->SetRight(nullptr);
      return root;
    }
  }

  // Now we start to fix the tree.


  // Now to fix the tree.
  while (itr != nullptr) {
    // We have not deleted the root.
    if (parent != nullptr) {
      if (todel->GetValue() < parent->GetValue()) {
        parent->SetLeft(itr);
      }

      else {
        parent->SetRight(itr);
      }
      parent = nullptr;
    }

    if (itr->GetRight()) 
      temp_right = itr->GetRight();
    itr->SetRight(temp);
    temp = temp_right;
    itr = itr->GetLeft();
  }

  return root;
}

// Delete a given node of a binary search tree.
BSTNode* Delete(BSTNode* root, BSTNode* todel) {
  // Edge cases of one node to be deleted or no nodes.
  if (root == nullptr) return root;
  if (root == todel && root->GetLeft() == nullptr && root->GetRight() == nullptr) return nullptr;

  // Find the node to be deleted.
  BSTNode* itr = root;
  BSTNode* parent = root;
  BSTNode* temp_left {};
  BSTNode* temp_right {};

  while (itr != nullptr && itr != todel) {
    parent = itr;

    if (todel->GetValue() < itr->GetValue()) {
      itr = itr->GetLeft();
    }

    else {
      itr = itr->GetRight();
    }
  }

  // Broke from search due to node not existing.
  if (itr == nullptr) return root;

  // Special case that root is to be deleted.
  if (itr == root) parent = nullptr;

  // Case 1: Leaf node.
  if (itr->GetLeft() == nullptr && itr->GetRight() == nullptr) {
    // We already addressed the edge case of a single node tree to be deleted so parent has to be valid here.
    if (itr->GetValue() < parent->GetValue()) {
      parent->SetLeft(nullptr);
      return root;
    }

    else {
      parent->SetRight(nullptr);
      return root;
    }
  }

  // Case 2: One child.
  else {
    // Unlike case 1 we could be deleting the root with only one child so check the parent.
    if (parent != nullptr) {
      if (itr->GetRight() == nullptr) {
        if (itr->GetValue() < parent->GetValue()) {
          parent->SetLeft(itr->GetLeft());
          return root;
        }
        else {
          parent->SetRight(itr->GetLeft());
          return root;
        }
      }
  
      else if (itr->GetLeft() == nullptr) {
        if (itr->GetValue() < parent->GetValue()) {
          parent->SetLeft(itr->GetRight());
          return root;
        }
        else {
          parent->SetRight(itr->GetRight());
          return root;
        }
      }
    }
    // We are deleting the root.
    else {
      if (itr->GetRight() == nullptr) return itr->GetLeft();
      else if (itr->GetLeft() == nullptr) return itr->GetRight();
    }
  }

  // Case 3: Two children, choose the lowest left node of the right subtree.
  temp_left = itr->GetLeft();
  temp_right = itr->GetRight();

  // Find lowest node of the right subtree.
  BSTNode* itr_parent = itr;
  itr = itr->GetRight();
  while (itr->GetLeft() != nullptr) {
    itr_parent = itr;
    itr = itr->GetLeft();
  }

  // Fix the parents children unless we are deleting the root.
  if (parent != nullptr) {
    if (todel->GetValue() < parent->GetValue()) {
      parent->SetLeft(itr);
    } else {
      parent->SetRight(itr);
    } 
  }

  // Replace the node with the found one.
  itr->SetLeft(temp_left);
  // Instance where the found node is the only child on the right subtree of the node to be deleted.
  if (itr != temp_right) itr->SetRight(temp_right);
  if (parent == nullptr) root = itr;

  // Delete the leaf node we found.
  if (itr->GetValue() < itr_parent->GetValue()) {
    itr_parent->SetLeft(nullptr);
  }
  else {
    itr_parent->SetRight(nullptr);
  }

  return root;
}

// Find the height of the binary tree.
void Height(BSTNode* root, int& height, int& max_height) {
  if (root == nullptr || (root->GetLeft() == nullptr && root->GetRight() == nullptr)) {
    if (height > max_height) max_height = height;
    --height;
    return;
  }
  Height(root->GetLeft(), ++height, max_height);
  Height(root->GetRight(), ++height, max_height);
  --height;
}

// Count the number of leaves in the binary tree.
void CountLeaves(BSTNode* root, int& leaves) {
  if (root == nullptr) return;
  if (root->GetLeft() == nullptr && root->GetRight() == nullptr) {
    leaves++;
    return;
  }
  CountLeaves(root->GetLeft(), leaves);
  CountLeaves(root->GetRight(), leaves);
}

// Preorder traversal of the tree, goes root, left, right.
void PreorderTraversal(BSTNode* root) {
  if (root == nullptr) return;
  std::cout << "Node: " << root->GetValue();
  PreorderTraversal(root->GetLeft());
  PreorderTraversal(root->GetRight());
}
// Inorder traversal of the tree, goes left, root, right.
void InorderTraversal(BSTNode* root) {
  if (root == nullptr) return;
  InorderTraversal(root->GetLeft());
  std::cout << "Node: " << root->GetValue();
  InorderTraversal(root->GetRight());
}

// Postorder traversal of the tree, goes left, right, root.
void PostorderTraversal(BSTNode* root) {
  if (root == nullptr) return;
  PostorderTraversal(root->GetLeft());
  PostorderTraversal(root->GetRight());
  std::cout << "Node: " << root->GetValue();
}

// Summation of all the values of the nodes of the tree.
void SumOfTree(BSTNode* root, int& sum) {
  // Using preorder traversal.
  if (root == nullptr) return;
  sum += root->GetValue();
  SumOfTree(root->GetLeft(), sum);
  SumOfTree(root->GetRight(), sum);
}

// Helper function to find the minimum height and perform 
int MinHeight(BSTNode* root, int& height, int& min_height) {
  if (root == nullptr || (root->GetLeft() == nullptr && root->GetRight() == nullptr)) {
    if (height > min_height + 1) return 0;
    else if (height < min_height) min_height = height;
    --height;
    return 1;
  }
  int res {};
  res = MinHeight(root->GetLeft(), ++height, min_height);
  if (res == 0) return 0;
  res = MinHeight(root->GetRight(), ++height, min_height);
  if (res == 0) return 0;
  --height;
  return res;
}

// A balanced tree is one where the difference in heights of the subtrees is no more than one.
// Uses the helper function MinHeight() above.
bool IsBalanced(BSTNode* root) {
  // A single node tree is balanced.
  if (root->GetLeft() == nullptr && root->GetRight() == nullptr) return true;
  int height {1};
  int min_height {INT_MAX - 1};

  if (MinHeight(root, height, min_height) == 0) return false;
  return true;
}

// Helper function for checking the height of a perfect tree.
int PerfectHeight(BSTNode* root, int& height, int perf_height) {
  if (root == nullptr) return 0;
  if (root->GetLeft() == nullptr && root->GetRight() == nullptr) {
    if (height != perf_height) return 0;
    --height;
    return 1;
  }

  int res {};
  res = PerfectHeight(root->GetLeft(), ++height, perf_height);
  if (res == 0) return 0;
  res = PerfectHeight(root->GetRight(), ++height, perf_height);
  if (res == 0) return 0;
  --height;
  return 1;
}

// Determines if the given tree is a perfect binary tree.
// This means all internal nodes have two children and the leaves are at the same level.
// Uses the above helper function for height checking.
bool PerfectTree(BSTNode* root) {
  // A single node tree is perfect.
  if (root->GetLeft() == nullptr && root->GetRight() == nullptr) return true;

  // First gather the height of the tree by iterating down the left-most subtree.
  BSTNode* itr = root;
  int perf_height {1};
  while (itr ->GetLeft() != nullptr) {
    itr = itr->GetLeft();
    ++perf_height;
  }
  // Now check the height which also checks the presence of invalid children nodes (only one child).
  int height {1};
  if (PerfectHeight(root, height, perf_height) == 0) return false;
  return true;
}

// Helper function for balancing the tree.
void CreateArray(BSTNode* root, std::vector<BSTNode*>& nodes) {
  if (root == nullptr) return;

  if (root->GetLeft() == nullptr && root->GetRight() == nullptr) {
    nodes.push_back(root);
    return;
  }

  CreateArray(root->GetLeft(), nodes);
  nodes.push_back(root);
  CreateArray(root->GetRight(), nodes);
}

// If the tree is unbalanced balance it.
BSTNode* BalanceTree(BSTNode* root) {
  // If the tree is balanced we are done.
  if (IsBalanced(root)) return root;

  // Add the nodes to a sorted array through traversal, using the helper function CreateArray() above.
  std::vector<BSTNode*> nodes {};
  CreateArray(root, nodes);

  // Construct the new balanced tree. 
  auto left_itr = nodes.begin();
  auto left_parent = left_itr;
  auto right_itr = nodes.begin();
  auto right_parent = right_itr;

  // Find the middle.
  int mid = nodes.size() / 2;
  // If it is an even number of nodes select the right of the middle two (my choice).
  for (int i = 0; i < mid; i++) {
    left_itr = left_parent;
    right_itr = right_parent;
    left_parent++;
    right_parent++;
  }

  BSTNode* new_root = *left_parent;
  right_itr = right_parent;
  right_itr++;

  // We selected the right of the middle two so the loop will end before the left iterator reaches outside the list.
  while (right_itr != nodes.end()) {
    (*left_parent)->SetLeft(*left_itr);
    if (left_parent != right_parent) (*left_parent)->SetRight(nullptr);
    (*right_parent)->SetRight(*right_itr);
    if (left_parent != right_parent) (*right_parent)->SetLeft(nullptr);
    // Error will occur if we try to go beyond the beginning of the vector.
    if (left_itr != nodes.begin()) left_itr--;
    // We do not have to construct the tree anymore.
    else break;
    left_parent--;
    right_itr++;
    right_parent++;
  }

  // If we broke one node short of completing the tree.
  if ((*left_parent)->GetLeft() != *left_itr) {
    (*left_parent)->SetLeft(*left_itr);
    (*left_parent)->SetRight(nullptr);
  }

  // Make the final nodes leaf nodes.
  (*left_itr)->SetLeft(nullptr);
  (*left_itr)->SetRight(nullptr);
  (*right_itr)->SetLeft(nullptr);
  (*right_itr)->SetRight(nullptr);

  return new_root;
}

// Now to balance a tree with a minimum possible height.
// Used the same CreateArray() utility.
BSTNode* BalanceMinHeight(BSTNode* root) {
  // If the tree is balanced we are done.
  if (IsBalanced(root)) return root;

  // Add the nodes to a sorted array through traversal, using the helper function CreateArray() above.
  std::vector<BSTNode*> nodes {};
  CreateArray(root, nodes);
  
  int left_itr {0};
  int right_itr {0};
  int left_parent {0};
  int right_parent {0};

  // Determine the middle and move the parent pointers there.
  int mid = nodes.size() / 2;
  left_parent += mid;
  right_parent += mid;

  BSTNode* new_root = nodes[left_parent];
  
  // Store the last index for checking purposes.
  int bound = nodes.size() - 1;

  while (left_parent > 0 || right_parent < bound) {
    if (left_parent != 0) {
      // Create the left subtree.
      if ((left_parent - 2) >= 0) {
        left_itr = left_parent - 2;
        nodes[left_parent]->SetLeft(nodes[left_itr]);
      
        nodes[left_itr]->SetRight(nodes[left_itr + 1]);
        // The right child will always be a leaf node.
        nodes[left_itr + 1]->SetLeft(nullptr);
        nodes[left_itr + 1]->SetRight(nullptr);
      }
      else {
        left_itr = left_parent - 1;
        nodes[left_parent]->SetLeft(nodes[left_itr]);
        // At a leaf node.
        nodes[left_itr]->SetLeft(nullptr);
        nodes[left_itr]->SetRight(nullptr);
      }
      left_parent = left_itr;
    }
    
    if (right_parent != bound) {
      // Create the right subtree.
      if ((right_parent + 2) <= bound) {
        right_itr = right_parent + 2;
        nodes[right_parent]->SetRight(nodes[right_itr]);
      
        nodes[right_itr]->SetLeft(nodes[right_itr - 1]);
        // The left child will always be a leaf node.
        nodes[right_itr - 1]->SetLeft(nullptr);
        nodes[right_itr - 1]->SetRight(nullptr);
      }
      else {
        right_itr = right_parent + 1;
        nodes[right_parent]->SetRight(nodes[right_itr]);
        // At a leaf node.
        nodes[right_itr]->SetLeft(nullptr);
        nodes[right_itr]->SetRight(nullptr);
      }
      right_parent = right_itr;
    }
  }

  return new_root;
}

BSTNode* MergeTrees(BSTNode* root1, BSTNode* root2) {

}

int main(int argc, char* argv[]) {
  BSTNode root(10);
  BSTNode left_child(3);
  BSTNode right_child(11);
  BSTNode x(2);
  BSTNode y(4);
  BSTNode z(5);
  BSTNode a(6);

  root.SetLeft(&left_child);
  root.SetRight(&right_child);

  std::cout << "Initial tree\n";
  root.PrintTree();

  Insert(&root, &x);
  InsertRecursive(&root, &y);
  InsertRecursive(&root, &z);
  InsertRecursive(&root, &a);

  std::cout << "\n\nTree after insertions\n";
  root.PrintTree();

  std::cout << "\n\nCounting leaves\n";
  int leaves {0};
  CountLeaves(&root, leaves);
  std::cout << "Leaves: " << leaves << "\n";

  std::cout << "\n\nGetting the height of the tree\n";
  int height {1};
  int max {0};
  Height(&root, height, max);
  std::cout << "Height: " << max << "\n";
/*
  std::cout << "\n\nTree after deleting 3\n";
  root = *Delete(&root, &root);
  root.PrintTree();
*/
  std::cout << "\n\nSeeing if the tree is balanced\n";
  if (IsBalanced(&root)) std::cout << "Tree is balanced\n";
  else std::cout << "Tree is not balanced\n";

  std::cout << "\n\nSeeing if the tree is perfect\n";
  if (PerfectTree(&root)) std::cout << "Tree is perfect\n";
  else std::cout << "Tree is not perfect\n";

  std::cout << "\n\nSum of the tree is: ";
  int sum {0};
  SumOfTree(&root, sum);
  std::cout << sum << "\n";
/*
  std::cout << "\n\nBalancing the tree\n";
  BSTNode* new_root = BalanceTree(&root);
  height = 1;
  max = 0;
  Height(new_root, height, max);
  std::cout << "This has a height of : " << max << "\n";
  new_root->PrintTree();
*/
  std::cout << "\n\nBalancing the tree with a minimum height\n";
  BSTNode* new_root = BalanceMinHeight(&root);
  height = 1;
  max = 0;
  Height(new_root, height, max);
  std::cout << "This has a height of : " << max << "\n";
  new_root->PrintTree();

  return 0;
}
