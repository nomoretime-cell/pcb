#include <memory>
#include <thread>
#include <future>
#include <algorithm>
#include <vector>
#include "NormalBlock.h"
#include "VisionToolNodeFactory.h"

ENGINE_NAMESPACE_BEGIN

// 注册 NormalBlock 对象
static NormalBlock::NormalEngineBlockFactory registerBlock;

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

bool NormalBlock::process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) {
	// 算子并行计算
	std::map<std::string, std::future<std::string>&> nodeIdMapFuture;
	for (const auto& node : m_nodeIDMapNodePtr) {
		std::string thisNodeId = node.first;
		auto		thisNodePtr = node.second;
		std::string thisNodeResult;

		std::string lastNodeId = getFromNodeID(thisNodeId);
		std::string lastNodeResult = "";

		if (lastNodeId == "") {
			// thisNode是第一个算子
		}
		else {
			// thisNode有被连为输入算子
			auto lastNodePair = nodeMapInJson.find(lastNodeId);
			if (lastNodePair == nodeMapInJson.end()) {
				// error 有连线，但是id对应的算子指针为空
				continue;
			}
			lastNodeResult = lastNodePair->second;
		}

		std::future<std::string> future = std::async(std::launch::async, [=] {
			std::string result;
			thisNodePtr->process(img, lastNodeResult, result);
			return result;
			});

		nodeIdMapFuture.emplace(std::pair<std::string, std::future<std::string>&>(thisNodeId, future));
	}

	// 等待所有并行算子结束运行
	for (const std::pair<std::string, std::future<std::string>&> f : nodeIdMapFuture) {
		std::string nodeId = f.first;
		std::future<std::string>& future = f.second;
		std::string nodeResult = future.get();
		m_nodeIDMapResult.insert(std::pair<std::string, std::string>(nodeId, nodeResult));
	}
	return true;
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
	std::string strNodeid = m_blockType + std::to_string(nodeId);
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

std::string NormalBlock::getFromNodeID(_In_ const std::string& thisNodeId) {
	for (const auto& link: m_links) {
		if (link.toNodeID == thisNodeId) {
			return link.fromNodeID;
		}
	}
	return "";
}

ENGINE_NAMESPACE_END