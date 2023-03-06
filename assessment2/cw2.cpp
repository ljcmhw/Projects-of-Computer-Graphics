#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector"
#include <iostream>

using namespace std;

int width = 600; //Default window size
int height = 400;
const double PI = acos(-1.0);
float FOV = 90; //Field Of View
float Zoom = 1.5; //Zoom amount
float X0 = 0.0; //Camera position
float Y0 = 150.0;
float Z0 = -500.0;
float XRef = 0.0; //Look At reference point
float YRef = 0.0;
float ZRef = 0.0;
float XUp = 0.0; //Up vector
float YUp = 1.0;
float ZUp = 0.0;
float PoleOffset = 750.0;
float BuildingOffset = -250.0;
float Acceleration = 0; //Speed of animation
float AnimationOffset = 0.0; //Animation offsets for various objects
float LightPoleOffset = 750.0;
float TreeOffset = 0.0;
float doorappear = 0.0;//ת���ų���ʱ��
float dooroffset = 0.0;//ת���ŵ��ƶ�
GLint imagewidth0, imagewidth1, imagewidth2;
GLint imageheight0, imageheight1, imageheight2;
GLint pixellength0, pixellength1, pixellength2;
vector<GLubyte*>p; // Similar to GLubyte* for program 3 but for 3 images (so a vector)
GLuint texture;
GLuint texture1;
GLfloat angle = 0;
//���õƹ�λ��
GLfloat light_x = 0.0;
GLfloat light_y = 500.0;
GLfloat light_z = 2900.0;
//���û����Ƶĳ�ʼ���ȣ�ҹ��
float ambientvalue = 0.8;
//���û����Ƶĳ�ʼ���ȣ����磩
float ambientvalue2 = 0.0;
//���Ƴ����л��������ĳ��ֺ���ʧ��
int selfswitch = 0;

float r = 0;
GLfloat step = 1; // declare step
int time_interval = 16; // declare refresh interval in ms
void OnTimer(int value) {
	r += step;
	if (r >= 360)
		r = 0;
	else if (r <= 0)
		r = 359;
	glutTimerFunc(time_interval , OnTimer, 1);
}








//��ʼ������
void initlight(float ambientvalue) {
	//���õƹ�0
	
	
	
		GLfloat light_position0[] = { light_x, light_y, light_z, 0 }; // Directional light�����ĸ�������Ϊ-1��ʾ��Դ����Զ��Ϊ1���ʾǰ���������趨��λ��,0Ϊƽ�й�
		GLfloat light_diffuse0[] = { 5,5,5,1 };//ǰ�������������������ȣ����һ����������͸����
		GLfloat light_specular0[] = { 0,0,0,0 };//����һ����ͬ��ֻ�����ǵ������ߵľ��淴��ǿ��
		GLfloat light_ambient0[] = { ambientvalue,ambientvalue,ambientvalue,1 };//���û����⣬ǰ����������rgbֵ�����ĸ���ʾ͸����
		//0�ŵ�
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);  //���淴���
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);   //ɢ�������

		//��·���ݼ��Ϲ�Դ(�۹�ƣ�
		GLfloat light_position1[] = { -10, 20, 100, 1 }; // Directional light�����ĸ�������Ϊ-1��ʾ��Դ����Զ��Ϊ1���ʾǰ���������趨��λ��,0Ϊƽ�й�
		GLfloat light_diffuse1[] = { 15,15,0,1 };//ǰ�������������������ȣ����һ����������͸����
		GLfloat light_specular1[] = { 0.5,0.5,0.5,1 };//����һ����ͬ��ֻ�����ǵ������ߵľ��淴��ǿ��
		GLfloat light_ambient1[] = { 0.0,0.0,0.0,1 };//���û����⣬ǰ����������rgbֵ�����ĸ���ʾ͸����
		GLfloat spot_direction1[] = { 1.0, 0.0, 0.0 };//���þ۹�Ƶĳ���
		//1�ŵ���(����·��Ч����
		//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);//��ʾ���ߵ�˥��
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);//��ʾ�۹�̶ȣ���ֵԽ���ʾ��Խ�۽�����
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);  //���淴���
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);   //ɢ�������
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);//���þ۹��Ч�������һ��������ʾ�н�

		//2�ŵƣ��������ƣ�
		//GLfloat light_position2[] = { 0, 50, 100, 1 }; // Directional light�����ĸ�������Ϊ-1��ʾ��Դ����Զ��Ϊ1���ʾǰ���������趨��λ��,0Ϊƽ�й�
		//GLfloat light_diffuse2[] = { 15,15,15,1 };//ǰ�������������������ȣ����һ����������͸����
		//GLfloat light_specular2[] = { 3,3,3,1 };//����һ����ͬ��ֻ�����ǵ������ߵľ��淴��ǿ��
		//GLfloat light_ambient2[] = { 0.0,0.0,0.0,1 };//���û����⣬ǰ����������rgbֵ�����ĸ���ʾ͸����
		//GLfloat spot_direction2[] = { 0.0, 0.0, 1.0 };//���þ۹�Ƶĳ���
		//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);//��ʾ���ߵ�˥��
		//glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);//��ʾ�۹�̶ȣ���ֵԽ���ʾ��Խ�۽�����
		//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
		//glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
		//glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		//glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);  //���淴���
		//glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);   //ɢ�������
		//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 145.0f);//���þ۹��Ч�������һ��������ʾ�н�

		glEnable(GL_LIGHTING);   //����
		/*glEnable(GL_LIGHT1);*///����1#��ʹ��
		//glEnable(GL_LIGHT2);//����2#��ʹ��
		glEnable(GL_LIGHT0);//����0#��ʹ��
		/*glEnable(GL_LIGHT1);*/
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST); //����Ȳ���
	
	
	
	
	
	//GLfloat light1_position[] = { 0, 150, -575 ,1};
	//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);  //���淴���
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);   //ɢ�������

	
	
}
//���ո�������£�С��ֹͣǰ��
void keyboard_input(unsigned char key, int x, int y) {
	if (key == ' ') {
		Acceleration = 0;
		glutPostRedisplay();
	}
	if ((key == 'w' || key == 'W') && Zoom < 2) {
		Zoom += 0.5;
	}
	if ((key == 's' || key == 'S') && Zoom > 0.5) {
		Zoom -= 0.5;
	}
}

