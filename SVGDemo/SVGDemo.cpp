#include "stdafx.h"



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
            svgFilename = L"svg-07.svg";
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