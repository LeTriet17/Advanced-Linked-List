#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    class CharALNode {

    public:
        friend class ReferencesList;

        string s;
        CharALNode *next;

        CharALNode();

        CharALNode(string s, ConcatStringList::CharALNode *next);

    };

    CharALNode *head, *tail;
public:
    ConcatStringList();

    explicit ConcatStringList(const char *);

    int length() const;

    int get(int index) const;

    int indexOf(char c) const;

    std::string toString() const;

    ConcatStringList concat(const ConcatStringList &otherS) const;

    ConcatStringList subString(int from, int to) const;

    ConcatStringList reverse() const;

    ConcatStringList *copy() const;

    ~ConcatStringList();

public:
    class ReferenceNode {
    public:
        ConcatStringList::CharALNode *CharNode;
        int headCount;
        int tailCount;
        ConcatStringList::ReferenceNode *next;

        explicit ReferenceNode(CharALNode *);
    };

    static ReferenceNode *containsRefNode(CharALNode *, ConcatStringList::ReferenceNode *head);

    void insertRefNode(CharALNode *, ConcatStringList::ReferenceNode*,bool isHead, ConcatStringList::ReferenceNode **head,
                       ConcatStringList::ReferenceNode **tail) const;

    ConcatStringList::ReferenceNode * deleteRefNode(CharALNode *, bool isHead, ConcatStringList::ReferenceNode *head,
                       ConcatStringList::ReferenceNode *tail) const;
    ConcatStringList::ReferenceNode* SortedMerge(ConcatStringList::ReferenceNode* a, ConcatStringList::ReferenceNode* b);
    void FrontBackSplit(ConcatStringList::ReferenceNode* source,
                        ConcatStringList::ReferenceNode** frontRef, ConcatStringList::ReferenceNode** backRef);
    void MergeSort(ConcatStringList::ReferenceNode** headRef);
    bool isEmpty(ConcatStringList::ReferenceNode **head) const;
    void deleteN(ConcatStringList::ReferenceNode** head);

    class ReferencesList {

    public:
        friend class ConcatStringList;

        ReferenceNode *Rhead, *Rtail, *Rsorted;


        int size();

        int refCountAt(int index) const;

        std::string refCountsString() const;
    };

    class DeleteStringList {

    public:
        ReferenceNode *Dhead, *Dtail;

        friend class ConcatStringList;

        int size() const;

        std::string totalRefCountsString() const;
    };
};

#endif // __CONCAT_STRING_LIST_H__