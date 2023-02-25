//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Lru.h"

namespace paging::strategy {
// Lru
int Lru::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  return dl_list_.GetTail()->val;
}
void Lru::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  Node* node = new Node(page_number);
  page_node_map_[page_number] = node;
  dl_list_.AddToHead(*node);
}
void Lru::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  if (page_node_map_.find(page_number) != page_node_map_.end()) {
    Node* node = page_node_map_[page_number];
    dl_list_.MoveToHead(node);
  }
}
void Lru::AfterReplace_(PhysicalMemory &frame,
                        PageTable &page_table,
                        int old_page_number,
                        int new_page_number) {
  page_node_map_.erase(dl_list_.GetTail()->val);
  dl_list_.RemoveTail();
  AfterNewPage_(frame, page_table, new_page_number);
}
std::string Lru::GetName() {
  return name_;
}

// DLList
void DLList::AddToHead(Node& node) {
  head_->next->prev = &node;
  node.next = head_->next;

  head_->next = &node;
  node.prev = head_;
}
void DLList::RemoveTail() {
  Node* node = tail_->prev;
  Remove(node);
}
void DLList::Remove(Node *node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;

  delete node;
  node = nullptr;
}
void DLList::MoveToHead(Node *node) {
  // Remove current position
  node->prev->next = node->next;
  node->next->prev = node->prev;

  // add to head
  AddToHead(*node);
}
Node *DLList::GetTail() {
  return tail_->prev;
}
} // paging