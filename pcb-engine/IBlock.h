#pragma once

#include <string>
#include <list>
#include <memory>
#include <map>
#include "Defs.h"
#include "IComponent.h"
#include "IVisionTool.h"

ENGINE_NAMESPACE_BEGIN

struct LinkItem
{
	std::string		fromNodeID; ///< 连线的起始点
	std::string		fromParam;  ///< 连线的起始点参数 格式如 "point.x"
	std::string		toNodeID;   ///< 连线的终点
	std::string		toParam;    ///< 连线的终点参数   格式如 "count"
};

class IBlock : public IComponent::IObjectUnknown
{
public:
	class IFactory : public IComponent::IFactoryUnknown
	{
	public:

		virtual ~IFactory() {}

		virtual const char* iid() { return "IBlock"; }

		static const char* siid() { return "IBlock"; }
	};

	IBlock() {};
	virtual ~IBlock() {};

	/// \brief	初始化所有算子（没有initConfigJson的算子，初始化时传入空）
	/// \param[in]	img						图像指针
	/// \param[in]	nodeIDMapInitConfigJson	node对应初始化参数
	/// \retval		true  成功   false 失败
	virtual bool initAllNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson) = 0;
	
	/// \brief	初始化特定算子
	/// \param[in]	img				图像指针
	/// \param[in]	nodeID			nodeid
	/// \param[in]	initConfigJson	初始化参数
	/// \retval		true  成功   false 失败
	virtual bool initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson) = 0;

	/// \brief	设置算子输入参数
	/// \param[in]	nodeID			nodeid
	/// \param[in]	inputJson		输入参数
	/// \retval		true  成功   false 失败
	virtual bool setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) = 0;
	
	/// \brief	设置算子配置参数
	/// \param[in]	nodeID			nodeid
	/// \param[in]	configJson		输入参数
	/// \retval		true  成功   false 失败
	virtual bool setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) = 0;

	/// \brief	获取算子配置参数
	/// \param[in]	nodeID			nodeid
	/// \retval		算子配置参数
	virtual std::string getConfig(_In_ const std::string& nodeID) = 0;

	/// \brief	处理函数
	/// \param[in]	img					图像指针
	/// \param[in]	nodeMapInJson		输入参数
	/// \param[in]	nodeMapOutJson		输出结果
	/// \retval		true  成功   false 失败
	virtual bool process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) = 0;

	/// \brief	CMD函数
	/// \param[in]	img			图像指针
	/// \param[in]	nodeID		nodeID
	/// \param[in]	inJson		输入参数
	/// \param[in]	outJson		输出结果
	/// \retval		true  成功   false 失败
	virtual bool command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson) = 0;

	/// \brief	获取block所有结果
	/// \retval		nodeid对应结果
	virtual std::map<std::string, std::string> getAllResult() = 0;

	/// \brief	获取指定nodeid结果
	/// \retval		nodeid结果
	virtual std::string getResult(_In_ std::string nodeID) = 0;

	/// \brief	获取block id
	/// \retval	block id
	virtual std::string getBlockID() = 0;

	/// \brief	获取block id
	/// \retval	block id
	virtual std::string getBlockType() = 0;
	
	/// \brief	增加算子
	/// \param[in]	nodeType	算子类型
	/// \retval		算子id
	virtual std::string addNode(_In_ const std::string& nodeType) = 0;

	/// \brief	删除算子
	/// \param[in]	nodeID	算子id
	/// \retval		是否删除成功
	virtual bool removeNode(_In_ const std::string& nodeID) = 0;

	/// \brief	是否包含nodeid
	/// \param[in]	nodeID	算子id
	/// \retval		是否删除成功
	virtual bool hasNode(_In_ const std::string& nodeID) = 0;

	/// \brief	获取所有算子id
	/// \retval 此block下的所有算子id
	virtual std::map<std::string, std::shared_ptr<VisionTool::IVisionTool>> getAllNode() = 0;

	/// \brief	 增加连线（fromNodeID来自上一个block）
	/// \param[in]	link 连线信息
	/// \retval		是否连线成功
	virtual bool addLink(_In_ const LinkItem& link) = 0;

	/// \brief	 更新连线（fromNodeID来自上一个block）
	/// \param[in]	link 连线信息
	/// \retval		是否更新连线成功
	virtual bool deleteLink(_In_ const LinkItem& link) = 0;

};

ENGINE_NAMESPACE_END
