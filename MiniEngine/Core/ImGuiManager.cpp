#include "pch.h"
#include "ImGuiManager.h"

#include "imgui-docking/imgui.h"
#include "imgui-docking/imgui_impl_dx12.h"
#include "imgui-docking/imgui_impl_win32.h"
namespace ImGuiA {
    //ImGuiManager* ImGuiManager::sm_instance = nullptr;

    ImGuiManager* ImGuiManager::Instance()
    {
        static ImGuiManager Man;
        return &Man;
    }
    ImGuiManager::ImGuiManager()
    {
        
    }
 ImGuiManager::~ImGuiManager()
    {
     ImGui_ImplDX12_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    bool ImGuiManager::Initialise(HWND hwnd, ID3D12Device* device, ID3D12DescriptorHeap* HeapPtr)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);

        ImGui_ImplDX12_Init(device, 3,
            DXGI_FORMAT_R8G8B8A8_UNORM, HeapPtr,
            HeapPtr->GetCPUDescriptorHandleForHeapStart(),
            HeapPtr->GetGPUDescriptorHandleForHeapStart());

        return true;
    }

    void ImGuiManager::Render(CommandContext& BaseContext, ID3D12DescriptorHeap* HeapPtr)
    {
        // Start the Dear ImGui frame
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        for (auto layer : RenderLayers)
        {
            layer->Render();
        }

        ImGui::Render();

      
        
       
        BaseContext.SetDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,HeapPtr);
        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), BaseContext.GetCommandList());
      
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault(NULL, (void*)BaseContext.GetCommandList());
            }
       
    }

    void ImGuiManager::AddRenderLayer(ImguiLayer* layer)
    {
        RenderLayers.push_back(layer);
    }

    void ImGuiManager::RemoveRenderLayer(ImguiLayer* layer)
    {
        RenderLayers.erase(std::find(RenderLayers.begin(), RenderLayers.end(), layer), RenderLayers.end());
    }

}