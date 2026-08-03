#include "FileManager.h"

FileManager::FileManager() {
}

bool FileManager::LoadData(const std::string& filepath, Clinic& clinic) {
	// TODO: Implement data loading from file
	return true;
}

void FileManager::WriteOutput(const std::string& filepath,
							  DoublyLinkedList<Patient*>& doneList,
							  Branch* branches, int branchCount,
							  int totalRegular, int escalatedCount) {
	// TODO: Implement writing output to file
}

void FileManager::mergeSort(Patient** arr, int left, int right) {
	// TODO: Implement merge sort
}

void FileManager::merge(Patient** arr, int left, int mid, int right) {
	// TODO: Implement merge operation
}

int FileManager::comparePatients(Patient* a, Patient* b) {
	// TODO: Implement patient comparison
	return 0;
}
