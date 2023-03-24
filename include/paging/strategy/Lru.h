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
  Node *next;
  Node *prev;
  Node() : val(-1), next(nullptr), prev(nullptr) {};
  explicit Node(int t_val) : val(t_val), next(nullptr), prev(nullptr) {};
};

// Double-ended Linked List
class DLList {
 public:
  DLList() : head_(new Node()), tail_(new Node()), size_(0) {
    head_->next = tail_;
    tail_->prev = head_;
  }
 public:
  void AddToHead(Node &node);
  void RemoveTail();
  void Remove(Node *node);
  void MoveToHead(Node *node);
  Node *GetTail();
  size_t Size();
  void PrintListAndVictim();

 private:
  Node *head_;
  Node *tail_;
  size_t size_;
};

// use `double-ended linked list` and `map` to ensure both
// insert and remove is O(1).
class Lru : public IStrategy {
 protected:
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) override;
  void PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) override {};
 public:
  int GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "LRU";
  // double-ended linked list
  DLList dl_list_{};
 protected:
  void Reset_() override;
 private:
  // page_no -> node*
  std::unordered_map<int, Node *> page_node_map_{};
};

} // paging

