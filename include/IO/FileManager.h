#pragma once
#include <string>
#include "../DataStructures/LinkedList.h"

class Clinic;
class Patient;
class Branch;

class FileManager {
private:
    static void mergeSort(Patient** arr, int left, int right);
    static void merge(Patient** arr, int left, int mid, int right);
    static int comparePatients(Patient* a, Patient* b);

public:
    FileManager();

    bool LoadData(const std::string& filepath, Clinic& clinic);
    void WriteOutput(const std::string& filepath,
                     DoublyLinkedList<Patient*>& doneList,
                     Branch* branches, int branchCount,
                     int totalRegular, int escalatedCount);
};
