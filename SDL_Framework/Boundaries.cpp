#include "Boundaries.h"

Boundaries::Boundaries(int xmin, int xmax, int ymin, int ymax)
    : mXMin(xmin), mXMax(xmax), mYMin(ymin), mYMax(ymax) {
}

Boundaries::Boundaries() : mXMin(0), mXMax(0), mYMin(0), mYMax(0) {

}

int Boundaries::GetXMin() const {
    return mXMin;
}

int Boundaries::GetXMax() const {
    return mXMax;
}

int Boundaries::GetYMin() const {
    return mYMin;
}

int Boundaries::GetYMax() const {
    return mYMax;
}

int Boundaries::GetWidth() const {
    return mXMax - mXMin;
}

int Boundaries::GetHeight() const {
    return mYMax - mYMin;
}

bool Boundaries::IsInside(int x, int y) const {
    return x >= mXMin && x <= mXMax && y >= mYMin && y <= mYMax;
}

int Boundaries::ClampX(int x) const {
    if (x < mXMin) {
        return mXMin;
    }
    else if (x > mXMax) {
        return mXMax;
    }
    return x;
}

int Boundaries::ClampY(int y) const {
    if (y < mYMin) {
        return mYMin;
    }
    else if (y > mYMax) {
        return mYMax;
    }
    return y;
}

