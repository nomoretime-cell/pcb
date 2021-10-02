#pragma once

#include <vector>
#include <string>
#include "Defs.h"
#include "IVisionTool.h"

VISIONTOOL_NAMESPACE_BEGIN

class VisionToolMock : IVisionTool
{
public: 
	class VisionToolMockFactory : public IVisionTool::IFactory
	{
	public:
		VisionToolMockFactory() {
			registerFactory();
		}

		~VisionToolMockFactory() {
			unregisterFactory();
		}

		VisionToolMock* create(int nodeId) override {
			return new VisionToolMock(std::to_string(nodeId));
		}

		const char* clsid() const override {
			return "VisionToolMock";
		}
	};


public:
	VisionToolMock(std::string nodeID) {
		m_nodeID = nodeID;
	};
	~VisionToolMock() {};

	virtual void destroy() override {delete this;};

	virtual bool getToolID(std::string& id) const override { return true; };

	virtual bool getOutputParam(std::string& param) const override { return true; };

	virtual bool getInputParam(std::string& param) const override { return true; };

	virtual bool setInputParam(const std::string& inputList) override { return true; };

	virtual bool init(const std::shared_ptr<MvpImage>& img, const std::string& inputList) override { return true; };

	virtual bool uninit() override { return true; };

	virtual bool process(std::shared_ptr<MvpImage> img, const std::string& inParam, std::string& outParam) override { 
		outParam = m_nodeID;
		return true; 
	}

	virtual bool setConfig(const std::string& cfgList) override { return true; };

	virtual bool getConfig(std::string& cfgList) const {
		return true;
	};

	virtual bool command(const std::string& cmd, const std::shared_ptr<MvpImage>& img, const std::string& inParam, std::string& outParam) {
		return true;
	};

private:
	std::string m_nodeID;
};

VISIONTOOL_NAMESPACE_END