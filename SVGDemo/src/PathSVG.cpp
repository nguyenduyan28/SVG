#include "stdafx.h"

void PathSVG::setBesides(vector<pair<string, string>> a)
{
    bool fo = 0, f = 0, so = 0, sw = 0, s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        const string& attributeName = a[i].first;
        string attributeValue = a[i].second;

        if (attributeName == "d")
        {
            this->dData = parsePath(attributeValue);
        }
        else
            (*this).setShape(attributeName, attributeValue, fo, f, s, sw, so);
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

void PathSVG::drawShape(Graphics& graphics)
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
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(data[0].y) });
                    updatePoint(data[0]);
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{ int(data[i - 1].x), int(data[i - 1].y) }, Point{ int(data[i].x), int(data[i].y) });
                        updatePoint(data[i]);
                    }
                }
                else
                    updatePoint(data[0]);
            }
        }
        else
        {
            if (nameCommand == 'M') {

                if (data.size() > 1)
                {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(data[0].y) });
                    updatePoint(data[0]);
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{ int(data[i - 1].x), int(data[i - 1].y) }, Point{ int(data[i].x), int(data[i].y) });
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
                for (int i = 0; i < data.size(); i++) {
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
            else if (nameCommand == 'S')
            {
                for (int i = 0; i < data.size(); i = i + 2) {
                    myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[i].x), int(data[i].y) }, Point{ int(data[i + 1].x), int(data[i + 1].y) }, Point{ int(data[i + 1].x), int(data[i + 1].y) });
                    updatePoint(Points{ data[i + 1].x, data[i + 1].y });
                }
            }
            else if (nameCommand == 's')
            {
                for (int i = 0; i < data.size(); i = i + 2) {
                    myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[i].x), int(curPoint.y + data[i].y) }, Point{ int(curPoint.x + data[i + 1].x), int(curPoint.y + data[i + 1].y) }, Point{ int(curPoint.x + data[i + 1].x), int(curPoint.y + data[i + 1].y) });
                    updatePoint(Points{ curPoint.x + data[i + 1].x, curPoint.y + data[i + 1].y });
                }
            }
            else if (nameCommand == 'Z' || nameCommand == 'z')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(startPoint.x), int(startPoint.y) });
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
    if (hasColor)
        graphics.FillPath(&brush, &myPath);
    graphics.EndContainer(container);
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
        case 's':
        case 'S':
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
                points.push_back({ x, y });
            }
            commands.push_back({ command, points });
            break;
        }
        case 'H':
        case 'h':
        {
            float x;
            ss >> x;
            points.push_back({ x, 0 });
            commands.push_back({ command, points });
            break;
        }
        case 'V':
        case 'v':
        {
            float y;
            ss >> y;
            points.push_back({ 0, y });
            commands.push_back({ command, points });
            break;
        }
        case 'Z': case 'z':
        {
            commands.push_back({ command, points });
            break;
        }
        }
    }

    return commands;
}