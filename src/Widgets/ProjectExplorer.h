#pragma once

#include <ProjectTree.h>
#include "AssetDisplay.h"
#include <array>

class ProjectExplorer
{
private:
	ProjectTree* tree;
	AssetDisplay* ad;

	// Node Creator
	bool nodeCreatorOpen = false;
	bool dataNodeCreatorOpen = false;
	PathNode* creatorSelectedNode;


	std::array<char, 32> newNodeName;
	std::array<char, 32> newNodePrefix;
	DataType newNodeType;

public:
	void ShowWindow();
	void Init(ProjectTree* tree, AssetDisplay* ad);
private:
	void ShowMenuBar();
	void ShowTree();
	void TraverseBranch(PathNode* start);
	void ShowDataNodes(DataNode* data, int i);

	void AddableType(std::string name, std::string prefix);

	void NodeCreator();
	void ProcessNewNode();
	void PrepareNewNode();

	void DataNodeCreator();
	void ProcessNewDataNode();
	void PrepareNewDataNode();
};