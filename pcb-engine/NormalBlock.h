#pragma once

#include "Defs.h"
#include "IBlock.h"

ENGINE_NAMESPACE_BEGIN

class NormalEngineBlockFactory : public IBlock::IFactory
{
public:

	/// 获取Class ID
	const char* clsid(void)
	{
		return "NormalEngineBlock";
	}

	/// 获取单例对象
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