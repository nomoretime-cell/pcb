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

	/// \brief ��ʼ��block������node
	/// \param[in] blockID blockID
	/// \param[in] img ͼ��
	/// \param[in] nodeIDMapInitConfigJson	node��Ӧ��ʼ������
	/// \retval û��blockID��Ӧ���󷵻�false
	bool initBlock(_In_ std::string blockID, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::map<std::string, std::string>& nodeIDMapInitConfigJson);

	/// \brief ��ʼ���ض�node
	/// \param[in] img ͼ��ָ��
	/// \param[in] nodeID nodeID
	/// \param[in] initConfigJson ��ʼ������
	/// \retval ������block��nodeid��Ӧnode����
	bool initNode(_In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& nodeID, _In_ const std::string& initConfigJson);

	/// \brief ���������������
	/// \param[in] nodeID nodeID
	/// \param[in] inputJson �������
	/// \retval ������block��nodeid��Ӧnode����
	bool setInput(_In_ const std::string& nodeID, _In_ const std::string& inputJson);

	/// \brief �����������ò���
	/// \param[in] nodeID nodeid
	/// \param[in] configJson �������
	/// \retval ������block��nodeid��Ӧnode����
	bool setConfig(_In_ const std::string& nodeID, _In_ const std::string& configJson);

	/// \brief ��ȡ�������ò���
	/// \param[in] nodeID nodeid
	/// \retval ������block��nodeid��Ӧnode����
	std::string getConfig(_In_ const std::string& nodeID);

	/// \brief ����
	/// \param[in] img ͼ��ָ��
	/// \param[in] runFromBlockID ��ʼblock id
	/// \param[in] runToBlockID ����block id
	/// \retval true �ɹ� false ʧ��
	bool run(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID = "", _In_ std::string runToBlockID = "");

	/// \brief ����һ��
	/// \param[in] img ͼ��ָ��
	/// \param[in] runFromBlockID ��ʼblock id
	/// \param[in] runToBlockID ����block id
	/// \retval true �ɹ� false ʧ��
	bool runOnce(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID = "", _In_ std::string runToBlockID = "");

	/// \brief ֹͣ����
	/// \retval true �ɹ� false ʧ��
	bool stop();

	/// \brief CMD
	/// \param[in] nodeID nodeID
	/// \param[in] cmd cmdָ��
	/// \param[in] img ͼ��
	/// \param[in] inJson �������
	/// \param[in] outJson �������
	/// \retval true �ɹ� false ʧ��
	bool command(_In_ const std::string& nodeID, _In_ const std::string& cmd, _In_ const std::shared_ptr<MvpImage>& img, _In_ const std::string& inJson, _Out_ std::string& outJson);

	/// \brief ��ȡblockid��Ӧ����node���
	/// \param[in] blockId blockId
	/// \retval ����û��blockid��Ӧ��block
	std::map<std::string, std::string> getBlockResult(_In_ const std::string& blockId);

	/// \brief ��ȡnodeid��Ӧ����node���
	/// \param[in] nodeID nodeID
	/// \retval ������block��nodeid��Ӧnode����
	std::string getNodeResult(_In_ const std::string& nodeID);

	/// \brief �������
	/// \param[in] blockID blockID
	/// \param[in] nodeType nodeType
	/// \retval nodeid
	std::string addNode(_In_ const std::string& blockID, _In_ const std::string& nodeType);

	/// \brief ɾ������
	/// \param[in] blockID blockID
	/// \param[in] nodeID nodeID
	/// \retval �Ҳ���nodeID��Ӧ������ʵ��
	bool removeNode(_In_ const std::string& blockID, _In_ const std::string& nodeID);
	
	/// \brief ��ȡblockid������node
	/// \param[in] blockID blockID
	/// \retval nodeid��Ӧ��node����
	std::map<std::string, std::shared_ptr<VisionTool::IVisionTool >> getAllNode(_In_ const std::string& blockID);

	/// \brief ��ȡblockid������node
	/// \param[in] blockID blockID
	/// \retval nodeid��Ӧ��node����
	std::vector<BlockInfo> getAllBlock();

	/// \brief ��ȡblockid��Ӧ��blocktype
	/// \param[in] blockID blockID
	/// \retval block type
	std::string getBlockType(const std::string blockID);

	/// \brief ��ȡnodeID��Ӧ��node type
	/// \param[in] nodeID nodeID
	/// \retval node type
	std::string getNodeType(const std::string nodeID);

	/// \brief ��������
	/// \param[in] ���߶�������л�����
	/// \retval ���������Ƿ�ɹ�
	bool addLink(_In_ const std::string& link);

	/// \brief ɾ������
	/// \param[in] ɾ�����߶�������л�����
	/// \retval ɾ�������Ƿ�ɹ�
	bool deleteLink(_In_ const std::string& link);

private:

	void innerRun(_In_ const std::shared_ptr<MvpImage>& img, _In_ std::string runFromBlockID, _In_ std::string runToBlockID);

private:
	std::vector<BlockInfo> m_vecBlockInfos;
	std::atomic<bool> m_running;
	std::thread m_runThread;
};

ENGINE_NAMESPACE_END
