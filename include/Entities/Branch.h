#pragma once
#include "Doctor.h"

class Branch {
private:
    int branchNum;
    Doctor* docArr;
    int docCnt;
public:
    Branch();
    Branch(int branchNum, int numDoc);
    ~Branch();

    Doctor* getDoc();
    int getDocCnt() const;
    int getBranchNum() const;

    void setDoc(int index, const Doctor& d);
    Doctor* findAvlblDoc(int currTime);
};
