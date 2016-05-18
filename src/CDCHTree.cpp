#include "CDCHTree.h"
#include <fstream>

TIME CDCHTree::Process()
{
	return m_rootNode->Process();
}

void CDCHTree::LoadFromFile(std::string fileName)
{
	std::ifstream fInput(fileName);
	while(!fInput.eof())
	{
		std::string line = "";
		std::getline(fInput, line);
		if(line.find("<node") == std::string::npos)
			continue;
		if(line.find("id=") == std::string::npos)
			throw "id attribute not founded";
		if(line.find("parentId=") == std::string::npos)
			throw "parentId attribute not founded";
		if(line.find("devType=") == std::string::npos)
			throw "devType attribute not founded";
		
		line = line.substr(line.find("id=")+4);
		std::size_t id = std::stoi(line.substr(0, line.find("\"")));
		
		line = line.substr(line.find("parentId=")+10);
		std::size_t parentId = std::stoi(line.substr(0, line.find("\"")));
		
		line = line.substr(line.find("devType=")+9);
		std::string devType =line.substr(0, line.find("\""));
		
		std::shared_ptr<CNode> pNode = nullptr;
		
		if(devType == "S")
		{
			line = line.substr(line.find("speed=")+7);
			std::size_t speed = std::stoi(line.substr(0, line.find("\"")));
			pNode = std::make_shared<CSwitch>(id, speed);
		}
		if(devType == "W")
		{
			line = line.substr(line.find("perfomance=")+12);
			float perfomance = std::stof(line.substr(0, line.find("\"")));
			pNode = std::make_shared<CWorker>(id, perfomance);
		}
		if(devType == "C")
		{
			line = line.substr(line.find("perfomance=")+12);
			float perfomance = std::stof(line.substr(0, line.find("\"")));
			pNode = std::make_shared<CCoordinator>(id, perfomance);
		}
		if(devType == "L")
		{
			line = line.substr(line.find("weight=")+8);
			std::size_t weight = std::stoi(line.substr(0, line.find("\"")));
			pNode = std::make_shared<CLine>(id, weight);
		}
		AddNode(pNode, parentId);
	}
	return;
}

CNode& CDCHTree::FindNode(size_t id)
{
	if(m_rootNode == nullptr)
		throw "Tree is empty. Node not founded";
	if(
}
void CDCHTree::AddNode(CNode::CNodePtr pNode, size_t parentId)
{
	FindNode(parentId).AddChild(pNode);
}