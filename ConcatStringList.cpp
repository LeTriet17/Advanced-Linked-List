#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();


ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ConcatStringList(const char *s) {
    string str(s);
    ConcatStringList::CharALNode *newNode = new ConcatStringList::CharALNode(str, NULL);
    ConcatStringList::head = ConcatStringList::tail = newNode;
    ConcatStringList::insertRefNode(this->head, NULL, true, &refList.Rhead, &refList.Rtail);
    ConcatStringList::insertRefNode(this->tail, NULL,false, &refList.Rhead, &refList.Rtail);
//    sort(refList.Rhead);


}

int ConcatStringList::length() const {
    ConcatStringList::CharALNode *curr = ConcatStringList::head;
    int totalLen = 0;
    while (curr) {
        totalLen += curr->s.length();
        curr = curr->next;
    }
    return totalLen;
}

int ConcatStringList::get(int index) const {
    int strLen = ConcatStringList::length();
    if (index < 0 || index >= strLen) throw out_of_range("Index of string is invalid");
    string str = ConcatStringList::toString();
    return str[index];
}

std::string ConcatStringList::toString() const {
    ConcatStringList::CharALNode *curr = ConcatStringList::head;
    string totalStr = "";
    while (curr) {
        totalStr += curr->s;
        curr = curr->next;
    }

    return totalStr;
}

int ConcatStringList::indexOf(char c) const {
    string str = ConcatStringList::toString();
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == c) return i;
    }
    return -1;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const {
    ConcatStringList newConStr = ConcatStringList();
    newConStr.head = ConcatStringList::head;
    newConStr.tail = ConcatStringList::tail;
    if (otherS.head) {
        newConStr.tail->next = otherS.head;
        newConStr.tail = otherS.tail;
    }
    ConcatStringList::insertRefNode(newConStr.head,NULL, true, &refList.Rhead, &refList.Rtail);
    ConcatStringList::insertRefNode(newConStr.tail,NULL, false, &refList.Rhead, &refList.Rtail);
//    sort(refList.Rhead);

    return newConStr;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
    int strLen = ConcatStringList::length();
    if (from < 0 || from >= strLen || to < 0 || to > strLen) throw out_of_range("Index of string is invalid");
    if (from > to) throw logic_error("Invalid range");
    ConcatStringList newConStr = ConcatStringList();
    ConcatStringList::CharALNode *curr = this->head;
    string currStr = curr->s;
    int iteLen = currStr.length();
    while (true) {
        int start = 0;
        int end = currStr.length();
        if (from < iteLen) {
            if (from > 0) start = from;
            if (to > 0 and to < currStr.length()) end = to;
            ConcatStringList::CharALNode *newNode = new CharALNode(currStr.substr(start, end), NULL);
            if (newConStr.length() == 0) {
                newConStr.head = newConStr.tail = newNode;
            } else {
                newConStr.tail = newConStr.tail->next = newNode;
            }
        }
        from -= currStr.length();
        to -= currStr.length();
        if (to < 0) break;
        curr = curr->next;
        currStr = curr->s;
        iteLen += currStr.length();
    }
    ConcatStringList::insertRefNode(newConStr.head,NULL, true, &refList.Rhead, &refList.Rtail);
    ConcatStringList::insertRefNode(newConStr.tail,NULL, false, &refList.Rhead, &refList.Rtail);
//    sort(refList.Rhead);

    return newConStr;
}

ConcatStringList ConcatStringList::reverse() const {
    // Initialize current, previous and next pointers
    ConcatStringList newConStr = ConcatStringList();

    ConcatStringList *copyStr = this->copy();
    ConcatStringList::CharALNode *current = copyStr->head;
    ConcatStringList::CharALNode *next = NULL, *prev = NULL;
    while (current != NULL) {
        int n = current->s.length();
        for (int i = 0; i < n / 2; i++)
            swap(current->s[i], current->s[n - i - 1]);
        // Store next
        next = current->next;
        // Reverse current node's pointer
        current->next = prev;
        // Move pointers one position ahead.
        prev = current;
        current = next;

    }
    copyStr->head = prev;
    ConcatStringList::insertRefNode(copyStr->head, NULL,true, &refList.Rhead, &refList.Rtail);
    ConcatStringList::insertRefNode(copyStr->tail, NULL,false, &refList.Rhead, &refList.Rtail);
//    sort(refList.Rhead);

    return *copyStr;
}

