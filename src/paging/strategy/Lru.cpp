//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Lru.h"

namespace paging::strategy {
// Lru
uint32_t Lru::GetReplacePage(PageTable &page_table) {
  Node* node = dl_list_.GetTail();
  page_node_map_.erase(node->val);
  auto page_number = node->val;
  dl_list_.RemoveTail();
  return page_number;
}
void Lru::AfterNewPage(PageTable &page_table, uint32_t page_number) {
  Node* node = new Node(page_number);
  page_node_map_[page_number] = node;
  dl_list_.AddToHead(*node);
}
void Lru::AfterReference(PageTable &page_table, uint32_t page_number) {
  if (page_node_map_.find(page_number) != page_node_map_.end()) {
    Node* node = page_node_map_[page_number];
    dl_list_.MoveToHead(node);
  }
}
void Lru::AfterReplace(PageTable &page_table, uint32_t new_page_number) {
  AfterNewPage(page_table, new_page_number);
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