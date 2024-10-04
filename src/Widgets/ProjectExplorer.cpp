#include "ProjectExplorer.h"

#include <ImGuiInclude.h>
#include <iostream>
#include <algorithm>

void ProjectExplorer::ShowWindow()
{
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_MenuBar;

    // For some odd reason, the three spaces need to be here
    if (!ImGui::Begin("Asset Tree", nullptr, window_flags))
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

    if (nodeCreatorOpen)
        NodeCreator();

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
    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    ImGuiTreeNodeFlags node_flags = base_flags;
    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (ImGui::TreeNode(start->name.c_str()))
    {
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::Button("New Node"))
            {
                nodeCreatorOpen = true;
                creatorSelectedNode = start;
                PrepareNewNode();
            }
            ImGui::EndPopup();
        }

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
    for each (auto node in tree->GetRoot()->childNodes)
    {
        if (node->name == name)
            return;
    }

    if (ImGui::MenuItem(name.c_str()))
    {
        tree->MakeNode(const_cast<PathNode*>(tree->GetRoot()), name, prefix);
    }
}

void ProjectExplorer::NodeCreator()
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    // For some odd reason, the three spaces need to be here
    if (!ImGui::Begin("Node Creator", &nodeCreatorOpen, window_flags))
    {
        ImGui::End();
        return;
    }

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    ImVec2 size = ImVec2(main_viewport->WorkSize.x / 5, main_viewport->WorkSize.y / 4);
    ImVec2 pos = ImVec2(
        main_viewport->WorkSize.x / 2 - size.x / 2,
        main_viewport->WorkSize.y / 2 - size.y / 2);

    ImGui::SetWindowPos(pos, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(size, ImGuiCond_FirstUseEver);

    ImGui::Text("Create New Node");
    ImGui::Spacing();
    ImGui::Text("Name:");
    ImGui::InputText(" ##1", newNodeName.data(), newNodeName.size());
    ImGui::Text("Prefix (empty = default):");
    ImGui::InputText(" ##2", newNodePrefix.data(), newNodePrefix.size());

    if (ImGui::Button("Create"))
    {
        nodeCreatorOpen = false;
        ProcessNewNode();
    }

    ImGui::End();
}

void ProjectExplorer::ProcessNewNode()
{
    std::string name(newNodeName.begin(), newNodeName.end());
    std::string prefix(newNodePrefix.begin(), newNodePrefix.end());

    if (newNodePrefix[0] == 0)
        prefix = name;
        
    tree->MakeNode(creatorSelectedNode, name, prefix);
}

void ProjectExplorer::PrepareNewNode()
{
    std::fill(newNodeName.begin(), newNodeName.end(), 0);
    std::fill(newNodePrefix.begin(), newNodePrefix.end(), 0);
}


