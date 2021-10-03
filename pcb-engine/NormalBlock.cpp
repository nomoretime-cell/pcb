#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <algorithm>
#include <vector>
#include "NormalBlock.h"
#include "VisionToolNodeFactory.h"
#include "VisionToolMock.hpp"
#include "VisionToolMock2.hpp"

ENGINE_NAMESPACE_BEGIN

// 注册 NormalBlock 对象
static NormalBlock::NormalEngineBlockFactory registerBlock;
static VisionTool::VisionToolMock::VisionToolMockFactory registerVisionTool;
static VisionTool::VisionToolMock2::VisionToolMockFactory registerVisionTool2;

NormalBlock::NormalBlock(int blockId) {
	m_blockID = "NormalBlock" + std::to_string(blockId);	
}

NormalBlock::~NormalBlock() {

}

void NormalBlock::destroy() {
	delete this;
}

bool NormalBlock::initAllNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson){
	for (const auto& node : m_nodeIDMapNodePtr) {
		auto nodeConfig = nodeIDMapInitConfigJson.find(node.first);
		if (nodeConfig != nodeIDMapInitConfigJson.end()) {
			node.second->init(img, nodeConfig->second);
		}
		else {
			node.second->init(img, "");
		}
	}
	return true;
}

bool NormalBlock::initNode(_In_ const std::string& nodeID, _In_ const std::shared_ptr<MvpImage>& img,  _In_ const std::string& initConfigJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		node->second->init(img, initConfigJson);
		return true;
	}
	else {
		return false;
	}
}

bool NormalBlock::setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		node->second->setInputParam(inputJson);
		return true;
	}
	else {
		return false;
	}
}

std::string NormalBlock::getInput(_In_ const std::string& nodeID) {
	auto nodePtr = m_nodeIDMapInput.find(nodeID);
	if (nodePtr != m_nodeIDMapInput.end()) {
		return nodePtr->second;
	}
	else {
		return "";
	}
}

bool NormalBlock::setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		node->second->setConfig(configJson);
		return true;
	}
	else {
		return false;
	}
}

bool NormalBlock::setOutput(_In_ const std::string& nodeID, _In_ const std::string& resultJson) {
	auto item = m_nodeIDMapResult.find(nodeID);
	if (item != m_nodeIDMapResult.end()) {
		m_nodeIDMapResult.erase(item);
	}

	m_nodeIDMapResult.insert(std::pair<std::string, std::string>(nodeID, resultJson));
	return true;
}

std::string NormalBlock::getConfig(_In_ const std::string& nodeID) {
	std::string config;
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		if (node->second->getConfig(config)) {
			return config;
		}
		else{
			return "";
		}
	}
	else {
		return "";
	}
}

bool NormalBlock::process(_InOut_ std::shared_ptr<MvpImage> img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) {
	// 算子并行计算
	std::shared_ptr<std::atomic<bool>> runningState =std::make_shared<std::atomic<bool>>(true);
	std::map<std::string, std::shared_future<std::string>> nodeIdMapFuture;
	for (const auto& node : m_nodeIDMapNodePtr) {
		std::string thisNodeId = node.first;
		auto thisNodePtr = node.second;
		std::string thisNodeResult;

		std::list <std::string> lastNodeIds = getFromNodeID(thisNodeId);
		std::string lastNodeResults = "";

		if (lastNodeIds.size() < 1) {
			// 无输入算子
		} else {
			nlohmann::json jResult = nullptr;
			for (const auto& nodeID : lastNodeIds) {
				// 遍历输入算子
				auto pair = nodeMapInJson.find(nodeID);
				if (pair == nodeMapInJson.end()) {
					// error 被连线的输入算子指针为空
					continue;
				}
				jResult[nodeID] = nlohmann::json::parse(pair->second);
			}
			if (jResult != nullptr) {
				lastNodeResults = jResult.dump();
			}
		}

		// 缓存输入
		auto item = m_nodeIDMapInput.find(node.first);
		if (item != m_nodeIDMapInput.end()) {
			m_nodeIDMapInput.erase(item);
		}
		m_nodeIDMapInput.insert(std::pair<std::string, std::string>(node.first, lastNodeResults));

		// 运行
		std::shared_future<std::string> future = std::async(std::launch::async, [=] () {
			std::string result;
			bool state = thisNodePtr->process(img, lastNodeResults, result);
			runningState->store(runningState->load() && state);
			return result;
			}).share();

		nodeIdMapFuture.emplace(std::pair<std::string, std::shared_future<std::string>>(thisNodeId, future));
	}

	// 等待所有并行算子结束运行
	m_nodeIDMapResult.clear();
	for (const std::pair<std::string, std::shared_future<std::string>> f : nodeIdMapFuture) {
		std::string nodeId = f.first;
		std::shared_future<std::string> future = f.second;
		std::string nodeResult = future.get();
		m_nodeIDMapResult.insert(std::pair<std::string, std::string>(nodeId, nodeResult));
	}
	return runningState->load();
}

