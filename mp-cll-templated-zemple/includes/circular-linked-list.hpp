#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

using namespace std;

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();
  void Clear();
  void SwitchOrder();
  void DESC(const T& data);

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
void CircularLinkedList<T>::SwitchOrder() {
  if(node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  }
  else if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  }
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
    node_order_ = source.node_order_;
    if(source.head_ == nullptr) {
      head_ = tail_ = nullptr;
      return;
    }
    if(source.head_ == source.tail_) {
      head_ = new Node<T>(source.head_->data);
      tail_ = head_;
      tail_ -> next = head_;
      return;
    }
    Node<T>* curr = source.head_;
    head_ = new Node<T>(curr -> data);
    Node<T>* n = head_;
    curr = curr -> next;
    while (curr != source.head_) {
      n->next = new Node<T>(curr->data);
      n = n->next;
      curr = curr->next;
    }
    tail_ = n;
    tail_ -> next = head_;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
    if(head_ == source.head_) {
      return *this;
    }
    Clear();
    node_order_ = source.node_order_;
    if(source.head_ == nullptr) {
      head_ = tail_ = nullptr;
      return *this;
    }
    if(source.head_ == source.tail_) {
      head_ = new Node<T>(source.head_ -> data);
      tail_ = head_;
      tail_->next = head_;
      return *this;
    }

    Node<T>* curr = source.head_;
    head_ = new Node<T>(curr -> data);
    Node<T>* n = head_;
    curr = curr -> next;
    while (curr != source.head_) {
      n->next = new Node<T>(curr -> data);
      n = n->next;
      curr = curr->next;
    }
    tail_ = n;
    tail_->next = head_;
    return *this;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (node_order_ == Order::kASC) {
    if(head_ == nullptr) {
      head_ = new Node<T>(data);
      tail_ = head_;
      tail_ -> next = head_;
      return;
    }
    Node<T>* n = new Node<T>(data);
    if(data <= head_ -> data) {
      n->next = head_;
      head_ = n;
      tail_ -> next = head_;
      return;
    }
    Node<T>* prev = head_;
    Node<T>* curr = head_ -> next;
    while (curr != head_) {
      if(data <= curr -> data) {
        prev->next = n;
        n->next = curr;
        return;
      }
      prev = curr;
      curr = curr -> next;
    }
    tail_->next = n;
    tail_ = n;
    tail_ -> next = head_;
  } else if (node_order_ == Order::kDESC) {
    DESC(data);
  }
}

template <typename T>
void CircularLinkedList<T>::DESC(const T& data) {
  if(head_ == nullptr) {
    head_ = new Node<T>(data);
    tail_ = head_;
    tail_->next = head_;
    return;
  }
  Node<T>* n = new Node<T>(data);
  if(data >= head_->data) {
    n -> next = head_;
    head_ = n;
    tail_ -> next = head_;
    return;
  }
  Node<T>* prev = head_;
  Node<T>* curr = head_->next;
  while (curr != head_) {
    if(data >= curr -> data) {
      prev->next = n;
      n->next = curr;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  tail_ -> next = n;
  tail_ = n;
  tail_ -> next = head_;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Clear();
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  SwitchOrder();
  if (head_ != nullptr) {
    Node<T>* curr = head_;
    Node<T>* n = curr->next;
    Node<T>* nn = curr->next->next;
    Node<T>* tmp1 = head_;
    Node<T>* tmp2 = tail_;
    while (curr != tail_) {
      n->next = curr;
      curr = n;
      n = nn;
      nn = nn->next;
    }
    n->next = curr;
    head_->next = tail_;
    head_ = tmp2;
    tail_ = tmp1;
  }
}

template <typename T>
void CircularLinkedList<T>::Clear() {
  Node<T>* curr = head_;
  while (curr != tail_) {
    Node<T>* next = curr -> next;
    delete curr;
    curr = next;
  }
  delete tail_;
}

#endif