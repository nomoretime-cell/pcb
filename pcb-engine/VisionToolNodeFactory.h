#pragma once

#include "Defs.h"
#include "IVisionTool.h"

VISIONTOOL_NAMESPACE_BEGIN

class VisionToolNodeFactory
{
public:
	static std::shared_ptr<IVisionTool> createNode(std::string toolID, int32_t nodeID) {
		return VisionToolNodeFactory::instance()->innerCreateNode(toolID, nodeID);
	}

private:
	static VisionToolNodeFactory* instance();
	std::shared_ptr<IVisionTool> innerCreateNode(std::string toolID, int32_t nodeID);
	VisionToolNodeFactory();
	~VisionToolNodeFactory();
};

VISIONTOOL_NAMESPACE_END