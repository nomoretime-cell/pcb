#pragma once

#include <vector>
#include <list>
#include <string>
#include <atomic>
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

	/// \brief 初始化block下所有node
	/// \param[in] blockID blockID
	/// \param[in] img 图像
	/// \param[in] nodeIDMapInitConfigJson	node对应初始化参数
	/// \retval 没有blockID对应对象返回false
	bool initBlock(_In_ std::string blockID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson);

	/// \brief 初始化特定node
	/// \param[in] img 图像指针
	/// \param[in] nodeID nodeID
	/// \param[in] initConfigJson 初始化参数
	/// \retval 在所有block无nodeid对应node对象
	bool initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson);

	/// \brief 设置算子输入参数
	/// \param[in] nodeID nodeID
	/// \param[in] inputJson 输入参数
	/// \retval 在所有block无nodeid对应node对象
	bool setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson);

	/// \brief 设置算子配置参数
	/// \param[in] nodeID nodeid
	/// \param[in] configJson 输入参数
	/// \retval 在所有block无nodeid对应node对象
	bool setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson);

	/// \brief 获取算子配置参数
	/// \param[in] nodeID nodeid
	/// \retval 在所有block无nodeid对应node对象
	std::string getConfig(_In_ const std::string& nodeID);

	/// \brief 运行
	/// \param[in] img 图像指针
	/// \param[in] runFromBlockID 开始block id
	/// \param[in] runToBlockID 结束block id
	/// \retval true 成功 false 失败
	bool run(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID = "", _In_ std::string runToBlockID = "");

	/// \brief 运行一次
	/// \param[in] img 图像指针
	/// \param[in] runFromBlockID 开始block id
	/// \param[in] runToBlockID 结束block id
	/// \retval true 成功 false 失败
	bool runOnce(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID = "", _In_ std::string runToBlockID = "");

	/// \brief 停止运行
	/// \retval true 成功 false 失败
	bool stop();

	/// \brief CMD
	/// \param[in] nodeID nodeID
	/// \param[in] cmd cmd指令
	/// \param[in] img 图像
	/// \param[in] inJson 输入参数
	/// \param[in] outJson 输出参数
	/// \retval true 成功 false 失败
	bool command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson);

	/// \brief 获取blockid对应所有node结果
	/// \param[in] blockId blockId
	/// \retval 本地没有blockid对应的block
	std::map<std::string, std::string> getBlockResult(_In_ const std::string& blockId);

	/// \brief 获取nodeid对应所有node结果
	/// \param[in] nodeID nodeID
	/// \retval 在所有block无nodeid对应node对象
	std::string getNodeResult(_In_ const std::string& nodeID);

	/// \brief 添加算子
	/// \param[in] blockID blockID
	/// \param[in] nodeType nodeType
	/// \retval nodeid
	std::string addNode(_In_ const std::string& blockID, _In_ const std::string& nodeType);

	/// \brief 删除算子
	/// \param[in] blockID blockID
	/// \param[in] nodeID nodeID
	/// \retval 找不到nodeID对应的算子实例
	bool removeNode(_In_ const std::string& blockID, _In_ const std::string& nodeID);
	
	/// \brief 获取blockid下所有node
	/// \param[in] blockID blockID
	/// \retval nodeid对应的node对象
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> getAllNode(_In_ const std::string& blockID);

	/// \brief 获取blockid下所有node
	/// \param[in] blockID blockID
	/// \retval nodeid对应的node对象
	std::vector<BlockInfo> getAllBlock();

	/// \brief 获取blockid对应的blocktype
	/// \param[in] blockID blockID
	/// \retval block type
	std::string getBlockType(const std::string blockID);

	/// \brief 获取nodeID对应的node type
	/// \param[in] nodeID nodeID
	/// \retval node type
	std::string getNodeType(const std::string nodeID);

	/// \brief 增加连线
	/// \param[in] 连线对象的序列化参数
	/// \retval 增加连线是否成功
	bool addLink(_In_ const std::string& link);

	/// \brief 删除连线
	/// \param[in] 删除连线对象的序列化参数
	/// \retval 删除连线是否成功
	bool deleteLink(_In_ const std::string& link);

private:

	void innerRun(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID);

private:
	std::vector<BlockInfo> m_vecBlockInfos;
	std::atomic<bool> m_running;
	std::thread m_runThread;
};

ENGINE_NAMESPACE_END