bool NormalBlock::command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		return node->second->command(cmd, img, inJson, outJson);
	}
	else {
		return false;
	}
}

std::map<std::string, std::string> NormalBlock::getAllNodeResult() {
	return m_nodeIDMapResult;
}

std::string NormalBlock::getNodeResult(_In_ const std::string& nodeID) {
	auto result = m_nodeIDMapResult.find(nodeID);
	if (result != m_nodeIDMapResult.end()) {
		return result->second;
	}
	else {
		return "";
	}
}

std::string NormalBlock::getNodeType(_In_ const std::string& nodeID) {
	auto item = m_nodeIDMapNodePtr.find(nodeID);
	if (item != m_nodeIDMapNodePtr.end()) {
		std::string nodeType;
		item->second->getToolID(nodeType);
		return nodeType;
	}
	else {
		return "";
	}
}

std::string NormalBlock::getBlockID() {
	return m_blockID;
}

std::string NormalBlock::getBlockType() {
	return m_blockType;
}

std::string NormalBlock::addNode(_In_ const std::string& nodeType) {
	int nodeId = NodeIDCreator::instance()->getID();
	std::shared_ptr<VisionTool::IVisionTool > node = VisionTool::VisionToolNodeFactory::createNode(nodeType, nodeId);
	if (node == nullptr) {
		return "";
	}
	std::string strNodeid = nodeType + std::to_string(nodeId);
	m_nodeIDMapNodePtr.insert(std::pair<std::string, std::shared_ptr<VisionTool::IVisionTool>>(strNodeid, node));
	return strNodeid;
}

bool NormalBlock::removeNode(_In_ const std::string& nodeID) {
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >>::iterator pos = m_nodeIDMapNodePtr.find(nodeID);
	if (pos != m_nodeIDMapNodePtr.end()) 
	{
		m_nodeIDMapNodePtr.erase(pos);
	};
	return true;
}

bool NormalBlock::hasNode(_In_ const std::string& nodeID) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node == m_nodeIDMapNodePtr.end()) {
		return false;
	}
	else {
		return true;
	}
}

std::map<std::string, std::shared_ptr<VisionTool::IVisionTool>> NormalBlock::getAllNode() {
	return m_nodeIDMapNodePtr;
}

bool NormalBlock::addLink(_In_ const LinkItem& link) {
	std::vector<LinkItem>::iterator it = m_links.begin();
	for (; it != m_links.end(); ++it)
	{
		if (it->fromNodeID == link.fromNodeID
			&& it->fromParam == link.fromParam
			&& it->toNodeID == link.toNodeID
			&& it->toParam == link.toParam)
		{
			return false;
		}
	}

	m_links.emplace_back(link);
	return true;
}

bool NormalBlock::deleteLink(_In_ const LinkItem& link) {
	std::vector<LinkItem>::iterator it = m_links.begin();
	for (; it != m_links.end(); ++it)
	{
		if (it->fromNodeID == link.fromNodeID
			&& it->fromParam == link.fromParam
			&& it->toNodeID == link.toNodeID
			&& it->toParam == link.toParam)
		{
			m_links.erase(it);
			return true;
		}
	}

	return false;
}

void NormalBlock::clearResult() {
	m_nodeIDMapResult.clear();
}

std::list<std::string> NormalBlock::getFromNodeID(_In_ const std::string& thisNodeId) {
	std::list<std::string> result;
	for (const auto& link: m_links) {
		if (link.toNodeID == thisNodeId) {
			result.emplace_back(link.fromNodeID);
		}
	}
	return result;
}

ENGINE_NAMESPACE_END