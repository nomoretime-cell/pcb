#pragma once

#include <memory>
#include "Defs.h"
#include "IBlock.h"
#include "IComponent.h"

ENGINE_NAMESPACE_BEGIN

class NormalBlockFactory
{
public:
	static std::shared_ptr<IBlock> createNode(std::string toolID, int32_t nodeID) {
		return NormalBlockFactory::instance()->innerCreateNode(toolID, nodeID);
	}
private:
	static NormalBlockFactory* instance();
	std::shared_ptr<IBlock> innerCreateNode(std::string toolID, int32_t nodeID);
	NormalBlockFactory();
	~NormalBlockFactory();
};

ENGINE_NAMESPACE_END