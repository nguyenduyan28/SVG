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
#include <map>
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

std::map<std::string, std::string> colorMap = {
    {"black", "rgb(0,0,0)"},
    {"white", "rgb(255,255,255)"},
    {"red", "rgb(255,0,0)"},
    {"maroon", "rgb(128,0,0)"},
    {"dark red", "rgb(139,0,0)"},
    {"brown", "rgb(165,42,42)"},
    {"firebrick", "rgb(178,34,34)"},
    {"crimson", "rgb(220,20,60)"},
    {"red", "rgb(255,0,0)"},
    {"tomato", "rgb(255,99,71)"},
    {"coral", "rgb(255,127,80)"},
    {"indian red", "rgb(205,92,92)"},
    {"light coral", "rgb(240,128,128)"},
    {"dark salmon", "rgb(233,150,122)"},
    {"salmon", "rgb(250,128,114)"},
    {"light salmon", "rgb(255,160,122)"},
    {"orange red", "rgb(255,69,0)"},
    {"dark orange", "rgb(255,140,0)"},
    {"orange", "rgb(255,165,0)"},
    {"gold", "rgb(255,215,0)"},
    {"dark golden rod", "rgb(184,134,11)"},
    {"golden rod", "rgb(218,165,32)"},
    {"pale golden rod", "rgb(238,232,170)"},
    {"dark khaki", "rgb(189,183,107)"},
    {"khaki", "rgb(240,230,140)"},
    {"olive", "rgb(128,128,0)"},
    {"yellow", "rgb(255,255,0)"},
    {"yellow green", "rgb(154,205,50)"},
    {"dark olive green", "rgb(85,107,47)"},
    {"olive drab", "rgb(107,142,35)"},
    {"lawn green", "rgb(124,252,0)"},
    {"chartreuse", "rgb(127,255,0)"},
    {"green yellow", "rgb(173,255,47)"},
    {"dark green", "rgb(0,100,0)"},
    {"green", "rgb(0,128,0)"},
    {"forest green", "rgb(34,139,34)"},
    {"lime", "rgb(0,255,0)"},
    {"lime green", "rgb(50,205,50)"},
    {"light green", "rgb(144,238,144)"},
    {"pale green", "rgb(152,251,152)"},
    {"dark sea green", "rgb(143,188,143)"},
    {"medium spring green", "rgb(0,250,154)"},
    {"spring green", "rgb(0,255,127)"},
    {"sea green", "rgb(46,139,87)"},
    {"medium aqua marine", "rgb(102,205,170)"},
    {"medium sea green", "rgb(60,179,113)"},
    {"light sea green", "rgb(32,178,170)"},
    {"dark slate gray", "rgb(47,79,79)"},
    {"teal", "rgb(0,128,128)"},
    {"dark cyan", "rgb(0,139,139)"},
    {"aqua", "rgb(0,255,255)"},
    {"cyan", "rgb(0,255,255)"},
    {"light cyan", "rgb(224,255,255)"},
    {"dark turquoise", "rgb(0,206,209)"},
    {"turquoise", "rgb(64,224,208)"},
    {"medium turquoise", "rgb(72,209,204)"},
    {"pale turquoise", "rgb(175,238,238)"},
    {"aqua marine", "rgb(127,255,212)"},
    {"powder blue", "rgb(176,224,230)"},
    {"cadet blue", "rgb(95,158,160)"},
    {"steel blue", "rgb(70,130,180)"},
    {"corn flower blue", "rgb(100,149,237)"},
    {"deep sky blue", "rgb(0,191,255)"},
    {"dodger blue", "rgb(30,144,255)"},
    {"light blue", "rgb(173,216,230)"},
    {"sky blue", "rgb(135,206,235)"},
    {"light sky blue", "rgb(135,206,250)"},
    {"midnight blue", "rgb(25,25,112)"},
    {"navy", "rgb(0,0,128)"},
    {"dark blue", "rgb(0,0,139)"},
    {"medium blue", "rgb(0,0,205)"},
    {"blue", "rgb(0,0,255)"},
    {"royal blue", "rgb(65,105,225)"},
    {"blue violet", "rgb(138,43,226)"},
    {"indigo", "rgb(75,0,130)"},
    {"dark slate blue", "rgb(72,61,139)"},
    {"slate blue", "rgb(106,90,205)"},
    {"medium slate blue", "rgb(123,104,238)"},
    {"medium purple", "rgb(147,112,219)"},
    {"dark magenta", "rgb(139,0,139)"},
    {"dark violet", "rgb(148,0,211)"},
    {"dark orchid", "rgb(153,50,204)"},
    {"medium orchid", "rgb(186,85,211)"},
    {"purple", "rgb(128,0,128)"},
    {"thistle", "rgb(216,191,216)"},
    {"plum", "rgb(221,160,221)"},
    {"violet", "rgb(238,130,238)"},
    {"magenta", "rgb(255,0,255)"},
    {"fuchsia", "rgb(255,0,255)"},
    {"orchid", "rgb(218,112,214)"},
    {"medium violet red", "rgb(199,21,133)"},
    {"pale violet red", "rgb(219,112,147)"},
    {"deep pink", "rgb(255,20,147)"},
    {"hot pink", "rgb(255,105,180)"},
    {"light pink", "rgb(255,182,193)"},
    {"pink", "rgb(255,192,203)"},
    {"antique white", "rgb(250,235,215)"},
    {"beige", "rgb(245,245,220)"},
    {"bisque", "rgb(255,228,196)"},
    {"blanched almond", "rgb(255,235,205)"},
    {"wheat", "rgb(245,222,179)"},
    {"corn silk", "rgb(255,248,220)"},
    {"lemon chiffon", "rgb(255,250,205)"},
    {"light golden rod yellow", "rgb(250,250,210)"},
    {"light yellow", "rgb(255,255,224)"},
    {"saddle brown", "rgb(139,69,19)"},
    {"sienna", "rgb(160,82,45)"},
    {"chocolate", "rgb(210,105,30)"},
    {"peru", "rgb(205,133,63)"},
    {"sandy brown", "rgb(244,164,96)"},
    {"burly wood", "rgb(222,184,135)"},
    {"tan", "rgb(210,180,140)"},
    {"rosy brown", "rgb(188,143,143)"},
    {"moccasin", "rgb(255,228,181)"},
    {"navajo white", "rgb(255,222,173)"},
    {"peach puff", "rgb(255,218,185)"},
    {"misty rose", "rgb(255,228,225)"},
    {"lavender blush", "rgb(255,240,245)"},
    {"linen", "rgb(250,240,230)"},
    {"old lace", "rgb(253,245,230)"},
    {"papaya whip", "rgb(255,239,213)"},
    {"sea shell", "rgb(255,245,238)"},
    {"mint cream", "rgb(245,255,250)"},
    {"slate gray", "rgb(112,128,144)"},
    {"light slate gray", "rgb(119,136,153)"},
    {"light steel blue", "rgb(176,196,222)"},
    {"lavender", "rgb(230,230,250)"},
    {"floral white", "rgb(255,250,240)"},
    {"alice blue", "rgb(240,248,255)"},
    {"ghost white", "rgb(248,248,255)"},
    {"honeydew", "rgb(240,255,240)"},
    {"ivory", "rgb(255,255,240)"},
    {"azure", "rgb(240,255,255)"},
    {"snow", "rgb(255,250,250)"},
    {"dim gray", "rgb(105,105,105)"},
    {"gray", "rgb(128,128,128)"},
    {"dark gray", "rgb(169,169,169)"},
    {"silver", "rgb(192,192,192)"},
    {"light gray", "rgb(211,211,211)"},
    {"gainsboro", "rgb(220,220,220)"},
    {"white smoke", "rgb(245,245,245)"},
    {"none", "rgb(255,255,255)"},
    {"white", "rgb(255,255,255)"}
};


