#ifndef CODING_PRACTICE_HASH_TABLE_H_
#define CODING_PRACTICE_HASH_TABLE_H_

#include <iostream>

struct DataItem {
  int key;
  int value;
};

// One of the simplest hashes, more for understanding the data structure than hashing itself.
int hash(int key) {
  return key % 20;
}

class HashTable {
  public:
    HashTable() {
      for (int i = 0; i < 20; i++) {
        table_[i] = nullptr;
      }
    }
    ~HashTable() = default;

    void Insert(DataItem* toadd);
    void Delete(DataItem* todel);
    DataItem* Search(int tofind);

    void PrintTable() {
      for (int i = 0; i < 20; i++) {
        std::cout << i << ": ";
        if (table_[i] != nullptr) {
          std::cout << table_[i]->key << ", " << table_[i]->value << "\n";
        } else {
          std::cout << "\n";
        }
      }
    }

  private:
    DataItem* table_[20] {};
};

#endif // CODING_PRACTICE_HASH_TABLE_H_
