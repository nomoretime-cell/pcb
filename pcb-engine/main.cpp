// pcb.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// todo list

// ui和manager之间接口
// manager和block之间接口
// block和平台算子之间接口

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include "json.hpp"
#include "IBlock.h"
#include "Defs.h"
#include "Manager.h"

Engine::LinkItem getLinkItem(std::string inparam) {
    nlohmann::json jObj = nlohmann::json::parse(inparam);
    Engine::LinkItem linkItem{
    jObj["fromNodeID"].get<std::string>(),
    jObj["fromParam"].get<std::string>(),
    jObj["toNodeID"].get<std::string>(),
    jObj["toParam"].get<std::string>()
    };
    return linkItem;
}

int main()
{
    std::string NormalBlock1 = Engine::Manager::instance()->addBlock("NormalBlock");
    std::string VisionToolMock1 = Engine::Manager::instance()->addNode(NormalBlock1, "VisionToolMock2");

    std::string NormalBlock2 = Engine::Manager::instance()->addBlock("NormalBlock");
    std::string VisionToolMock2 = Engine::Manager::instance()->addNode(NormalBlock2, "VisionToolMock");
    std::string VisionToolMock3 = Engine::Manager::instance()->addNode(NormalBlock2, "VisionToolMock");
    
    std::string NormalBlock3 = Engine::Manager::instance()->addBlock("NormalBlock");
    std::string VisionToolMock4 = Engine::Manager::instance()->addNode(NormalBlock3, "VisionToolMock");

    std::string NormalBlock4 = Engine::Manager::instance()->addBlock("NormalBlock");
    std::string VisionToolMoc5 = Engine::Manager::instance()->addNode(NormalBlock4, "VisionToolMock");

    std::string str = "{\"fromNodeID\": \"VisionToolMock3\", \"fromParam\" : \"2\",\"toNodeID\" : \"VisionToolMock4\", \"toParam\" : \"4\"}";
    Engine::LinkItem link = Engine::LinkItem::getLinkItem(str);
    Engine::Manager::instance()->addLink(str);

    std::shared_ptr<MvpImage> image = std::make_shared<MvpImage>();
    Engine::Manager::instance()->runOnce(image);
    Engine::Manager::instance()->runOnce(image, NormalBlock3, NormalBlock4);
    Engine::Manager::instance()->run(image, NormalBlock2);
    //Engine::Manager::instance()->run(nullptr);


    std::cout << "Hello World!\n";

    while (true) {

    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
