#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
unsigned char opacity2alpha(double opacity)
{
    opacity = max(0.0, min(1.0, opacity));
    return static_cast<unsigned char>(opacity * 255.0);
}

Shape::Shape()
{
    this->fill.r = this->fill.g = this->fill.b = 0;
    this->stroke.r = this->stroke.g = this->stroke.b = 255;
    this->fillOpacity = 1.0;
    this->strokeOpacity = 1.5;
    this->strokeWidth = 2;
    this->hasStroke = false;
    this->translate = Points({0.0, 0.0});
    this->rotate = 0;
    this->scale = Points({0.0, 0.0});
}

void Shape::drawShape(Graphics &graphics) {

}

void Shape::setBesides(vector<pair<string, string>> a) {}

RectangleSVG::RectangleSVG()
{
    point.x = point.y = 0;
    width = 0;
    height = 0;
}

void RectangleSVG::drawShape(Graphics &graphics)
{   
    
    
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();

    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(strokealpha, stroke.r, stroke.b, stroke.g), strokeWidth);
    Rect rect(point.x, point.y, width, height);
    graphics.DrawRectangle(&pen, rect);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillRectangle(&brush, rect);
    graphics.EndContainer(container);
}

TextSVG::TextSVG()
{
    point.x = point.y = 0;
    int fontSize = 12;
    info = "";
}

void TextSVG::drawShape(Graphics &graphics)
{
    
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    FontFamily fontFamily(this -> fontFamily);
    Font font(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
    PointF pointF(point.x - fontSize, point.y - fontSize);

    wstring infostr = wstring(info.begin(), info.end());
    const WCHAR *infocstr = infostr.c_str();
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    SolidBrush solidBrush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.DrawString(infocstr, -1, &font, pointF, &solidBrush);
    graphics.EndContainer(container);
}

LineSVG::LineSVG()
{
    from.x = from.y = to.x = to.y = 0;
}

void LineSVG::drawShape(Graphics &graphics)
{
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    graphics.DrawLine(&pen, from.x, from.y, to.x, to.y);
    graphics.EndContainer(container);
}

CircleSVG::CircleSVG()
{
    point.x = point.y = 0;
    radius = 0.0;
}

void CircleSVG::drawShape(Graphics &graphics)
{
    
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    Rect rect(point.x - radius, point.y - radius, radius * 2, radius * 2);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillEllipse(&brush, rect);
    graphics.DrawEllipse(&pen, rect);
    graphics.EndContainer(container);
}

PolylineSVG::PolylineSVG()
{
    points.clear();
}

void PolylineSVG::drawShape(Graphics &graphics)
{
    
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    vector<PointF> newP;
    for (int i = 0; i < points.size(); i++)
    {
        newP.push_back(PointF{points[i].x, points[i].y});
    }
    PointF *p = newP.data();
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillPolygon(&brush, p, newP.size());
    if (strokeWidth)
        graphics.DrawLines(&pen, p, newP.size());
    graphics.EndContainer(container);
}

EllipseSVG::EllipseSVG()
{
    c.x = c.y = 0;
    radiusX = radiusY = 0.0;
}

void EllipseSVG::drawShape(Graphics &graphics)
{
    
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    Rect rect(c.x - radiusX, c.y - radiusY, radiusX * 2, radiusY * 2);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    GraphicsContainer container = graphics.BeginContainer();
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    graphics.FillEllipse(&brush, rect);
    graphics.DrawEllipse(&pen, rect);
    graphics.EndContainer(container);
}

PolygonSVG::PolygonSVG()
{

    points.clear();
}

void PolygonSVG::drawShape(Graphics &graphics)
{
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    vector<PointF> newP;
    for (int i = 0; i < points.size(); i++)
    {
        newP.push_back(PointF{points[i].x, points[i].y});
    }
    PointF *p = newP.data();
    GraphicsContainer container = graphics.BeginContainer();
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    graphics.FillPolygon(&brush, p, newP.size());
    graphics.DrawPolygon(&pen, p, newP.size());
    graphics.EndContainer(container);
}

void setProperties(char *nodeName, vector<pair<string, string>> a, Graphics &graphics)
{
    //! Chỗ này có time thì sửa lại chung setBesides và drawShape

    if (strcmp(nodeName, "rect") == 0)
    {
        RectangleSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "text") == 0)
    {
        TextSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "circle") == 0)
    {
        CircleSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "polyline") == 0)
    {
        PolylineSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "ellipse") == 0)
    {
        EllipseSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "line") == 0)
    {
        LineSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "polygon") == 0)
    {
        PolygonSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
    else if (strcmp(nodeName, "path") == 0)
    {
        PathSVG r;
        r.setBesides(a);
        r.drawShape(graphics);
    }
}

