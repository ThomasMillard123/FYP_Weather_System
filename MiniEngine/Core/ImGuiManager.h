#pragma once	
#include <wrl/client.h>
	#include <vector>
#include"ImguiLayer.h"
#include "CommandContext.h"
namespace ImGuiA {

	class ImGuiManager
	{
	public:
		static ImGuiManager* Instance();
		bool Initialise(HWND hwnd, ID3D12Device* device, ID3D12DescriptorHeap* HeapPtr);
		void Render(CommandContext& BaseContext, ID3D12DescriptorHeap* HeapPtr);
		void AddRenderLayer(ImguiLayer* layer);
		void RemoveRenderLayer(ImguiLayer* layer);

		~ImGuiManager();

	private:
		ImGuiManager();
		
	public:

	private:
		static ImGuiManager* sm_instance;
		std::vector<ImguiLayer*>RenderLayers;
	};

}