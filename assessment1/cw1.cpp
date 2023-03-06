#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "windows.h"
#define MAX_CHAR 128
using namespace std;
int width = 800;
int height = 800;
const double PI = acos(-1.0);
BOOLEAN tap = false;//�����ж�����Ƿ񱻵��
int time_interval = 16; // declare refresh interval in ms
GLfloat step = 0; // ���ƽ���ɡ�½��ٶ�
GLfloat step1 = 0;//���ƺؿ����ٶ�
typedef struct { GLfloat x, y; } point1; // define a 2D point
point1 p0 = { 0,1.2 }; // set initial co-ordinate values of the point
point1 p1 = { 0,-0.6 };//�ؿ��ĳ�ʼ���꣬Ϊһ����
float scale = 0;//�ؿ���������
float scale1 = 0;//ѩ���ı任
void BAP(float x, float y);
void BAP1(float x, float y);
void mouse_input(int button, int state, int x, int y);
float r = 18.0,t=-6.0;             //r����Ϊt������ʹ�ö�����ִ����һ��t�ı仯���ں�պý��Ϸ����½���r
void text();
void selectFont();
void when_in_mainloop() { // idle callback function
	glutPostRedisplay(); // force opengl to redraw the current window
}
void OnTimer(int value)
{
	if (r >=0) {
		r -= step*10;
	}
	if (t < 6) {
		t += step*10;
	}
	if (p0.y > -0.7) {
		p0.y -= step;
	}
	if (p0.y <= -0.7&&scale<1) {
		scale += step1*1.2;
	}
	if (scale >= 1&&scale1<1) {
		scale1 += step1 * 1.2;
	}
	
	
	glutTimerFunc(time_interval, OnTimer, 1);
}
//void keyboard_input(unsigned char key, int x, int y) {// keyboard interaction
//	if (key == 'q' || key == 'Q')
//		exit(0);
//	else if (key == 't' || key == 'T')
//		t += 0.05;
//	else if (key == 'b' || key == 'B')
//		t -= 0.05;
//	else if (key == 'r' || key == 'R')
//		r--;
//	else if (key == 'a' || key == 'A')
//		r++;
//	else if (key == 'i' || key == 'I')
//		s += 0.01;
//	else if (key == 'd' || key == 'D')
//		s -= 0.01;
//}
void mouse_input(int button, int state, int x, int y) // mouse interactions
{
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_DOWN) {
		step=0.01;
		/*printf("%d,%d\n", x, y);*/
		if (x >= 360 && x <= 440 && y <= 740 && y >= 640) {//�趨�������Χ
			step1 = 0.01;
			tap = true;
		}
	}
}

//Boxandparachute
//Box
void BAP1(float x, float y) {
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPushMatrix();
	if (t < 6) {               //ʵ�ֽ���ɡ����Ʒ�е�Ʈ���½�
		glRotatef(t, 0, 0, 1);
	}
	else{
		glRotatef(r, 0, 0, 1);
	}
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 0.0, 0.0);
	glVertex2f(x - 0.1, y + 0.06);
	glVertex2f(x + 0.1, y + 0.06);
	glVertex2f(x + 0.1, y - 0.1);
	glVertex2f(x - 0.1, y - 0.1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 0.0, 0.0);
	glVertex2f(x - 0.12, y + 0.06);
	glVertex2f(x + 0.12, y + 0.06);
	glVertex2f(x + 0.12, y + 0.1);
	glVertex2f(x - 0.12, y + 0.1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 1.0, 0.0);
	glVertex2f(x - 0.02, y + 0.1);
	glVertex2f(x + 0.02, y + 0.1);
	glVertex2f(x + 0.02, y - 0.1);
	glVertex2f(x - 0.02, y - 0.1);
	glEnd();
	glPopMatrix();
	glColor3f(0, 0, 0);
	glLineWidth(0.01);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(x - 0.12, y + 0.06);
	glVertex2f(x + 0.12, y + 0.06);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(x - 0.06, y + 0.12);
	glVertex2f(x - 0.04, y + 0.15);
	glVertex2f(x, y + 0.1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(x + 0.08, y + 0.11);
	glVertex2f(x + 0.06, y + 0.13);
	glVertex2f(x, y + 0.1);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}
