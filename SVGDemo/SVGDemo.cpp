#include "stdafx.h"




void DrawSVGFile(string& filename, HDC hdc) {
    Graphics graphics(hdc);

    xml_document<> doc;

    ifstream file("sample.svg");
    vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    xml_node<>* rootNode = doc.first_node();
    xml_node<>* node = rootNode->first_node();

    while (node)
    {
        char* nodeName = node->name();
        //cout << nodeName << " - ";

        xml_attribute<>* currentAttribute = node->first_attribute();

        vector<pair<string, string>>a;
        while (currentAttribute != NULL)
        {
            char* attributeName = currentAttribute->name();
            char* attributeValue = currentAttribute->value();

            a.push_back({ attributeName, attributeValue });
            //std::cout << "Attribute Name: " << attributeName << ", Attribute Value: " << attributeValue << std::endl;
            currentAttribute = currentAttribute->next_attribute();
        }
        if (strcmp(nodeName, "text") == 0)
        {
            a.push_back({ "text", node->value() });
            //cout << node->value() << endl; 
        }
        setProperties(nodeName, a, graphics);

        node = node->next_sibling();
    }

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
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
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
   
   while(GetMessage(&msg, NULL, 0, 0))
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
   
   switch(message)
   {
   case WM_PAINT: {
       hdc = BeginPaint(hWnd, &ps);
       Graphics graphics(hdc);
       graphics.SetSmoothingMode(SmoothingModeAntiAlias);
       string svgFilename = "sample.svg";
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
