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

void ProjectTree::LoadRandomTree()
{
	PathNode* sk = MakeNode(root, "Skeletal Meshes", "SK");
	PathNode* sm = MakeNode(root, "Static Meshes", "SM");
	PathNode* t = MakeNode(root, "Textures", "T");
	PathNode* s = MakeNode(root, "Sounds", "S");
	PathNode* m = MakeNode(root, "Music", "M");

	{
		PathNode* sophia = MakeNode(sk, "Sophia", "Sophia");
		MakeDataNode(sophia, "Healthy", DataType::Skeletal_Mesh);
		MakeDataNode(sophia, "Dead", DataType::Skeletal_Mesh);
		MakeDataNode(sophia, "Exploded", DataType::Skeletal_Mesh);
		MakeDataNode(sophia, "Chapter_2", DataType::Skeletal_Mesh);
		MakeDataNode(sophia, "Ending", DataType::Skeletal_Mesh);
	}

	{
		PathNode* spencer = MakeNode(sk, "Spencer", "Spencer");
		MakeDataNode(spencer, "Healthy", DataType::Skeletal_Mesh);
		MakeDataNode(spencer, "Dead", DataType::Skeletal_Mesh);
		MakeDataNode(spencer, "Exploded", DataType::Skeletal_Mesh);
		MakeDataNode(spencer, "Chapter_2", DataType::Skeletal_Mesh);
		MakeDataNode(spencer, "Ending", DataType::Skeletal_Mesh);
	}

	{
		PathNode* guns = MakeNode(sm, "Guns", "Guns");
		PathNode* pistol = MakeNode(guns, "Pistol", "Pistol");
		PathNode* ranged = MakeNode(guns, "Ranged", "Ranged");
		PathNode* heavy = MakeNode(guns, "Heavy", "Heavy");

		MakeDataNode(pistol, "Glock", DataType::Static_Mesh);
		MakeDataNode(pistol, "Revolver", DataType::Static_Mesh);
		MakeDataNode(ranged, "M16", DataType::Static_Mesh);
		MakeDataNode(ranged, "Ak47", DataType::Static_Mesh);
		MakeDataNode(ranged, "MP", DataType::Static_Mesh);
		MakeDataNode(heavy, "Rocket Launcher", DataType::Static_Mesh);
	}

	{
		PathNode* guns = MakeNode(s, "Guns", "Guns");
		PathNode* pistol = MakeNode(guns, "Pistol", "Pistol");
		PathNode* ranged = MakeNode(guns, "Ranged", "Ranged");
		PathNode* heavy = MakeNode(guns, "Heavy", "Heavy");

		MakeDataNode(pistol, "Glock", DataType::Sound);
		MakeDataNode(pistol, "Revolver", DataType::Sound);
		MakeDataNode(ranged, "M16", DataType::Sound);
		MakeDataNode(ranged, "Ak47", DataType::Sound);
		MakeDataNode(ranged, "MP", DataType::Sound);
		MakeDataNode(heavy, "Rocket Launcher", DataType::Sound);
	}

	{
		PathNode* character = MakeNode(s, "Character", "Character");
		PathNode* spencer = MakeNode(character, "Spencer", "Spencer");
		PathNode* sophia = MakeNode(character, "Sophia", "Sophia");

		MakeDataNode(spencer, "Walk", DataType::Sound);
		MakeDataNode(spencer, "Hit", DataType::Sound);
		MakeDataNode(spencer, "Jump", DataType::Sound);
		MakeDataNode(sophia, "Walk", DataType::Sound);
		MakeDataNode(sophia, "Hit", DataType::Sound);
		MakeDataNode(sophia, "Jump", DataType::Sound);
	}

	{
		PathNode* desert = MakeNode(m, "Desert", "Desert");
		PathNode* forest = MakeNode(m, "Forest", "Forest");
		PathNode* city = MakeNode(m, "City", "City");
		PathNode* menu = MakeNode(m, "Menu", "Menu");

		MakeDataNode(desert, "sand", DataType::Music);
		MakeDataNode(desert, "Dunes", DataType::Music);
		MakeDataNode(desert, "Heat", DataType::Music);
		MakeDataNode(forest, "Lost", DataType::Music);
		MakeDataNode(forest, "Greenery", DataType::Music);
		MakeDataNode(forest, "Wild", DataType::Music);
		MakeDataNode(city, "Alive", DataType::Music);
		MakeDataNode(city, "Modern", DataType::Music);
		MakeDataNode(city, "Civilization", DataType::Music);
		MakeDataNode(menu, "Theme", DataType::Music);
		MakeDataNode(menu, "Game Complete", DataType::Music);
		MakeDataNode(menu, "Game Over", DataType::Music);
	}

	{
		PathNode* character = MakeNode(t, "Character", "Character");
		PathNode* spencer = MakeNode(character, "Spencer", "Spencer");
		PathNode* sophia = MakeNode(character, "Sophia", "Sophia");
		PathNode* objects = MakeNode(t, "Objects", "Objects");

		MakeDataNode(spencer, "Default", DataType::Texture);
		MakeDataNode(spencer, "Destroyed", DataType::Texture);
		MakeDataNode(sophia, "Default", DataType::Texture);
		MakeDataNode(sophia, "Destroyed", DataType::Texture);

		MakeDataNode(objects, "Coffee", DataType::Texture);
		MakeDataNode(objects, "Table", DataType::Texture);
		MakeDataNode(objects, "Apple", DataType::Texture);
		MakeDataNode(objects, "Banana", DataType::Texture);
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
	node->parent = parent;
	parent->data.push_back(node);

	return node;
}
