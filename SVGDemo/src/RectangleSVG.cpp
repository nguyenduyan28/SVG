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

    /*for (string s : transformCommand) {
        if (s == "translate")
            graphics.TranslateTransform(translate.x, translate.y);
        if (s == "scale")
            graphics.ScaleTransform(scale.x, scale.y);
        if (s == "rotate")
            graphics.RotateTransform(rotate);
    }*/
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    
    Rect rect(point.x, point.y, width, height);
    if (!hasGradient.empty()) {
        this->gradient = Gradients["a"];
        cout << Gradients[hasGradient].id;
        cout << Gradients[hasGradient].type;
        cout << gradient.type;
        if (gradient.type == "linearGradient") {
            Color colors[100];
            REAL pos[100];
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            LinearGradientBrush brush(Point(gradient.startPoint.x, gradient.startPoint.y), Point(gradient.endPoint.x, gradient.endPoint.y),
                Color(gradient.stops[0].opacity * 255 * fillOpacity, gradient.stops[0].color.r, gradient.stops[0].color.g, gradient.stops[0].color.b),
                Color(gradient.stops[gradient.stops.size() - 1].opacity * 255 * fillOpacity, gradient.stops[gradient.stops.size() - 1].color.r, gradient.stops[gradient.stops.size() - 1].color.g, gradient.stops[gradient.stops.size() - 1].color.b)
            );
            brush.SetInterpolationColors(colors, pos, gradient.stops.size());
            graphics.FillRectangle(&brush, rect);
        }
        if (gradient.type == "radialGradient") {
            Color colors[100];
            REAL pos[100];
            GraphicsPath myPath;
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            PathGradientBrush brush(&myPath);
            int size = gradient.stops.size();
            brush.SetSurroundColors(colors, &size);
            brush.SetInterpolationColors(colors, pos, size);
            graphics.FillRectangle(&brush, rect);

        }
    }
    else {
        SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
        if (hasColor)
            graphics.FillRectangle(&brush, rect);
    }
    if (!hasStrokeGradient.empty()) {
        this->gradient = Gradients[hasGradient];
        if (gradient.type == "linearGradient") {
            Color colors[100];
            REAL pos[100];
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            LinearGradientBrush brush(Point(gradient.startPoint.x, gradient.startPoint.y), Point(gradient.endPoint.x, gradient.endPoint.y),
                Color(gradient.stops[0].opacity * 255 * fillOpacity, gradient.stops[0].color.r, gradient.stops[0].color.g, gradient.stops[0].color.b),
                Color(gradient.stops[gradient.stops.size() - 1].opacity * 255 * fillOpacity, gradient.stops[gradient.stops.size() - 1].color.r, gradient.stops[gradient.stops.size() - 1].color.g, gradient.stops[gradient.stops.size() - 1].color.b)
            );
            brush.SetInterpolationColors(colors, pos, gradient.stops.size());
            Pen pen(&brush, strokeWidth);
            graphics.DrawRectangle(&pen, rect);
        }
        if (gradient.type == "radialGradient") {
            Color colors[100];
            REAL pos[100];
            GraphicsPath myPath;
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            PathGradientBrush brush(&myPath);
            int size = gradient.stops.size();
            brush.SetSurroundColors(colors, &size);
            brush.SetInterpolationColors(colors, pos, size);
            Pen pen(&brush, strokeWidth);
            graphics.DrawRectangle(&pen, rect);

        }
    }
    else {
        Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
        if (hasStroke) {
            graphics.DrawRectangle(&pen, rect);
        }
    }
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