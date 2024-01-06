#include "stdafx.h"

Shape::Shape()
{
    this->fill.r = this->fill.g = this->fill.b = 0;
    this->stroke.r = this->stroke.g = this->stroke.b = 255;
    this->fillOpacity = 1.0;
    this->strokeOpacity = 1.5;
    this->strokeWidth = 2;
    this->hasStroke = false;
    this->translate = Points({ 0.0, 0.0 });
    this->rotate = 0;
    this->scale = Points({ 0.0, 0.0 });
}

void Shape::drawShape(Graphics& graphics) {}

void Shape::setBesides(vector<pair<string, string>> a) {}

void Shape::setShape(const string& attributeName, string& attributeValue, bool& fo, bool& f, bool& s, bool& sw, bool& so)
{
    if (attributeName == "fill-opacity")
    {
        if (fo == 0)
            this->fillOpacity = stod(attributeValue), fo = 1;
    }
    else if (attributeName == "fill")
    {
        if (f == 0)
            this->fill = parseRGB(attributeValue), f = 1;
        if (fill.r == -1 || fill.g == -1 || fill.b == -1)
            hasColor = false;
        else hasColor = true;
    }
    else if (attributeName == "stroke")
    {
        if (s == 0)
        {
            this->hasStroke = true;
            this->stroke = parseRGB(attributeValue);
            s = 1;
        }

    }
    else if (attributeName == "stroke-width")
    {
        if (sw == 0)
        {
            this->hasStroke = true;
            this->strokeWidth = stoi(attributeValue);
            sw = 1;
        }

    }
    else if (attributeName == "stroke-opacity")
    {
        if (so == 0)
        {
            so = 1;
            this->hasStroke = true;
            this->strokeOpacity = stod(attributeValue);
        }

    }

    else if (attributeName == "transform")
    {
        for (int i = 0; i < attributeValue.length(); i++)
        {
            if (attributeValue[i] == '(' || attributeValue[i] == ')')
            {
                attributeValue[i] = ' ';
            }
        }
        stringstream ss(attributeValue);
        string token;
        while (ss >> token)
        {
            if (token == "translate" || token == "rotate" || token == "scale")
            {
                string transformType = token;
                Points p;
                ss >> p.x;
                if (ss.peek() == ',')
                {
                    ss.ignore();
                    ss >> p.y;
                }
                else
                {
                    if (transformType == "scale") p.y = p.x;
                    else ss >> p.y;
                }
                if (token == "rotate") this->rotate += p.x;
                else if (token == "translate") this->translate.x += p.x, this->translate.y += p.y;
                else this->scale.x += p.x, this->scale.y += p.y;
            }
        }
    }
}