#include "IComponent.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

ICOMPONENT_NAMESPACE_BEGIN

IObjectUnknown::IObjectUnknown()
{

}

IObjectUnknown::~IObjectUnknown()
{

}

IFactoryUnknown::IFactoryUnknown()
{

}

IFactoryUnknown::~IFactoryUnknown()
{

}

map < string, map<string, IFactoryUnknown*>> g_mapFactory;

bool IFactoryUnknown::registerFactory()
{
	string strIID = iid();
	string strCLSID = clsid();
	auto itIID = g_mapFactory.find(strIID);
	if (itIID == g_mapFactory.end())
	{
		map<string, IFactoryUnknown*> fm;
		fm[strCLSID] = this;
		g_mapFactory[strIID] = fm;
	}
	else
	{
		auto& fm = itIID->second;
		auto itCLSID = fm.find(strCLSID);
		if (itCLSID == fm.end())
		{
			fm[strCLSID] = this;
		}
		else
		{
			itCLSID->second = this;
		}
	}

	return true;
}

bool IFactoryUnknown::unregisterFactory()
{
	string strIID = iid();
	string strCLSID = clsid();
	auto itIID = g_mapFactory.find(strIID);
	if (itIID != g_mapFactory.end())
	{
		auto& fm = itIID->second;
		auto itCLSID = fm.find(strCLSID);
		if (itCLSID != fm.end())
		{
			fm.erase(itCLSID);
		}

		if (fm.size() <= 0)
		{
			g_mapFactory.erase(itIID);
		}
	}

	return true;
}

IObjectUnknown* createComponentObject(const char* iid, const char* clsid, int nodeId)
{
	string strIID = iid;
	string strCLSID = clsid;
	auto itIID = g_mapFactory.find(strIID);
	if (itIID != g_mapFactory.end())
	{
		auto& fm = itIID->second;
		auto itCLSID = fm.find(strCLSID);
		if (itCLSID != fm.end())
		{
			return itCLSID->second->create(nodeId);
		}
	}

	return 0;
}

IObjectUnknown* getComponentInstance(const char* iid, const char* clsid, int nodeId)
{
	string strIID = iid;
	string strCLSID = clsid;
	auto itIID = g_mapFactory.find(strIID);
	if (itIID != g_mapFactory.end())
	{
		auto& fm = itIID->second;
		auto itCLSID = fm.find(strCLSID);
		if (itCLSID != fm.end())
		{
			return itCLSID->second->instance(nodeId);
		}
	}

	return 0;
}

ICOMPONENT_NAMESPACE_END