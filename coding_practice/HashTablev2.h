#ifndef CODING_PRACTICE_HASH_TABLE_V2_
#define CODING_PRACTICE_HASH_TABLE_V2_

#include <iostream>

struct DataItem {
  int key;
  int value;
  DataItem* next {nullptr};
};

int hash(int key) {
  return key % 10;
}

class HashTable {
  public:
    HashTable() {
      for (int i = 0; i < 10; i++) {
        table_[i] = nullptr;
      }
    }
    ~HashTable() = default;

  void Insert(DataItem* toadd);
  void Delete(DataItem* todel);
  DataItem* Search(int key);

  void PrintTable() {
    for (int i = 0; i < 10; i++) {
      std::cout << i << ": ";
      if (table_[i] != nullptr) {
        std::cout << table_[i]->key << ", " << table_[i]->value;
        DataItem* item = table_[i]->next;
        while (item != nullptr) {
          std::cout << " -> " << item->key << ", " << item->value;
          item = item->next;
        }
      } 
      std::cout << "\n";
    }
  }

  private:
    DataItem* table_[10];
};

#endif // CODING_PRACTICE_HASH_TABLE_V2_
