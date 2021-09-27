#pragma once

#include <vector>
#include "Defs.h"
#include "IBlock.h"
#include "IVisionTool.h"

ENGINE_NAMESPACE_BEGIN

class NormalBlock : public IBlock
{
public:

	class NormalEngineBlockFactory : public IBlock::IFactory
	{
	public:
		NormalEngineBlockFactory() {
			registerFactory();
		}

		~NormalEngineBlockFactory() {
			unregisterFactory();
		}

		NormalBlock* create(int blockId) override {
			return new NormalBlock(blockId);
		}

		const char* clsid() const override {
			return "NormalBlock";
		}
	};
private:


public:
	NormalBlock(int blockId);
	virtual ~NormalBlock();

	virtual void destroy() override;

	virtual bool initAllNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson) override;

	virtual bool initNode(_In_ const std::string& nodeID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& initConfigJson) override;

	virtual bool setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) override;

	virtual bool setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) override;

	virtual std::string getConfig(_In_ const std::string& nodeID) override;

	virtual bool process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) override;

	virtual bool command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson)override;

	virtual std::map<std::string, std::string> getAllNodeResult() override;

	virtual std::string getNodeResult(_In_ const std::string& nodeID) override;

	virtual std::string getNodeType(_In_ const std::string& nodeID) override;

public:
	virtual std::string getBlockID() override;

	virtual std::string getBlockType() override;

	virtual std::string addNode(_In_ const std::string& nodeType) override;

	virtual bool removeNode(_In_ const std::string& nodeID) override;

	virtual bool hasNode(_In_ const std::string& nodeID) override;

	virtual std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> getAllNode() override;

	virtual bool addLink(_In_ const LinkItem& link) override;

	virtual bool deleteLink(_In_ const LinkItem& link) override;

private:

	std::string getFromNodeID(_In_ const std::string& thisNodeId);

private:
	std::string	m_blockType = "NormalBlock";										///< block type
	std::string	m_blockID;																///< block id
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool>>	m_nodeIDMapNodePtr;	///< 算子
	std::map<std::string, std::string> m_nodeIDMapResult;								///< 算子结果
	std::vector<LinkItem> m_links;														///< 连接关系
};

ENGINE_NAMESPACE_END