#pragma once

#include <atomic>

class NodeIDCreator
{
public:
	static NodeIDCreator* instance() {
		static NodeIDCreator ins;
		return &ins;
	}

	int getIncrementID() {
		return ++idCount;
	}

	void clearID() {
		idCount = 0;
	}

	void setIDCount(int id) {
		idCount = id;
	}

	int getIDCount() {
		return idCount;
	}

	std::string getIndex(std::string ID) {
		int numIndex = 0;
		for (int index = 0; index < ID.length(); index++) {
			if (ID[index] >= 48 && ID[index] <= 57) {
				numIndex = index;
				break;
			}
		}
		return ID.substr(numIndex);
	}

private:
	NodeIDCreator():idCount(0){
	};
	~NodeIDCreator() {};
	std::atomic<int> idCount;
private:

};
