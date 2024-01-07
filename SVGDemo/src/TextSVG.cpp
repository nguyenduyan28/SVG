#include "stdafx.h"

TextSVG::TextSVG()
{
    point.x = point.y = 0;
    int fontSize = 16;
    info = "";
    dx = dy = 0;
    this->fontFamily = "Times New Roman";

}

void TextSVG::drawShape(Graphics& graphics)
{
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
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
    graphics.TranslateTransform(dx, dy);
    wstring ws = wstring(fontFamily.begin(), fontFamily.end());
    FontFamily fontFamily(ws.c_str());
    FontStyle fontStyleSet = FontStyleRegular;
    for (int i = 0; i < fontStyle.size(); i++) {
        fontStyle[i] = tolower(fontStyle[i]);
    }
    cout << fontStyle;
    if (this->fontStyle == "italic")
    {
        fontStyleSet = FontStyleItalic;
    }
    if (this->fontStyle == "Bold") {
        fontStyleSet = FontStyleBold;
    }
    if (this->fontStyle == "italic bold" || this->fontStyle == "bold italic") {
        fontStyleSet = FontStyleBoldItalic;
    }

    for (int i = 0; i < textAnchor.size(); i++) {
        textAnchor[i] = tolower(textAnchor[i]);
    }
    StringFormat stringFormat = new StringFormat();
    if (this->textAnchor == "middle") {
        stringFormat.SetAlignment(StringAlignmentCenter);
        stringFormat.SetLineAlignment(StringAlignmentCenter);
    }
    if (this->textAnchor == "start") {
        stringFormat.SetAlignment(StringAlignmentNear);
        stringFormat.SetLineAlignment(StringAlignmentNear);
    }
    if (this->textAnchor == "end") {
        stringFormat.SetAlignment(StringAlignmentFar);
        stringFormat.SetLineAlignment(StringAlignmentFar);
    }
    Font font(&fontFamily, fontSize, fontStyleSet, UnitPixel);
    wstring infostr = wstring(info.begin(), info.end());
    const WCHAR* infocstr = infostr.c_str();
    PointF pointF(point.x - 0.09 * fontSize, point.y - 0.9 * fontSize);
    GraphicsPath myPath;
    myPath.AddString(infocstr, -1, &fontFamily, fontStyleSet, fontSize, pointF, &stringFormat);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    SolidBrush solidBrush(Color(fillalpha, fill.r, fill.g, fill.b));
    
    if (hasColor)
        graphics.DrawString(infocstr, -1, &font, pointF, &stringFormat, &solidBrush);
    if (hasStroke)
        graphics.DrawPath(&pen, &myPath);
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
        else if (attributeName == "font-family")
        {
            this->fontFamily = string(attributeValue);
        }
        else if (attributeName == "font-style") {
            this->fontStyle = string(attributeValue);
        }
        else if (attributeName == "text-anchor")
        {
            this->textAnchor = string(attributeValue);
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

