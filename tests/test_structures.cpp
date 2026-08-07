#include <iostream>
#include <cassert>
#include "../include/DataStructures/Queue.h"
#include "../include/DataStructures/LinkedList.h"
#include "../include/DataStructures/PriorityQueue.h"
#include "../include/DataStructures/LookupTable.h"
#include "../include/Entities/Patient.h"

// Sample function pointer comparator hook for Regular patients
double customPatientPriority(Patient* const & p) {
    if (!p) return 0.0;
    // Formula: 2 * checkInTime + 3 * numTests
    return (2.0 * p->getCheckInTime()) + (3.0 * p->getNumTests());
}

void testQueue() {
    std::cout << "[TEST] Running Queue Edge Cases & Stress Tests...\n";
    Queue<int> q;
    int val = 0;

    // 1. Empty queue checks
    assert(q.isEmpty());
    assert(q.size() == 0);
    assert(!q.dequeue(val));
    assert(!q.peek(val));

    // 2. Single element
    q.enqueue(100);
    assert(!q.isEmpty());
    assert(q.size() == 1);
    assert(q.peek(val) && val == 100);
    assert(q.dequeue(val) && val == 100);
    assert(q.isEmpty());
    assert(q.size() == 0);

    // 3. Repeated enqueue & dequeue stress test
    for (int i = 0; i < 5000; i++) {
        q.enqueue(i);
    }
    assert(q.size() == 5000);

    for (int i = 0; i < 5000; i++) {
        assert(q.dequeue(val) && val == i);
    }
    assert(q.isEmpty());

    std::cout << "  -> Queue tests PASSED successfully.\n";
}

void testDoublyLinkedList() {
    std::cout << "[TEST] Running DoublyLinkedList Edge Cases & Stress Tests...\n";
    DoublyLinkedList<Patient*> list;
    Patient* pOut = nullptr;

    // 1. Empty list checks
    assert(list.isEmpty());
    assert(list.size() == 0);
    assert(list.getHead() == nullptr);
    assert(list.getTail() == nullptr);
    assert(!list.removeHead(pOut));
    assert(!list.removeNode(nullptr));

    // 2. Single element insertion and removal
    Patient* p1 = new Patient(1, 10, PatientType::Regular, 2, 1);
    list.insertEnd(p1);
    assert(list.size() == 1);
    assert(list.getHead()->data == p1);
    assert(list.getTail()->data == p1);

    assert(list.removeHead(pOut) && pOut == p1);
    assert(list.isEmpty());
    assert(list.getHead() == nullptr);
    assert(list.getTail() == nullptr);

    // 3. Multiple element operations & mid-structure removal
    Patient* p2 = new Patient(2, 12, PatientType::Emergency, 1, 1);
    Patient* p3 = new Patient(3, 15, PatientType::Regular, 4, 1);
    Patient* p4 = new Patient(4, 20, PatientType::Emergency, 3, 1);

    list.insertEnd(p1);
    list.insertEnd(p2);
    list.insertEnd(p3);
    list.insertEnd(p4);
    assert(list.size() == 4);

    // Remove middle node (p3)
    auto node3 = list.getHead()->next->next;
    assert(node3->data == p3);
    assert(list.removeNode(node3));
    assert(list.size() == 3);

    // Remove tail (p4)
    auto tailNode = list.getTail();
    assert(tailNode->data == p4);
    assert(list.removeNode(tailNode));
    assert(list.size() == 2);

    // Clear list
    list.clear();
    assert(list.isEmpty());

    delete p1;
    delete p2;
    delete p3;
    delete p4;

    std::cout << "  -> DoublyLinkedList tests PASSED successfully.\n";
}

