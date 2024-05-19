#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
	glEnd();
}

void drawLand() {
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-3.5f, -3.5f, 0.5f);
	glVertex3f(3.5f, -3.5f, 0.5f);
	glVertex3f(3.5f, 3.5f, 0.5f);
	glVertex3f(-3.5f, 3.5f, 0.5f);
	glEnd();
}

void drawWheel(float radius, float depth, int segments) {
	glBegin(GL_QUAD_STRIP);
	glColor3f(0, 0, 0);
	for (int i = 0; i <= segments; ++i) {
		float angle = (2.0f * 3.14159f / segments) * i;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex3f(x, y, 0);
		glVertex3f(x, y, depth);
	}
	glEnd();
}

void drawRectangle(int x, int  y, int z, float width, float height, float depth, GLfloat r, GLfloat g, GLfloat b) {
	glBegin(GL_QUADS);

	// Front face
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x, y + height, z);

	// Back face
	glColor3f(r, g, b);
	glVertex3f(x, y, z - depth);
	glVertex3f(x + width, y, z - depth);
	glVertex3f(x + width, y + height, z - depth);
	glVertex3f(x, y + height, z - depth);

	// Top face
	glColor3f(r, g, b);
	glVertex3f(x, y + height, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x + width, y + height, z - depth);
	glVertex3f(x, y + height, z - depth);

	// Bottom face
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y, z - depth);
	glVertex3f(x, y, z - depth);

	// Left face
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - depth);
	glVertex3f(x, y + height, z - depth);
	glVertex3f(x, y + height, z);

	// Right face
	glColor3f(r, g, b);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y, z - depth);
	glVertex3f(x + width, y + height, z - depth);
	glVertex3f(x + width, y + height, z);
	glEnd();
}

void drawBike(int x, int y, int z, int w, int h,int frontWheelAngle,int backWheelAngle) {
	//back wheel
	glPushMatrix();
	glTranslatef(x-0.5, y, z);
	glRotatef(backWheelAngle, 0, 1, 0);
	drawWheel(0.2, 0.05f, 100);
	glPopMatrix();
	//front wheel
	glPushMatrix();
	glTranslatef(x + 0.5, y, z);
	glRotatef(frontWheelAngle, 0, 1, 0);
	drawWheel(0.2, 0.05f, 100);
	glPopMatrix();
	//draw body
	glPushMatrix();
	glTranslatef(x - 0.75, y + 0.15, z + 0.05f);
	drawRectangle(0, 0, 0, 1.5f, 0.1f, 0.06f, 0, 0, 0);
	glPopMatrix();
	//draw hand
	glPushMatrix();
	glTranslatef(x + 0.6, y + 0.15, z + 0.05f);
	drawRectangle(0, 0, 0, 0.01f, 0.5f, 0.06f, 0, 0, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x + 0.6, y + 0.6, z + 0.125f);
	drawRectangle(0, 0, 0, 0.05f, 0.06f, 0.25f, 0, 0, 0);
	glPopMatrix();
	//draw seat
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.15, z + 0.05f);
	drawRectangle(0, 0, 0, 0.01f, 0.3f, 0.06f, 0, 0, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x, y + 0.45, z + 0.07f);
	drawRectangle(0, 0, 0, 0.2f, 0.06f, 0.15f, 0, 0, 0);
	glPopMatrix();
}

void drawCube() {
	glBegin(GL_QUADS);

	glColor3f(70.0 / 255, 25.0 / 255, 30.0 / 255);

	// Front face
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Top face
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Bottom face
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Right face
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	// Left face
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();
}

void drawRoof() {
	glBegin(GL_QUADS);
	// Bottom face
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Right face
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	// Left face
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Front face
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
}

void drawSeparator() {
	glBegin(GL_QUADS);
	// Right face
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	// Left face
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Front face
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
}

