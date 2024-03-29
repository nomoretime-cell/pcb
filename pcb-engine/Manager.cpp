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

Manager::Manager(){
	m_running = false;
	m_blockIndex = 0;
	m_resultCallback = nullptr;
}

Manager::~Manager(){
	if (m_runThread.joinable())
		m_runThread.join();
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
			return blockInfo.ptr->initNode(nodeID, img, initConfigJson);
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

std::string Manager::getInput(_In_ const std::string& nodeID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->getInput(nodeID);
		}
	}
	return "";
}

bool Manager::setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->setConfig(nodeID, configJson);
		}
	}
	return false;
}

bool Manager::setOutput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.ptr->hasNode(nodeID)) {
			return blockInfo.ptr->setOutput(nodeID, inputJson);
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

bool Manager::run(_In_ std::shared_ptr<MvpImage> img, _In_ std::string runFromBlockID) {
	if (m_running) {
		// 程序运行中
		return false;
	}
	if (m_runThread.joinable()) {
		m_runThread.join();
	}
	m_running = true;
	m_runThread = std::thread(std::bind(&Manager::innerRun, this, img, runFromBlockID, ""));
	return true;
}

bool Manager::attachResultCallback(std::function<void(std::map<std::string, std::map<std::string, std::string>>)> func) {
	m_resultCallback = func;
	return true;
}

bool Manager::detachResultCallback() {
	m_resultCallback = nullptr;
	return true;
}

bool Manager::runOnce(_In_ std::shared_ptr<MvpImage> img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID) {
	if (m_runThread.joinable()) {
		m_runThread.join();
	}
	m_running = false;
	m_runThread = std::thread(std::bind(&Manager::innerRun, this, img, runFromBlockID, runToBlockID));
	//m_runThread.join();
	return true;
}

void Manager::innerRun(_In_ std::shared_ptr<MvpImage> img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID) {
	bool isBlockRun = false;
	do {
		bool isBlockRunFromFirst = true;
		for (const auto& blockInfo : m_vecBlockInfos) {
			if (!isBlockRun && runFromBlockID != "" && blockInfo.blockId != runFromBlockID) {
				isBlockRunFromFirst = false;
				continue;
			}
			isBlockRun = true;
			if (isBlockRunFromFirst) {
				isBlockRunFromFirst = false;
				for (const auto& blockInfo : m_vecBlockInfos) {
					// 清空历史结果（是否要在第一次进来清空所有block结果）
					//blockInfo.ptr->clearResult();
				}
			}

			// 获取当前block之前所有block中所有node结果
			std::map<std::string, std::string> nodeMapInJson;
			for (const auto& block : m_vecBlockInfos) {
				if (block.blockId == blockInfo.blockId) {
					break;
				}
				for (const auto& nodeResult : block.ptr->getAllNodeResult()) {
					nodeMapInJson.insert(nodeResult);
				}
			}

			// block处理函数
			std::map<std::string, std::string> nodeMapOutJson = std::map<std::string, std::string>();
			if (!blockInfo.ptr->process(img, nodeMapInJson, nodeMapOutJson)) {
				m_running = false;
				break;
			}

			if (isBlockRun && runToBlockID == blockInfo.blockId) {
				break;
			}
		}

		if (m_resultCallback != nullptr) {
			// 获取结果
			std::map<std::string, std::map<std::string, std::string>> result;
			for (const auto& blockInfo : m_vecBlockInfos) {
				std::string blockID = blockInfo.blockId;
				std::map<std::string, std::string> blockResult = blockInfo.ptr->getAllNodeResult();
				result.insert(std::pair<std::string, std::map<std::string, std::string>>(blockID, blockResult));
			}
			m_resultCallback(result);
		}
	} while (m_running);
}

bool Manager::stop() {
	if (m_runThread.joinable())
		m_runThread.join();
	m_running = false;
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

bool Manager::addBlock(_In_ const std::string& blockType, _InOut_ std::string& blockID) {
	int tmpBlockID = 0;
	if (blockID == "") {
		tmpBlockID = ++m_blockIndex;
	}
	else {
		std::string indexStr = NodeIDCreator::instance()->getIndex(blockID);
		if (m_blockIndex < atoi(indexStr.c_str())) {
			m_blockIndex = atoi(indexStr.c_str());
		}
		tmpBlockID = atoi(indexStr.c_str());
	}


	BlockInfo blockInfo;
	blockInfo.ptr = Engine::NormalBlockFactory::createNode(BLOCK_TYPE, tmpBlockID);
	std::string strBlockId = BLOCK_TYPE + std::to_string(tmpBlockID);
	blockInfo.blockId = strBlockId;
	if (blockInfo.ptr == nullptr) {
		return false;
	}
	m_vecBlockInfos.emplace_back(blockInfo);
	blockID = strBlockId;
	return true;
}

bool Manager::clearAllBlock() {
	for (const auto& blockInfo : m_vecBlockInfos) {
		blockInfo.ptr->deleteAllLink();
		for (const auto& node : blockInfo.ptr->getAllNode()) {
			node.second->uninit();
		}
	}
	m_vecBlockInfos.clear();
	NodeIDCreator::instance()->clearID();
	m_blockIndex = 0;
	return true;
}

bool Manager::addNode(_In_ const std::string& blockID, _In_ const std::string& nodeType, _InOut_ std::string& nodeID) {
	for (const auto& blockInfo : m_vecBlockInfos) {
		if (blockInfo.blockId == blockID) {
			return blockInfo.ptr->addNode(nodeType, nodeID);
		}
	}
	return false;
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