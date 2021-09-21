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
	char	name[32];	///< �������
	int		major;		///< ���汾�ţ��ܹ��䶯ʱ����
	int		minor;		///< �ΰ汾�ţ��ӿڱ仯������ȱ������ʱ����
	int		revision;	///< �޶��汾�ţ�ȱ������ʱ����
	int		svn;		///< svn�汾�ţ���¼����3�汾�ű��ʱ��Ӧ��svn�汾��
	char date[32];	///< �������ڣ�ʹ��__DATE__��

	/// ���캯�����汾����һ����Ϊȫ�ֶ�����
	CVersion(const char* name, int major, int minor, int revision, const char* svnString, const char* dateString);

	/// �汾��Ϣ��ӡ
	void print() const;
};

class COMPONENT_API IObjectUnknown
{
public:
	/// ���캯��
	IObjectUnknown();

	/// ����������
	virtual ~IObjectUnknown();

	/// �����������
	virtual void destroy() = 0;

	/// ��ȡ����汾����
	virtual CVersion getVersion() const = 0;
};

class COMPONENT_API IFactoryUnknown
{
public:
	/// ���캯��
	IFactoryUnknown();
	/// ����������
	virtual ~IFactoryUnknown();

	/// ע���������
	bool registerFactory();

	/// ע���������
	bool unregisterFactory();

	/// �����������
	virtual IObjectUnknown* create() { return NULL; }
	/// �����������
	virtual IObjectUnknown* create(int nodeId) { return NULL; }

	/// ��ȡ�ӿ�ID��
	virtual const char* iid() const = 0;

	/// ��ȡʵ����ID��
	virtual const char* clsid() const = 0;

	/// ��ȡ����,param Ϊ����
	virtual IObjectUnknown* instance(int nodeId)
	{
		return NULL;
	}
};

/// \brief �����������
/// \param [in] iid �ӿ�ID��
/// \param [in] clsid ʵ�ֽӿ���ID��
/// \retval ָ����������ָ��
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