void testPriorityQueue() {
    std::cout << "[TEST] Running PriorityQueue Edge Cases & Comparator Hook Tests...\n";
    PriorityQueue<Patient*> pq;
    Patient* pOut = nullptr;

    // 1. Empty priority queue checks
    assert(pq.isEmpty());
    assert(pq.size() == 0);
    assert(!pq.extractMax(pOut));
    assert(!pq.peekMax(pOut));
    assert(!pq.removeAtIndex(0, pOut));
    assert(!pq.remove(nullptr, pOut));

    // 2. Single element removal & heapIndex reset check
    Patient* p1 = new Patient(101, 5, PatientType::Regular, 2, 1);
    pq.insert(p1, 50.0);
    assert(pq.size() == 1);
    assert(p1->getHeapIndex() == 0);

    assert(pq.extractMax(pOut) && pOut == p1);
    assert(pq.isEmpty());
    assert(p1->getHeapIndex() == -1); // Must be reset to -1!

    // 3. Heap deletion: Root vs Leaf vs Middle node
    Patient* pRoot = new Patient(201, 1, PatientType::Regular, 1, 1); // priority 100
    Patient* pMid1 = new Patient(202, 2, PatientType::Regular, 2, 1); // priority 80
    Patient* pMid2 = new Patient(203, 3, PatientType::Regular, 3, 1); // priority 70
    Patient* pLeaf = new Patient(204, 4, PatientType::Regular, 4, 1); // priority 30

    pq.insert(pRoot, 100.0);
    pq.insert(pMid1, 80.0);
    pq.insert(pMid2, 70.0);
    pq.insert(pLeaf, 30.0);
    assert(pq.size() == 4);

    assert(pRoot->getHeapIndex() == 0);
    assert(pLeaf->getHeapIndex() == 3);

    // Remove leaf node directly via pointer
    assert(pq.remove(pLeaf, pOut) && pOut == pLeaf);
    assert(pLeaf->getHeapIndex() == -1);
    assert(pq.size() == 3);

    // Remove root node via extractMax
    assert(pq.extractMax(pOut) && pOut == pRoot);
    assert(pRoot->getHeapIndex() == -1);
    assert(pq.size() == 2);

    // Remaining elements must have valid non-negative heap indices matching their positions
    Patient* peekVal = nullptr;
    assert(pq.peekMax(peekVal) && peekVal == pMid1);
    assert(pMid1->getHeapIndex() == 0);

    // Clear remaining
    assert(pq.extractMax(pOut));
    assert(pq.extractMax(pOut));
    assert(pq.isEmpty());

    delete p1;
    delete pRoot;
    delete pMid1;
    delete pMid2;
    delete pLeaf;

    // 4. Comparator Hook Test (using function pointer)
    PriorityQueue<Patient*> hookedPQ(customPatientPriority);
    Patient* cp1 = new Patient(301, 10, PatientType::Regular, 1, 1); // priority 2*10 + 3*1 = 23
    Patient* cp2 = new Patient(302, 5, PatientType::Regular, 8, 1);  // priority 2*5 + 3*8 = 34

    hookedPQ.insert(cp1);
    hookedPQ.insert(cp2);

    assert(hookedPQ.peekMax(pOut) && pOut == cp2); // cp2 has higher custom priority (34 > 23)
    assert(hookedPQ.extractMax(pOut) && pOut == cp2);
    assert(cp2->getHeapIndex() == -1);

    assert(hookedPQ.extractMax(pOut) && pOut == cp1);
    assert(cp1->getHeapIndex() == -1);
    assert(hookedPQ.isEmpty());

    delete cp1;
    delete cp2;

    std::cout << "  -> PriorityQueue tests PASSED successfully.\n";
}

void testLookupTable() {
    std::cout << "[TEST] Running LookupTable Edge Cases & Stress Tests...\n";
    LookupTable<Patient*> lookup(10);
    assert(lookup.size() == 0);

    Patient* p1 = new Patient(15, 1, PatientType::Regular, 1, 1);
    lookup.insert(15, p1);
    assert(lookup.size() == 1);
    assert(lookup.contains(15));
    assert(lookup.get(15) == p1);

    // Remove
    assert(lookup.remove(15));
    assert(!lookup.contains(15));
    assert(lookup.get(15) == nullptr);
    assert(lookup.size() == 0);

    delete p1;
    std::cout << "  -> LookupTable tests PASSED successfully.\n";
}

