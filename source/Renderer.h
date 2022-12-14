#pragma once

#include <cstdint>
#include <vector>

#include "Camera.h"
#include "DataTypes.h"

struct SDL_Window;
struct SDL_Surface;

namespace dae
{
	class Texture;
	struct Mesh;
	struct Vertex;
	class Timer;
	class Scene;

	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update(Timer* pTimer);
		void Render();

		bool SaveBufferToImage() const;

		void ToggleCameraLock()
		{ 
			m_IsCamLocked = !m_IsCamLocked;

			if(m_IsCamLocked) SDL_SetRelativeMouseMode(SDL_TRUE);
			else SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		void ToggleColorState() { m_IsColoringTexture = !m_IsColoringTexture; }
		
	private:
		SDL_Window* m_pWindow{};

		SDL_Surface* m_pFrontBuffer{ nullptr };
		SDL_Surface* m_pBackBuffer{ nullptr };
		uint32_t* m_pBackBufferPixels{};

		float* m_pDepthBufferPixels{};

		int m_NrOfPixels;

		Camera m_Camera{};

		Texture* m_pTexture{};

		int m_Width{};
		int m_Height{};

		float m_AspectRatio{};

		bool m_IsCamLocked{ true };

		bool m_IsColoringTexture{ true };

		const float m_RotateSpeed{ 25.f };

		//Function that transforms the vertices from the mesh from World space to Screen space
		void VertexTransformationFunction(Mesh& mesh); //W1 Version

		Vector2 CalcUVComponent(const float weight, const float depth, const size_t index, const Mesh& mesh) const;

		void RenderTriangle(const size_t idx, const Mesh& mesh, const bool swapVertices);

		void ClearBackGround() const
		{
			SDL_FillRect(m_pBackBuffer, NULL, SDL_MapRGB(m_pBackBuffer->format, 100, 100, 100));
		}

		void constexpr ClearDepthBuffer()
		{
			std::fill_n(m_pDepthBufferPixels, m_NrOfPixels, FLT_MAX);
		}

		bool IsOutOfFrustrum(const Vertex_Out& vOUT) const;

		//std::vector<Vertex> m_Vertices_NDC{};
		std::vector<Vector2> m_Vertices_ScreenSpace{};

		//define mesh
		/*const std::vector<Mesh> meshesWorld
		{
			Mesh{
				{
					Vertex{{ -3.f, 3.f, -2.f },{0,0}},
					Vertex{{ 0.f, 3.f, -2.f },{0.5f,0}},
					Vertex{{ 3.f, 3.f, -2.f },{1,0}},
					Vertex{{ -3.f, 0.f, -2.f },{0,0.5f}},
					Vertex{{ 0.f, 0.f, -2.f },{0.5f,0.5f}},
					Vertex{{ 3.f, 0.f, -2.f },{1,0.5f}},
					Vertex{{ -3.f, -3.f, -2.f },{0,1}},
					Vertex{{ 0.f, -3.f, -2.f },{0.5f,1}},
					Vertex{{ 3.f, -3.f, -2.f },{1,1}},
				},
				{
					3,0,1,        1,4,3,        4,1,2,
					2,5,4,        6,3,4,        4,7,6,
					7,4,5,        5,8,7
				},
				PrimitiveTopology::TriangleList
			}
		};*/

		//define mesh
		std::vector<Mesh> m_Meshes_World
		{
			Mesh
			{
				{},
				{},
				PrimitiveTopology::TriangleList
			}
			/*,
			Mesh
			{
				{},
				{},
				PrimitiveTopology::TriangleList
			}*/
		};

	};
}
