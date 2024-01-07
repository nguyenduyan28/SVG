#include "stdafx.h"


extern map<string, GradientSVG> Gradients;

void readLinearGr(xml_node<>* node)
{

    while (node)
    {
        GradientSVG r;
        if (strcmp(node->name(), "linearGradient") == 0)
        {
            r.type = node->name();
            xml_attribute<>* gradientIdAttr = node->first_attribute("id");
            if (gradientIdAttr) {
                r.id = gradientIdAttr->value();
            }
            xml_attribute<>* x1Attr = node->first_attribute("x1");
            xml_attribute<>* y1Attr = node->first_attribute("y1");
            xml_attribute<>* x2Attr = node->first_attribute("x2");
            xml_attribute<>* y2Attr = node->first_attribute("y2");
            r.startPoint.x = 0;
            r.startPoint.y = 0;
            r.endPoint.x = 0;
            r.endPoint.y = 0;
            if (x1Attr && y1Attr && x2Attr && y2Attr)
            {
                r.startPoint.x = stof(x1Attr->value());
                r.startPoint.y = stof(y1Attr->value());
                r.endPoint.x = stof(x2Attr->value());
                r.endPoint.y = stof(y2Attr->value());

            }
            xml_attribute<>* graUnit = node->first_attribute("gradientUnits");
            if (graUnit)
            {
                r.gradientUnits = graUnit->value();
            }
            xml_node<>* stopNode = node->first_node();
            while (stopNode)
            {
                xml_attribute<>* attributeNode = stopNode->first_attribute();
                GradientStop gr;
                while (attributeNode)
                {
                    char* attributeName = attributeNode->name();
                    char* attributeValue = attributeNode->value();
                    gr.opacity = 1.5;
                    if (strcmp(attributeName, "stop-opacity") == 0)
                    {
                        gr.opacity = stod(attributeValue);
                    }
                    else if (strcmp(attributeName, "offset") == 0)
                    {
                        gr.offset = stod(attributeValue);
                    }
                    else if (strcmp(attributeName, "stop-color") == 0)
                    {
                        string s(attributeValue);
                        changeRGB(s);
                        gr.color = parseRGB(s);
                    }
                    attributeNode = attributeNode->next_attribute();
                }
                r.stops.push_back(gr);
                stopNode = stopNode->next_sibling();
            }
        }
        else if (strcmp(node->name(), "radialGradient") == 0)
        {
            xml_attribute<>* currentAttribute = node->first_attribute();
            while (currentAttribute)
            {
                char* attributeName = currentAttribute->name();
                char* attributeValue = currentAttribute->value();
                if (strcmp(attributeName, "id") == 0)
                {
                    r.id = attributeValue;

                }
                else if (attributeName == "cx")
                {
                    r.startPoint.x = stod(attributeValue);

                }
                else if (attributeName == "cy")
                {
                    r.startPoint.y = stod(attributeValue);
                }
                else if (attributeName == "r")
                {
                    r.radius = stod(attributeValue);
                }
                else if (attributeName == "fx")
                {
                    r.endPoint.x = stod(attributeValue);
                }
                else if (attributeName == "fy")
                {
                    r.endPoint.y = stod(attributeValue);
                }
                else if (attributeName == "xlink:href")
                {
                    r.xlink = string(attributeValue);
                    r.xlink = r.xlink.substr(1);

                }
                else if (attributeName == "gradientUnits")
                {
                    r.gradientUnits = attributeValue;
                }
                currentAttribute = currentAttribute->next_attribute();
            }

        }
        Gradients.insert({ r.id, r });
        node = node->next_sibling();
    }

}


void applyAttributesToChildren(xml_node<>* parentNode, vector<pair<string, string>>& attributes) {
    // Apply attributes to all child nodes within <g>
    xml_node<>* childNode = parentNode->first_node();
    while (childNode) {
        for (auto& attribute : attributes) {
            childNode->append_attribute(childNode->document()->allocate_attribute(
                childNode->document()->allocate_string(attribute.first.c_str()),
                childNode->document()->allocate_string(attribute.second.c_str())
            ));
        }
        /*if (strcmp(childNode->name(), "g") == 0) {
            // Recursively read children
            applyAttributesToChildren(childNode, attributes);
        }*/
        childNode = childNode->next_sibling();
    }
}

void read(xml_node<>* node, vector<pair<string, string>>& gAttributes, Graphics& graphics)
{
    while (node) {
        char* nodeName = node->name();
        cout << nodeName << " - ";


        xml_attribute<>* currentAttribute = node->first_attribute();
        if (strcmp(nodeName, "defs") == 0)
        {
            readLinearGr(node->first_node());
            node = node->next_sibling();
            continue;
        }

        vector<pair<string, string>> a;
        gAttributes.clear();
        while (currentAttribute != NULL)
        {
            char* attributeName = currentAttribute->name();
            char* attributeValue = currentAttribute->value();

            a.push_back({ attributeName, attributeValue });
            cout << "Attribute Name: " << attributeName << ", Attribute Value: " << attributeValue << endl;

            if (strcmp(nodeName, "g") == 0)
            {
                gAttributes.push_back({ attributeName, attributeValue }); // Store attributes of <g>
            }

            currentAttribute = currentAttribute->next_attribute();
        }

        if (strcmp(nodeName, "text") == 0) {
            a.push_back({ "text", node->value() });
        }
        for (int i = 0; i < a.size(); i++)
        {
            cout << a[i].first << " " << a[i].second << endl;
        }
        setProperties(nodeName, a, graphics);
        if (strcmp(nodeName, "g") == 0) {
            // If the node is <g>, apply its attributes to its children
            applyAttributesToChildren(node, gAttributes);
            read(node->first_node(), gAttributes, graphics);
        }

        node = node->next_sibling();
    }
}

void DrawSVGFile(wstring& filename, HDC hdc) {
    Graphics graphics(hdc);

    xml_document<> doc;

    ifstream file(filename);
    vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    xml_node<>* rootNode = doc.first_node();
    xml_node<>* node = rootNode->first_node();

    vector<pair<string, string>> gAttributes;
    read(node, gAttributes, graphics);

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    HDC                 hdc;
    PAINTSTRUCT         ps;




    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG Demo"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps);
        Graphics graphics(hdc);
        graphics.SetSmoothingMode(SmoothingModeAntiAlias);
        int argc;
        LPWSTR commandLine = GetCommandLineW();
        LPWSTR* argv = CommandLineToArgvW(commandLine, &argc);
        wstring svgFilename;

        if (argc > 1) {
            svgFilename = argv[1];
        }
        else {
            // Default SVG file name if not provided in command line
            svgFilename = L"instagram.svg";
        }
        DrawSVGFile(svgFilename, hdc);
        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc

ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;