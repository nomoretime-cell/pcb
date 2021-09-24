#include "VisionToolNodeFactory.h"

VISIONTOOL_NAMESPACE_BEGIN

VisionToolNodeFactory* VisionToolNodeFactory::instance()
{
	static VisionToolNodeFactory ins;
	return &ins;
}

/// \brief �����ڵ����
/// \param[in]  toolID    ����ID
/// \retval     �ڵ����
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