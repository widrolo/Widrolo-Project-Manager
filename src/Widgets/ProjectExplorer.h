#pragma once

#include <ProjectTree.h>

class ProjectExplorer
{
private:
	ProjectTree* tree;

public:
	void ShowWindow();
	void Init(ProjectTree* tree);
private:
	void ShowMenuBar();
	void ShowTree();
	void TraverseBranch(PathNode* start);

	void AddableType(std::string name, std::string prefix);
};