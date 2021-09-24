#pragma once

#include <memory>
#include "Defs.h"
#include "IBlock.h"
#include "IComponent.h"

ENGINE_NAMESPACE_BEGIN

class NormalBlockFactory
{
public:
	static NormalBlockFactory* instance();

	std::shared_ptr<IBlock> createNode(std::string nodeType, int32_t nodeID);

private:
	NormalBlockFactory();
	~NormalBlockFactory();
};

#define CREATE_VISIONTOOLNODE(toolID,nodeID) VisionToolNodeFactory::instance()->createNode(toolID, nodeID)

ENGINE_NAMESPACE_END