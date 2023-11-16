#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
unsigned char opacity2alpha(double opacity) {
	opacity = max(0.0, min(1.0, opacity));
	return  static_cast<unsigned char>(opacity * 255.0);
}

Shape::Shape() {
	this->fill.r = this->fill.g = this->fill.b = 0;
	this->stroke.r = this->stroke.g = this->stroke.b = 0;
	this->fillOpacity = 1.0;
	this->strokeOpacity = 1.5;
	this->strokeWidth = 2;
    this->hasStroke = false;
}

RectangleSVG::RectangleSVG() {
	point.x = point.y = 0;
	width = 0;
	height = 0;
}

void RectangleSVG::drawRectangleSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	Pen pen(Color(strokealpha, stroke.r, stroke.b, stroke.g), strokeWidth);
	Rect rect(point.x, point.y, width, height);
	graphics.DrawRectangle(&pen, rect);
	SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
	graphics.FillRectangle(&brush, rect);
}

TextSVG::TextSVG() {
	point.x = point.y = 0;
	int fontSize = 12;
	info = "";
}

void TextSVG::drawTextSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
	PointF      pointF(point.x - fontSize, point.y - fontSize);
	SolidBrush  solidBrush(Color(fillalpha, fill.r, fill.g, fill.b));
	wstring infostr = wstring(info.begin(), info.end());
	const WCHAR* infocstr = infostr.c_str();
	graphics.DrawString(infocstr, -1, &font, pointF, &solidBrush);
    
}

LineSVG::LineSVG() {
	from.x = from.y = to.x = to.y = 0;
}

void LineSVG::drawLineSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
	graphics.DrawLine(&pen, from.x, from.y, to.x, to.y);
}

CircleSVG::CircleSVG() {
	point.x = point.y = 0;
	radius = 0.0;
}

void CircleSVG::drawCircleSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
	Rect rect(point.x - radius, point.y - radius, radius * 2 , radius * 2);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillEllipse(&brush, rect);
	graphics.DrawEllipse(&pen, rect);
	
}

PolylineSVG::PolylineSVG() {
	points.clear();
}

void PolylineSVG::drawPolylineSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
	vector <Point> newP;
	for (int i = 0; i < points.size(); i++) {
		newP.push_back(Point{ points[i].x, points[i].y });
	}
	Point* p = newP.data();
	SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
	graphics.FillPolygon(&brush, p, newP.size());
    if (strokeWidth)
	graphics.DrawLines(&pen, p, newP.size());
}

EllipseSVG::EllipseSVG() {
	c.x = c.y = 0;
	radiusX = radiusY = 0.0;
}


void EllipseSVG::drawEllipseSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
	Rect rect(c.x - radiusX, c.y - radiusY, radiusX * 2, radiusY * 2);
	SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
	graphics.FillEllipse(&brush, rect);
	graphics.DrawEllipse(&pen, rect);
	
}




PolygonSVG::PolygonSVG() {
	
	points.clear();
}



void PolygonSVG::drawPolygonSVG(Graphics& graphics) {
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	unsigned char fillalpha, strokealpha;
	fillalpha = opacity2alpha(fillOpacity);
	strokealpha = opacity2alpha(strokeOpacity);
	Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
	vector <Point> newP;
	for (int i = 0; i < points.size(); i++) {
		newP.push_back(Point{points[i].x, points[i].y });
	}
	Point* p = newP.data();
	SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
	graphics.FillPolygon(&brush, p, newP.size());
	graphics.DrawPolygon(&pen, p, newP.size());
	
}

void setProperties(char* nodeName, vector<pair<string, string>> a, Graphics& graphics)
{
    if (strcmp(nodeName, "rect") == 0)
    {
        RectangleSVG r;
        r.setRect(a);
        r.drawRectangleSVG(graphics);

    }
    else if (strcmp(nodeName, "text") == 0)
    {
        TextSVG r;
        r.setText(a);
        r.drawTextSVG(graphics);
        // r.display();
    }
    else if (strcmp(nodeName, "circle") == 0)
    {
        CircleSVG r;
        r.setCircle(a);
        r.drawCircleSVG(graphics);

    }
    else if (strcmp(nodeName, "polyline") == 0)
    {
        PolylineSVG r;
        r.setPolyline(a);
        r.drawPolylineSVG(graphics);

    }
    else if (strcmp(nodeName, "ellipse") == 0)
    {
        EllipseSVG r;
        r.setEllipse(a);
        r.drawEllipseSVG(graphics);

    }
    else if (strcmp(nodeName, "line") == 0)
    {
        LineSVG r;
        r.setLine(a);
        r.drawLineSVG(graphics);

    }
    else if (strcmp(nodeName, "polygon") == 0)
    {
        PolygonSVG r;
        r.setPolygon(a);
        r.drawPolygonSVG(graphics);
    }
}

