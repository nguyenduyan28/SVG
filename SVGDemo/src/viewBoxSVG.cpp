#include "stdafx.h"
ViewBoxSVG::ViewBoxSVG()
{
    point.x = point.y = 0;
    width = height = 0;
}

void ViewBoxSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = false, f = false, s = false, sw = false, so = false;
    for (int i = 0; i < a.size(); i++) {
        string attributeValue = a[i].second;
        cout << a[i].second;

        if (i == 0) {
            this->point.x = stoi(attributeValue);
        }
        else if (i == 1) {
            this->point.y = stoi(attributeValue);
        }
        else if (i == 2) {
            this->width = stoi(attributeValue);
        }
        else if (i == 3) {
            this->height = stoi(attributeValue);
        }
        else {
            (*this).setShape(a[i].first, attributeValue, fo, f, s, sw, so);
        }
    }

    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}