#include "branched-linked-list.hpp"

using namespace std;

BLL::BLL(const BLL& to_copy) {
    if (to_copy.head_ == nullptr) {
        head_ = nullptr;
        return;
    }
    head_ = new Node(to_copy.head_->data_);
    Node* curr1 = to_copy.head_;
    Node* curr2 = head_;
    while (curr1 != nullptr) {
        if (curr1->next_bll_ != nullptr) {
            curr2->next_bll_ = new BLL(*curr1->next_bll_);
        } 
        if (curr1->next_node_ != nullptr) {
            curr2->next_node_ = new Node(curr1->next_node_->data_);
        }
        curr1 = curr1->next_node_;
        curr2 = curr2->next_node_;
    }
}

BLL::~BLL() {
    Node* tmp = head_;
    while (tmp != nullptr) {
        Node* n = tmp->next_node_;
        if (tmp->next_bll_ != nullptr) {
            tmp->next_bll_->~BLL();
            delete tmp->next_bll_;
            tmp->next_bll_ = nullptr;
        }
        delete tmp;
        tmp = n;
    }
    head_ = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (rhs.head_ == nullptr) {
        head_ = nullptr;
        return *this;
    }
    head_ = new Node(rhs.head_->data_);
    Node* curr1 = rhs.head_;
    Node* curr2 = head_;
    while (curr1 != nullptr) {
        if (curr1->next_bll_ != nullptr) {
            curr2->next_bll_ = new BLL(*curr1->next_bll_);
        } 
        if (curr1->next_node_ != nullptr) {
            curr2->next_node_ = new Node(curr1->next_node_->data_);
        }
        curr1 = curr1->next_node_;
        curr2 = curr2 ->next_node_;
    }
    return *this;
}

Node* BLL::PushBack(char dat) {
    Node* tmp = new Node(dat);
    if (head_ == nullptr) {
        head_ = tmp;
    } else {
        Node* curr =  head_;
        while (curr->next_node_ != nullptr) {
            curr = curr->next_node_;
        }
        curr->next_node_ = tmp;
    }
    return tmp;
}

char BLL::GetAt(size_t idx) const {
    if (idx >= Size() || head_ == nullptr) {
        throw std::invalid_argument("");
    }
    return ToString()[idx];
}

void BLL::SetAt(size_t idx, char dat) {
    if (idx >= Size() || head_ == nullptr) {
        throw std::invalid_argument("");
    }
    GetNodeAt(idx)->data_ = dat;
}

Node* BLL::GetNodeAt(size_t idx) const {
    size_t i = idx;
    Node* curr = head_;
    while (curr != nullptr) {
        if (i == 0) {
            return curr;
        } else if (curr->next_bll_ != nullptr && curr->next_bll_->Size() < i) {
            i -= curr->next_bll_->Size() - 1;
            curr = curr->next_node_;
            continue;
        } else if (curr->next_bll_ != nullptr && curr->next_bll_->Size() >= i) {
            BLL* b = curr->next_bll_;
            return b->GetNodeAt(i - 1);
        }
        i--;
        curr = curr->next_node_;
    }
    return curr;
}

Node* BLL::GetNext(Node* curr) const {
	if (curr == nullptr) {
        return nullptr;
    }
	if (curr->next_bll_ != nullptr) {
        return curr->next_bll_->head_;
    }
	if (curr->next_node_ != nullptr) {
        return curr->next_node_;
    }
	return nullptr;
}
void BLL::Join(size_t idx, BLL* list) {
    Node* tmp = GetNodeAt(idx);
    if (idx >= Size() || tmp->next_bll_ != nullptr) {
        throw invalid_argument("");
    }
    tmp->next_bll_ = list;
    if (!IsBLLAcyclic()) {
        throw std::invalid_argument("");
    }
}

string BLL::ToString() const {
    string str;
    Node* curr = head_;
    if (head_ == nullptr) {
        return "";
    }
    while (curr != nullptr) {
        str.push_back(curr->data_);
        if (curr->next_bll_ != nullptr) {
            str += curr->next_bll_->ToString();
        }
        curr = curr->next_node_;
    }
    return str;
}

size_t BLL::Size() const {
    size_t size = 0;
    if (head_ == nullptr) {
        return 0;
    }
    Node* curr = head_;
    while (curr != nullptr) {
        size++;
        if (curr->next_bll_ != nullptr) {
            size += curr->next_bll_->Size();
        }
        curr = curr->next_node_;
    }
    return size;
}

bool BLL::IsBLLAcyclic() const {
    if (head_ == nullptr) {
        return true;
    }
    Node* turtle = head_;
    Node* rabbit  = GetNext(head_);
    while (turtle != nullptr && rabbit != nullptr) {
        if (turtle == rabbit) {
            return false;
        }
        turtle = GetNext(turtle);
        rabbit = GetNext(GetNext(rabbit));
    }
    return true;
}