void SVGElement::setGroup(vector<pair<string, string>>& attributes) {
    for (int i = 0; i < attributes.size(); i++) {
        const string& attributeName = attributes[i].first;
        const string& attributeValue = attributes[i].second;

        // cout << attributeName << ": " << attributeValue << endl;
    }
}

void SVGElement::processAttributes(xml_node<>* node) {
    vector<pair<string, string>> attributes;
    for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        attributes.push_back(make_pair(attr->name(), attr->value()));
    }
    setGroup(attributes);
}
void processGroupNode(xml_node<>* groupNode) {
    SVGElement svgElement;
    svgElement.processAttributes(groupNode);

    for (xml_node<>* childNode = groupNode->first_node(); childNode; childNode = childNode->next_sibling()) {
        if (childNode->type() == rapidxml::node_element) {
            string elementName = childNode->name();
            //cout << "Unhandled element: " << elementName << endl;

            if (elementName == "g") {
                processGroupNode(childNode);
            }
            else if (elementName == "rect") {
                SVGElement rect;
                rect.processAttributes(childNode);
            }
            else if (elementName == "text") {
                SVGElement text;
                text.processAttributes(childNode);
            }
            else if (elementName == "circle") {
                SVGElement circle;
                circle.processAttributes(childNode);
            }
            else if (elementName == "line") {
                SVGElement line;
                line.processAttributes(childNode);
            }
            else if (elementName == "polygon") {
                SVGElement polygon;
                polygon.processAttributes(childNode);
            }
            else if (elementName == "ellipse") {
                SVGElement ellipse;
                ellipse.processAttributes(childNode);
               
            }
            else if (elementName == "polyline") {
                SVGElement polyline;
                polyline.processAttributes(childNode);
            }
        }
    }
}

