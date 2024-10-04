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

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkSize.x / 3, main_viewport->WorkSize.y), ImGuiCond_FirstUseEver);

    // For some odd reason, the three spaces need to be here
    if (!ImGui::Begin("Asset Explorer   ", nullptr, window_flags))
    {
        ImGui::End();
        return;
    }

    ShowMenuBar();
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

    ImGui::BulletText("Hello World!");
    ImGui::End();
}

void ProjectExplorer::ShowMenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Add Types"))
        {
            ImGui::MenuItem("Static Mesh");
            ImGui::MenuItem("Skeletal Mesh");
            ImGui::MenuItem("Animations");
            ImGui::MenuItem("Texture");
            ImGui::MenuItem("Sounds");
            ImGui::MenuItem("Music");
            ImGui::MenuItem("Images");
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
