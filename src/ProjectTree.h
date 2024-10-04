#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

enum class DataType
{
	None,
	Static_Mesh,
	Skeletal_Mesh,
	Animation,
	Texture,
	Sound,
	Music,
	Image,
	Vector_Image,
	Sprite,
	Map,
	Script,

	DataType_SIZE,
};

extern const char* DataTypeNames[];

struct DataNode
{
	std::string name;
	DataType type;
};

struct PathNode
{
	std::string name;
	std::string assetPrefix; 
	std::vector<PathNode*> childNodes;
	std::vector<DataNode*> data;
	PathNode* parent;


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
	void SaveTree(std::filesystem::path path);

	PathNode* MakeNode(PathNode* parent, std::string name, std::string prefix) const;
	DataNode* MakeDataNode(PathNode* parent, std::string name, DataType type) const;

	DataNode* PathToNode(std::string path);
};

