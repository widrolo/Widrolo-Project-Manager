#include "ProjectTree.h"

namespace fs = std::filesystem;

const char* DataTypeNames[] = {
	"None",
	"Static Mesh",
	"Skeletal Mesh",
	"Animation",
	"Texture",
	"Sound",
	"Music",
	"Image",
	"Vector Image",
	"Sprite",
	"Map",
	"Script"
};

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

void ProjectTree::SaveTree(std::filesystem::path path)
{
	if (!fs::exists(path.parent_path())) {
		fs::create_directories(path.parent_path());
	}


}

PathNode* ProjectTree::MakeNode(PathNode* parent, std::string name, std::string prefix) const
{
	PathNode* node = new PathNode;
	node->name = name;
	node->parent = parent;
	node->assetPrefix = prefix;
	if (parent) // because root needs to be created here aswell
		parent->childNodes.push_back(node);

	return node;
}

DataNode* ProjectTree::MakeDataNode(PathNode* parent, std::string name, DataType type) const
{
	DataNode* node = new DataNode;
	node->name = name;
	node->type = type;
	parent->data.push_back(node);

	return node;
}