//����ɡ
void BAP(float x,float y)
{
	glPushMatrix();
	if (t < 6) {
		glRotatef(t, 0, 0, 1);
	}
	else {
		glRotatef(r, 0, 0, 1);
	}
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(x - 0.3, y + 0.5);
	glVertex2f(x, y + 0.1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(x, y + 0.5);
	glVertex2f(x , y + 0.1);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(x +0.3, y + 0.5);
	glVertex2f(x, y + 0.1);
	glEnd();
	glPopMatrix();
	float R = 0.3f;
	int n = 200;//�����n��ʾ�ö���λ���Բ�ľ��ȣ����Կ������󾫶�
	glColor3f(0, 0.3, 0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	/*
		��ʾ�����»����ĵ���еĲ������������γɶ����
		���ƵĻ���GL_LINE_STRIP��GL_LINE_LOOP��GL_POINT��
	*/
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		float scope = R * sin(2 * PI * i / n);
		if (scope >= 0)
		{
			glVertex2f(x + R * cos(2 * PI * i / n), y+0.5 + scope);
		}
		
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

//�ؿ�����

//�ؿ��ϵ�ѩ������
#define N 3//�ݹ����
#define C 0.017453//����cosX�Ƕȵ�һ��ϵ��
typedef float point[2];
point vertex[3] = { {-0.5,0.1},{0.5,0.1},{0,0.8} };//�ֱ������ҡ���
float theta = 0;//��ʼ�Ƕ�

	void draw_line(point p1, point p2)
	{
		glBegin(GL_LINES);
		glVertex2fv(p1);
		glVertex2fv(p2);
		glEnd();
	}
	//�ݹ飬һ��Ϊ��������ȷ����������
	void divide_line(point firstPoint, point secondPoint, int n, float theta)//theta������ѧ�Ƕ��Ǹ�ϣ����ĸceiTa
	{
		if (n > 0)
		{
			point p[3];//���� ��ð�����������ε�������
			float length_X, length_Y, length;
			length_X = (secondPoint[0] - firstPoint[0])*scale1;//
			length_Y = (secondPoint[1] - firstPoint[1])*scale1;
			length = sqrt(length_X * length_X + length_Y * length_Y) / 3;//ÿ�ε������������α߳�����ΪԽ��ԽС�

			//ȷ���������ε��������涥������
			p[0][0] = firstPoint[0] + length_X / 3;
			p[0][1] = firstPoint[1] + length_Y / 3;
			p[2][0] = secondPoint[0] - length_X / 3;
			p[2][1] = secondPoint[1] - length_Y / 3;
			//ȷ���������εĶ������꣬�����Ǹ���ð�����ļ��
			p[1][0] = p[0][0] + length * cos((theta - 60.0) * C);
			p[1][1] = p[0][1] + length * sin((theta - 60.0) * C);
			
				divide_line(firstPoint, p[0], n - 1, theta);
				divide_line(p[0], p[1], n - 1, theta - 60);
				divide_line(p[1], p[2], n - 1, theta + 60);
				divide_line(p[2], secondPoint, n - 1, theta);
			
		}
		else
		{
			//printf("���ԣ�������һ��n < 0\n");
			draw_line(firstPoint, secondPoint);
		}
	}



//�ؿ�
void Card(float x,float y,float s) {//��Ӧ��ʼ����ͷŴ���
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0, 0.0);
	glVertex2f(x-0.7*s, y+0.4*s);
	glVertex2f(x-0.7*s, y+1.4*s);
	glVertex2f(x+0.7*s, y+1.4*s);
	glVertex2f(x+0.7*s, y+0.4*s);
	glEnd();
	//Draw dotted line
	glEnable(GL_LINE_STIPPLE);//�򿪻���ģʽ
	glLineStipple(3, 0X00FF);//�������ߵ�ģʽ
	glColor3f(1, 1, 0.8);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x-0.7*s, y+1.4*s); glVertex2f(x+0.7*s, y+1.4*s);
	glEnd();
	glColor3f(1, 1, 0.8);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x-0.7*s, y+1.4*s); glVertex2f(x-0.7*s, y+0.4*s);
	glEnd();
	glColor3f(1, 1, 0.8);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x-0.7*s, y+0.4*s); glVertex2f(x+0.7*s, y+0.4*s);
	glEnd();
	glColor3f(1.0, 1.0, 0.8);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x+0.7*s, y+0.4*s); glVertex2f(x+0.7*s, y+1.4*s);
	glEnd();
}

//����ؿ�����
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}
void text() {
	//Draw 2D text
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.325, 0.3);
	drawString("Happy New Year");
}