RGB parseRGB(const string& s)
{
    RGB c;
    string values = s.substr(4, s.size() - 5);
    stringstream ss(values);
    string token;
    vector<int> a;

    while (getline(ss, token, ','))
    {
        a.push_back(stoi(token));
    }

    c.r = static_cast<unsigned char>(a[0]);
    c.g = static_cast<unsigned char>(a[1]);
    c.b = static_cast<unsigned char>(a[2]);

    //cout << s << " ";
    //cout << static_cast<int>(c.r) << " " << static_cast<int>(c.g) << " " << static_cast<int>(c.b) << endl;
    return c;
}
void Shape::setShape(const string& attributeName, const string& attributeValue)
{
    if (attributeName == "fill-opacity")
    {
        this->fillOpacity = stod(attributeValue);
    }
    else if (attributeName == "fill")
    {
        this->fill = parseRGB(attributeValue);
    }
    else if (attributeName == "stroke")
    {
        this->hasStroke = true;
        this->stroke = parseRGB(attributeValue);
    }
    else if (attributeName == "stroke-width")
    {
        this->hasStroke = true;
        this->strokeWidth = stoi(attributeValue);
    }
    else if (attributeName == "stroke-opacity")
    {
        this->hasStroke = true;
        this->strokeOpacity = stod(attributeValue);
    }
    
}
void RectangleSVG::setRect(vector<pair<string, string>>& a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;
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
        else (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void TextSVG::setText(vector<pair<string, string>>a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;
        if (attributeName == "x")
        {
            this->point.x = stoi(attributeValue);
        }
        else if (attributeName == "y")
        {
            this->point.y = stoi(attributeValue);
        }
        else if (attributeName == "fill")
        {
            this->fill = parseRGB(attributeValue);
        }
        else if (attributeName == "fill-opacity")
        {
            this->fillOpacity = stod(attributeValue);
        }
        else if (attributeName == "font-size")
        {
            this->fontSize = stoi(attributeValue);
        }
        else if (attributeName == "text")
        {
            this->info = string(attributeValue);
        }
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void CircleSVG::setCircle(vector<pair<string, string>>a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;
        if (attributeName == "cx")
        {
            this->point.x = stoi(attributeValue);
        }
        else if (attributeName == "cy")
        {
            this->point.y = stoi(attributeValue);
        }
        else if (attributeName == "r")
        {
            this->radius = stoi(attributeValue);
        }
        else (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

vector<Points> parsePoints(const string& a)
{
    vector<Points> points;
    stringstream ss(a);

    while (!ss.eof()) {
        Points p;
        char comma;
        ss >> p.x >> comma >> p.y;
        points.push_back(p);
    }
    return points;
}


void PolylineSVG::setPolyline(vector<pair<string, string>>a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;
        if (attributeName == "points")
        {
            this->points = parsePoints(attributeValue);
        }
        else (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void EllipseSVG::setEllipse(vector<pair<string, string>>a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;
        if (attributeName == "cx")
        {
            this->c.x = stoi(attributeValue);
        }
        else if (attributeName == "cy")
        {
            this->c.y = stoi(attributeValue);
        }
        else if (attributeName == "rx")
        {
            this->radiusX = stoi(attributeValue);
        }
        else if (attributeName == "ry")
        {
            this->radiusY = stoi(attributeValue);
        }
        else (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void LineSVG::setLine(vector<pair<string, string>>a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;
        if (attributeName == "x1")
        {
            this->from.x = stoi(attributeValue);
        }
        else if (attributeName == "y1")
        {
            this->from.y = stoi(attributeValue);
        }
        else if (attributeName == "x2")
        {
            this->to.x = stoi(attributeValue);
        }
        else if (attributeName == "y2")
        {
            this->to.y = stoi(attributeValue);
        }
        else if (attributeName == "stroke")
        {
            this->hasStroke = true;
            this->stroke = parseRGB(attributeValue);
        }
        else if (attributeName == "stroke-width")
        {
            this->hasStroke = true;
            this->strokeWidth = stoi(attributeValue);
        }
        else if (attributeName == "stroke-opacity")
        {
            this->hasStroke = true;
            this->strokeOpacity = stod(attributeValue);
        }
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void PolygonSVG::setPolygon(vector<pair<string, string>>a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        const string& attributeValue = a[i].second;

        if (attributeName == "points")
        {
            this->points = parsePoints(attributeValue);
        }
        else (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}
