#pragma once

#include <ProjectTree.h>
#include <GLFW/glfw3.h>


class AssetDisplay
{
public:
	DataNode* selectedNode;

	GLuint placeholder;

public:
	void ShowWindow();
	void Init();
private:
	void ShowMenuBar();

	void ShowSkeletalMesh();
	void ShowStaticMesh();
	void ShowAnimation();
	void ShowTexture();
	void ShowSound();
	void ShowMusic();
	void ShowImage();
	void ShowVectorImage();
	void ShowSprite();
	void ShowMap();
	void ShowScript();

	void GeneratePlaceholderTexture();
};