void drawBuilding(int theta1, int theta2) {
	// first floor
	glPushMatrix();
	glScaled(0.25f, 0.25f, 0.25f);
	drawCube();

	// door matrix
	glPushMatrix();
	glTranslated(0.51, -0.5, 0.1);
	glRotated(90, 0, 1, 0);
	glRotated(-theta1, 0, 1, 0);
	drawRectangle(0, 0, 0, 0.25, 0.65, 0.0, (float) 150 / 255, (float) 75 / 255, 0);
	glPopMatrix();
	
	// windows matrix
	glPushMatrix();
	glTranslated(0.51, 0.2, -0.2);
	glRotated(90, 0, 1, 0);
	
	// right window matrix
	glPushMatrix();
	glTranslated(0.1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(theta2, 0, 1, 0);
	drawRectangle(0, 0, 0, 0.15, 0.15, 0.0, (float)150 / 255, (float)75 / 255, 0);
	glPopMatrix();
	
	// left window matrix
	glPushMatrix();
	glTranslated(-0.5, 0, 0);
	glRotated(-theta2, 0, 1, 0);
	drawRectangle(0, 0, 0, 0.15, 0.15, 0.0, (float)150 / 255, (float)75 / 255, 0);
	glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();

	// separator
	glPushMatrix();
	glTranslated(0.0f, 0.14f, 0.0f);
	glScaled(0.25f, 0.03f, 0.25f);
	drawSeparator();
	glPopMatrix();

	// second floor
	glPushMatrix();
	glTranslated(0.0f, 0.28f, 0.0f);
	glScaled(0.25f, 0.25f, 0.25f);
	drawCube();

	// windows matrix
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	
	// right window
	glPushMatrix();
	glTranslated(0.25, 0.2, 0.51);
	glRotated(180, 0, 1, 0);
	glRotated(theta2, 0, 1, 0);
	drawRectangle(0, 0, 0, 0.15, 0.15, 0.0, (float)150 / 255, (float)75 / 255, 0);
	glPopMatrix();
	
	// left window
	glPushMatrix();
	glTranslated(-0.30, 0.2, 0.51);
	glRotated(-theta2, 0, 1, 0);
	drawRectangle(0, 0, 0, 0.15, 0.15, 0.0, (float)150 / 255, (float)75 / 255, 0);
	glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();

	// roof
	glPushMatrix();
	glTranslated(0.0f, 0.456f, 0.0f);
	glScaled(0.25f, 0.1f, 0.25f);
	drawRoof();
	glPopMatrix();
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
	int  iPixelFormat;
	static int w,h;

	static double x0 = 10, y0 = 11, z0 = 10;
	static double x = 0, y = 0, z = 0;

	static double landScale = 3;

	static double buildingScale = 12;
	static int buildingDoorTheta = 0;
	static int buildingDoorDirection = 1;
	static int buildingWindowsTheta = 0;
	static int buildingWindowsDirection = 1;
	static bool isBuildingDoorMoving = false;
	static bool isBuildingWindowsMoving = false;

	static double bikeScale = 1.5;
	static double bikeTheta = 1;
	static double bikeRadius = 3;
	static int bikeDirection = 1;
	static bool isBikeMoving = false;
	static int bikeFrontAngle = 0;
	static int bikeBackAngle = 0;

	SetTimer(hwnd, 1, 10, NULL);
	switch (m)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);
		hgl=wglCreateContext(hdc);
		wglMakeCurrent(hdc,hgl);
		glClearColor(0, 0.75, 0, 0);
		break;
	case WM_SIZE:
		w = LOWORD(lp);
		h = HIWORD(lp);
		glViewport(0, 0, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glFlush();
		SwapBuffers(hdc);

		x = x0;
		y = y0;
		z = z0;

		break;
	case WM_TIMER:

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, 16.0 / 9.0, 1, 50);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

		//drawAxes();

		glPushMatrix();
		glRotated(90, 1, 0, 0);
		glScaled(landScale, landScale, landScale);
		glTranslated(0, 0, -0.5);
		drawLand();
		glPopMatrix();

		glPushMatrix();
		glScaled(buildingScale, buildingScale, buildingScale);
		glTranslated(0, 0.125, 0);
		glRotated(-90, 0, 1, 0);
		drawBuilding(buildingDoorTheta, buildingWindowsTheta);
		glPopMatrix();

		glPushMatrix();
		glScaled(bikeScale, bikeScale, bikeScale);
		glRotated(bikeTheta, 0, 1, 0);
		glTranslated(-bikeRadius, 0, 0);
		glTranslated(0, 0.2, 0);
		glRotated(-90, 0, 1, 0);
		drawBike(0, 0, 0, w, h,bikeFrontAngle,bikeBackAngle);
		glPopMatrix();

		glFlush();
		SwapBuffers(hdc);

		if (isBikeMoving) {
			bikeTheta += bikeDirection;
		}

		if (isBuildingDoorMoving) {
			if (buildingDoorTheta >= 0 && buildingDoorTheta <= 160)
			{
				buildingDoorTheta += buildingDoorDirection;
			}
			else
			{
				isBuildingDoorMoving = false;
				if (buildingDoorTheta < 0)
				{
					buildingDoorTheta = 0;
				}
				else if (buildingDoorTheta > 160)
				{
					buildingDoorTheta = 160;
				}
			}
		}

		if (isBuildingWindowsMoving) {
			if (buildingWindowsTheta >= 0 && buildingWindowsTheta <= 160)
			{
				buildingWindowsTheta += buildingWindowsDirection;
			}
			else
			{
				isBuildingWindowsMoving = false;
				if (buildingWindowsTheta < 0)
				{
					buildingWindowsTheta = 0;
				}
				else if (buildingWindowsTheta > 160)
				{
					buildingWindowsTheta = 160;
				}
			}
		}

		break;
	case WM_KEYDOWN:
	{
		if (GetKeyState('0') & GetKeyState(VK_CONTROL) & 0x8000) {
			x = x0;
			y = y0;
			z = z0;
		}
		else if (wp == VK_UP)
		{
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				y += 1.0;
			}
			else
			{
				z += 0.1;
			}
		}
		else if (wp == VK_DOWN)
		{
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				y -= 1.0;
			}
			else
			{
				z -= 0.1;
			}
		}
		else if (wp == VK_RIGHT)
		{
			x += 0.1;
		}
		else if (wp == VK_LEFT)
		{
			x -= 0.1;
		}
		else if (GetKeyState('L') & 0x8000)
		{
			if (bikeFrontAngle == 0) {
				bikeFrontAngle = 30;
			}
			else
			{
				bikeFrontAngle = 0;
			}
		}
		else if (GetKeyState('R') & 0x8000)
		{
			if (bikeBackAngle == 0) {
				bikeBackAngle = -30;
			}
			else
			{
				bikeBackAngle = 0;
			}
		}
		else if (GetKeyState('B') & 0x8000)
		{
			if (bikeRadius > 1.7) {
				bikeRadius -= 0.1;
			}
		}
		else if (GetKeyState('F') & 0x8000)
		{
			if (bikeRadius < 6) {
				bikeRadius += 0.1;
			}
		}
		else if (GetKeyState('O') & 0x8000 & GetKeyState(VK_SHIFT))
		{
			isBuildingWindowsMoving = true;
			buildingWindowsDirection = 1;
		}
		else if (GetKeyState('O') & 0x8000)
		{
			isBuildingDoorMoving = true;
			buildingDoorDirection = 1;
		}
		else if (GetKeyState('C') & 0x8000 & GetKeyState(VK_SHIFT))
		{
			isBuildingWindowsMoving = true;
			buildingWindowsDirection = -1;
		}
		else if (GetKeyState('C') & 0x8000)
		{
			isBuildingDoorMoving = true;
			buildingDoorDirection = -1;
		}
		break;
	}
	case WM_LBUTTONDOWN:
		isBikeMoving = true;
		break;
	case WM_RBUTTONDOWN:
		isBikeMoving = false;
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