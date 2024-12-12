#pragma once

class Boundaries {
public:
	Boundaries(int xMin, int xMax, int yMin, int yMax);
	Boundaries();

	int GetXMin() const;
	int GetXMax() const;
	int GetYMin() const;
	int GetYMax() const;

	int GetWidth() const;
	int GetHeight() const;

	bool IsInside(int x, int y) const;

	int ClampX(int x) const;
	int ClampY(int y) const;

private:
	int mXMin;
	int mXMax;
	int mYMin;
	int mYMax;
};