ConcatStringList *ConcatStringList::copy() const {
    ConcatStringList *newConStr = new ConcatStringList();
    ConcatStringList::CharALNode *curr = this->head;
    while (curr) {
        ConcatStringList::CharALNode *newNode = new CharALNode(curr->s, NULL);

        if (newConStr->length() == 0) {
            newConStr->head = newConStr->tail = newNode;
        } else {
            newConStr->tail = newConStr->tail->next = newNode;
        }
        curr = curr->next;
    }
    return newConStr;
}

ConcatStringList::ConcatStringList() {
    this->head = this->tail = NULL;
}

ConcatStringList::~ConcatStringList() {
    ConcatStringList::ReferenceNode * delNodeH = ConcatStringList::deleteRefNode(this->head, true, refList.Rhead, refList.Rtail);
    ConcatStringList::ReferenceNode * delNodeT = ConcatStringList::deleteRefNode(this->tail, false, refList.Rhead, refList.Rtail);
    if (isEmpty(&refList.Rhead)) {
        refList.Rhead = NULL;
        refList.Rtail = NULL;
    }


    ConcatStringList::insertRefNode(NULL,delNodeH, true, &delStrList.Dhead, &delStrList.Dtail);
    ConcatStringList::insertRefNode(NULL, delNodeT, false, &delStrList.Dhead, &delStrList.Dtail);
    ConcatStringList::deleteN(&delStrList.Dhead);
    MergeSort(&refList.Rhead);

    ConcatStringList::ReferenceNode* curr = refList.Rhead;
    while(curr->next) {
        curr = curr->next;
    }
    refList.Rtail = curr;
//    MergeSort(&delStrList.Dhead);
//    curr = delStrList.Dtail;
//    while(curr->next) {
//        curr = curr->next;
//        curr = curr->next;
//    }
//    delStrList.Dtail = curr;

}


ConcatStringList::CharALNode::CharALNode() {
    ConcatStringList::CharALNode::s = "";
    ConcatStringList::CharALNode::next = NULL;
}

ConcatStringList::CharALNode::CharALNode(string s, ConcatStringList::CharALNode *next = NULL) {
    ConcatStringList::CharALNode::s = s;
    ConcatStringList::CharALNode::next = next;
}


ConcatStringList::ReferenceNode::ReferenceNode::ReferenceNode(ConcatStringList::CharALNode *newNode) {
    ConcatStringList::ReferenceNode::CharNode = new CharALNode(newNode->s, NULL);
    ConcatStringList::ReferenceNode::headCount = 1;
    ConcatStringList::ReferenceNode::tailCount = 1;
    ConcatStringList::ReferenceNode::next = NULL;

}


void
ConcatStringList::insertRefNode(ConcatStringList::CharALNode *node = NULL,ConcatStringList::ReferenceNode* Rnode = NULL, bool isHead = NULL, ConcatStringList::ReferenceNode **head = NULL,
                                ConcatStringList::ReferenceNode **tail = NULL) const {
    ConcatStringList::ReferenceNode *currNode;
    if (node) {
        currNode= containsRefNode(node, *head);
        if (currNode) {
            if (isHead) currNode->headCount++;
            else currNode->tailCount++;
        } else {
            ConcatStringList::ReferenceNode *nNode = new ConcatStringList::ReferenceNode(node);
            if (isHead) nNode->tailCount--;
            else nNode->headCount--;
            if (*head) {
                (*tail)->next = nNode;
            } else {
                *head = *tail = nNode;
            }
    }

    }
    else {
        if (*head ) {
            currNode = containsRefNode((Rnode)->CharNode,*head);
            if (!currNode) {
                (*tail)->next = Rnode;
            }
        } else if(!(*head)){

            *head = *tail = Rnode;
        }


    }
}


