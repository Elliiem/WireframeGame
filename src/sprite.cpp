#include <vector>
#include "point.h"
#include "sprite.h"
#include "globals.h"
#include <cmath>
#include <fmt/format.h>

Sprite::Sprite(std::vector<Point> points)
{
    pointVec = points;
    polar = {};
    rot = 0;
    FormatSprite();
}

void Sprite::FormatSprite()
{
    for(int i = 0;i< pointVec.size();i++)
    {
        polar.push_back(ToPolar(pointVec.at(i).x,pointVec.at(i).y));
    }
}

void Sprite::UpdatePointVec()
{
    for(int i=0;i<pointVec.size();i++)
    {
        pointVec.at(i) = ToKartesian(polar.at(i).x,polar.at(i).y,rot);
    }
}

void Sprite::Rotate(float degrees)
{
    rot += degrees;
    if(rot>=360)
    {
        rot -= 360;
    }
    else if(rot<0)
    {
        rot += 360;
    }
    UpdatePointVec();
}

Point ToKartesian(float len,float deg,float rot)
{
    deg += rot;
    if(deg>=360)
    {
        deg -= 360;
    }
    else if(rot<0)
    {
        deg += 360;
    }

    int x,y;

    if(deg <= 180)
    {
        if(deg<=90)
        {
            x = round(cos((deg)*0.017453292519943295)*len);
            y = -round(sin((deg)*0.017453292519943295)*len);
        }
        else
        {
            x = -round(sin((deg-90)*0.017453292519943295)*len);
            y = -round(cos((deg-90)*0.017453292519943295)*len);
        }
    }
    else
    {
        if(deg<=270)
        {
            x = -round(cos((deg-180)*0.017453292519943295)*len);
            y = round(sin((deg-180)*0.017453292519943295)*len);
        }
        else
        {
            x = round(sin((deg-270)*0.017453292519943295)*len);
            y = round(cos((deg-270)*0.017453292519943295)*len);
        }
    }
    return Point(x,y);
}

Point ToPolar(float x,float y)
{
    int add=0;

    if(x==0 & y==0)
    {
        return Point(0,0);
    }
    else if (x == 0)
    {
        if(y<0)
        {
            return Point(fabs(y),270);
        }
        else if (y > 0)
        {
            return Point(fabs(y),90);
        }
    }
    else if(y == 0)
    {
        if(x<0)
        {
            return Point(fabs(x),180);
        }
        else if (x>0)
        {
            return Point(fabs(x),0);
        }
    }

    if(x < 0 & y > 0)
    {
        x = fabs(x);
        y = fabs(y);
        return Point(sqrt(powf(x,2)+powf(y,2)),fabs(180-(atan((y/x))*57.29577951308232)));
    }
    else if (x < 0 & y < 0)
    {
        x = fabs(x);
        y = fabs(y);
        return Point(sqrt(powf(x,2)+powf(y,2)),(atan((y/x))*57.29577951308232)+180);
    }
    else if (x > 0 & y < 0)
    {
        x = fabs(x);
        y = fabs(y);
        return Point(sqrt(powf(x,2)+powf(y,2)),(atan((y/x))*57.29577951308232)+270);
    }
    return Point(0,0);
}

void Sprite::Draw(int x, int y)
{
    Win.DrawPolygon(pointVec,&green,x,y);
    Win.SetPixel(x,y,&white);
}
