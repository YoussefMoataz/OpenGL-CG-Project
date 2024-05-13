#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

void drawTriangle() {
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1); glVertex2d(0, 0.3);
	glColor3f(0, 0, 1); glVertex2d(-0.3, -0.3);
	glColor3f(0, 0, 1); glVertex2d(0.3, -0.3);
	glEnd();
}

void drawCube() {
	glBegin(GL_QUADS);

	// Front face
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glColor3f(0.0f, 1.0f, 0.0f); // Green color
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Top face
	glColor3f(0.0f, 0.0f, 1.0f); // Blue color
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Bottom face
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Right face
	glColor3f(1.0f, 0.0f, 1.0f); // Magenta color
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	// Left face
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan color
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();
}

void drawLand() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
}

LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
	static PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
	1,                     // version number  
	PFD_DRAW_TO_WINDOW |   // support window  
	PFD_SUPPORT_OPENGL |   // support OpenGL  
	PFD_DOUBLEBUFFER,      // double buffered  
	PFD_TYPE_RGBA,         // RGBA type  
	24,                    // 24-bit color depth  
	0, 0, 0, 0, 0, 0,      // color bits ignored  
	0,                     // no alpha buffer  
	0,                     // shift bit ignored  
	0,                     // no accumulation buffer  
	0, 0, 0, 0,            // accum bits ignored  
	32,                    // 32-bit z-buffer  
	0,                     // no stencil buffer  
	0,                     // no auxiliary buffer  
	PFD_MAIN_PLANE,        // main layer  
	0,                     // reserved  
	0, 0, 0                // layer masks ignored  
	};
	static HDC hdc;
	static HGLRC hgl;
	static int x[3], y[3],w,h;
	static int count = 0;
	int  iPixelFormat;
	static double theta = 1;
	SetTimer(hwnd, 1, 10, NULL);
	switch (m)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);
		hgl=wglCreateContext(hdc);
		wglMakeCurrent(hdc,hgl);
		glClearColor(0, 0, 0, 0);
		break;
	case WM_SIZE:
		w = LOWORD(lp);
		h = HIWORD(lp);
		glViewport(0, 0, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glFlush();
		SwapBuffers(hdc);
		break;
	case WM_LBUTTONDOWN:	
		break;
	case WM_TIMER:

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		glRotated(theta, 0, 0, 1);
		glPushMatrix();
		glRotated(70, 1, 0, 0);
		drawLand();
		glPopMatrix();

		glLoadIdentity();
		glPushMatrix();
		drawTriangle();
		glPopMatrix();

		glFlush();
		SwapBuffers(hdc);

		theta+= 1;

		break;
	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hgl);
		ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, m, wp, lp);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR c, int ns)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hInstance = hi;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MyClass";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(L"MyClass", L"Computer Graphics", WS_OVERLAPPEDWINDOW, 0, 0, 1000, 800, NULL, NULL, hi, 0);
	ShowWindow(hwnd, ns);
	UpdateWindow(hwnd);
	SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}