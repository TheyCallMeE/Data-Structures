#include "HashTablev2.h"

// This version of hash table uses a linked list to resolve collisions.
void HashTable::Insert(DataItem* toadd) {
  if (toadd == nullptr) return;

  // Find the index using the hash function.
  int index = hash(toadd->key);

  // Collision detected, add to the end of the list.
  if (table_[index] != nullptr) {
    DataItem* prev = table_[index];
    DataItem* itr = table_[index]->next;
    while (itr != nullptr) {
      prev = itr;
      itr = itr->next;
    }
    prev->next = toadd;
    return;
  }
  // Otherwise we are at an empty slot.
  table_[index] = toadd;
}

// Helper function for Delete()
bool Match(DataItem* left, DataItem* right) {
  if (left != nullptr && right != nullptr 
      && left->key == right->key && left->value == right->value) return true;
  return false;
}

// Delete an item from the table.
// If it is part of the linked list at a given bucket, remove it from the list.
void HashTable::Delete(DataItem* todel) {
  if (todel == nullptr) return;

  // Find the index using the hash function.
  int index = hash(todel->key);

  // If the first item in the bucket does not match we parse the linked list.
  if (!Match(table_[index], todel)) {
    DataItem* prev = table_[index];
    DataItem* itr = table_[index]->next;

    while (itr != nullptr) {
      if (Match(itr, todel)) {
        prev->next = itr->next;
        itr->next = nullptr;
        return;
      }
      prev = itr;
      itr = itr->next;
    }
    // If we have reached here the item does not exist in the table.
    return;
  }

  // Otherwise we have found a match.
  // If there is a linked list at this bucket remove the head.
  if (table_[index]->next != nullptr) {
    DataItem* temp = table_[index]->next;
    table_[index]->next = nullptr;
    table_[index] = temp;
    return;
  }
  // Otherwise merely delete the entry.
  table_[index] = nullptr;
}

// Search for the given key.
DataItem* HashTable::Search(int key) {
  // FInd the index using the hash function.
  int index = hash(key);

  // We have the bucket the key should be in, traverse the list if it exists.
  // Otherwise the item does not exist in the table.
  DataItem* itr = table_[index];
  while (itr != nullptr) {
    if (itr->key == key) return itr;
    itr = itr->next;
  }
  return nullptr;
}

int main(int argc, char* argv[]) {
  HashTable hash;

  DataItem item1;
  item1.key = 1;
  item1.value = 16;
  item1.next = nullptr;
  DataItem item2;
  item2.key = 16;
  item2.value = 47;
  item2.next = nullptr;
  DataItem item3;
  item3.key = 6;
  item3.value = 600;
  item3.next = nullptr;
  DataItem item4;
  item4.key = 7;
  item4.value = 1;
  item4.next = nullptr;
  DataItem item5;
  item5.key = 0;
  item5.value = 519;
  item5.next = nullptr;
  DataItem item6;
  item6.key = 20;
  item6.value = 88;
  item6.next = nullptr;
  DataItem item7;
  item7.key = 27;
  item7.value = 321;
  item7.next = nullptr;
  DataItem item8;
  item8.key = 47;
  item8.value = 67;
  item8.next = nullptr;

  hash.Insert(&item1);
  hash.Insert(&item2);
  hash.Insert(&item3);
  hash.Insert(&item4);
  hash.Insert(&item5);
  hash.Insert(&item6);
  hash.Insert(&item7);  
  hash.Insert(&item8);  

  hash.PrintTable();

  std::cout << "\n";

  std::cout << "Deleting key 27.\n";

  hash.Delete(&item7);

  hash.PrintTable();

  std::cout << "\nSearching for key 6\n";

  DataItem* item = hash.Search(6);
  if (item != nullptr) std::cout << "Found: " << item->key << ", " << item->value << "\n";
  else std::cout << "Not found\n";

  return 0;
}
