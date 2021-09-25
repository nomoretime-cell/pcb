#include <memory>
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
	return true;
}

bool NormalEngineBlock::initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson) {
	return true;
}

bool NormalEngineBlock::setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) {
	return true;
}

bool NormalEngineBlock::setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) {
	return true;
}

std::string NormalEngineBlock::getConfig(_In_ const std::string& nodeID) {
	return std::string("");
}

bool NormalEngineBlock::process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) {
	return true;
}

bool NormalEngineBlock::command(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& inJson, _Out_ std::string& outJson) {
	return true;
}

std::map<std::string, std::string> NormalEngineBlock::getAllResult() {
	std::map<std::string, std::string> ret;
	return ret;
}

std::string NormalEngineBlock::getResult(_In_ std::string nodeID) {
	return std::string("");
}

std::string NormalEngineBlock::getBlockID() {
	return m_blockID;
}

std::string NormalEngineBlock::addNode(_In_ const std::string& nodeType) {
	int nodeId = 0;
	std::shared_ptr<VisionTool::IVisionTool > node = VisionTool::VisionToolNodeFactory::createNode(nodeType, nodeId);
	if (node == nullptr) {
		return "";
	}
	m_nodeIDMapNodePtr.insert(std::pair<std::string, std::shared_ptr<VisionTool::IVisionTool>>());
	return std::string("");
}

bool NormalEngineBlock::removeNode(_In_ const std::string& nodeID) {
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >>::iterator pos = m_nodeIDMapNodePtr.find(nodeID);
	if (pos != m_nodeIDMapNodePtr.end()) 
	{
		m_nodeIDMapNodePtr.erase(pos);
	};
	return true;
}

std::map<std::string, std::shared_ptr<VisionTool::IVisionTool>> NormalEngineBlock::getAllNode() {
	return m_nodeIDMapNodePtr;
}

bool NormalEngineBlock::addLink(_In_ const std::string& fromNodeID, _In_ const std::string& toNodeID) {
	return true;
}

bool NormalEngineBlock::updateLinks(_In_ const std::string& oldfromNodeID, _In_ const std::string& newfromNodeID, _In_ const std::string& toNodeID) {
	return true;
}

ENGINE_NAMESPACE_END