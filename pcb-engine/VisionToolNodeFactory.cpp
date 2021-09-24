#include "VisionToolNodeFactory.h"

VISIONTOOL_NAMESPACE_BEGIN

VisionToolNodeFactory* VisionToolNodeFactory::instance()
{
	static VisionToolNodeFactory ins;
	return &ins;
}

/// \brief 创建节点对象
/// \param[in]  toolID    工具ID
/// \retval     节点对象
IVisionToolPtr VisionToolNodeFactory::createNode(std::string toolID, int32_t nodeID)
{
	if (toolID == "" || nodeID < 0)
	{
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