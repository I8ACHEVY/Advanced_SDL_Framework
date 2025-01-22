#pragma once
#include "Graphics.h"
#include "glew.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "ShaderUtil.h"
#include "GLTexture.h"


namespace SDL_Framework {

	class GLGraphics : public Graphics {
	public:
		static GLGraphics* Instance();

		GLGraphics();
		~GLGraphics();

		void ClearBackBuffer() override;
		void Render() override;

		void DrawTexture(GLTexture* glTex, SDL_Rect* srcRect = nullptr,
			SDL_Rect* dstRect = nullptr, float angle = 0.0f,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

		void InitRenderData(Texture* texture, SDL_Rect* srcRect, float angle,
			float x, float y, float w, float h, GLuint quadVAO);

	protected:
		bool Init() override;

		SDL_GLContext glContext;
		glm::mat4 orthoMatrix;
		ShaderUtil mShaderUtil;

		void InitLoadShaderData();
	};
}