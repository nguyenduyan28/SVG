#include "stdafx.h"
map<string, GradientSVG> Gradients;
PolylineSVG::PolylineSVG()
{
    points.clear();
}

void PolylineSVG::drawShape(Graphics& graphics)
{

    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    
    vector<PointF> newP;
    for (int i = 0; i < points.size(); i++)
    {
        newP.push_back(PointF{ points[i].x, points[i].y });
    }
    PointF* p = newP.data();
    
    GraphicsContainer container = graphics.BeginContainer();
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
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
            graphics.FillPolygon(&brush, p, newP.size(), FillModeWinding);
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
            graphics.FillPolygon(&brush, p, newP.size(), FillModeWinding);

        }
    }
    else {
        SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
        if (hasColor)
            graphics.FillPolygon(&brush, p, newP.size(), FillModeWinding);
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
            graphics.DrawLines(&pen, p, newP.size());
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
            graphics.DrawLines(&pen, p, newP.size());

        }
    }
    else {
        Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
        if (hasStroke) {
            graphics.DrawLines(&pen, p, newP.size());
        }
    }
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