RGB parseRGB(const string &s) // rgb()
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

    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] > 255)
            a[i] = 255;
    }

    c.r = static_cast<unsigned char>(a[0]);
    c.g = static_cast<unsigned char>(a[1]);
    c.b = static_cast<unsigned char>(a[2]);

    // cout << s << " ";
    // cout << static_cast<int>(c.r) << " " << static_cast<int>(c.g) << " " << static_cast<int>(c.b) << endl;
    return c;
}
void Shape::setShape(const string &attributeName, string &attributeValue)
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
                if (token == "rotate") this->rotate = p.x;
                else if (token == "translate") this->translate.x = p.x, this->translate.y = p.y;
                else this->scale.x = p.x, this->scale.y = p.y;
            }
        }
    }
}
void RectangleSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string &attributeValue = a[i].second;
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
        else
            (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void TextSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string &attributeValue = a[i].second;
        if (attributeName == "x")
        {
            this->point.x = stoi(attributeValue);
        }
        else if (attributeName == "y")
        {
            this->point.y = stoi(attributeValue);
        }
        else if (attributeName == "font-size")
        {
            this->fontSize = stoi(attributeValue);
        }
        else if (attributeName == "text")
        {
            this->info = string(attributeValue);
        }
        else
            (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void CircleSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string &attributeValue = a[i].second;
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
        else
            (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}
//
//vector<Points> parsePoints(const string &a)
//{
//    vector<Points> points;
//    stringstream ss(a);
//
//    while (!ss.eof())
//    {
//        Points p;
//        char comma;
//        ss >> p.x >> comma >> p.y;
//        points.push_back(p);
//    }
//    return points;
//}

vector<Points> parsePoints(const string& a)
{
    vector<Points> points;
    stringstream ss(a);

    while (!ss.eof()) {
        Points p;
        char comma;
        ss >> p.x;
        ss >> comma;
        if (isdigit(comma)) ss.unget();
        ss >> p.y;
        //>> comma >> p.y;
        points.push_back(p);
    }
    return points;
}


void PolylineSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string &attributeValue = a[i].second;
        if (attributeName == "points")
        {
            this->points = parsePoints(attributeValue);
        }
        else
            (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void EllipseSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string &attributeValue = a[i].second;
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
        else
            (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void LineSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string& attributeValue = a[i].second;
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
        else
            (*this).setShape(attributeName, attributeValue);

    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}

void PolygonSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string &attributeValue = a[i].second;

        if (attributeName == "points")
        {
            this->points = parsePoints(attributeValue);
        }
        else
            (*this).setShape(attributeName, attributeValue);
    }
    if (this->hasStroke == false)
    {
        this->strokeWidth = 0;
        this->strokeOpacity = 0;
    }
}
vector<pair<char, vector<Points>>> parsePath(string pathData)
{
    for (int i = 1; i < pathData.size(); i++)
    {
        if (pathData[i] == ' ')
            continue;
        else if (pathData[i] == ',')
            pathData[i] = ' ', i++;
        else if (!isdigit(pathData[i]) && pathData[i] != '.')
            pathData.insert(i, " "), i++;
        else if (isdigit(pathData[i]) && !isdigit(pathData[i - 1]) && pathData[i - 1] != '-' && pathData[i - 1] != '.')
            pathData.insert(i, " "), i++;
    }
    cout << endl;
    cout << pathData << endl;
    stringstream ss(pathData);
    vector<pair<char, vector<Points>>> commands;

    char command = '\0';
    vector<Points> points;

    while (ss >> command)
    {
        points.clear();
        switch (command)
        {
        case 'M':
        case 'm':
        case 'L':
        case 'l':
        case 'C':
        case 'c':
        {
            float x, y;
            char c;
            while (ss >> c)
            {
                cout << c << " ";
                if (c != '-' && !isdigit(c))
                {
                    ss.unget();
                    break;
                }
                ss.unget();
                ss >> x >> y;
                cout << x << " " << y << endl;
                points.push_back({x, y});
            }
            commands.push_back({command, points});
            break;
        }
        case 'H':
        case 'h':
        {
            float x;
            ss >> x;
            points.push_back({x, 0});
            commands.push_back({command, points});
            break;
        }
        case 'V':
        case 'v':
        {
            float y;
            ss >> y;
            points.push_back({0, y});
            commands.push_back({command, points});
            break;
        }
        case 'Z': case 'z':
        {
            commands.push_back({command, points});
            break;
        }
        }
    }

    return commands;
}

void PathSVG::setBesides(vector<pair<string, string>> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        const string &attributeName = a[i].first;
        string attributeValue = a[i].second;

        if (attributeName == "d")
        {
            this->dData = parsePath(attributeValue);
        }
        else
            (*this).setShape(attributeName, attributeValue);
    }
}
PathSVG::PathSVG()
{
    startPoint.x = startPoint.y = curPoint.x = curPoint.y = 0;
}

void PathSVG::updatePoint(Points newPoint)
{
    this->curPoint = newPoint;
}