std::map<std::string, std::string> hexMap = {
    {"#000000", "rgb(0,0,0)"},
    {"#ffffff", "rgb(255,255,255)"},
    {"#ff0000", "rgb(255,0,0)"},
    {"#00ff00", "rgb(0,255,0)"},
    {"#0000ff", "rgb(0,0,255)"},
    {"#ffff00", "rgb(255,255,0)"},
    {"#ff00ff", "rgb(255,0,255)"},
    {"#00ffff", "rgb(0,255,255)"},
    {"#800000", "rgb(128,0,0)"},
    {"#8b0000", "rgb(139,0,0)"},
    {"#a52a2a", "rgb(165,42,42)"},
    {"#b22222", "rgb(178,34,34)"},
    {"#dc143c", "rgb(220,20,60)"},
    {"#ff6347", "rgb(255,99,71)"},
    {"#ff4500", "rgb(255,69,0)"},
    {"#ff8c00", "rgb(255,140,0)"},
    {"#ffd700", "rgb(255,215,0)"},
    {"#bdb76b", "rgb(189,183,107)"},
    {"#f0e68c", "rgb(240,230,140)"},
    {"#808000", "rgb(128,128,0)"},
    {"#ffff00", "rgb(255,255,0)"},
    {"#9acd32", "rgb(154,205,50)"},
    {"#556b2f", "rgb(85,107,47)"},
    {"#6b8e23", "rgb(107,142,35)"},
    {"#7cfc00", "rgb(124,252,0)"},
    {"#7fff00", "rgb(127,255,0)"},
    {"#adff2f", "rgb(173,255,47)"},
    {"#008000", "rgb(0,128,0)"},
    {"#00ff00", "rgb(0,255,0)"},
    {"#228b22", "rgb(34,139,34)"},
    {"#00ff00", "rgb(0,255,0)"},
    {"#32cd32", "rgb(50,205,50)"},
    {"#90ee90", "rgb(144,238,144)"},
    {"#98fb98", "rgb(152,251,152)"},
    {"#8fbc8f", "rgb(143,188,143)"},
    {"#00fa9a", "rgb(0,250,154)"},
    {"#00ff7f", "rgb(0,255,127)"},
    {"#2e8b57", "rgb(46,139,87)"},
    {"#66cdaa", "rgb(102,205,170)"},
    {"#3cb371", "rgb(60,179,113)"},
    {"#20b2aa", "rgb(32,178,170)"},
    {"#2f4f4f", "rgb(47,79,79)"},
    {"#008080", "rgb(0,128,128)"},
    {"#008b8b", "rgb(0,139,139)"},
    {"#00ffff", "rgb(0,255,255)"},
    {"#00ffff", "rgb(0,255,255)"},
    {"#e0ffff", "rgb(224,255,255)"},
    {"#00ced1", "rgb(0,206,209)"},
    {"#40e0d0", "rgb(64,224,208)"},
    {"#48d1cc", "rgb(72,209,204)"},
    {"#afeeee", "rgb(175,238,238)"},
    {"#7fffd4", "rgb(127,255,212)"},
    {"#b0e0e6", "rgb(176,224,230)"},
    {"#5f9ea0", "rgb(95,158,160)"},
    {"#4682b4", "rgb(70,130,180)"},
    {"#6495ed", "rgb(100,149,237)"},
    {"#00bfff", "rgb(0,191,255)"},
    {"#1e90ff", "rgb(30,144,255)"},
    {"#add8e6", "rgb(173,216,230)"},
    {"#87ceeb", "rgb(135,206,235)"},
    {"#87cefa", "rgb(135,206,250)"},
    {"#191970", "rgb(25,25,112)"},
    {"#000080", "rgb(0,0,128)"},
    {"#00008b", "rgb(0,0,139)"},
    {"#0000cd", "rgb(0,0,205)"},
    {"#0000ff", "rgb(0,0,255)"},
    {"#4169e1", "rgb(65,105,225)"},
    {"#8a2be2", "rgb(138,43,226)"},
    {"#4b0082", "rgb(75,0,130)"},
    {"#483d8b", "rgb(72,61,139)"},
    {"#6a5acd", "rgb(106,90,205)"},
    {"#7b68ee", "rgb(123,104,238)"},
    {"#9370db", "rgb(147,112,219)"},
    {"#8b008b", "rgb(139,0,139)"},
    {"#9400d3", "rgb(148,0,211)"},
    {"#9932cc", "rgb(153,50,204)"},
    {"#ba55d3", "rgb(186,85,211)"},
    {"#800080", "rgb(128,0,128)"},
    {"#d8bfd8", "rgb(216,191,216)"},
    {"#dda0dd", "rgb(221,160,221)"},
    {"#ee82ee", "rgb(238,130,238)"},
    {"#ff00ff", "rgb(255,0,255)"},
    {"#ff00ff", "rgb(255,0,255)"},
    {"#da70d6", "rgb(218,112,214)"},
    {"#c71585", "rgb(199,21,133)"},
    {"#db7093", "rgb(219,112,147)"},
    {"#ff1493", "rgb(255,20,147)"},
    {"#ff69b4", "rgb(255,105,180)"},
    {"#ffb6c1", "rgb(255,182,193)"},
    {"#ffc0cb", "rgb(255,192,203)"},
    {"#faebd7", "rgb(250,235,215)"},
    {"#f5f5dc", "rgb(245,245,220)"},
    {"#ffe4c4", "rgb(255,228,196)"},
    {"#ffebcd", "rgb(255,235,205)"},
    {"#f5deb3", "rgb(245,222,179)"},
    {"#fff8dc", "rgb(255,248,220)"},
    {"#fffacd", "rgb(255,250,205)"},
    {"#fafad2", "rgb(250,250,210)"},
    {"#ffffe0", "rgb(255,255,224)"},
    {"#8b4513", "rgb(139,69,19)"},
    {"#a0522d", "rgb(160,82,45)"},
    {"#d2691e", "rgb(210,105,30)"},
    {"#cd853f", "rgb(205,133,63)"},
    {"#f4a460", "rgb(244,164,96)"},
    {"#deb887", "rgb(222,184,135)"},
    {"#d2b48c", "rgb(210,180,140)"},
    {"#bc8f8f", "rgb(188,143,143)"},
    {"#ffe4b5", "rgb(255,228,181)"},
    {"#ffdead", "rgb(255,222,173)"},
    {"#ffdab9", "rgb(255,218,185)"},
    {"#ffe4e1", "rgb(255,228,225)"},
    {"#fff0f5", "rgb(255,240,245)"},
    {"#faf0e6", "rgb(250,240,230)"},
    {"#fdf5e6", "rgb(253,245,230)"},
    {"#ffefd5", "rgb(255,239,213)"},
    {"#fff5ee", "rgb(255,245,238)"},
    {"#f5fffa", "rgb(245,255,250)"},
    {"#708090", "rgb(112,128,144)"},
    {"#778899", "rgb(119,136,153)"},
    {"#b0c4de", "rgb(176,196,222)"},
    {"#e6e6fa", "rgb(230,230,250)"},
    {"#fffaf0", "rgb(255,250,240)"},
    {"#f0f8ff", "rgb(240,248,255)"},
    {"#f8f8ff", "rgb(248,248,255)"},
    {"#f0fff0", "rgb(240,255,240)"},
    {"#fffff0", "rgb(255,255,240)"},
    {"#f0f8ff", "rgb(240,248,255)"},
    {"#ffffff", "rgb(255,255,255)"}
};
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
    const wchar_t* fontFamily = L"Times New Roman"; //to do

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
