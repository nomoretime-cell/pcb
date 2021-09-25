#include "Manager.h"

ENGINE_NAMESPACE_BEGIN

Manager* Manager::instance()
{
	static Manager ins;
	return &ins;
}

Manager::Manager()
{
}

Manager::~Manager()
{
}

bool Manager::initBlock(_In_ std::string blockID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			blockInfo.ptr->initAllNode(img, nodeIDMapInitConfigJson);
			return true;
		}
	}
	return false;
}

bool Manager::initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->initNode(img, nodeID, initConfigJson);
		}
	}
	return false;
}

bool Manager::setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->setInput(nodeID, inputJson);
		}
	}
	return false;
}

bool Manager::setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->setConfig(nodeID, configJson);
		}
	}
	return false;
}

std::string Manager::getConfig(_In_ const std::string& nodeID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->getConfig(nodeID);
		}
	}
	return "";
}

bool Manager::process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID = "", _In_ std::string runToBlockID = "") {
	for (const auto& blockInfo : m_vecBlockInfos) {

	}
	return true;
}

bool Manager::stop() {
	return true;
}

bool Manager::command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson) {
	return true;
}

std::map<std::string, std::string> Manager::getBlockResult(_In_ const std::string& blockId) {
	std::map<std::string, std::string> ret;
	return ret;
}

std::string Manager::getNodeResult(_In_ const std::string& nodeID) {
	return "";
}

std::string Manager::addNode(_In_ const std::string& blockID, _In_ const std::string& nodeType) {
	return "";
}

bool Manager::removeNode(_In_ const std::string& blockID, _In_ const std::string& nodeID) {
	return true;
}

std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> Manager::getBlockNode(_In_ const std::string& blockID) {
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> ret;
	return ret;
}

std::map<std::string, std::shared_ptr<IBlock>> Manager::getAllBlock() {
	return std::map<std::string, std::shared_ptr<IBlock>>();
}

std::string Manager::getBlockType(const std::string blockID) {
	return "";
}

std::string Manager::getNodeType(const std::string nodeID) {
	return "";
}

bool Manager::addLink(_In_ const LinkItem& link) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		blockInfo.ptr->addLink(link);
	}
	return true;
}

bool Manager::deleteLink(_In_ const LinkItem& link) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		blockInfo.ptr->deleteLink(link);
	}
	return true;
}

ENGINE_NAMESPACE_END