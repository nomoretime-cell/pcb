#include <memory>
#include <thread>
#include <future>
#include <algorithm>
#include <vector>
#include "NormalBlock.h"
#include "VisionToolNodeFactory.h"

ENGINE_NAMESPACE_BEGIN

static int blockIdIndex = 0;

NormalEngineBlock::NormalEngineBlock() {
	m_blockID = "NormalEngineBlock" + std::to_string(++blockIdIndex);
}

NormalEngineBlock::~NormalEngineBlock() {

}

void NormalEngineBlock::destroy() {
	delete this;
}

bool NormalEngineBlock::initAllNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson){
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

bool NormalEngineBlock::initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		node->second->init(img, initConfigJson);
		return true;
	}
	else {
		return false;
	}
}

bool NormalEngineBlock::setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		node->second->setInputParam(inputJson);
		return true;
	}
	else {
		return false;
	}
}

bool NormalEngineBlock::setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		node->second->setConfig(configJson);
		return true;
	}
	else {
		return false;
	}
}

std::string NormalEngineBlock::getConfig(_In_ const std::string& nodeID) {
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

bool NormalEngineBlock::process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) {
	// ���Ӳ��м���
	std::map<std::string, std::future<std::string>&> nodeIdMapFuture;
	for (const auto& node : m_nodeIDMapNodePtr) {
		std::string thisNodeId = node.first;
		auto		thisNodePtr = node.second;
		std::string thisNodeResult;
		std::string lastNodeId = getFromNodeID(thisNodeId);
		std::string lastNodeResult;

		if (lastNodeId == "") {
			// error
			continue;
		}

		auto lastNodePair = nodeMapInJson.find(lastNodeId);
		if (lastNodePair == nodeMapInJson.end()) {
			// error, no lastNode result
			continue;
		}
		lastNodeResult = lastNodePair->second;

		std::future<std::string> future = std::async(std::launch::async, [=] {
			std::string result;
			thisNodePtr->process(img, lastNodeResult, result);
			return result;
			});

		nodeIdMapFuture.emplace(std::pair<std::string, std::future<std::string>&>(thisNodeId, future));
	}

	for (const std::pair<std::string, std::future<std::string>&> f : nodeIdMapFuture) {
		std::string nodeId = f.first;
		std::future<std::string>& future = f.second;
		std::string nodeResult = future.get();
		m_nodeIDMapResult.insert(std::pair<std::string, std::string>(nodeId, nodeResult));
	}
	return true;
}

bool NormalEngineBlock::command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node != m_nodeIDMapNodePtr.end()) {
		return node->second->command(cmd, img, inJson, outJson);
	}
	else {
		return false;
	}
}

std::map<std::string, std::string> NormalEngineBlock::getAllResult() {
	return m_nodeIDMapResult;
}

std::string NormalEngineBlock::getResult(_In_ std::string nodeID) {
	auto result = m_nodeIDMapResult.find(nodeID);
	if (result != m_nodeIDMapResult.end()) {
		return result->second;
	}
	else {
		return "";
	}
}

std::string NormalEngineBlock::getBlockID() {
	return m_blockID;
}

std::string NormalEngineBlock::getBlockType() {
	return m_blockType;
}

std::string NormalEngineBlock::addNode(_In_ const std::string& nodeType) {
	int nodeId = 0;
	std::shared_ptr<VisionTool::IVisionTool > node = VisionTool::VisionToolNodeFactory::createNode(nodeType, nodeId);
	if (node == nullptr) {
		return "";
	}
	m_nodeIDMapNodePtr.insert(std::pair<std::string, std::shared_ptr<VisionTool::IVisionTool>>(std::to_string(nodeId), node));
	return std::to_string(nodeId);
}

bool NormalEngineBlock::removeNode(_In_ const std::string& nodeID) {
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >>::iterator pos = m_nodeIDMapNodePtr.find(nodeID);
	if (pos != m_nodeIDMapNodePtr.end()) 
	{
		m_nodeIDMapNodePtr.erase(pos);
	};
	return true;
}

bool NormalEngineBlock::hasNode(_In_ const std::string& nodeID) {
	auto node = m_nodeIDMapNodePtr.find(nodeID);
	if (node == m_nodeIDMapNodePtr.end()) {
		return false;
	}
	else {
		return true;
	}
}

std::map<std::string, std::shared_ptr<VisionTool::IVisionTool>> NormalEngineBlock::getAllNode() {
	return m_nodeIDMapNodePtr;
}

bool NormalEngineBlock::addLink(_In_ const LinkItem& link) {
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

bool NormalEngineBlock::deleteLink(_In_ const LinkItem& link) {
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

std::string NormalEngineBlock::getFromNodeID(_In_ const std::string& thisNodeId) {
	for (const auto& link: m_links) {
		if (link.toNodeID == thisNodeId) {
			return link.fromNodeID;
		}
	}
	return "";
}

ENGINE_NAMESPACE_END