#include "GLGraphics.h"
#include "AssetManager.h"
#include "MathHelper.h"

namespace SDL_Framework {
	GLGraphics* GLGraphics::Instance() {
		if (sInstance == nullptr) {
			Graphics::Instance();
		}

		return static_cast<GLGraphics*>(sInstance);
	}

	GLGraphics::GLGraphics() {
		sInitialized = Init();
	}

	GLGraphics::~GLGraphics() {
		//SDL_GL_DeleteContext(mWindow);
	}

	void GLGraphics::ClearBackBuffer() {
		glClearDepth(1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLGraphics::Render() {
		//glBegin(GL_TRIANGLES);
		////If we want color, color NEEDS to be applied first
		//glColor3f(1.0f, 0.0f, 0.0f);

		//glVertex2f(0.0f, 0.0f);
		//glVertex2f(0.0f, 500.0);
		//glVertex2f(500.0f, 500.0f);

		//glEnd();

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		SDL_GL_SwapWindow(mWindow);
	}

	bool GLGraphics::Init() {
		mGLContext = SDL_GL_CreateContext(mWindow);
		if (mGLContext == nullptr) {
			std::cerr << "SDL_GL_Context could not be created!" << SDL_GetError() << std::endl;
			return false;
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cerr << "Could not initialize glew!" << glewGetErrorString(error) << std::endl;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		InitLoadShaderData();

		return true;
	}

	void GLGraphics::InitLoadShaderData() {
		std::string basepath = SDL_GetBasePath();
		basepath.append("Assets/");

		std::string vShaderPath = basepath.append("Shaders/vs.shader");
		std::string fShaderPath = basepath.append("Shaders/fs.shader");

		AssetManager::Instance()->LoadShader(vShaderPath.c_str(), fShaderPath.c_str(),
			nullptr, "Sprite-Default");
		mShaderUtil = AssetManager::Instance()->GetShaderUtil("Sprite-Default");
		orthoMatrix = glm::ortho(0.0f, (float)SCREEN_WIDTH,
			(float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);

		mShaderUtil.Use();
		mShaderUtil.SetVector2f("vertexPosition", glm::vec2(0, 0));
		mShaderUtil.SetMatrix4f("proj", orthoMatrix);
	}

	void GLGraphics::DrawSprite(GLTexture* glTex, SDL_Rect* srcRect,
		SDL_Rect* dstRect, float angle, SDL_RendererFlip flip) {
		float x = -1;
		float y = -1;
		float w = 1;
		float h = 1;

		if (glTex->ID == 0) {
			glGenBuffers(1, &glTex->ID);
		}

		float vertexData[12];

		//First triangle
		vertexData[0] = x + w;
		vertexData[1] = y + h;

		vertexData[2] = x;
		vertexData[3] = y + h;

		vertexData[4] = x;
		vertexData[5] = y;

		//Second Triangle
		vertexData[6] = x;
		vertexData[7] = y;

		vertexData[8] = x + w;
		vertexData[9] = y;

		vertexData[10] = x + w;
		vertexData[11] = y + h;

		glBindBuffer(GL_ARRAY_BUFFER, glTex->ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData),
			vertexData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);

		//This is us unbinding everything aka a reset to our buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLGraphics::InitRenderData(Texture* texture, SDL_Rect* srcRect,
		float angle, float x, float y, float w, float h, GLuint quadVAO, SDL_RendererFlip flip) {
		GLTexture* glTex = dynamic_cast<GLTexture*>(texture);

		if (!glTex) {
			std::cerr << "TEXTURE ERROR" << std::endl;
			return;
		}

		float height = glTex->mSurface->h;
		float width = glTex->mSurface->w;

		if (quadVAO == 0) {
			glGenBuffers(1, &quadVAO);
		}

		glm::vec2 topRight = glm::vec2(1, 1);
		glm::vec2 topLeft = glm::vec2(0, 1);
		glm::vec2 bottomLeft = glm::vec2(0, 0);
		glm::vec2 bottomRight = glm::vec2(1, 0);

		if (srcRect) {
			topRight = glm::vec2((srcRect->x + srcRect->w) / width,
				(srcRect->y + srcRect->h) / height);
			topLeft = glm::vec2(srcRect->x / width,
				(srcRect->y + srcRect->h) / height);
			bottomLeft = glm::vec2(srcRect->x / width, srcRect->y / height);
			bottomRight = glm::vec2((srcRect->x + srcRect->w) / width,
				srcRect->y / height);
		}

		if (flip == SDL_FLIP_HORIZONTAL) {
			std::swap(topRight.x, topLeft.x);
			std::swap(bottomRight.x, bottomLeft.x);
		}

		if (flip == SDL_FLIP_VERTICAL) {
			std::swap(topRight.y, bottomRight.y);
			std::swap(topLeft.y, bottomLeft.y);
		}

		Vertex vertexData[6];
		vertexData[0].SetPosition(x + w, y + h);
		vertexData[0].SetUV(topRight.x, topRight.y);

		vertexData[1].SetPosition(x, y + h);
		vertexData[1].SetUV(topLeft.x, topLeft.y);

		vertexData[2].SetPosition(x, y);
		vertexData[2].SetUV(bottomLeft.x, bottomLeft.y);

		vertexData[3].SetPosition(x, y);
		vertexData[3].SetUV(bottomLeft.x, bottomLeft.y);

		vertexData[4].SetPosition(x + w, y);
		vertexData[4].SetUV(bottomRight.x, bottomRight.y);

		vertexData[5].SetPosition(x + w, y + h);
		vertexData[5].SetUV(topRight.x, topRight.y);

		for (int i = 0; i < 6; i++) {
			vertexData[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		glBindBuffer(GL_ARRAY_BUFFER, quadVAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}