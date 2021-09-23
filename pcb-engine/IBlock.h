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

	/// \brief	��ʼ���������ӣ�û��initConfigJson�����ӣ���ʼ��ʱ����գ�
	/// \param[in]	img						ͼ��ָ��
	/// \param[in]	nodeIDMapInitConfigJson	node��Ӧ��ʼ������
	/// \retval		true  �ɹ�   false ʧ��
	virtual bool initAllNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson) = 0;
	
	/// \brief	��ʼ���ض�����
	/// \param[in]	img				ͼ��ָ��
	/// \param[in]	nodeID			nodeid
	/// \param[in]	initConfigJson	��ʼ������
	/// \retval		true  �ɹ�   false ʧ��
	virtual bool initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson) = 0;

	/// \brief	���������������
	/// \param[in]	nodeID			nodeid
	/// \param[in]	inputJson		�������
	/// \retval		true  �ɹ�   false ʧ��
	virtual int setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) = 0;
	
	/// \brief	�����������ò���
	/// \param[in]	nodeID			nodeid
	/// \param[in]	configJson		�������
	/// \retval		true  �ɹ�   false ʧ��
	virtual bool setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson) = 0;

	/// \brief	��ȡ�������ò���
	/// \param[in]	nodeID			nodeid
	/// \retval		�������ò���
	virtual std::string getConfig(_In_ const std::string& nodeID) = 0;

	/// \brief	������
	/// \param[in]	img					ͼ��ָ��
	/// \param[in]	nodeMapInJson		�������
	/// \param[in]	nodeMapOutJson		������
	/// \retval		true  �ɹ�   false ʧ��
	virtual bool process(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::map<std::string, std::string>& nodeMapInJson, _Out_ std::map<std::string, std::string>& nodeMapOutJson) = 0;

	/// \brief	CMD����
	/// \param[in]	img			ͼ��ָ��
	/// \param[in]	nodeID		nodeID
	/// \param[in]	inJson		�������
	/// \param[in]	outJson		������
	/// \retval		true  �ɹ�   false ʧ��
	virtual bool command(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& inJson, _Out_ std::string& outJson) = 0;

	/// \brief	��ȡblock���
	/// \retval		nodeid��Ӧ���
	virtual std::map<std::string, std::string> getResult() = 0;

	/// \brief	��ȡblock id
	/// \retval	block id
	virtual std::string getBlockID() = 0;

	// ��������
	virtual std::string addNode(_In_ const std::string& nodeType) = 0;

	// ɾ������
	virtual bool removeNode(_In_ const std::string& nodeID) = 0;

	// ��ȡ��������id
	virtual std::list<std::string> getAllNode() = 0;

	// �������ߣ�fromNodeID������һ��block��
	virtual bool addLink(_In_ const std::string& fromNodeID, _In_ const std::string& toNodeID) = 0;

	// �������ߣ�fromNodeID������һ��block��
	virtual bool updateLinks(_In_ const std::string& oldfromNodeID, _In_ const std::string& newfromNodeID, _In_ const std::string& toNodeID) = 0;

private:
	// ���ӽ��
	// ��������
	// ����uuid����
};

ENGINE_NAMESPACE_END
