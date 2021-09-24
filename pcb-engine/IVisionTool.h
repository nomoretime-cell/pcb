#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Defs.h"
#include "IComponent.h"

VISIONTOOL_NAMESPACE_BEGIN

/// \抽象节点接口
class IVisionTool : public IComponent::IObjectUnknown
{
public:

	/// 组件工厂
	class IFactory : public IComponent::IFactoryUnknown
	{
	public:
		/// 组件创建接口
		virtual IObjectUnknown* create() { return nullptr; };

		/// 组件接口ID定义
		virtual const char* iid() { return "IVisionTool"; }

		static const char* siid() { return "IVisionTool"; }

		const char* clsid() { return "VisionTool"; }
	};

	/// 获取工具ID
	/// \param[out] id   工具ID
	/// \retval     true 成功   false 失败
	virtual bool getToolID(std::string& id) const = 0;

	/// \brief 获取输出参数描述
	/// \param[out] param 参数的描述
	/// \retval     true 成功   false 失败
	virtual bool getOutputParam(std::string& param) const = 0;

	/// \brief 获取输入参数描述
	/// \param[out] param 参数的描述
	/// \retval     true 成功   false 失败
	virtual bool getInputParam(std::string& param) const = 0;

	/// \brief 配置输入参数的默认值
	/// \param[in] inputList 配置
	/// \retval    true  成功   false 失败
	virtual bool setInputParam(const std::string& inputList) = 0;

	/// \brief 初始化算子
	/// \param[in]  param  初始化参数
	/// \retval     true 成功   false 失败
	virtual bool init(const std::string& inputList) = 0;

	/// \brief 反初始化算子
	/// \retval     true 成功   false 失败
	virtual bool uninit() = 0;

	/// \brief 处理接口
	/// \param[in]  inParam  输入参数
	/// \param[out] outParam 输出参数
	/// \retval     true 成功   false 失败
	virtual bool process(const std::string& inParam, std::string& outParam) = 0;

	/// \brief 配置设置
	/// \param[in] cfgList 配置
	/// \retval    true  成功   false 失败
	virtual bool setConfig(const std::string& cfgList) = 0;

	/// \brief 配置获取
	/// \param[in]  cfgName 配置名称
	/// \param[out] cfgList 配置
	/// \retval     true  成功   false 失败
	virtual bool getConfig(const std::string& cfgList) const = 0;

	/// \brief 命令运行
	/// \param[in] cmd  "AddInputParam"  添加输入参数
	///                 "DelInputParam"  删除输入参数
	///                 "AddOutputParam" 添加输出参数
	///                 "DelOutputParam" 删除输出参数
	///                 "AddConfig"      添加配置参数
	///                 "DelConfig"      删除配置参数
	/// \param[in]  inParam  输入参数
	/// \param[out] outParam 输出参数
	/// \retval    true  成功   false 失败
	virtual bool command(const std::string& cmd, const std::string& inParam, const std::string& outParam) = 0;

protected:

	/// \brief 虚析构
	virtual ~IVisionTool() {}
};

typedef std::shared_ptr<IVisionTool> IVisionToolPtr;

VISIONTOOL_NAMESPACE_END
