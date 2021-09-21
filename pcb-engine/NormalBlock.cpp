#include "NormalBlock.h"

ENGINE_NAMESPACE_BEGIN

IBlock* NormalEngineBlock::create(int32_t nodeID)
{
	return new NormalEngineBlock(nodeID);
}

NormalEngineBlock::NormalEngineBlock(int nodeID)
{
}

NormalEngineBlock::~NormalEngineBlock()
{
}

ENGINE_NAMESPACE_END