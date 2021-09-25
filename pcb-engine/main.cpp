// pcb.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// todo list

// ui和manager之间接口
// manager和block之间接口
// block和平台算子之间接口

#include <iostream>
#include "json.hpp"
#include "IBlock.h"

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
    std::string str = "{\"fromNodeID\": \"1\", \"fromParam\" : \"2\",\"toNodeID\" : \"3\", \"toParam\" : \"4\"}";
    Engine::LinkItem link = Engine::LinkItem::getLinkItem(str);
    std::cout << "Hello World!\n";
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
