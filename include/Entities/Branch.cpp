#include "Branch.h"

Branch::Branch() : branchNum(0), docArr(nullptr), docCnt(0) {}

Branch::Branch(int branchNum, int numDoc) : branchNum(branchNum), docCnt(numDoc) {
    docArr = new Doctor[numDoc];
}

Branch::Branch(const Branch& other) : branchNum(other.branchNum), docCnt(other.docCnt) {
    docArr = new Doctor[docCnt];
    for (int i = 0; i < docCnt; i++) {
        docArr[i] = other.docArr[i];
    }
}

Branch& Branch::operator=(const Branch& other) {
    if (this != &other) {
        delete[] docArr;
        branchNum = other.branchNum;
        docCnt    = other.docCnt;
        docArr    = new Doctor[docCnt];
        for (int i = 0; i < docCnt; i++) {
            docArr[i] = other.docArr[i];
        }
    }
    return *this;
}

Branch::~Branch() {
    delete[] docArr;
}

Doctor* Branch::getDoc()            { return docArr; }
int     Branch::getDocCnt()   const { return docCnt; }
int     Branch::getBranchNum() const { return branchNum; }

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
