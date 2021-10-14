#pragma once

#include <atomic>

class NodeIDCreator
{
public:
	static NodeIDCreator* instance() {
		static NodeIDCreator ins;
		return &ins;
	}

	int getID() {
		return ++count;
	}

	void clearID() {
		count = 0;
	}
private:
	NodeIDCreator():count(0){
	};
	~NodeIDCreator() {};
	std::atomic<int> count;
private:

};
