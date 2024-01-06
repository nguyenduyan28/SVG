#include "stdafx.h"

radialGradientSVG::radialGradientSVG() {
    this->gradientId = "";
    this->cx = 0.0;
    this->r = 0.0;
    this->cy = 0.0;
    this->xlinkHref = "";
    this->gradientUnits = "";
    this->gradientTransform = "";
    this->fx = 0.0;
    this->fy = 0.0;
}

void radialGradientSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = false, f = false, s = false, sw = false, so = false;

    for (int i = 0; i < a.size(); i++)
    {
        string attributeName = a[i].first;
        string attributeValue = a[i].second;

        if (attributeName == "id")
        {
            this->gradientId = attributeValue;

        }
        else if (attributeName == "cx")
        {
            this->cx = stod(attributeValue);

        }
        else if (attributeName == "cy")
        {
            this->cy = stod(attributeValue);
        }
        else if (attributeName == "r")
        {
            this->r = stod(attributeValue);
        }
        else if (attributeName == "fx")
        {
            this->fx = stod(attributeValue);
        }
        else if (attributeName == "fy")
        {
            this->fy = stod(attributeValue);
        }
        else if (attributeName == "xlink:href")
        {
            this->xlinkHref = attributeValue;
           
        }
        else if (attributeName == "gradientUnits")
        {
            this->gradientUnits = attributeValue;
        }
        else if (attributeName == "gradientTransform")
        {
            this->gradientTransform = attributeValue;
        }
        else
        {
            (*this).setShape(attributeName, attributeValue, fo, f, s, sw, so);
        }
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }

}
