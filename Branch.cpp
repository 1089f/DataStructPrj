#include "Entities/Branch.h"

Branch::Branch() : branchNum(0), docArr(nullptr), docCnt(0) {}

Branch::Branch(int branchNum, int numDoc)
    : branchNum(branchNum), docCnt(numDoc) {
    docArr = new Doctor[numDoc];
}

Branch::~Branch() {
    delete[] docArr;
}

Doctor* Branch::getDoc() { return docArr; }
int Branch::getDocCnt() const { return docCnt; }
int Branch::getBranchNum() const { return branchNum; }

void Branch::setDoc(int index, const Doctor& d) {
    docArr[index] = d;
}

Doctor* Branch::findAvlblDoc(int currTime) {
    for (int i = 0; i < docCnt; i++) {
        if (docArr[i].IsAvlbl(currTime)) {
            return &docArr[i];
        }
    }
    return nullptr;
}