// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
// TODO: reference additional headers your program requires here
struct RGB {
    unsigned char r, g, b;
    RGB& operator=(const RGB& other)
    {
        if (this != &other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
        }
        return *this;
    }
};

struct Points {
    float x, y;
};

void setProperties(char* nodeName, vector<pair<string, string>> a, Graphics& graphics);
void DrawSVGFile(string& filename, HDC hdc);

class Shape {
protected:
    RGB fill;
    double fillOpacity;
    RGB stroke;
    int strokeWidth;
    double strokeOpacity;
    bool hasStroke;
    Points translate;
    double rotate;
    Points scale;


public:
    Shape();
    virtual void drawShape();
    void setShape(const string& a, string& b);

};
vector<Points> parsePoints(const string& p);
class RectangleSVG : public Shape {
private:
    Points point;
    int width;
    int height;

public:
    RectangleSVG();
    void drawRectangleSVG(Graphics& graphics);
    void setRect(vector<pair<string, string>>& a);
};

class TextSVG : public Shape {
private:
    Points point;
    int fontSize;
    string info;

public:
    TextSVG();
    void drawTextSVG(Graphics& graphics);
    void setText(vector<pair<string, string>>a);
};

class CircleSVG : public Shape {
private:
    Points point;
    double radius;

public:
    CircleSVG();
    void drawCircleSVG(Graphics& graphics);
    void setCircle(vector<pair<string, string>>a);
};

class PolylineSVG : public Shape {
private:
    vector<Points> points;

public:
    PolylineSVG();
    void drawPolylineSVG(Graphics& graphics);
    void setPolyline(vector<pair<string, string>>a);

};

class EllipseSVG : public Shape {
private:
    Points c;
    float radiusX, radiusY;

public:
    EllipseSVG();
    void drawEllipseSVG(Graphics& graphics);
    void setEllipse(vector<pair<string, string>>a);
};

class LineSVG : public Shape {
private:
    Points from, to;

public:
    LineSVG();
    void drawLineSVG(Graphics& graphics);
    void setLine(vector<pair<string, string>>a);
};

class PolygonSVG : public Shape {
private:
    vector<Points> points;
public:
    PolygonSVG();
    void drawPolygonSVG(Graphics& graphics);
    void setPolygon(vector<pair<string, string>>a);
};

class PathSVG : public Shape {
private:
    Points startPoint;
    Points curPoint;
    vector <pair <char, vector<Points>>> dData;
public:
    PathSVG();
    void updatePoint(Points newPoint);
    void drawPathSVG(Graphics& graphics);
    void setPath(vector<pair<string, string>>a);
};
