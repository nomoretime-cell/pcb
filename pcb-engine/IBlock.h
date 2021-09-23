#pragma once

#include <string>
#include <list>
#include <memory>
#include <map>
#include "Defs.h"
#include "CommonStruct.h"
#include "IComponent.h"

ENGINE_NAMESPACE_BEGIN

class IBlock : public IComponent::IObjectUnknown
{
public:
	class IFactory : public IComponent::IFactoryUnknown
	{
	public:

		virtual ~IFactory() {}

		virtual const char* iid() { return "IBlock"; }
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
	virtual int setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) = 0;
	
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
	virtual bool command(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& inJson, _Out_ std::string& outJson) = 0;

	/// \brief	获取block结果
	/// \retval		nodeid对应结果
	virtual std::map<std::string, std::string> getResult() = 0;

	/// \brief	获取block id
	/// \retval	block id
	virtual std::string getBlockID() = 0;

	// 增加算子
	virtual std::string addNode(_In_ const std::string& nodeType) = 0;

	// 删除算子
	virtual bool removeNode(_In_ const std::string& nodeID) = 0;

	// 获取所有算子id
	virtual std::list<std::string> getAllNode() = 0;

	// 增加连线（fromNodeID来自上一个block）
	virtual bool addLink(_In_ const std::string& fromNodeID, _In_ const std::string& toNodeID) = 0;

	// 更新连线（fromNodeID来自上一个block）
	virtual bool updateLinks(_In_ const std::string& oldfromNodeID, _In_ const std::string& newfromNodeID, _In_ const std::string& toNodeID) = 0;

private:
	// 算子结果
	// 算子连线
	// 算子uuid创建
};

ENGINE_NAMESPACE_END
