#include "TestImgui.h"
#include"imgui-docking/imgui.h"
#include"imgui-docking/imgui_stdlib.h"
static bool a;
void TestImgui::Render()
{
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &a);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &a);

   

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
