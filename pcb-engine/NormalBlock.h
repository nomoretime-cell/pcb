#pragma once

#include "Defs.h"
#include "IBlock.h"

ENGINE_NAMESPACE_BEGIN

class NormalEngineBlock : public IBlock
{
public:

	class NormalEngineBlockFactory : public IBlock::IFactory
	{
	public:
		NormalEngineBlockFactory() {
			registerFactory();
		}

		~NormalEngineBlockFactory() {
			unregisterFactory();
		}

		IObjectUnknown* create(int nodeId) override {
			return NormalEngineBlock();
		}

		const char* clsid() const override {
			return "NormalEngineBlock";
		}
	};


};

ENGINE_NAMESPACE_END