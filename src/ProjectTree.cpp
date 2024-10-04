#include "ProjectTree.h"

ProjectTree::ProjectTree()
{
	root = MakeNode(nullptr, "Root", "");
}

ProjectTree::~ProjectTree()
{
}

const PathNode* ProjectTree::GetRoot() const
{
	return root;
}

PathNode* ProjectTree::MakeNode(PathNode* parent, std::string name, std::string prefix) const
{
	PathNode* node = new PathNode;
	node->name = name;
	node->partent = parent;
	node->assetPrefix = prefix;
	if (parent) // because root needs to be created here aswell
		parent->childNodes.push_back(node);

	return node;
}

DataNode* ProjectTree::MakeDataNode(PathNode* parent, std::string name) const
{
	return nullptr;
}