void PathSVG::drawShape(Graphics &graphics)
{

    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    GraphicsPath myPath;
    Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
    SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
    for (int i = 0; i < dData.size(); i++)
    {
        char nameCommand = dData[i].first;
        vector<Points> data = dData[i].second;
        if (i == 0)
        {   
            startPoint = data[0];
            curPoint = data[0];
            if (nameCommand == 'M' || nameCommand == 'm')
            {
                if (data.size() > 1)
                {
                    myPath.AddLine(Point{int(curPoint.x), int(curPoint.y)}, Point{int(data[0].x), int(data[0].y)});
                    updatePoint(data[0]);
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{int(data[i - 1].x), int(data[i - 1].y)}, Point{int(data[i].x), int(data[i].y)});
                        updatePoint(data[i]);
                    }
                }
                else
                    updatePoint(data[0]);
            }
        }
        else
        {
            if (nameCommand == 'M'){
            
                if (data.size() > 1)
                {
                    myPath.AddLine(Point{int(curPoint.x), int(curPoint.y)}, Point{int(data[0].x), int(data[0].y)});
                    updatePoint(data[0]);
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{int(data[i - 1].x), int(data[i - 1].y)}, Point{int(data[i].x), int(data[i].y)});
                        updatePoint(data[i]);
                    }
                    startPoint = data[data.size() - 1];
                }
                else
                {
                    updatePoint(data[0]);
                    startPoint = data[0];
                }
            }
            else if (nameCommand == 'm')
            {
                if (data.size() > 1)
                {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x + curPoint.x), int(data[0].y + curPoint.y) });
                    updatePoint(data[0]);
                    
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[i].x + curPoint.x), int(data[i].y + curPoint.y) });
                        updatePoint(data[i]);
                    }
                    startPoint = { curPoint.x + data[data.size() - 1].x , curPoint.y + data[data.size() - 1].y };
                }
                else
                {
                    
                    startPoint = { curPoint.x + data[0].x, curPoint.y + data[0].y };
                    updatePoint(Points{ curPoint.x + data[0].x, curPoint.y + data[0].y });
                }

            }
            else if (nameCommand == 'L')
            {
                for (int i = 0; i < data.size(); i++) {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[i].x), int(data[i].y) });
                    updatePoint(data[i]);
                }
            }
            else if (nameCommand == 'l')
            {
                for (int i = 0; i < data.size(); i++) {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[i].x), int(curPoint.y + data[i].y) });
                    updatePoint(Points{ curPoint.x + data[i].x, curPoint.y + data[i].y });
                }
                
            }
            else if (nameCommand == 'H')
            {
                for (int i = 0; i < data.size(); i++) {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[i].x), int(curPoint.y) });
                    updatePoint(Points{ data[i].x, curPoint.y });
                }
            }
            else if (nameCommand == 'h')
            {
                for (int i = 0; i < data.size(); i++){
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[i].x), int(curPoint.y) });
                    updatePoint(Points{ data[i].x + curPoint.x, curPoint.y });
                }
            }
            else if (nameCommand == 'V')
            {
                for (int i = 0; i < data.size(); i++) {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x), int(data[i].y) });
                    updatePoint(Points{ curPoint.x, data[i].y });
                }
            }
            else if (nameCommand == 'v')
            {
                for (int i = 0; i < data.size(); i++) {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x), int(data[i].y + curPoint.y) });
                    updatePoint(Points{ curPoint.x, data[i].y + curPoint.y });
                }
            }
            else if (nameCommand == 'C')
            {
                for (int i = 0; i < data.size(); i = i + 3) {
                    myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[i].x), int(data[i].y) }, Point{ int(data[i + 1].x), int(data[i + 1].y) }, Point{ int(data[i + 2].x), int(data[i + 2].y) });
                    updatePoint(Points{ data[i + 2].x, data[i + 2].y });
                }
            }
            else if (nameCommand == 'c')
            {
                for (int i = 0; i < data.size(); i = i + 3) {
                    myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[i].x), int(curPoint.y + data[i].y) }, Point{ int(curPoint.x + data[i + 1].x), int(curPoint.y + data[i + 1].y) }, Point{ int(curPoint.x + data[i + 2].x), int(curPoint.y + data[i + 2].y) });
                    updatePoint(Points{ curPoint.x + data[i + 2].x, curPoint.y + data[i + 2].y });
                }
            }
            else if (nameCommand == 'Z' || nameCommand == 'z')
            {
                myPath.AddLine(Point{int(curPoint.x), int(curPoint.y)}, Point{int(startPoint.x), int(startPoint.y)});
                updatePoint(startPoint);
                myPath.CloseFigure();
            }
        }
    }
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    if (hasStroke) {
        graphics.DrawPath(&pen, &myPath);
    }
    graphics.FillPath(&brush, &myPath);
    graphics.EndContainer(container);
}
