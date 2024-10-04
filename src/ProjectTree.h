#pragma once

#include <string>
#include <vector>

struct DataNode
{
	std::string name;

};

struct PathNode
{
	std::string name;
	std::string assetPrefix; 
	std::vector<PathNode*> childNodes;
	std::vector<DataNode*> data;
	PathNode* partent;


};

class ProjectTree
{
public:
	ProjectTree();
	~ProjectTree();

private:
	PathNode* root;

public:
	const PathNode* GetRoot() const;

	PathNode* MakeNode(PathNode* parent, std::string name, std::string prefix) const;
	DataNode* MakeDataNode(PathNode* parent, std::string name) const;

	DataNode* PathToNode(std::string path);
};

