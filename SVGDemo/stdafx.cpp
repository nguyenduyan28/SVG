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
	this->strokeOpacity = 1.0;
	this->strokeWidth = 0;
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