//�������������£�С��������2ǰ��
void mouse_input(int button, int state, int x, int y) // mouse interactions
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Acceleration = 2;
	}
	
}

//��ȡ�����ı���ͼƬ
void Readimages(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
	GLubyte* pixeldata;
	FILE* pfile;
	fopen_s(&pfile, path, "rb");//��ȡ�ļ�
	if (pfile == 0) exit(0);
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	pixellength = imagewidth * 3;//����ÿһ�е����ص���
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;//�������е����ص���
	pixeldata = (GLubyte*)malloc(pixellength);//�����ڴ�
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);//�����ض�ȡ�ļ�
	fread(pixeldata, pixellength, 1, pfile);
	p.push_back(pixeldata);
	fclose(pfile);
}

//��ʼ������ͼƬ
void myinit(void) {
	/*glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);*/
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	Readimages("star.bmp", imagewidth0, imageheight0, pixellength0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
	glGenTextures(1, &texture); //����һ������װ��������
	glBindTexture(GL_TEXTURE_2D, texture); // target to which texture is bound and name of a texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(p[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//ʹ��modulate���ݵ�ǰ�����Զ���������Ĺ��պ�����
}

void myinit2(void) {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	Readimages("blank.bmp", imagewidth1, imageheight1, pixellength1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
	glGenTextures(1, &texture); //����һ������װ��������
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(p[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//ʹ��modulate���ݵ�ǰ�����Զ���������Ĺ��պ�����
}

//չʾ����ͼƬ���ǿգ�
void background() {
	GLfloat background1_diffuse[] = { 0.7,0.7,0.8,1 };
	GLfloat background1_ambient[] = { 0.9,0.9,1,1 };
	GLfloat background1_emission[] = { 0.0,0.0,0,1 };
	GLfloat background1_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, background1_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, background1_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, background1_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, background1_shininess);
	glTranslatef(7500, 0.0, 4000.0);
	glScalef(7500, 4800, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
	glEnd();
	glFlush();
}


//���ǿ��滻�ɰ���
void background2() {
	GLfloat background1_diffuse[] = { 0.7,0.7,0.8,1 };
	GLfloat background1_ambient[] = { 0.9,0.9,1,1 };
	GLfloat background1_emission[] = { 0.0,0.0,0,1 };
	GLfloat background1_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, background1_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, background1_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, background1_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, background1_shininess);
	glTranslatef(7500, 0.0, 4000.0);
	glScalef(7500, 4800, 1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
	glEnd();
	glFlush();
}


//�����ƶ����ƹ�仯
void animate()
{   
	
	//�ƹ���������
	if (ambientvalue > 0) {
		initlight(ambientvalue);
		ambientvalue -= 0.00008;
		if (ambientvalue < 0.4) {
			glEnable(GL_LIGHT1);
			if (selfswitch == 0) {
				myinit();
				selfswitch = 1;
			}
		}
	}
	if (ambientvalue <= 0 && ambientvalue2 <= 0.8) {
		initlight(ambientvalue2);
		glEnable(GL_LIGHT1);
		ambientvalue2 += 0.00008;
		if (ambientvalue2 > 0.4) {
			glDisable(GL_LIGHT1);
			if (selfswitch == 1) {
				myinit2();
				selfswitch = 2;
			}

		}
	}

	
	
	//Increments/decrements animation variables
	AnimationOffset -= Acceleration;
	if (AnimationOffset <= -20.0)
		AnimationOffset = 0.0;
	else if (AnimationOffset >= 0.0)
		AnimationOffset = -20.0;
	LightPoleOffset -= Acceleration;
	if (LightPoleOffset <= -400.0)
		LightPoleOffset = 0.0;
	else if (LightPoleOffset >= 0.0)
		LightPoleOffset = -400.0;
	TreeOffset -= Acceleration;
	if (TreeOffset <= -700.0)
		TreeOffset = 0.0;
	else if (TreeOffset >= 0.0)
		TreeOffset = -700.0;
	BuildingOffset -= Acceleration;
	if (BuildingOffset <= -2500.0)
		BuildingOffset = 2500.0;
	else if (BuildingOffset >= 2500.0)
		BuildingOffset = -2500.0;
	glutPostRedisplay();
}
void scene() {
	
	
	//����·��
	for (int LightPoleNumber = -25; LightPoleNumber < 25; LightPoleNumber += 4.0) {
		glPushMatrix();
		glTranslatef(-210.0, 0.0, ((LightPoleNumber * 100) + LightPoleOffset));
		glPushMatrix();
		glTranslatef(30.0, 190.0, 0.0);
		glPushMatrix();
		glTranslatef(28, -5, 0);
		//����·���ݵĲ���
		GLfloat lightinpole_diffuse[] = { 0.6,0.6,0,1 };//������Ĺ���
		GLfloat lightinpole_ambient[] = { 0.9,0.9,0,1 };//���屾�����ɫ
		GLfloat lightinpole_emission[] = { 1,1,0,1 };
		GLfloat lightinpole_shininess[] = { 30.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, lightinpole_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, lightinpole_ambient);
		glMaterialfv(GL_FRONT, GL_EMISSION, lightinpole_emission);
		glMaterialfv(GL_FRONT, GL_SHININESS, lightinpole_shininess);
		glutSolidSphere(5, 50, 50);
		glColor3f(0.9, 0.9, 0.0);
		glutWireSphere(5, 50, 50);
		glPopMatrix(); 
		glScalef(80.0, 6.0, 10.0);
		
		



		//����·�����Ĳ���
		GLfloat pole_diffuse[] = { 0.6,0.2,0,1 };
		GLfloat pole_ambient[] = { 0.9,0.3,0,1 };
		GLfloat pole_emission[] = { 0.0,0.0,0,1 };
		GLfloat pole_shininess[] = { 30.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pole_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, pole_ambient);
		glMaterialfv(GL_FRONT, GL_EMISSION, pole_emission);
		glMaterialfv(GL_FRONT, GL_SHININESS, pole_shininess);
		glutSolidCube(1);
		/*glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);*/
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glScalef(7.0, 200.0, 7.0);
		glColor3f(0.9, 0.3, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();
	}
	

	//������
	
	glPushMatrix();
	glTranslatef(-450.0, 0.0, BuildingOffset - 100);
	glPushMatrix();
	glTranslatef(0.0, 75, 0.0);
	glScalef(200.0, 350.0, 1000.0);
	GLfloat b1_diffuse[] = { 5.7,5.7,5.4,1 };
	GLfloat b1_ambient[] = { 0.7,0.7,0.4,1 };
	GLfloat b1_emission[] = { 0.0,0.0,0,1 };
	GLfloat b1_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, b1_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, b1_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, b1_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, b1_shininess);
	glColor3f(0.7, 0.7, 0.4);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(650.0, 0.0, BuildingOffset);
	glPushMatrix();
	glTranslatef(0.0, 75, 0.0);
	glScalef(400.0, 200.0, 600.0);
	GLfloat b2_diffuse[] = { 5.6,5.7,5.9,1 };
	GLfloat b2_ambient[] = { 0.4,0.5,0.7,1 };
	GLfloat b2_emission[] = { 0.0,0.0,0,1 };
	GLfloat b2_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, b2_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, b2_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, b2_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, b2_shininess);
	glColor3f(0.4, 0.5, 0.7);
	glutSolidCube(1);
	/*glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);*/
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(450.0, 0.0, BuildingOffset + 600);
	glPushMatrix();
	glTranslatef(0.0, 75, 0.0);
	glScalef(200.0, 600.0, 300.0);
	GLfloat b3_diffuse[] = { 5.6,5.9,5.9,1 };
	GLfloat b3_ambient[] = { 0.4,0.7,0.7,1 };
	GLfloat b3_specular[] = { 1,1,1,1 };
	GLfloat b3_emission[] = { 0.0,0.0,0,1 };
	GLfloat b3_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, b3_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, b3_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, b3_emission);
	glMaterialfv(GL_FRONT, GL_SPECULAR, b3_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, b3_shininess);
	glColor3f(0.4, 0.7, 0.7);
	glutSolidCube(1);
	/*glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);*/
	glPopMatrix();
	glPopMatrix();
	//����
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	glScalef(7400.0, 10.0, 5000.0);
	glPushMatrix();
	GLfloat ground_diffuse[] = { 0.3,0.2,0.1,1 };
	GLfloat ground_ambient[] = { 0.4,0.3,0.2,1 };
	GLfloat ground_emission[] = { 0.0,0.0,0,1 };
	GLfloat ground_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ground_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, ground_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, ground_shininess);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	
	//�糵
	glPushMatrix();
	glTranslatef(-1000, 100, BuildingOffset - 500);
	glScalef(150, 600, 150);
	glPushMatrix();
	glTranslatef(0, 0.49, 0);
	glRotatef(90, -1, 0, 0);
	glPushMatrix();
	GLfloat windmill_diffuse[] = { 9,9,9,1 };
	GLfloat windmill_ambient[] = { 0.3,0.3,0.3,1 };
	GLfloat windmill_emission[] = { 0.0,0.0,0,1 };
	GLfloat windmill_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, windmill_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, windmill_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, windmill_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, windmill_shininess);
	//����
	glutSolidCone(1, 0.3, 10, 10);
	glPopMatrix();
	glPopMatrix();
	//����
	glPushMatrix();
	glTranslatef(0, 0.3, -1.5);
	glRotatef(r, 0, 0, 1);
	//ҶƬ
	glPushMatrix();
	glTranslatef(0,0,0.1);
	glScalef(0.15, 0.6, 0.1);
	glPushMatrix();
	GLfloat blade_diffuse[] = { 9,0,0,1 };
	GLfloat blade_ambient[] = { 0.3,0,0,1 };
	GLfloat blade_emission[] = { 0.0,0.0,0,1 };
	GLfloat blade_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blade_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blade_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, blade_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, blade_shininess);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 0.02);
	glScalef(0.6, 0.15, 0.1);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glutSolidCylinder(0.06, 0.7, 10, 10);
	glPopMatrix();
	glPopMatrix();

	//����
	GLfloat body_diffuse[] = { 9,9,9,1 };
	GLfloat body_ambient[] = { 0.3,0.3,0.3,1 };
	GLfloat body_emission[] = { 0.0,0.0,0,1 };
	GLfloat body_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, body_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, body_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, body_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, body_shininess);
	glutSolidCube(1);
	glColor3f(0.9, 0.9, 0.9);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	
	//��������Զ�����̻���
	
	glPushMatrix();
	glTranslatef(2500.0, 20.0, 0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(2000.0, 2.0, 4800.0);
	GLfloat treelawnleft_diffuse[] = { 0.0,0.03,0.01,1 };
	GLfloat treelawnleft_ambient[] = { 0.0,0.3,0.1,1 };
	GLfloat treelawnleft_emission[] = { 0.0,0.0,0,1 };
	GLfloat treelawnleft_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, treelawnleft_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, treelawnleft_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, treelawnleft_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, treelawnleft_shininess);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2500.0, 20.0, 0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(2000.0, 2.0, 4800.0);
	GLfloat treelawnright_diffuse[] = { 0.0,0.03,0.01,1 };
	GLfloat treelawnright_ambient[] = { 0.0,0.3,0.1,1 };
	GLfloat treelawnright_emission[] = { 0.0,0.0,0,1 };
	GLfloat treelawnright_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, treelawnright_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, treelawnright_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, treelawnright_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, treelawnright_shininess);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();




	//��
	for (int LightPoleNumber = -25; LightPoleNumber < 25; LightPoleNumber += 7.0) {
		if ((TreeOffset + LightPoleNumber * 100 + 100) < BuildingOffset - 100 || (TreeOffset + LightPoleNumber * 100 + 100) > BuildingOffset + 600) {//ʹ�������ڵ���෿��
			glPushMatrix();
			glTranslatef(220.0, 0.0, TreeOffset + LightPoleNumber * 100 + 100);
			glPushMatrix();
			glTranslatef(0.0, 100.0, 0.0);
			glScalef(60.0, 65.0, 60.0);
			GLfloat crown_diffuse[] = { 0.0,1,0.3,1 };
			GLfloat crown_ambient[] = { 0.0,0.7,0.1,1 };
			GLfloat crown_emission[] = { 0.0,0.0,0,1 };
			GLfloat crown_shininess[] = { 30.0f };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, crown_diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, crown_ambient);
			glMaterialfv(GL_FRONT, GL_EMISSION, crown_emission);
			glMaterialfv(GL_FRONT, GL_SHININESS, crown_shininess);
			glutSolidIcosahedron();
			/*glColor3f(0.0, 0.0, 0.0);
			glutWireIcosahedron();*/
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.0, 25.0, 0.0);
			glScalef(15.0, 50.0, 15.0);
			GLfloat tree_diffuse[] = { 0.5,0.1,0.0,1 };
			GLfloat tree_ambient[] = { 0.7,0.3,0.0,1 };
			GLfloat tree_emission[] = { 0.0,0.0,0,1 };
			GLfloat tree_shininess[] = { 30.0f };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, tree_ambient);
			glMaterialfv(GL_FRONT, GL_EMISSION, tree_emission);
			glMaterialfv(GL_FRONT, GL_SHININESS, tree_shininess);
			glutSolidCube(1);
			/*glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1);*/
			glPopMatrix();
			glPopMatrix();
		}
	}
	
}

