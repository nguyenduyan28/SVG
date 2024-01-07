#include "stdafx.h"

CircleSVG::CircleSVG()
{
    point.x = point.y = 0;
    radius = 0.0;
}

void CircleSVG::drawShape(Graphics& graphics)
{

    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    Rect rect(point.x - radius, point.y - radius, radius * 2, radius * 2);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillEllipse(&brush, rect);
    graphics.DrawEllipse(&pen, rect);
    graphics.EndContainer(container);
}

void CircleSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
        if (attributeName == "cx")
        {
            this->point.x = stoi(attributeValue);
        }
        else if (attributeName == "cy")
        {
            this->point.y = stoi(attributeValue);
        }
        else if (attributeName == "r")
        {
            this->radius = stoi(attributeValue);
        }
        else
            (*this).setShape(attributeName, attributeValue, fo, f, s, sw, so);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}