#include "dna_strand.hpp"

#include <stdexcept>
using namespace std;

DNAstrand::~DNAstrand() {
    while (head_ != nullptr) {
        Node* tmp = head_->next;
        delete head_;
        head_ = tmp;
    }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    Node* start = nullptr;
    Node* begin = nullptr;
    Node* end = nullptr;
    Node* current = head_;
    Node* pre = nullptr;
    while (current != nullptr) {
        int i = 0;
        Node* tmp = current;
        while (tmp != nullptr && pattern[i] == tmp-> data) {
            tmp = tmp->next;
            i++;
        }
        if (pattern[i] == '\0') {
            start = current;
            end = tmp;
            begin = pre;
        }
        pre = current;
        current = current->next;
    }
    if(start == nullptr) {throw std::runtime_error("");}
    if(start == head_) {
        head_ = to_splice_in.head_;
        to_splice_in.tail_ -> next = end;
    } else {
        begin -> next = to_splice_in.head_;
        to_splice_in.tail_ -> next = end;
    }
    if(end == nullptr) {tail_ = to_splice_in.tail_;}
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
    current = start;
    while (current != end) {
        Node* tmp = current -> next;
        delete current;
        current = tmp;
    }
}