void roadandcar() {
	glColorMaterial(GL_FRONT, GL_DIFFUSE); //�����������
	glEnable(GL_COLOR_MATERIAL);
	//��·
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(400, 10, 5000);
	glPushMatrix();
	GLfloat road_diffuse[] = { 0.3,0.3,0.3,1 };
	GLfloat road_ambient[] = { 0.6,0.6,0.6,1 };
	GLfloat road_emission[] = { 0.0,0.0,0,1 };
	GLfloat road_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, road_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, road_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, road_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, road_shininess);
	glColor3f(0.6, 0.6, 0.6);
	glutSolidCube(1);
	/*glColor3f(0, 0, 0);
	glutWireCube(1);*/
	glPopMatrix();
	glPopMatrix();
	//��·�������
	glPushMatrix();
	glTranslatef(200, 10, 0);
	glScalef(10, 10, 5000);
	glPushMatrix();
	GLfloat line_diffuse[] = { 0.5,0.5,0.5,1 };
	GLfloat line_ambient[] = { 0.7,0.7,0.7,1 };
	GLfloat line_emission[] = { 0.0,0.0,0,1 };
	GLfloat line_shininess[] = { 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, line_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, line_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, line_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, line_shininess);
	glColor3f(1, 1, 1);
	glutSolidCube(1);
	/*glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);*/
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-185, 10, 0);
	glScalef(10, 10, 5000);
	glPushMatrix();
	GLfloat line2_diffuse[] = { 0.8,0.8,0.8,1 };
	GLfloat line2_ambient[] = { 1,1,1,1 };
	GLfloat line2_emission[] = { 0.0,0.0,0,1 };
	GLfloat line2_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, line2_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, line2_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, line2_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, line2_shininess);
	glColor3f(1, 1, 1);
	glutSolidCube(1);
	/*glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);*/
	glPopMatrix();
	glPopMatrix();

	//����(����Ϊ�����壬��ʻ��Ϊ���򣬳���ΪԲ���壩

	  //�ĸ����ӣ���Բ���壩
	glPushMatrix();
	glTranslatef(-50, 50, -625);
	glScalef(1, 1, 1);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	GLfloat wheel_diffuse[] = { 0,0,0,1 };
	GLfloat wheel_ambient[] = { 0,0,0,1 };
	GLfloat wheel_emission[] = { 0.0,0.0,0,1 };
	GLfloat wheel_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wheel_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, wheel_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, wheel_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, wheel_shininess);
	glColor3f(0, 0, 0);
	glutSolidCylinder(10, 100, 100, 10);
	/*glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(10, 100, 100, 10);*/
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-50, 50, -525);
	glScalef(1, 1, 1);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glutSolidCylinder(10, 100, 100, 10);
	/*glColor3f(0.0, 0.0, 0.0);
	glutWireCylinder(10, 100, 100, 10);*/
	glPopMatrix();
	glPopMatrix();
	//����
	glPushMatrix();
	glTranslatef(0, 60, -575);
	glScalef(80, 50, 120);
	glPushMatrix();
	GLfloat body_diffuse[] = { 5.3,5.7,5,1 };
	GLfloat body_ambient[] = { 0.5,0.9,0,1 };
	GLfloat body_emission[] = { 0.0,0.0,0,1 };
	GLfloat body_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, body_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, body_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, body_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, body_shininess);
	glColor3f(0.5, 0.9, 0.0);
	glutSolidCube(1);
	/*glColor3f(0, 0, 0.0);
	glutWireCube(1);*/
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glEnable(GL_COLOR_MATERIAL);
	//��ʻ��
	glPushMatrix();
	glTranslatef(0, 80, -575);
	glScalef(10, 10, 10);
	glPushMatrix();
	GLfloat cab_diffuse[] = { 0.5,0.5,0.6,1 };
	GLfloat cab_ambient[] = { 0.8,0.8,1,1 };
	GLfloat cab_specular[] = { 10,10,10,1 };
	GLfloat cab_emission[] = { 0.0,0.0,0,1 };
	GLfloat cab_shininess[] = { 30.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cab_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cab_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, cab_emission);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cab_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, cab_shininess);
	glColor3f(0.8, 0.8, 0.9);
	glutSolidSphere(4, 100, 100);
	/*glColor3f(0.9, 0.9, 1);
	glutWireSphere(4, 100, 100);*/
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);

	/*glPushMatrix();
	glTranslatef(-100, 160, -590);
	glScalef(50, 50, 50);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();*/
	//����ת����

	//if (doorappear <= 250) {
	//	doorappear += Acceleration * 0.02;
	//}
	//else {
	//	dooroffset += Acceleration;
	//	glPushMatrix();
	//	glTranslatef(5.0, 0.0, 5000 - dooroffset);
	//	glPushMatrix();
	//	glScalef(350.0, 600.0, 10.0);
	//	GLfloat door_diffuse[] = { 0,0,0,1 };
	//	GLfloat door_ambient[] = { 0,0,0,1 };
	//	GLfloat door_emission[] = { 0.0,0.0,0,1 };
	//	GLfloat door_shininess[] = { 30.0f };
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, door_diffuse);
	//	glMaterialfv(GL_FRONT, GL_AMBIENT, door_ambient);
	//	glMaterialfv(GL_FRONT, GL_EMISSION, door_emission);
	//	glMaterialfv(GL_FRONT, GL_SHININESS, door_shininess);
	//	glColor3f(0.0, 0.0, 0.0);
	//	glutSolidCube(1);
	//	/*glColor3f(0.0, 0.0, 0.0);
	//	glutWireCube(1);*/
	//	glPopMatrix();
	//	glPopMatrix();
	//}
}






void display(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, 1.5, 0.1, 5000);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(X0 * Zoom, Y0 * Zoom, Z0 * Zoom, XRef, YRef, ZRef, XUp,
			  YUp, ZUp);//��������ӽ�
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);//���ñ���ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*if (dooroffset <= 5745) {*/
	
		scene();
		roadandcar();
		background();
		background2();
	/*}
	else {
		roadandcar();
	}*/
		
	glutSwapBuffers();
}


void reshape(int width, int height) {
	glViewport(0, 0, width, height);  //�����ӿڣ���ʱ��������λ��Ϊ����ԭ��
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("3D scene");
	glClearColor(0.4f, 0.4f, 1.0f, 0);
	
	
	/*while (1) {*/
		
		
		/*cout << timer;
		if (timer % 10 == 0) {
			ambientvalue += 0.1;
			timer++;
			continue;
		}*/
		
		
		/*init();*/
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutIdleFunc(animate);
		glutTimerFunc(time_interval, OnTimer, 1);
		glutMouseFunc(mouse_input);
		glutKeyboardFunc(keyboard_input);
		glutMainLoop();
		

	/*}*/
}




