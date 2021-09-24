#include "NormalBlockFactory.h"

ENGINE_NAMESPACE_BEGIN

NormalBlockFactory* NormalBlockFactory::instance()
{
	static NormalBlockFactory ins;
	return &ins;
}

/// \brief 创建节点对象
/// \param[in]  toolID    工具ID
/// \retval     节点对象
std::shared_ptr<IBlock> NormalBlockFactory::createNode(std::string toolID, int32_t nodeID)
{
	if (toolID == "" || nodeID < 0)
	{
		return nullptr;
	}

	return IComponent::createComponentObject<IBlock>(toolID.c_str(), nodeID);
	//return nullptr;
}

NormalBlockFactory::NormalBlockFactory()
{
}

NormalBlockFactory::~NormalBlockFactory()
{
}

ENGINE_NAMESPACE_END