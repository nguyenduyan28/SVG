#include "stdafx.h"

EllipseSVG::EllipseSVG()
{
    c.x = c.y = 0;
    radiusX = radiusY = 0.0;
}

void EllipseSVG::drawShape(Graphics& graphics)
{

    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    Rect rect(c.x - radiusX, c.y - radiusY, radiusX * 2, radiusY * 2);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    graphics.FillEllipse(&brush, rect);
    graphics.DrawEllipse(&pen, rect);
    graphics.EndContainer(container);
}


void EllipseSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
        if (attributeName == "cx")
        {
            this->c.x = stoi(attributeValue);
        }
        else if (attributeName == "cy")
        {
            this->c.y = stoi(attributeValue);
        }
        else if (attributeName == "rx")
        {
            this->radiusX = stoi(attributeValue);
        }
        else if (attributeName == "ry")
        {
            this->radiusY = stoi(attributeValue);
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