#include "FrameProvider.h"
#include <cmath>
#include <ctime>

Frame FrameProvider::readCurrentFrame() {
    int width = 200, height = 100;
    int index = static_cast<int>(std::time(nullptr) * 10) % 100;
    Frame out(height, std::vector<double>(width, 0.0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double term1 = std::exp(-(x*x + (y-50)*(y-50)) / 400.0);
            double term2 = std::exp(-((x-199)*(x-199) + (y-50)*(y-50)) / 400.0);
            double term3 = std::exp(-((x-2*index)*(x-2*index)
                        + (y-50 + std::sin(index/10.0)*40) *
                          (y-50 + std::sin(index/10.0)*40)) / 1000.0);
            out[y][x] = term1 + term2 + term3;
        }
    }
    return out;
}
