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
	std::string		fromNodeID; ///< ���ߵ���ʼ��
	std::string		fromParam;  ///< ���ߵ���ʼ����� ��ʽ�� "point.x"
	std::string		toNodeID;   ///< ���ߵ��յ�
	std::string		toParam;    ///< ���ߵ��յ����   ��ʽ�� "count"
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
	virtual bool setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson) = 0;
	
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
	virtual bool command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson) = 0;

	/// \brief	��ȡblock���н��
	/// \retval		nodeid��Ӧ���
	virtual std::map<std::string, std::string> getAllResult() = 0;

	/// \brief	��ȡָ��nodeid���
	/// \retval		nodeid���
	virtual std::string getResult(_In_ std::string nodeID) = 0;

	/// \brief	��ȡblock id
	/// \retval	block id
	virtual std::string getBlockID() = 0;

	/// \brief	��ȡblock id
	/// \retval	block id
	virtual std::string getBlockType() = 0;
	
	/// \brief	��������
	/// \param[in]	nodeType	��������
	/// \retval		����id
	virtual std::string addNode(_In_ const std::string& nodeType) = 0;

	/// \brief	ɾ������
	/// \param[in]	nodeID	����id
	/// \retval		�Ƿ�ɾ���ɹ�
	virtual bool removeNode(_In_ const std::string& nodeID) = 0;

	/// \brief	�Ƿ����nodeid
	/// \param[in]	nodeID	����id
	/// \retval		�Ƿ�ɾ���ɹ�
	virtual bool hasNode(_In_ const std::string& nodeID) = 0;

	/// \brief	��ȡ��������id
	/// \retval ��block�µ���������id
	virtual std::map<std::string, std::shared_ptr<VisionTool::IVisionTool>> getAllNode() = 0;

	/// \brief	 �������ߣ�fromNodeID������һ��block��
	/// \param[in]	link ������Ϣ
	/// \retval		�Ƿ����߳ɹ�
	virtual bool addLink(_In_ const LinkItem& link) = 0;

	/// \brief	 �������ߣ�fromNodeID������һ��block��
	/// \param[in]	link ������Ϣ
	/// \retval		�Ƿ�������߳ɹ�
	virtual bool deleteLink(_In_ const LinkItem& link) = 0;

};

ENGINE_NAMESPACE_END
