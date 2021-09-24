#include "NormalBlockFactory.h"

ENGINE_NAMESPACE_BEGIN

NormalBlockFactory* NormalBlockFactory::instance()
{
	static NormalBlockFactory ins;
	return &ins;
}

/// \brief �����ڵ����
/// \param[in]  toolID    ����ID
/// \retval     �ڵ����
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