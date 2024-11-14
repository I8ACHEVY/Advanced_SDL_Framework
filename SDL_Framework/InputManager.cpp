#define _CRT_SECURE_DEPRECATE_MEMORY	//memcpy
#define _CRT_SECURE_NO_WARNINGS
#include <memory.h>					//memcpy

//#include <string>

#include "InputManager.h"


namespace SDL_Framework {
	InputManager* InputManager::sInstance = nullptr;

	InputManager* InputManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new InputManager();
		}
		return sInstance;
	}

	void InputManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	bool InputManager::KeyDown(SDL_Scancode scanCode) {
		return mKeyboardState[scanCode];
	}

	bool InputManager::KeyPressed(SDL_Scancode scanCode) {
		return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
	}

	bool InputManager::KeyReleased(SDL_Scancode scanCode) {
		return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];
	}

	bool InputManager::MouseButtonDown(MouseButton button) {
		Uint32 mask = 0;

		switch (button) {
		case Left:
			mask = SDL_BUTTON_LMASK;
			break;

		case Right:
			mask = SDL_BUTTON_RMASK;
			break;

		case Middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case Back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case Forward:
			mask = SDL_BUTTON_X2MASK;
			break;

		}
		return (mMouseState & mask) != 0;

	}

	bool InputManager::MouseButtonPressed(MouseButton button) {
		Uint32 mask = 0;

		switch (button) {
		case Left:
			mask = SDL_BUTTON_LMASK;
			break;

		case Right:
			mask = SDL_BUTTON_RMASK;
			break;

		case Middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case Back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case Forward:
			mask = SDL_BUTTON_X2MASK;
			break;

		}
		return !(mPrevMouseState & mask) && (mMouseState & mask);

	}

	bool InputManager::MouseButtonReleased(MouseButton button) {
		Uint32 mask = 0;

		switch (button) {
		case Left:
			mask = SDL_BUTTON_LMASK;
			break;

		case Right:
			mask = SDL_BUTTON_RMASK;
			break;

		case Middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case Back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case Forward:
			mask = SDL_BUTTON_X2MASK;
			break;

		}
		return (mPrevMouseState & mask) && !(mMouseState & mask);

	}

	Vector2 InputManager::MousePosition() {
		return Vector2((float)mMouseXPos, (float)mMouseYPos);
	}

	void InputManager::Update() {
		mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
		//mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	}

	void InputManager::UpdatePrevInput() {
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
		mPrevMouseState = mMouseState;
	}

	InputManager::InputManager() {
		mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
		mPrevKeyboardState = new Uint8[mKeyLength];
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	}

	InputManager::~InputManager() {
		delete[] mPrevKeyboardState;
		mPrevKeyboardState = nullptr;
	}

}