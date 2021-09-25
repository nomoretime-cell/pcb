#pragma once

#include <vector>
#include "Defs.h"
#include "IVisionTool.h"

VISIONTOOL_NAMESPACE_BEGIN

class VisionToolMock : IVisionTool
{
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
			return new VisionToolMock();
		}

		const char* clsid() const override {
			return "VisionToolMock";
		}
	};


public:
	VisionToolMock() {};
	~VisionToolMock() {};

	virtual void destroy() override {delete this;};

	virtual bool getToolID(std::string& id) const override { return true; };

	virtual bool getOutputParam(std::string& param) const override { return true; };

	virtual bool getInputParam(std::string& param) const override { return true; };

	virtual bool setInputParam(const std::string& inputList) override { return true; };

	virtual bool init(const std::string& inputList) override { return true; };

	virtual bool uninit() override { return true; };

	virtual bool process(const std::string& inParam, std::string& outParam) override { return true; };

	virtual bool setConfig(const std::string& cfgList) override { return true; };

	virtual bool getConfig(const std::string& cfgList) const override { return true; };

	virtual bool command(const std::string& cmd, const std::string& inParam, const std::string& outParam)override { return true; };

private:

};

VISIONTOOL_NAMESPACE_END