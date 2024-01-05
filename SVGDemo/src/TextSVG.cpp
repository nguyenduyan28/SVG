#include "stdafx.h"

TextSVG::TextSVG()
{
    point.x = point.y = 0;
    int fontSize = 16;
    info = "";
    dx = dy = 0;
}

void TextSVG::drawShape(Graphics& graphics)
{
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    FontFamily fontFamily(this->fontFamily);
    Font font(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
    PointF pointF(point.x - fontSize, point.y - fontSize);

    wstring infostr = wstring(info.begin(), info.end());
    const WCHAR* infocstr = infostr.c_str();
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    graphics.TranslateTransform(dx, dy);
    GraphicsPath myPath;
    myPath.AddString(infocstr, -1, &fontFamily, FontStyleRegular, fontSize, pointF, NULL);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    SolidBrush solidBrush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.DrawPath(&pen, &myPath);
    graphics.DrawString(infocstr, -1, &font, pointF, &solidBrush);
    graphics.EndContainer(container);

}


void TextSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
        if (attributeName == "x")
        {
            this->point.x = stof(attributeValue);
        }
        else if (attributeName == "y")
        {
            this->point.y = stof(attributeValue);
        }
        else if (attributeName == "font-size")
        {
            this->fontSize = stoi(attributeValue);
        }
        else if (attributeName == "text")
        {
            this->info = string(attributeValue);
        }
        else if (attributeName == "dx")
        {
            this->dx = stoi(attributeValue);
        }
        else if (attributeName == "dy")
        {
            this->dy = stoi(attributeValue);
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
