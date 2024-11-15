#pragma once

#include <SDL.h>
#include "MathHelper.h"
//#define _CRT_SECURE_DEPRECATE_MEMORY
//#include <memory.h>

namespace SDL_Framework {
	class InputManager {
	public:
		enum MouseButton { Left = 0, Right, Middle, Back, Forward };

		static InputManager* Instance();
		static void Release();
		
		bool KeyDown(SDL_Scancode scanCode);
		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);

		bool MouseButtonDown(MouseButton button);
		bool MouseButtonPressed(MouseButton button);
		bool MouseButtonReleased(MouseButton button);

		Vector2 MousePosition();

		void Update();
		void UpdatePrevInput();
	
	private:
		static InputManager* sInstance;

		const Uint8* mKeyboardState;
		Uint8* mPrevKeyboardState;
		int mKeyLength;

		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;

		InputManager();
		~InputManager();


	};


}
