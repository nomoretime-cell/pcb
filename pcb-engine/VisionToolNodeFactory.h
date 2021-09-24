#pragma once

#include "Defs.h"
#include "IVisionTool.h"

VISIONTOOL_NAMESPACE_BEGIN

class VisionToolNodeFactory
{
public:
	static VisionToolNodeFactory* instance();

	IVisionToolPtr createNode(std::string nodeType, int32_t nodeID);

private:
	VisionToolNodeFactory();
	~VisionToolNodeFactory();
};

#define CREATE_VISIONTOOLNODE(toolID,nodeID) VisionToolNodeFactory::instance()->createNode(toolID, nodeID)

VISIONTOOL_NAMESPACE_END