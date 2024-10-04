#include "AssetDisplay.h"
#include <ImGuiInclude.h>

void AssetDisplay::ShowWindow()
{
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_MenuBar;
    window_flags |= ImGuiWindowFlags_HorizontalScrollbar;

    // For some odd reason, the three spaces need to be here
    if (!ImGui::Begin("Asset Display", nullptr, window_flags))
    {
        ImGui::End();
        return;
    }

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetWindowPos(ImVec2(main_viewport->WorkSize.x / 4, 19), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(ImVec2(main_viewport->WorkSize.x * 3/4, main_viewport->WorkSize.y - 19), ImGuiCond_FirstUseEver);

    if (!selectedNode)
    {
        ImGui::End();
        return;
    }

    ShowMenuBar();

    switch (selectedNode->type)
    {
    case DataType::Skeletal_Mesh: ShowSkeletalMesh(); break;
    case DataType::Static_Mesh: ShowStaticMesh(); break;
    case DataType::Animation: ShowAnimation(); break;
    case DataType::Texture: ShowTexture(); break;
    case DataType::Sound: ShowSound(); break;
    case DataType::Music: ShowMusic(); break;
    case DataType::Image: ShowImage(); break;
    case DataType::Vector_Image: ShowVectorImage(); break;
    case DataType::Sprite: ShowSprite(); break;
    case DataType::Map: ShowMap(); break;
    case DataType::Script: ShowScript(); break;
    default:
        break;
    }

    ImGui::End();

}

void AssetDisplay::Init()
{
    GeneratePlaceholderTexture();
}

void AssetDisplay::ShowMenuBar()
{
    
}

void AssetDisplay::ShowSkeletalMesh()
{
    ImGui::Text("Full Name Of Asset");
    ImGui::Text("Type: Skeletal Mesh");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Path To Project File: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##1"))
    {
        ImGui::SetClipboardText("Path");
    }
    ImGui::Button("Open In Blender");
    ImGui::Spacing();
    ImGui::Text("Path To Asset File: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##2"))
    {
        ImGui::SetClipboardText("Path");
    }
    ImGui::Button("Open In 3D Viewer");
}

void AssetDisplay::ShowStaticMesh()
{
    ImGui::Text("Full Name Of Asset");
    ImGui::Text("Type: Static Mesh");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Path To Project File: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##1"))
    {
        ImGui::SetClipboardText("Path");
    }
    ImGui::Button("Open In Blender");
    ImGui::Spacing();
    ImGui::Text("Path To Asset File: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##2"))
    {
        ImGui::SetClipboardText("Path");
    }
    ImGui::Button("Open In 3D Viewer");
}

void AssetDisplay::ShowAnimation()
{
    ImGui::Text("Full Name Of Asset");
    ImGui::Text("Type: Animation");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Path To Project File: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##1"))
    {
        ImGui::SetClipboardText("Path");
    }
    ImGui::Button("Open In Maya");
    ImGui::Spacing();
    ImGui::Text("Path To Asset File: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##2"))
    {
        ImGui::SetClipboardText("Path");
    }
}

void AssetDisplay::ShowTexture()
{
    ImGui::Text("Full Name Of Asset");
    ImGui::Text("Type: Texture");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImVec2 imageSize = ImVec2(128, 128);

    ImGui::Text("Path To Textures: ");
    ImGui::Text("Path");
    ImGui::SameLine();
    if (ImGui::Button("Copy to Clipboard##1"))
    {
        ImGui::SetClipboardText("Path");
    }

    ImGui::Text("Albedo");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Normal");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Roughness"); 
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Metallic");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Ambient Occlusion");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Height");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Specular");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

    ImGui::Text("Emission");
    ImGui::Image((void*)(intptr_t)placeholder, imageSize);

}

void AssetDisplay::ShowSound()
{
}

void AssetDisplay::ShowMusic()
{
}

void AssetDisplay::ShowImage()
{
}

void AssetDisplay::ShowVectorImage()
{
}

void AssetDisplay::ShowSprite()
{
}

void AssetDisplay::ShowMap()
{
}

void AssetDisplay::ShowScript()
{
}

void AssetDisplay::GeneratePlaceholderTexture()
{
    const int width = 64;
    const int height = 64;
    unsigned char pixels[width * height * 4];

    // Fill the texture with a checkerboard pattern (alternating black and pink)
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int offset = (y * width + x) * 4;
            if ((x / 8 + y / 8) % 2 == 0)
            {
                pixels[offset] = 0xff;     // R
                pixels[offset + 1] = 0x00; // G
                pixels[offset + 2] = 0xfe; // B
            }
            else
            {
                pixels[offset] = 0;       // R
                pixels[offset + 1] = 0;   // G
                pixels[offset + 2] = 0;   // B
            }
            pixels[offset + 3] = 255;     // A (Alpha)
        }
    }

    // Create OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    placeholder = textureID;
}
