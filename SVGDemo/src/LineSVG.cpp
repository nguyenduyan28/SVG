#include "stdafx.h"

LineSVG::LineSVG()
{
    from.x = from.y = to.x = to.y = 0;
}

void LineSVG::drawShape(Graphics& graphics)
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
    if (hasColor)
        graphics.DrawLine(&pen, from.x, from.y, to.x, to.y);
    graphics.EndContainer(container);
}

void LineSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
        if (attributeName == "x1")
        {
            this->from.x = stoi(attributeValue);
        }
        else if (attributeName == "y1")
        {
            this->from.y = stoi(attributeValue);
        }
        else if (attributeName == "x2")
        {
            this->to.x = stoi(attributeValue);
        }
        else if (attributeName == "y2")
        {
            this->to.y = stoi(attributeValue);
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
