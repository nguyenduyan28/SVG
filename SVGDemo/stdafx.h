// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
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
#pragma comment(lib, "Gdiplus.lib")
// TODO: reference additional headers your program requires here
struct RGB
{
    unsigned char r, g, b;
    RGB &operator=(const RGB &other)
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

struct Points
{
    float x, y;
};

void setProperties(char *nodeName, vector<pair<string, string>> a, Graphics &graphics);
void DrawSVGFile(string &filename, HDC hdc);

class Shape
{
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
    virtual void drawShape(Graphics &graphics);
    void setShape(const string &a, string &b);
    virtual void setBesides(vector<pair<string, string>> a);
};
vector<Points> parsePoints(const string &p);

class RectangleSVG : public Shape
{
private:
    Points point;
    int width;
    int height;

public:
    RectangleSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class TextSVG : public Shape
{
private:
    Points point;
    int fontSize;
    string info;

public:
    TextSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class CircleSVG : public Shape
{
private:
    Points point;
    double radius;

public:
    CircleSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class PolylineSVG : public Shape
{
private:
    vector<Points> points;

public:
    PolylineSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class EllipseSVG : public Shape
{
private:
    Points c;
    float radiusX, radiusY;

public:
    EllipseSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class LineSVG : public Shape
{
private:
    Points from, to;

public:
    LineSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class PolygonSVG : public Shape
{
private:
    vector<Points> points;

public:
    PolygonSVG();
    void drawShape(Graphics &graphics) override;
    void setBesides(vector<pair<string, string>> a) override;
};

class PathSVG : public Shape
{
private:
    Points startPoint;
    Points curPoint;
    vector<pair<char, vector<Points>>> dData;

public:
    PathSVG();
    void updatePoint(Points newPoint);
    void drawShape(Graphics &graphics);
    void setBesides(vector<pair<string, string>> a);
};
class SVGElement {
public:
    void setGroup(vector<pair<string, string>>& attributes);
    void processAttributes(xml_node<>* node);
};
void processGroupNode(xml_node<>* groupNode);
