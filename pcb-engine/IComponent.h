#pragma once

// WIN32 Dynamic Link Library
#ifdef _MSC_VER
#ifdef COMPONENT_DLL_BUILD
#define  COMPONENT_API _declspec(dllexport)
#elif defined( COMPONENT_DLL_USE ) || defined( UNIVERSAL_DLL_USE )
#define  COMPONENT_API _declspec(dllimport)
#else
#define COMPONENT_API
#endif
#else
#define COMPONENT_API
#endif

#define ICOMPONENT_NAMESPACE_BEGIN namespace IComponent{
#define ICOMPONENT_NAMESPACE_END }

#include <memory>

ICOMPONENT_NAMESPACE_BEGIN

class COMPONENT_API CVersion
{
public:
	char	name[32];	///< 组件名称
	int		major;		///< 主版本号，架构变动时增加
	int		minor;		///< 次版本号，接口变化或严重缺陷修正时增加
	int		revision;	///< 修订版本号，缺陷修正时增加
	int		svn;		///< svn版本号，记录上述3版本号变更时对应的svn版本号
	char date[32];	///< 编译日期，使用__DATE__宏

	/// 构造函数，版本对象一般作为全局对象构造
	CVersion(const char* name, int major, int minor, int revision, const char* svnString, const char* dateString);

	/// 版本信息打印
	void print() const;
};

class COMPONENT_API IObjectUnknown
{
public:
	/// 构造函数
	IObjectUnknown();

	/// 虚析构函数
	virtual ~IObjectUnknown();

	/// 销毁组件对象
	virtual void destroy() = 0;

	/// 获取组件版本号码
	virtual CVersion getVersion() const = 0;
};

class COMPONENT_API IFactoryUnknown
{
public:
	/// 构造函数
	IFactoryUnknown();
	/// 虚析构函数
	virtual ~IFactoryUnknown();

	/// 注册组件工厂
	bool registerFactory();

	/// 注销组件工厂
	bool unregisterFactory();

	/// 创建组件对象
	virtual IObjectUnknown* create() { return NULL; }
	/// 创建组件对象
	virtual IObjectUnknown* create(int nodeId) { return NULL; }

	/// 获取接口ID号
	virtual const char* iid() const = 0;

	/// 获取实现类ID号
	virtual const char* clsid() const = 0;

	/// 获取单例,param 为参数
	virtual IObjectUnknown* instance(int nodeId)
	{
		return NULL;
	}
};

/// \brief 创建组件对象
/// \param [in] iid 接口ID号
/// \param [in] clsid 实现接口类ID号
/// \retval 指向组件对象的指针
extern "C" COMPONENT_API IObjectUnknown * createComponentObject(const char* iid, const char* clsid, int nodeId);
extern "C" COMPONENT_API IObjectUnknown * getComponentInstance(const char* iid, const char* clsid, int nodeId);

template<typename T>
std::shared_ptr<T> createComponentObject(const char* clsid, int nodeId)
{
	return std::shared_ptr<T>((T*)createComponentObject(T::IFactory::siid(), clsid, nodeId));
}

template<class T>
T* getComponentInstance(const char* clsid, int nodeId) {
	return (T*)getComponentInstance(T::IFactory::siid(), clsid, nodeId);
}
ICOMPONENT_NAMESPACE_END
