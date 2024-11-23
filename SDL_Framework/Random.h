#pragma once
#include <random>
#include <chrono>

class Random {
public:
	static Random* Instance();
	static void Release();

	unsigned RandomInt();
	float RandomFloat(); 
	int RandomRange(int lo, int hi);
	float RandomRange(float lo, float hi);

private:
	static Random* sInstance;
	std::mt19937 mGenerator;

	Random();
	~Random();
};
