#include "HashTable.h"

// Insert a given data item into the table, using linear probing to resolve collisions.
// If the table is full do not alter it.
void HashTable::Insert(DataItem* toadd) {
  // Get the location for the key using the hash function.
  int index = hash(toadd->key);
  // Store the starting location to break the loop.
  int start = index;

  // This is linear probing, travelling forward in the hash table until an open spot is found.
  while (table_[index] != nullptr) {
    index++;
    // Wrap the index.
    if (index == 20) index = 0;

    // Havent found an empty slot.
    if (index == start) return;
  }
  // Insert the key at the found index.
  table_[index] = toadd;
}

// If the given data item is in the table, remove it. Otherwise do not alter the table.
// Upon removing an item, move to the next bucket and reinsert it to fix the table and any linear probing.
void HashTable::Delete(DataItem* todel) {
  // We could use the Search function to find the element, however, this returns a data item and we need an index.
  // Similarly to searching we iterate through the table until a match is found.
  int index = hash(todel->key);
  // Copy the index to break the search loop.
  int start = index;

  // Both the key and the value have to match for the element to match.
  // Could just compare the pointers (memory locations) but this is more concrete.
  // Maybe add a function to achieve this, something like bool Match(DataItem* item1, DataItem* item2).
  while (table_[index]->key != todel->key || table_[index]->value != todel->value) {
    index++;
    // Wrap the index.
    if (index == 20) index = 0;
    
    // Break the loop and function if we havent found the item.
    if (index == start) return;
  }
  // Delete the item.
  table_[index] = nullptr;

  // Fix the table.
  index++;
  while (table_[index] != nullptr) {
    DataItem* temp = table_[index];
    table_[index] = nullptr;
    Insert(temp);

    index++;
    if (index == 20) index = 0;
  }
}

// Return the DataItem that matches the key if it exists in the table, null otherwise.
DataItem* HashTable::Search(int tofind) {
  // Find the potential index of the given key.
  int index = hash(tofind);
  // Store the start to break the search loop if the item does not exist.
  int start = index;

  // Commence the search.
  while (table_[index] == nullptr || table_[index]->key != tofind) {
    index++;
    // Wrap the index.
    if (index == 20) index = 0;

    // Break the search.
    if (index == start) return nullptr;
  }
  return table_[index];
}

int main(int argc, char* argv[]) {
  HashTable hash;

  DataItem item1 {1, 16};
  DataItem item2 {16, 47};
  DataItem item3 {6, 600};
  DataItem item4 {7, 1};
  DataItem item5 {0, 519};
  DataItem item6 {20, 88};
  DataItem item7 {27, 321};

  hash.Insert(&item1);
  hash.Insert(&item2);
  hash.Insert(&item3);
  hash.Insert(&item4);
  hash.Insert(&item5);
  hash.Insert(&item6);
  hash.Insert(&item7);

  hash.PrintTable();

  std::cout << "\n";

  hash.Delete(&item4);

  hash.PrintTable();

  std::cout << "Searching for item with key 27\n";
  DataItem* item = hash.Search(27);
  if (item != nullptr) {
    std::cout << "Found: " << item->key << ", " << item->value << "\n";
  } else {
    std::cout << "Not found.\n";
  }

  return 0;
}
