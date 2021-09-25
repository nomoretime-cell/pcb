#include "VisionToolNodeFactory.h"

VISIONTOOL_NAMESPACE_BEGIN

VisionToolNodeFactory* VisionToolNodeFactory::instance()
{
	static VisionToolNodeFactory ins;
	return &ins;
}

std::shared_ptr<VisionTool::IVisionTool > VisionToolNodeFactory::innerCreateNode(std::string toolID, int32_t nodeID)
{
	if (toolID == "" || nodeID < 0){
		return nullptr;
	}

	return IComponent::createComponentObject<IVisionTool>(toolID.c_str(), nodeID);
}

VisionToolNodeFactory::VisionToolNodeFactory()
{
}

VisionToolNodeFactory::~VisionToolNodeFactory()
{
}

VISIONTOOL_NAMESPACE_END