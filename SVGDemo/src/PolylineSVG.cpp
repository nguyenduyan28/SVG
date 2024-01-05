#include "stdafx.h"

PolylineSVG::PolylineSVG()
{
    points.clear();
}

void PolylineSVG::drawShape(Graphics& graphics)
{

    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    vector<PointF> newP;
    for (int i = 0; i < points.size(); i++)
    {
        newP.push_back(PointF{ points[i].x, points[i].y });
    }
    PointF* p = newP.data();
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillPolygon(&brush, p, newP.size());
    if (strokeWidth)
        graphics.DrawLines(&pen, p, newP.size());
    graphics.EndContainer(container);
}

void PolylineSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
        if (attributeName == "points")
        {
            this->points = parsePoints(attributeValue);
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