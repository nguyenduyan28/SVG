#include "stdafx.h"

void bezier_arc_svg(double x0, double y0, double rx, double ry, double angle, bool large_arc_flag,
    bool sweep_flag, double x2, double y2, double& start_angle, double& sweep_angle, double& cx, double& cy)
{
    double pi = atan(1) * 4;
    bool m_radii_ok = true;

    if (rx < 0.0) rx = -rx;
    if (ry < 0.0) ry = -rx;

    // Calculate the middle point between the current and the final points

    double dx2 = (x0 - x2) / 2.0;
    double dy2 = (y0 - y2) / 2.0;

    double cos_a = std::cos(angle);
    double sin_a = std::sin(angle);

    // Calculate (x1, y1)

    double x1 = cos_a * dx2 + sin_a * dy2;
    double y1 = -sin_a * dx2 + cos_a * dy2;

    // Ensure radii are large enough

    double prx = rx * rx;
    double pry = ry * ry;
    double px1 = x1 * x1;
    double py1 = y1 * y1;

    // Check that radii are large enough

    double radii_check = px1 / prx + py1 / pry;
    if (radii_check > 1.0)
    {
        rx = std::sqrt(radii_check) * rx;
        ry = std::sqrt(radii_check) * ry;
        prx = rx * rx;
        pry = ry * ry;
        if (radii_check > 10.0) m_radii_ok = false;
    }

    // Calculate (cx1, cy1)

    double sign = (large_arc_flag == sweep_flag) ? -1.0 : 1.0;
    double sq = (prx * pry - prx * py1 - pry * px1) / (prx * py1 + pry * px1);
    double coef = sign * std::sqrt((sq < 0) ? 0 : sq);
    double cx1 = coef * ((rx * y1) / ry);
    double cy1 = coef * -((ry * x1) / rx);

    // Calculate (cx, cy) from (cx1, cy1)

    double sx2 = (x0 + x2) / 2.0;
    double sy2 = (y0 + y2) / 2.0;
    cx = sx2 + (cos_a * cx1 - sin_a * cy1);
    cy = sy2 + (sin_a * cx1 + cos_a * cy1);

    // Calculate the start_angle (angle1) and the sweep_angle (dangle)

    double ux = (x1 - cx1) / rx;
    double uy = (y1 - cy1) / ry;
    double vx = (-x1 - cx1) / rx;
    double vy = (-y1 - cy1) / ry;
    double p, n;

    // Calculate the angle start

    n = std::sqrt(ux * ux + uy * uy);
    p = ux; // (1 * ux) + (0 * uy)
    sign = (uy < 0) ? -1.0 : 1.0;
    double v = p / n;
    if (v < -1.0) v = -1.0;
    if (v > 1.0) v = 1.0;
    start_angle = sign * std::acos(v);

    // Calculate the sweep angle

    n = std::sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
    p = ux * vx + uy * vy;
    sign = (ux * vy - uy * vx < 0) ? -1.0 : 1.0;
    v = p / n;
    if (v < -1.0) v = -1.0;
    if (v > 1.0) v = 1.0;
    sweep_angle = sign * std::acos(v);
    if (!sweep_flag && sweep_angle > 0)
    {
        sweep_angle -= pi * 2.0;
    }
    else
        if (sweep_flag && sweep_angle < 0)
        {
            sweep_angle += pi * 2.0;
        }
}

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
    double pi = atan(1) * 4;
    unsigned char fillalpha, strokealpha;
    fillalpha = opacity2alpha(fillOpacity);
    strokealpha = opacity2alpha(strokeOpacity);
    GraphicsContainer container = graphics.BeginContainer();

    /*for (string s : transformCommand) {
        if (s == "translate")
            graphics.TranslateTransform(translate.x, translate.y);
        if (s == "scale")
            graphics.ScaleTransform(scale.x, scale.y);
        if (s == "rotate")
            graphics.RotateTransform(rotate);
    }*/
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.ScaleTransform(scale.x, scale.y);
    graphics.RotateTransform(rotate);
    
    GraphicsPath myPath;
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
            else if (nameCommand == 'S' || nameCommand == 'Q')
            {
                for (int i = 0; i < data.size(); i = i + 2) {
                    myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[i].x), int(data[i].y) }, Point{ int(data[i + 1].x), int(data[i + 1].y) }, Point{ int(data[i + 1].x), int(data[i + 1].y) });
                    updatePoint(Points{ data[i + 1].x, data[i + 1].y });
                }
            }
            else if (nameCommand == 's' || nameCommand == 'q')
            {
                for (int i = 0; i < data.size(); i = i + 2) {
                    myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[i].x), int(curPoint.y + data[i].y) }, Point{ int(curPoint.x + data[i + 1].x), int(curPoint.y + data[i + 1].y) }, Point{ int(curPoint.x + data[i + 1].x), int(curPoint.y + data[i + 1].y) });
                    updatePoint(Points{ curPoint.x + data[i + 1].x, curPoint.y + data[i + 1].y });
                }
            }
            else if (nameCommand == 'A') {
                for (int i = 0; i < data.size(); i = i + 4) {
                    double cx, cy;
                    double startAng, sweepAng;
                    bezier_arc_svg(curPoint.x, curPoint.y, data[i].x, data[i].y, data[i + 1].x, data[i + 1].y, data[i + 2].x, data[i + 2].y, data[i + 3].x, startAng, sweepAng,  cx, cy);
                    RectF b(cx - data[i].x, cy - data[i].y, 2 * data[i].x, 2 * data[i].y);
                    startAng = startAng * (180.0f / pi);
                    sweepAng = sweepAng * (180.0f / pi);
                    myPath.AddArc(b, startAng, sweepAng);
                    updatePoint({ data[i + 2].y, data[i + 3].x });
                }
            }
            else if (nameCommand == 'a') {
                for (int i = 0; i < data.size(); i = i + 4) {
                    data[i + 2].y += curPoint.x;
                    data[i + 3].x += curPoint.y;
                    double cx, cy;
                    double startAng, sweepAng;
                    bezier_arc_svg(curPoint.x, curPoint.y, data[i].x, data[i].y, data[i + 1].x, data[i + 1].y, data[i + 2].x, data[i + 2].y, data[i + 3].x, startAng, sweepAng, cx, cy);
                    RectF b(cx - data[i].x, cy - data[i].y, 2 * data[i].x, 2 * data[i].y);
                    startAng = startAng * (180.0f / pi);
                    sweepAng = sweepAng * (180.0f / pi);
                    myPath.AddArc(b, startAng, sweepAng);
                    updatePoint({ data[i + 2].y + curPoint.x, data[i + 3].x + curPoint.y });
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
    if (!hasGradient.empty()) {
        this->gradient = Gradients[hasGradient];
        cout << gradient.type;
        if (gradient.type == "linearGradient") {
            Color colors[100];
            REAL pos[100];
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            LinearGradientBrush brush(Point(gradient.startPoint.x, gradient.startPoint.y), Point(gradient.endPoint.x, gradient.endPoint.y),
                Color(gradient.stops[0].opacity * 255 * fillOpacity, gradient.stops[0].color.r, gradient.stops[0].color.g, gradient.stops[0].color.b),
                Color(gradient.stops[gradient.stops.size() - 1].opacity * 255 * fillOpacity, gradient.stops[gradient.stops.size() - 1].color.r, gradient.stops[gradient.stops.size() - 1].color.g, gradient.stops[gradient.stops.size() - 1].color.b)
            );
            brush.SetInterpolationColors(colors, pos, gradient.stops.size());
            graphics.FillPath(&brush, &myPath);
        }
        if (gradient.type == "radialGradient") {
            Color colors[100];
            REAL pos[100];
            if (!gradient.xlink.empty()) {
                gradient = Gradients[gradient.xlink];
            }
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            PathGradientBrush brush(&myPath);
            int size = gradient.stops.size();
            brush.SetSurroundColors(colors, &size);
            brush.SetInterpolationColors(colors, pos, size);
            graphics.FillPath(&brush, &myPath);

        }
    }
    else {
        SolidBrush brush(Color(fillalpha, fill.r, fill.g, fill.b));
        if (hasColor)
            graphics.FillPath(&brush, &myPath);
    }
    if (!hasStrokeGradient.empty()) {
           this->gradient = Gradients[hasStrokeGradient];
        if (gradient.type == "linearGradient") {
            Color colors[100];
            REAL pos[100];
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            LinearGradientBrush brush(Point(gradient.startPoint.x, gradient.startPoint.y), Point(gradient.endPoint.x, gradient.endPoint.y),
                Color(gradient.stops[0].opacity * 255 * fillOpacity, gradient.stops[0].color.r, gradient.stops[0].color.g, gradient.stops[0].color.b),
                Color(gradient.stops[gradient.stops.size() - 1].opacity * 255 * fillOpacity, gradient.stops[gradient.stops.size() - 1].color.r, gradient.stops[gradient.stops.size() - 1].color.g, gradient.stops[gradient.stops.size() - 1].color.b)
            );
            brush.SetInterpolationColors(colors, pos, gradient.stops.size());
            Pen pen(&brush, strokeWidth);
            graphics.DrawPath(&pen, &myPath);
        }
        if (gradient.type == "radialGradient") {
            Color colors[100];
            REAL pos[100];
            for (int i = 0; i < gradient.stops.size(); i++) {
                colors[i] = Color(gradient.stops[i].color.r, gradient.stops[i].color.g, gradient.stops[i].color.b);
                pos[i] = gradient.stops[i].offset;
            }
            PathGradientBrush brush(&myPath);
            int size = gradient.stops.size();
            brush.SetSurroundColors(colors, &size);
            brush.SetInterpolationColors(colors, pos, size);
            Pen pen(&brush, strokeWidth);
            graphics.DrawPath(&pen, &myPath);

        }
    }
    else {
        Pen pen(Color(strokealpha, stroke.r, stroke.g, stroke.b), strokeWidth);
        if (hasStroke) {
            graphics.DrawPath(&pen, &myPath);
        }
    }
    
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
                if (c != '-' && !isdigit(c) && c!= '.')
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
        case 'A' : case 'a':
        {
            commands.push_back({ command, points });
            break;
        }
        }
    }

    return commands;
}