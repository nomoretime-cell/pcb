#pragma once

#include <vector>
#include <list>
#include <string>
#include "Defs.h"
#include "IBlock.h"

ENGINE_NAMESPACE_BEGIN

struct BlockInfo
{
	std::string				blockId;
	std::shared_ptr<IBlock> ptr;
};

class Manager
{
public:
	static Manager* instance();

private:
	Manager();
	~Manager();

public:
	bool initBlock(_In_ std::string blockID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson);

	bool initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson);

	bool setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson);

	bool setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson);

	std::string getConfig(_In_ const std::string& nodeID);

	bool process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID);

	bool stop();

	bool command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson);

	std::map<std::string, std::string> getBlockResult(_In_ const std::string& blockId);

	std::string getNodeResult(_In_ const std::string& nodeID);

	std::string addNode(_In_ const std::string& blockID, _In_ const std::string& nodeType);

	bool removeNode(_In_ const std::string& blockID, _In_ const std::string& nodeID);
	
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> getBlockNode(_In_ const std::string& blockID);

	std::map<std::string, std::shared_ptr<IBlock>> getAllBlock();

	std::string getBlockType(const std::string blockID);

	std::string getNodeType(const std::string nodeID);

	bool addLink(_In_ const LinkItem& link);

	bool deleteLink(_In_ const LinkItem& link);

private:
	std::vector<BlockInfo> m_vecBlockInfos;
};

ENGINE_NAMESPACE_END
