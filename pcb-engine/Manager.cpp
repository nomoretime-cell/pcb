#include <thread>
#include "Manager.h"
#include "json.hpp"
#include "NormalBlockFactory.h"
ENGINE_NAMESPACE_BEGIN

Manager* Manager::instance()
{
	static Manager ins;
	return &ins;
}

Manager::Manager()
{
	m_running = false;
}

Manager::~Manager()
{
}

bool Manager::initBlock(_In_ const std::string& blockID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			blockInfo.ptr->initAllNode(img, nodeIDMapInitConfigJson);
			return true;
		}
	}
	return false;
}

bool Manager::initNode(_In_ const std::string& nodeID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& initConfigJson) {
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

bool Manager::run(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID) {
	m_running = true;
	m_runThread = std::thread(std::bind(&Manager::innerRun, this, img, runFromBlockID,runToBlockID));
	return true;
}

bool Manager::runOnce(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID) {
	m_running = false;
	m_runThread = std::thread(std::bind(&Manager::innerRun, this, img, runFromBlockID, runToBlockID));
	return true;
}

void Manager::innerRun(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID) {
	std::map<std::string, std::string> nodeMapInJson;
	std::map<std::string, std::string> nodeMapOutJson;
	bool isRunning = false;
	do {
		for (const auto& blockInfo : m_vecBlockInfos) {
			if (!isRunning && runFromBlockID != "" && blockInfo.blockId != runFromBlockID) {
				continue;
			}
			isRunning = true;
			nodeMapInJson = nodeMapOutJson;
			nodeMapOutJson = std::map<std::string, std::string>();
			blockInfo.ptr->process(img, nodeMapInJson, nodeMapOutJson);
			if (isRunning && runToBlockID == blockInfo.blockId) {
				break;
			}
		}
	} while (m_running);
}

bool Manager::stop() {
	m_running = false;
	m_runThread.join();
	return true;
}

bool Manager::command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->command(nodeID, cmd, img, inJson, outJson);
		}
	}
	return false;
}

std::map<std::string, std::string> Manager::getBlockResult(_In_ const std::string& blockID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			return blockInfo.ptr->getAllNodeResult();
		}
	}
	return std::map<std::string, std::string>();
}

std::string Manager::getNodeResult(_In_ const std::string& nodeID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->getNodeResult(nodeID);
		}
	}
	return "";
}

std::string Manager::addBlock(_In_ const std::string& blockType) {
	// TODO
	std::string blockId = "";
	BlockInfo blockInfo;
	blockInfo.ptr = Engine::NormalBlockFactory::createNode("NormalBlockFactory", 1);
	blockInfo.blockId = blockId;
	m_vecBlockInfos.emplace_back(blockInfo);
	return blockId;
}


std::string Manager::addNode(_In_ const std::string& blockID, _In_ const std::string& nodeType) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			return blockInfo.ptr->addNode(nodeType);
		}
	}
	return "";
}

bool Manager::removeNode(_In_ const std::string& blockID, _In_ const std::string& nodeID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			return blockInfo.ptr->removeNode(nodeID);
		}
	}
	return false;
}

std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> Manager::getAllNode(_In_ const std::string& blockID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			return blockInfo.ptr->getAllNode();
		}
	}
	return std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >>();
}

std::vector<BlockInfo> Manager::getAllBlock() {
	return m_vecBlockInfos;
}

std::string Manager::getBlockType(const std::string& blockID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			return blockInfo.ptr->getBlockType();
		}
	}
	return "";
}

std::string Manager::getNodeType(const std::string& nodeID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->getNodeType(nodeID);
		}
	}
	return "";
}

bool Manager::addLink(_In_ const std::string& strLink) {
	LinkItem link = LinkItem::getLinkItem(strLink);
	for (const auto& blockInfo : m_vecBlockInfos) {
		blockInfo.ptr->addLink(link);
	}
	return true;
}

bool Manager::deleteLink(_In_ const std::string& strLink) {
	LinkItem link = LinkItem::getLinkItem(strLink);
	for (const auto& blockinfo : m_vecBlockInfos) {
		blockinfo.ptr->deleteLink(link);
	}
	return true;
}

ENGINE_NAMESPACE_END