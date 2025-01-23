#pragma once
#include "Graphics.h"
#include "glew.h"
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include "ShaderUtil.h"
#include "GLTexture.h"


namespace SDL_Framework {

	class GLGraphics : public Graphics {
	public:
		static GLGraphics* Instance();

		GLGraphics();
		~GLGraphics();

		virtual void ClearBackBuffer() override;
		virtual void Render() override;

		virtual void DrawSprite(GLTexture* glTex, SDL_Rect* srcRect = nullptr,
			SDL_Rect* dstRect = nullptr, float angle = 0.0f,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

		void InitRenderData(Texture* texture, SDL_Rect* srcRect, float angle,
			float x, float y, float w, float h, GLuint quadVAO, SDL_RendererFlip flip);
		void InitLoadShaderData();

	protected:
		virtual bool Init() override;

		SDL_GLContext mGLContext;
		glm::mat4 orthoMatrix;
		ShaderUtil mShaderUtil;
	};
}