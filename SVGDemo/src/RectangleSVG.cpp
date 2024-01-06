#include "stdafx.h"

RectangleSVG::RectangleSVG()
{
    point.x = point.y = 0;
    width = 0;
    height = 0;
}

void RectangleSVG::drawShape(Graphics& graphics)
{


    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();

    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(strokealpha, stroke.r, stroke.b, stroke.g), strokeWidth);
    Rect rect(point.x, point.y, width, height);
    if (hasStroke)
        graphics.DrawRectangle(&pen, rect);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    if (hasColor)
        graphics.FillRectangle(&brush, rect);
    graphics.EndContainer(container);
}


void RectangleSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
        if (attributeName == "x")
        {
            this->point.x = stoi(attributeValue);
        }
        else if (attributeName == "y")
        {
            this->point.y = stoi(attributeValue);
        }
        else if (attributeName == "width")
        {
            this->width = stoi(attributeValue);
        }
        else if (attributeName == "height")
        {
            this->height = stoi(attributeValue);
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