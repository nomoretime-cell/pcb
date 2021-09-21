#pragma once

#include "Defs.h"
#include "IBlock.h"

ENGINE_NAMESPACE_BEGIN

class NormalEngineBlockFactory : public IBlock::IFactory
{
public:

	/// ��ȡClass ID
	const char* clsid(void)
	{
		return "NormalEngineBlock";
	}

	/// ��ȡ��������
	IBlock* create(int32_t nodeID)
	{
		return NormalEngineBlock::create(nodeID);
	}
};

class NormalEngineBlock
{
public:
	NormalEngineBlock(int nodeID);
	~NormalEngineBlock();

	static IBlock* create(int32_t nodeID);

private:

};



ENGINE_NAMESPACE_END