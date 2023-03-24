//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Lru.h"
#include <iomanip>

namespace paging::strategy {
// Lru
int Lru::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  // tail of DLList (least recently used)
  if (verbose_) {
    std::cout << "Recency order: ";
    dl_list_.PrintListAndVictim();
  }
  return dl_list_.GetTail()->val;
}

void Lru::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  Node *node = new Node(page_no);
  page_node_map_[page_no] = node;
  dl_list_.AddToHead(*node);
}

void Lru::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  // reference a bit, move the node to the head of DLList
  if (page_node_map_.find(page_no) != page_node_map_.end()) {
    Node *node = page_node_map_[page_no];
    dl_list_.MoveToHead(node);
  }
}

void Lru::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) {
  page_node_map_.erase(dl_list_.GetTail()->val);
  dl_list_.RemoveTail();
  AfterNewPage_(frame, page_table, new_page_no);
}

std::string Lru::GetName() {
  return name_;
}

void Lru::Reset_() {
  page_node_map_.clear();
  while (dl_list_.Size() > 0) {
    dl_list_.RemoveTail();
  }
}

// DLList
void DLList::AddToHead(Node &node) {
  head_->next->prev = &node;
  node.next = head_->next;

  head_->next = &node;
  node.prev = head_;
  size_++;
}

void DLList::RemoveTail() {
  Node *node = tail_->prev;
  Remove(node);
}

void DLList::Remove(Node *node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;

  delete node;
  node = nullptr;
  size_--;
}

void DLList::MoveToHead(Node *node) {
  // Remove current position
  node->prev->next = node->next;
  node->next->prev = node->prev;
  size_--;

  // add to head
  AddToHead(*node);
}

Node *DLList::GetTail() {
  return tail_->prev;
}

size_t DLList::Size() {
  return size_;
}
void DLList::PrintListAndVictim() {
  for (Node* cur = head_->next; cur != tail_; cur = cur->next) {
    if (cur == tail_->prev) {
      std::cout << cur->val << "(victim) ";
    } else {
      std::cout << cur->val << " ";
    }
  }
}
} // paging