//Draw houses
void Houses()
{
	glBegin(GL_POLYGON);
	glColor3f(0.4,0.3,0.0);
	glVertex2f(-0.9,-0.8);
	glVertex2f(-0.65, -0.8);
	glVertex2f(-0.65, -0.6);
	glVertex2f(-0.9, -0.6);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.95, -0.6);
	glVertex2f(-0.7725, -0.4);
	glVertex2f(-0.6, -0.6);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex2f(-0.78, -0.72);
	glVertex2f(-0.78, -0.64);
	glVertex2f(-0.7, -0.64);
	glVertex2f(-0.7, -0.72);
	glEnd();
	glLineStipple(1, 0XFFFF);
	glColor3f(0, 0, 0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2f(-0.782, -0.722);
	glVertex2f(-0.782, -0.638);
	glVertex2f(-0.782, -0.638);
	glVertex2f(-0.698, -0.638);
	glVertex2f(-0.698, -0.638);
	glVertex2f(-0.698, -0.722);
	glVertex2f(-0.698, -0.722);
	glVertex2f(-0.782, -0.722);
	glVertex2f(-0.78, -0.68);
	glVertex2f(-0.7, -0.68);
	glVertex2f(-0.74, -0.722);
	glVertex2f(-0.74, -0.638);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.3, 0);
	glVertex2f(-0.9f, -0.5f);
	glVertex2f(-0.83f, -0.43f);
	glVertex2f(-0.83f, -0.38f);
	glVertex2f(-0.9f, -0.38f);
	glVertex2f(-0.9f, -0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0);
	glVertex2f(-0.92f, -0.38f);
	glVertex2f(-0.81f, -0.38f);
	glVertex2f(-0.81f, -0.37f);
	glVertex2f(-0.92f, -0.37f);
	glEnd();
	//Smoke from the chimney
	float R = 0.01f;
	int n = 180;
	float y = -0.35;
	glColor3f(0.9, 0.9, 0.9);
	for (int count = 0; count < 3; count++) {
		glBegin(GL_POLYGON);
		R *= (count + 1);
		y += count * 0.05;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			glVertex2f(-0.86 + 2.0 * R * cos(2 * PI * i / n), y + R * sin(2 * PI * i / n));
		}
		glEnd();
	}
	


}

//Draw a Christmas tree
void ChristmasTree()
{
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.1, 0);
	glVertex2f(0.8, -0.8);
	glVertex2f(0.9, -0.8);
	glVertex2f(0.9, -0.65);
	glVertex2f(0.8, -0.65);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.8, 0.0);
	glVertex2f(0.7, -0.65);
	glVertex2f(1, -0.65);
	glVertex2f(0.85, -0.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.3, 0.8, 0.0);
	glVertex2f(0.72, -0.52);
	glVertex2f(0.98, -0.52);
	glVertex2f(0.85, -0.4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.8, 0.0);
	glVertex2f(0.74, -0.42);
	glVertex2f(0.96, -0.42);
	glVertex2f(0.85, -0.3);
	glEnd();
}

