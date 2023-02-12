#ifndef SPRITE_H
#define SPRITE_H
#include "object.h"
#include <vector>
#include "point.h"
class Sprite : public Object
{
private:
    std::vector<Point> pointVec;
    std::vector<Point> polar;
    void FormatSprite();
    void UpdatePointVec();
public:
    float rot;
    void Rotate(float degrees);
    Sprite(std::vector<Point> points);
    void Draw(int x,int y);
};
Point ToPolar(float x,float y);
Point ToKartesian(float len,float deg,float rot);
#endif
