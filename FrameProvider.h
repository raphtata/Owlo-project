#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <vector>

using Frame = std::vector<std::vector<double>>;

class FrameProvider {
public:
    Frame readCurrentFrame();
};

#endif // FRAMEPROVIDER_H