//Draw the snow
void Snow()
{
	float R = 0.02f;
	int n = 180;//�����n��ʾ�ö���λ���Բ�ľ��ȣ����Կ������󾫶�
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	/*
		��ʾ�����»����ĵ���еĲ������������γɶ����
		���ƵĻ���GL_LINE_STRIP��GL_LINE_LOOP��GL_POINT��
	*/
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(-0.96+R * cos(2 * PI * i / n), -0.58+R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(-0.7725,-0.4);
	glVertex2f(-0.95, -0.6);
	glVertex2f(-0.97, -0.56);
	glVertex2f(-0.7765, -0.3564);
	glVertex2f(-0.7725, -0.4);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(-0.7725 + R * cos(2 * PI * i / n), -0.38 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(-0.7725, -0.4);
	glVertex2f(-0.61, -0.585);
	glVertex2f(-0.565, -0.58);
	glVertex2f(-0.77, -0.356);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(-0.59 + R * cos(2 * PI * i / n), -0.58 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(0.69 + R * cos(2 * PI * i / n), -0.63 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0.7, -0.65);
	glVertex2f(0.825, -0.52);
	glVertex2f(0.78, -0.52);
	glVertex2f(0.67, -0.62);
	glVertex2f(0.7, -0.65);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(0.71 + R * cos(2 * PI * i / n), -0.5 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0.72, -0.52);
	glVertex2f(0.826, -0.42);
	glVertex2f(0.78, -0.42);
	glVertex2f(0.7, -0.48);
	glVertex2f(0.72, -0.52);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(0.726 + R * cos(2 * PI * i / n), -0.40 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0.74, -0.42);
	glVertex2f(0.85, -0.3);
	glVertex2f(0.85, -0.256);
	glVertex2f(0.71, -0.39);
	glVertex2f(0.74, -0.42);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(0.97 + R * cos(2 * PI * i / n), -0.40 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0.96, -0.42);
	glVertex2f(0.85, -0.3);
	glVertex2f(0.85, -0.256);
	glVertex2f(0.99, -0.39);
	glVertex2f(0.96, -0.42);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(0.99 + R * cos(2 * PI * i / n), -0.5 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0.98, -0.52);
	glVertex2f(0.87, -0.42);
	glVertex2f(0.916, -0.42);
	glVertex2f(1, -0.48);
	glVertex2f(0.98, -0.52);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(1 + R * cos(2 * PI * i / n), -0.625 + R * sin(2 * PI * i / n));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(1, -0.65);
	glVertex2f(0.87, -0.52);
	glVertex2f(0.92, -0.52);
	glVertex2f(1, -0.6);
	glVertex2f(1, -0.65);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	{
		glVertex2f(0.85 + R * cos(2 * PI * i / n), -0.28 + R * sin(2 * PI * i / n));
	}
	glEnd();
}

//Draw the star above Christmas Tree
void Star()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(0.85, -0.3);
	glVertex2f(0.85, -0.23);
	glEnd();
	GLfloat r1 = 0.06f;
    GLfloat r2 = 0.03f;
	GLfloat Pi = 3.1415926536f;
	GLfloat pointA[2] = { 0.85, r1-0.2 };
	GLfloat pointB[2] = { 0.85+r1 * cos(18 * Pi / 180), r1 * sin(18 * Pi / 180)-0.2 };
	GLfloat pointC[2] = { 0.85+r1 * cos(54 * Pi / 180), -r1 * sin(54 * Pi / 180)-0.2 };
	GLfloat pointD[2] = { 0.85-r1 * cos(54 * Pi / 180), -r1 * sin(54 * Pi / 180)-0.2 };
	GLfloat pointE[2] = { 0.85-r1 * cos(18 * Pi / 180), r1 * sin(18 * Pi / 180)-0.2 };
	GLfloat pointa[2] = { 0.85, -r2-0.2 };
	GLfloat pointb[2] = { 0.85-r2 * cos(18 * Pi / 180), -r2 * sin(18 * Pi / 180)-0.2 };
	GLfloat pointc[2] = { 0.85-r2 * cos(54 * Pi / 180), r2 * sin(54 * Pi / 180)-0.2 };
	GLfloat pointd[2] = { 0.85+r2 * cos(54 * Pi / 180), r2 * sin(54 * Pi / 180)-0.2 };
	GLfloat pointe[2] = { 0.85+r2 * cos(18 * Pi / 180), -r2 * sin(18 * Pi / 180)-0.2 };
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 0);
	glVertex2fv(pointA);
	glVertex2fv(pointd);
	glVertex2fv(pointd);
	glVertex2fv(pointB);
	glVertex2fv(pointe);
	glVertex2fv(pointC);
	glVertex2fv(pointa);
	glVertex2fv(pointD);
	glVertex2fv(pointb);
	glVertex2fv(pointE);
	glVertex2fv(pointc);
	glEnd();
	
}

void display(void)
{
	//glClearColor(0, 0, 1, 1);
	//glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw horizon line
	/*glLineStipple(1, 0XFFFF);
	glColor3f(0, 0, 0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(-1, -0.8f);
	glVertex2f(1, -0.8f);
	glEnd();*/
	//Draw Blue gradient background
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.1);
	glVertex2f(-1, 1);
	glColor3f(1, 1, 1);
	glVertex2f(-1, -0.8);
	glColor3f(1, 1, 1);
	glVertex2f(1, -0.8);
	glColor3f(0, 0, 0.1);
	glVertex2f(1, 1);
	glEnd();
	Houses();
	ChristmasTree();
	Snow();
	Star();
	
	/*glPushMatrix();*/
	/*glTranslatef(x, y, 0); */// the order of these transformations may affect the result
	//glScalef(s, s, 0); // because of the non-commutative features
	//glRotatef(r, 0, 0, 1); // here the translation is applied last
	/*DrawTriangles();*/
	if (p0.y > -0.7) {
		glPushMatrix();
		BAP(p0.x, p0.y);
		BAP1(p0.x, p0.y);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		BAP1(p0.x, p0.y);
		glPopMatrix();
		if (tap == true) {
			Card(p1.x,p1.y,scale);
			if (scale >= 1) {
				glColor3f(1, 1, 1);
				glPushMatrix();
				divide_line(vertex[0], vertex[1], N, theta);//�ױ�
				divide_line(vertex[1], vertex[2], N, theta + 120);//�ұ�
				divide_line(vertex[2], vertex[0], N, theta - 120);//���
				glPopMatrix();
				if (scale1 >= 1) {
					text();
				}
			}
			
		}
	}

	/*glPopMatrix();*/
	glutSwapBuffers();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("New Year's Greeting Card");
	glClearColor(1.0f, 1.0f, 1.0f,0);
	glutDisplayFunc(display);
	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer, 1);
	/*glutKeyboardFunc(keyboard_input);*/
	glutMouseFunc(mouse_input); // mouse callback function
	glutMainLoop();
}