#pragma once

#include <string>
#include <list>
#include "Defs.h"
#include "CommonStruct.h"
#include "IComponent.h"

ENGINE_NAMESPACE_BEGIN

class IBlock : public IComponent::IObjectUnknown
{
public:
	IBlock() {};
	~IBlock() {};

	/// �������
	class IFactory : public IComponent::IFactoryUnknown
	{
	public:
		/// ��������ӿ�
		virtual IBlock* create(int32_t nodeID) = 0;

		/// ����ӿ�ID����
		static const char* iid() { return "VisionEngine::IVisionEngineNode"; }
	};

	virtual int process(MvpImage& img, const char* inputJson, char** jsonData) = 0;
	virtual int init(const MvpImage* img) = 0;
	virtual int setConfig(const char* jsonData) = 0;
	virtual int getConfig(char** jsonData) = 0;
	virtual int getResult(char** jsonData) = 0;
	virtual char* getToolID() = 0;
	virtual int command(MvpImage& img, const char* inputJson, char** jsonData) = 0;
	virtual int addAlgrithm() = 0;
	virtual int removeAlgrithm() = 0;
	virtual int queryList(std::list<std::string> nodeID) = 0;// 
	virtual int setInput(const char* jsonData) = 0;
	virtual int updateLinks(std::string oldfromNodeID, std::string newfromNodeID, std::string tofromNodeID) = 0;
	virtual int addLinks(std::string newfromNodeID, std::string tofromNodeID) = 0;
	virtual const char* getCurrentNodeID() = 0;

private:
	// ���ӽ��
	// ��������
	// ����uuid����
};

ENGINE_NAMESPACE_END
