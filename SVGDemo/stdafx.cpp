#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

unsigned char opacity2alpha(double opacity)
{
    opacity = max(0.0, min(1.0, opacity));
    return static_cast<unsigned char>(opacity * 255.0);
}

RGB parseRGB(string &s)
{
    changeRGB(s);
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

    return c;
}

vector<Points> parsePoints(const string &a)
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



int hex2dec(string hexVal)
{
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0 
    int base = 1;

    int dec_val = 0; 
    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power 
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting 
        // it to integral 10 - 15 by subtracting 55 
        // from ASCII value 
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

            // incrementing base by power 
            base = base * 16;
        }
    }
    return dec_val;
}


void processHex(string& s) {
    int r, g, b;
    int size = s.size() - 1;
    if (size == 3) {
        string s1 = s;
        string s2 = s;
        s.clear();
        s.push_back('#');
        for (int i = 0; i < s1.size() - 1; i++){
            s.push_back(s1[i + 1]);
            s.push_back(s2[i + 1]);
        }
    }
    size = s.size() - 1;
    r = hex2dec(s.substr(1, 2));
    g = hex2dec(s.substr(3, 2));
    b = hex2dec(s.substr(5, 2));
    ostringstream ss;
    ss << "rgb(" << r << ", " << g << ", " << b << ")";
    s = ss.str();
}


void changeRGB(string& s) {
    if (s.find("rgb") != string::npos) {
        return;
    }

    if (s.find("#") != string::npos) {
        for (int i = 1; i < s.size(); i++) {
            s[i] = toupper(s[i]);
        }
        processHex(s);
    }
    else {
        for (int i = 0; i < s.size(); i++) {
            s[i] = tolower(s[i]);
        }
        s = colorMap[s];
    }
}


void setProperties(char* nodeName, vector<pair<string, string>> a, Graphics& graphics)
{
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