ConcatStringList::ReferenceNode *
ConcatStringList::deleteRefNode(ConcatStringList::CharALNode *node = NULL, bool isHead = false, ConcatStringList::ReferenceNode *head = NULL,
                                ConcatStringList::ReferenceNode *tail = NULL) const {
    ConcatStringList::ReferenceNode *currNode = containsRefNode(node, head);
    if (isHead) (currNode)->headCount--;
    else (currNode)->tailCount--;
    return currNode;
}

ConcatStringList::ReferenceNode *
ConcatStringList::containsRefNode(ConcatStringList::CharALNode *node, ConcatStringList::ReferenceNode *head) {
    ConcatStringList::ReferenceNode *curr = head;
    while (curr) {
        if (curr->CharNode->s.compare(node->s) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}





bool ConcatStringList::isEmpty(ConcatStringList::ReferenceNode **head) const {
    ConcatStringList::ReferenceNode* curr = *head;
    while (curr) {
        if (curr->headCount+curr->tailCount) return false;
        curr=curr->next;
    }
    return true;
}

void ConcatStringList::deleteN(ConcatStringList::ReferenceNode **head) {
    ConcatStringList::ReferenceNode* temp;
    ConcatStringList::ReferenceNode* prev;
    temp = *head;
    prev = *head;
    ConcatStringList::ReferenceNode* curr = *head;
    while(curr) {
        if (curr == *head && curr->tailCount+ curr->headCount ==0) {
            *head = (*head)->next;
//            free(temp);
        }
        else {
            if (curr->tailCount+ curr->headCount == 0 && temp) {
                prev->next = temp->next;
//                free(temp);
            }
            else {
                prev = temp;
                temp = temp->next;
            }
        }
        curr = curr->next;
    }

}

ConcatStringList::ReferenceNode *
ConcatStringList::SortedMerge(ConcatStringList::ReferenceNode *a, ConcatStringList::ReferenceNode *b) {
    ConcatStringList::ReferenceNode* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->tailCount + a->headCount <= b->headCount + b->headCount) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);}

void
ConcatStringList::FrontBackSplit(ConcatStringList::ReferenceNode *source, ConcatStringList::ReferenceNode **frontRef,
                                 ConcatStringList::ReferenceNode **backRef) {
    ConcatStringList::ReferenceNode* fast;
    ConcatStringList::ReferenceNode* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void ConcatStringList::MergeSort(ConcatStringList::ReferenceNode **headRef) {
    ConcatStringList::ReferenceNode* head = *headRef;
    ConcatStringList::ReferenceNode* a;
    ConcatStringList::ReferenceNode* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}


int ConcatStringList::ReferencesList::size() {
    int size = 0;
    ConcatStringList::ReferenceNode *curr = Rhead;
    while (curr) {
        size++;
        curr = curr->next;
    }
    return size;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const {
    ConcatStringList::ReferenceNode *curr = Rhead;
    while (index--) {
        curr = curr->next;
    }
    if (index && !curr) throw out_of_range("Index of references list is invalid!");
    return curr->tailCount + curr->headCount;
}

std::string ConcatStringList::ReferencesList::refCountsString() const {
    std::string res = "RefCounts[";
    ConcatStringList::ReferenceNode *curr = Rhead;

    while (curr) {
        res += std::to_string(curr->headCount + curr->tailCount);
        if (curr->next) res += ",";


        curr = curr->next;
    }
    res += "]";
    return res;
}

int ConcatStringList::DeleteStringList::size() const {
    int size = 0;
    ConcatStringList::ReferenceNode *curr = Dhead;
    while (curr) {
        size++;
        curr = curr->next;
    }
    return size;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const {
    std::string res = "TotalRefCounts[";
    ConcatStringList::ReferenceNode *curr = Dhead;
    int sum = 0;
    while (curr) {
        sum += curr->headCount + curr->tailCount;
        curr = curr->next;
    }
    if (sum)
    res += to_string(sum) + "]";
    else res += "]";
    return res;
}


