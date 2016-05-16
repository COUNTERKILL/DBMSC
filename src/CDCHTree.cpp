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
		
		std::shared_ptr<CNode> pNode;
		
		if(devType == "S")
			pNode = std::make_shared<CSwitch>();
		if(devType == "W")
			pNode = std::make_shared<CWorker>();
		if(devType == "C")
			pNode = std::make_shared<CCoordinator>();
		if(devType == "L")
			pNode = std::make_shared<CLine>();
		
	}
}

CNode& CDCHTree::FindNode(size_t id)
{
	
}
void CDCHTree::AddNode(CNode *node, size_t parentId)
{
	auto pNode = std::make_shared<CNode>(node);
	FindNode(parentId).AddChild(pNode);
}