#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Defs.h"
#include "IComponent.h"

VISIONTOOL_NAMESPACE_BEGIN

class IVisionTool : public IComponent::IObjectUnknown
{
public:
	class IFactory : public IComponent::IFactoryUnknown
	{
	public:

		virtual ~IFactory() {}

		virtual const char* iid() { return "IVisionTool"; }

		static const char* siid() { return "IVisionTool"; }
	};

	IVisionTool() {};
	virtual ~IVisionTool() {}

	/// ��ȡ����ID
	/// \param[out] id   ����ID
	/// \retval     true �ɹ�   false ʧ��
	virtual bool getToolID(std::string& id) const = 0;

	/// \brief ��ȡ�����������
	/// \param[out] param ����������
	/// \retval     true �ɹ�   false ʧ��
	virtual bool getOutputParam(std::string& param) const = 0;

	/// \brief ��ȡ�����������
	/// \param[out] param ����������
	/// \retval     true �ɹ�   false ʧ��
	virtual bool getInputParam(std::string& param) const = 0;

	/// \brief �������������Ĭ��ֵ
	/// \param[in] inputList ����
	/// \retval    true  �ɹ�   false ʧ��
	virtual bool setInputParam(const std::string& inputList) = 0;

	/// \brief ��ʼ������
	/// \param[in]  param  ��ʼ������
	/// \retval     true �ɹ�   false ʧ��
	virtual bool init(const std::string& inputList) = 0;

	/// \brief ����ʼ������
	/// \retval     true �ɹ�   false ʧ��
	virtual bool uninit() = 0;

	/// \brief ����ӿ�
	/// \param[in]  inParam  �������
	/// \param[out] outParam �������
	/// \retval     true �ɹ�   false ʧ��
	virtual bool process(const std::string& inParam, std::string& outParam) = 0;

	/// \brief ��������
	/// \param[in] cfgList ����
	/// \retval    true  �ɹ�   false ʧ��
	virtual bool setConfig(const std::string& cfgList) = 0;

	/// \brief ���û�ȡ
	/// \param[in]  cfgName ��������
	/// \param[out] cfgList ����
	/// \retval     true  �ɹ�   false ʧ��
	virtual bool getConfig(const std::string& cfgList) const = 0;

	/// \brief ��������
	/// \param[in] cmd  "AddInputParam"  ����������
	///                 "DelInputParam"  ɾ���������
	///                 "AddOutputParam" ����������
	///                 "DelOutputParam" ɾ���������
	///                 "AddConfig"      ������ò���
	///                 "DelConfig"      ɾ�����ò���
	/// \param[in]  inParam  �������
	/// \param[out] outParam �������
	/// \retval    true  �ɹ�   false ʧ��
	virtual bool command(const std::string& cmd, const std::string& inParam, const std::string& outParam) = 0;

};

VISIONTOOL_NAMESPACE_END
