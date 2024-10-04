#include "ProjectExplorer.h"

#include <ImGuiInclude.h>
#include <iostream>

void ProjectExplorer::ShowWindow()
{
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_MenuBar;

    // For some odd reason, the three spaces need to be here
    if (!ImGui::Begin("Asset Explorer", nullptr, window_flags))
    {
        ImGui::End();
        return;
    }

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(ImVec2(main_viewport->WorkSize.x / 3, main_viewport->WorkSize.y), ImGuiCond_FirstUseEver);

    ShowMenuBar();
    ShowTree();
    ImGui::End();
}

void ProjectExplorer::Init(ProjectTree* tree)
{
    this->tree = tree;
}

void ProjectExplorer::ShowMenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Add Types"))
        {
            AddableType("Static Meshes", "SM");
            AddableType("Skeletal Meshes", "SK");
            AddableType("Animations", "ANIM");
            AddableType("Textures", "T");
            AddableType("Sounds", "S");
            AddableType("Music", "MUS");
            AddableType("Images", "IMG");
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    
}

void ProjectExplorer::ShowTree()
{
    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    ImGuiTreeNodeFlags node_flags = base_flags;
    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    TraverseBranch(const_cast<PathNode*>(tree->GetRoot()));
}

void ProjectExplorer::TraverseBranch(PathNode* start) 
{
    

    if (ImGui::TreeNode(start->name.c_str()))
    {
        if (start->childNodes.size() == 0)
        {
            ImGui::TreePop();
            return;
        }
        for (size_t i = 0; i < start->childNodes.size(); i++)
        {
            TraverseBranch(start->childNodes[i]);
        }
        ImGui::TreePop();
    }
    
}

void ProjectExplorer::AddableType(std::string name, std::string prefix)
{
    if (ImGui::MenuItem(name.c_str()))
    {
        tree->MakeNode(const_cast<PathNode*>(tree->GetRoot()), name, prefix);
    }
}