void testCrossStructureMove() {
    std::cout << "[TEST] Running Cross-Structure Pointer Move (Auto-escalation / Urgent Event)...\n";
    PriorityQueue<Patient*> waitingRegular;
    DoublyLinkedList<Patient*> waitingEmergency;
    LookupTable<Patient*> patientLookup;

    Patient* pEscalate = new Patient(501, 10, PatientType::Regular, 2, 1);
    patientLookup.insert(501, pEscalate);
    waitingRegular.insert(pEscalate, 45.0);

    assert(waitingRegular.size() == 1);
    assert(waitingEmergency.size() == 0);
    assert(pEscalate->getHeapIndex() == 0);

    // Simulate handleEscalate(): Extract from Regular PQ, change type, insert to Emergency DLL
    Patient* pTarget = patientLookup.get(501);
    assert(pTarget == pEscalate);

    Patient* extracted = nullptr;
    bool removedOK = waitingRegular.remove(pTarget, extracted);
    assert(removedOK);
    assert(extracted == pEscalate);
    assert(pEscalate->getHeapIndex() == -1); // reset heap index!
    assert(waitingRegular.size() == 0);

    // Pointer move (SHARE, MOVE, DON'T COPY)
    pEscalate->setType(PatientType::Emergency);
    waitingEmergency.insertEnd(pEscalate);

    assert(waitingEmergency.size() == 1);
    assert(waitingEmergency.getHead()->data == pEscalate);

    // Cleanup
    Patient* doneP = nullptr;
    waitingEmergency.removeHead(doneP);
    delete doneP;

    std::cout << "  -> Cross-structure pointer move test PASSED successfully.\n";
}

void testNonDestructivePrintHooks() {
    std::cout << "[TEST] Running Non-Destructive Print & Traversal Hooks Test...\n";

    // 1. Queue Traversal & Print Test
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    assert(q.size() == 3);

    int sumQ = 0;
    q.traverse([&sumQ](const int& val) { sumQ += val; });
    assert(sumQ == 60);
    assert(q.size() == 3); // Encapsulation & size preserved

    // 2. DoublyLinkedList Traversal & Print Test
    DoublyLinkedList<int> dll;
    dll.insertEnd(100);
    dll.insertEnd(200);
    dll.insertEnd(300);
    assert(dll.size() == 3);

    int sumDLL = 0;
    dll.traverse([&sumDLL](const int& val) { sumDLL += val; });
    assert(sumDLL == 600);
    assert(dll.size() == 3);

    // 3. PriorityQueue Direct Heap Array Traversal & Print Test
    PriorityQueue<Patient*> pq;
    Patient* p1 = new Patient(10, 1, PatientType::Regular, 2, 1);
    Patient* p2 = new Patient(20, 2, PatientType::Regular, 4, 1);
    Patient* p3 = new Patient(30, 3, PatientType::Regular, 1, 1);

    pq.insert(p1, 50.0);
    pq.insert(p2, 90.0); // max priority -> root
    pq.insert(p3, 30.0);

    assert(pq.size() == 3);
    assert(p2->getHeapIndex() == 0); // Root must be p2

    // Traversal iterates heap[0..count-1] directly without extraction or heap modification
    int visitedCount = 0;
    pq.traverse([&visitedCount](Patient* const & p) {
        assert(p != nullptr);
        visitedCount++;
    });
    assert(visitedCount == 3);
    assert(pq.size() == 3);            // Size remains 3
    assert(p2->getHeapIndex() == 0);   // Heap indices untouched!

    // Peek max must still return p2
    Patient* top = nullptr;
    assert(pq.peekMax(top) && top == p2);

    delete p1;
    delete p2;
    delete p3;

    // 4. LookupTable Traversal & Print Test
    LookupTable<int*> table;
    int a = 5, b = 15;
    table.insert(1, &a);
    table.insert(2, &b);
    assert(table.size() == 2);

    int tableSum = 0;
    table.traverse([&tableSum](int* val) { tableSum += *val; });
    assert(tableSum == 20);
    assert(table.size() == 2);

    std::cout << "  -> Non-Destructive Print & Traversal hooks PASSED successfully.\n";
}

int main() {
    std::cout << "==================================================\n";
    std::cout << "  CIE205 Checkpoint 2 - Data Structures Test Suite\n";
    std::cout << "==================================================\n";

    testQueue();
    testDoublyLinkedList();
    testPriorityQueue();
    testLookupTable();
    testCrossStructureMove();
    testNonDestructivePrintHooks();

    std::cout << "==================================================\n";
    std::cout << "  ALL DATA STRUCTURE TESTS PASSED! ZERO ERRORS.\n";
    std::cout << "==================================================\n";
    return 0;
}
