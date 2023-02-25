//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include <unordered_map>
#include "IStrategy.h"

namespace paging::strategy {

struct Node {
  int val;
  Node* next;
  Node* prev;
  Node(): val(-1), next(nullptr), prev(nullptr) {};
  explicit Node(int t_val): val(t_val), next(nullptr), prev(nullptr) {};
};

// Double-ended Linked List
class DLList {
 public:
  DLList(): head_(new Node()), tail_(new Node()) {
    head_->next = tail_;
    tail_->prev = head_;
  }
 public:
  void AddToHead(Node& node);
  void RemoveTail();
  void Remove(Node* node);
  void MoveToHead(Node* node);
  Node* GetTail();

 private:
  Node* head_;
  Node* tail_;
};

// use `double-ended linked list` and `map` to ensure both
// insert and remove is O(1).
class Lru: public IStrategy{
 protected:
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) override;
  void AfterReplace_(PhysicalMemory &frame,
                     PageTable &page_table,
                     int old_page_number,
                     int new_page_number) override;
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override {};
 public:
  int GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "LRU";
  // double-ended linked list
  DLList dl_list_{};
  // page_number -> node*
  std::unordered_map<int, Node*> page_node_map_{};
};

} // paging

