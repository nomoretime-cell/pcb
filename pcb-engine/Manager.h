#pragma once

#include <vector>
#include <list>
#include <string>
#include "CommonStruct.h"

class Manager
{
public:
	Manager();
	~Manager();

	//virtual int getBlock









	// ��ʼ��
	virtual int init(const MvpImage* img) {};

	// ��������
	virtual int process(MvpImage& img, const char* inputJson, char** jsonData) {};

	virtual int setConfig(const char* jsonData) {};
	virtual int getConfig(char** jsonData) {};
	virtual int getResult(char** jsonData) {};
	virtual std::string getToolID() {};
	virtual int command(MvpImage& img, const char* inputJson, char** jsonData) {};

	//����block�нڵ�
	virtual int addNode(_In_ std::string inBlockID, _Out_ std::string& outNodeID) {};
	//ɾ��block�нڵ�
	virtual int removeNode() {};
	virtual int queryList(std::list<std::string> nodeID) {};// 
	virtual int setInput(const char* jsonData) {};
	virtual int updateLinks(std::string oldfromNodeID, std::string newfromNodeID, std::string tofromNodeID) {};
	virtual int addLinks(std::string newfromNodeID, std::string tofromNodeID) {};
	virtual int run(std::string blockID) {};//�ַ���Ϊ�����У���Ϊ������֤
	virtual int stop() {};
	virtual std::string getBlockID() {};
	virtual const char* getCurrentNodeID() {};
private:
	// block
	// block����
	// block uuid
};

