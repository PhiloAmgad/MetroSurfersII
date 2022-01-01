#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <glut.h>
#include <windows.h>
#include<mmsystem.h>

#include <stdio.h>


#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
#define PI 3.1415927

double px = 0;
double pz = 1.5;
bool frwd ;
bool back ;
bool right ;
bool left;
bool end;
bool ffrwd ;
bool fback ;
bool fright;
bool fleft ;
bool pres1;
bool pres2;
bool pres3;
bool pres4;
bool p1p;
bool p2p;
bool p3p;
bool p4p;
bool playLose;
bool playWin;
char view;
int time;
float s;
int r;
int g;
int b;
float rotAng;
float rotAngS;
float rotAngP;
class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		//eye = Vector3f(eyeX, 0.5f, 3.5);
		/*if(view =='s'){
		eye = Vector3f(3.86853f, 0.753072f, 1.00067f);
		center = Vector3f(2.86875, 0.739158, 0.985145);
		}
		else if (view == 't') {
			center = Vector3f( 1.07266, 0.518734, 2.80267);
			eye = Vector3f( 1.12294, 0.550196, 3.80091);
		}
		else {*/
		center = Vector3f(1, 0.5, 3);
		eye = Vector3f(1, 0.5, 4);
		
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		/*std::cout << "Eye X:";
		std::cout << eye.x;
		std::cout << "Eye Y:";
		std::cout << eye.y;
		std::cout << "Eye Z:";
		std::cout << eye.z;*/
		center = center + right * d;
		/*std::cout << "Center X:";
		std::cout << center.x;
		std::cout << "Center Y:";
		std::cout << center.y;
		std::cout << "Center Z:";
		std::cout << center.z;*/
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		/*std::cout << "Eye X:";
		std::cout<<eye.x;
		std::cout << "Eye Y:";
		std::cout << eye.y;
		std::cout << "Eye Z:";
		std::cout << eye.z;*/

		center = center + up.unit() * d;
		/*std::cout << "Center X:";
		std::cout << center.x;
		std::cout << "Center Y:";
		std::cout << center.y;
		std::cout << "Center Z:";
		std::cout << center.z;*/
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		/*std::cout << "Eye X:";
		std::cout << eye.x;
		std::cout << "Eye Y:";
		std::cout << eye.y;
		std::cout << "Eye Z:";
		std::cout << eye.z;*/
		center = center + view * d;
		/*std::cout << "Center X:";
		std::cout << center.x;
		std::cout << "Center Y:";
		std::cout << center.y;
		std::cout << "Center Z:";
		std::cout << center.z;*/
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
		/*std::cout << "Eye X:";
		std::cout << eye.x;
		std::cout << "Eye Y:";
		std::cout << eye.y;
		std::cout << "Eye Z:";
		std::cout << eye.z;
		std::cout << "Center X:";
		std::cout << center.x;
		std::cout << "Center Y:";
		std::cout << center.y;
		std::cout << "Center Z:";
		std::cout << center.z;*/
		//Eye X:3.86853Eye Y:0.753072Eye Z:1.00067Center X:2.86875Center Y:0.739158Center Z:0.985145
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
		/*std::cout << "Eye X:";
		std::cout << eye.x;
		std::cout << "Eye Y:";
		std::cout << eye.y;
		std::cout << "Eye Z:";
		std::cout << eye.z;
		std::cout << "Center X:";
		std::cout << center.x;
		std::cout << "Center Y:";
		std::cout << center.y;
		std::cout << "Center Z:";
		std::cout << center.z;*/
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
	void set(float eyeX, float eyeY, float eyeZ, float cameraX, float cameraY, float cameraZ) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(cameraX, cameraY, cameraZ);
	}
};

Camera camera;

void Anim() {
	if ((px + 0.25 >= 0.5 && px - 0.25 <= 0.51) && (pz + 0.25 >= 0.5 && pz - 0.25 <= 0.51)) {
		//PlaySound(TEXT("sounds/powerup.wav"), NULL, SND_FILENAME | SND_ASYNC);
		pres1 = true;
	}
	if ((px + 0.25 >= 0.5 && px - 0.25 <= 0.51) && (pz + 0.25 >= 1.5 && pz - 0.25 <= 1.51)) {
		//PlaySound(TEXT("sounds/powerup.wav"), NULL, SND_FILENAME | SND_ASYNC);
		pres2 = true;
	}
	if ((px + 0.25 >= 1 && px - 0.25 <= 1.01) && (pz + 0.25 >= 1.5 && pz - 0.25 <= 1.51)) {
		//PlaySound(TEXT("sounds/powerup.wav"), NULL, SND_FILENAME | SND_ASYNC);
		pres3 = true;
	}
	if ((px + 0.25 >= 1.5 && px - 0.25 <= 1.51) && (pz + 0.25 >= 1.5 && pz - 0.25 <= 1.51)) {
		//PlaySound(TEXT("sounds/powerup.wav"), NULL, SND_FILENAME | SND_ASYNC);
		pres4 = true;
	}
	r++;
	if (r > 255)
		r = 0;

	/*g++;
	if (g > 255)
		g = 0;
	b++;
	if (b > 255)
		b = 0;*/
	 time++;
	 if (time >= 1000) {
		 end = true;
	 }
	 if (pres1 && pres2 && pres3 && pres4) {
		 end = true;
	 }
	glutPostRedisplay();
}

void drawClosedCylinder(GLfloat radius,GLfloat height)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	//glColor3ub(102, 51, 0);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
	//glColor3ub(102, 51, 0);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}
void drawOpenCylinder(GLfloat radius, GLfloat height)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;


	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	glColor3ub(102, 51, 0);
	/*glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();*/
}
void drawCylinder(GLfloat radius, GLfloat height)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;


	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	glColor3ub(102, 51, 0);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	
	glEnd();
}
void drawPyramid()
{
	glBegin(GL_LINE_LOOP);

	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glEnd();
	//draw the nose
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.0, 1);
	glVertex3f(0.5, 0.5, 0.0);


	glVertex3f(0.0, 0.0, 1);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);

	glVertex3f(0.0, 0.0, 1);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.0, 1);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();


}

void drawStar() {
	glPushMatrix();
	glColor3f(1, 1, 0.2);
	glRotated(145, 1, 0, 0);
	glRotated(130, 0, 0, 1);
	//glTranslated(1.8, 0.2, 1);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 0, 1);
	glColor3f(1, 1, 0.2);
	glRotated(145, 1, 0, 0);
	glRotated(130, 0, 0, 1);
	//glTranslated(1.8, 0.2, 1);
	glutSolidTetrahedron();
	glPopMatrix();
}

void drawTree() {
	glColor3f(0.2f, 0.51f, 0.06f);

	glPushMatrix();
	glTranslated(0, 4.5, 0);
	glRotated(270, 1, 0, 0);
	glutSolidCone(1, 2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3, 0);
	glRotated(270, 1, 0, 0);
	glutSolidCone(1.2, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.5, 0);
	glRotated(270, 1, 0, 0);
	glutSolidCone(1.5,3.5,100,100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(102 - 40, 51 - 40, 0);
	glTranslated(0, 2, 0);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.3,2 );
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-0.07, 14, 0);
	drawStar();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-0.07, 10, 1.5);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-1, 7, 2);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 1.0f);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(1, 8.5, 1);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 1.0f);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(1, 3.5, 2.8);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();
	//kjhk
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-1.5, 10, 0.07);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2, 7, 1);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0.5, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-1, 8.5, -1);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.8, 3.5, 1);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	//
	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-0.07, 10, -1.5);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-1, 7, -2);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 1.0f);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(1, 8.5, -1);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 1.0f);
	glScaled(0.5, 0.5, 0.5);
	glTranslated(1, 3.5, -2.8);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();
	/*glPushMatrix();
	glRotated(60, 1, 0, 1);
	glTranslated(3, -1, 0);
	glutSolidTetrahedrfon();
	glRotated(90,0 , 0, 1);
	glTranslated(-1.2, 1, 1);
	glutSolidTetrahedron();
	glPopMatrix();*/
}

void drawWall(double thickness) {
	glPushMatrix();

	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}
void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawJackPart() {
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}
void drawJack() {
	glPushMatrix();
	drawJackPart();
	glRotated(90.0, 0, 1, 0);
	drawJackPart();
	glRotated(90.0, 1, 0, 0);
	drawJackPart();
	glPopMatrix();
}
void drawTable(double topWid, double topThick, double legThick, double legLen){
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
}
void drawSnowman() {

	glColor3f(1, 1, 1);
	glPushMatrix();
	glScaled(1, 1, 1.0);
	glutSolidSphere(0.2, 105, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.3f, 0);
	glScaled(0.7, 0.7, 0.7);
	glutSolidSphere(0.2, 105, 15);
	glPopMatrix(); 
	glPushMatrix();
	glTranslated(0, 0.52f, 0);
	glScaled(0.5, 0.5, 0.5);
	glutSolidSphere(0.2, 105, 15);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0.5f, 0.0f);
	glTranslated(0, 0.5f, 0.1f);
	//glScaled(0.5, 0.5, 1);
	//glRotated(270, 1, 0, 0);
	glutSolidCone(0.012, 0.1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-0.03, 0.56, 0.1);
	glutSolidSphere(0.02, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.03, 0.56, 0.1);
	glutSolidSphere(0.02, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glTranslated(0, 0.3, 0.15);
	glutSolidSphere(0.02, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glTranslated(0, 0.05, 0.2);
	glutSolidSphere(0.02, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(102 - 40, 51 - 40, 0);
	glTranslated(-0.1, 0.42f, 0);
	glRotated(-40, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.01, 0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(102 - 40, 51 - 40, 0);
	glTranslated(0.3, 0.17f, 0);
	glRotated(-140, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.01, 0.3);
	glPopMatrix();
}
void drawPresent() {
	glPushMatrix();
	glColor3f(0.54f, 0.0f, 0.0f);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.64f, 0.0f);
	glTranslated(0.1, 0, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.54f, 0.0f, 0.0f);
	glTranslated(0, 0, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1, 0, 0);
	glColor3f(0.54f, 0.0f, 0.0f);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.64f, 0.0f);
	glTranslated(-0.1, 0, -0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.54f, 0.0f, 0.0f);
	glTranslated(0, 0, -0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.54f, 0.0f, 0.0f);
	glTranslated(-0.1, 0, 0);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.64f, 0.0f);
	glTranslated(0.1, 0, -0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.64f, 0.0f);
	glTranslated(-0.1, 0, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

}
void drawFloor(int z) {
	glPushMatrix();
	glColor3f(0.54f, 0.0f, 0.0f);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	if (z == 0 || z == 2)
		glColor3f(0.5, 0.7, 1);
	else
		glColor3f(1, 1, 1);
	glTranslated(0.1, 0, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	if(z==0)
		glColor3ub(102, 51, 0);
	else
		glColor3f(0.5, 0.7, 1);
	glTranslated(0, 0, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1, 0, 0);
	glColor3f(0.5, 0.7, 1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	if (z == 0 || z == 2)
		glColor3f(0.5, 0.7, 1);
	else
		glColor3f(1, 1, 1);
	glTranslated(-0.1, 0, -0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.7, 1);
	glTranslated(0, 0, -0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.7, 1);
	glTranslated(-0.1, 0, 0);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	if (z == 0 || z == 2)
		glColor3f(0.5, 0.7, 1);
	else
		glColor3f(1, 1, 1);
	glTranslated(0.1, 0, -0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	if (z == 0||z==2)
		glColor3f(0.5, 0.7, 1);
	else
		glColor3f(1, 1, 1);
	glTranslated(-0.1, 0, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

}
void drawHouse() {
	glPushMatrix();
	drawFloor(0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.1, 0);
	drawFloor(2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.2, 0);
	drawFloor(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.3, 0);
	drawFloor(2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.4, 0);
	drawFloor(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.5, 0);
	drawFloor(2);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(99, 0, 0);
	
	glTranslated(0, 0.55, 0);
	glScaled(0.3, 0.3, 0.3);
	glRotated(-90, 1, 0, 0);
	drawPyramid();
	glPopMatrix();
}

void drawPlayerOld() {
	

	glPushMatrix();
	glColor3f(1.0f , 0.8f , 0.6);
	glTranslated(0,0.7,0);
	glutSolidSphere(0.1, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.6);
	glTranslated(0, 0.7, -0.1);
	glutSolidSphere(0.01, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.6);
	glTranslated(-0.03, 0.75, -0.1);
	glutSolidSphere(0.02, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.6);
	glTranslated(0.03, 0.75, -0.1);
	glutSolidSphere(0.02, 100, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	glTranslated(0, 0.77, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.07, 0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.6);
	glTranslated(0, 0.7, -0.1);
	glutSolidSphere(0.01, 100, 10);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.8, 0, 0);
	glTranslated(0, 0.55f, 0);
	glRotated(-40, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.03, 0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0, 0);
	glTranslated(0.3, 0.17f, 0);
	glRotated(-140, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.03, 0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8 , 0 , 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.25, 0.6, 100, 100);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.8, 0, 0);
	glTranslated(0.15, 0, 0);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.03, 0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0, 0);
	glTranslated(-0.15, 0, 0);
	glRotated(90, 1, 0, 0);
	drawCylinder(0.03, 0.3);
	glPopMatrix();
}
void drawFencePart() {

	glPushMatrix();
	glColor3ub(r, g, b);

	glTranslated(0, 0.4, 0);
	glScaled(0.05, 0.05, 0.1);
	glRotated(-90, 1, 0, 0);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(r, g, b);
	glTranslated(0, 0.25, 0.3);
	glRotated(-90, 0, 1, 0);
	glScaled(4.8, 1, 0.5);
	glRotated(-90, 1, 0, 0);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(r, g, b);
	glTranslated(0, 0.2, 0);
	glRotated(-90, 0, 1, 0);
	glScaled(1, 4, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();
}
void drawFence() {
	glPushMatrix();
	drawFencePart();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.5);
	drawFencePart();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1.5);
	drawFencePart();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1);
	drawFencePart();
	glPopMatrix();

}
void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { 7.0f, 6.0f, 15.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 'f':
		//Eye X:0.93Eye Y:0.5Eye Z:4Center X:0.93Center Y:0.5Center Z:30
		camera.set(0.93, 0.5, 4, 0.93, 0.5, 3);
		break;
	case 't':
		camera.set(0.869077, 3.44416, 0.931678, 0.869163, 2.44534, 0.9802910);
		break;
	case 'r':
		camera.set(3.86853f, 0.753072f, 1.00067f, 2.86875, 0.739158, 0.985145);
		break;
	



	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
 
void drawTunnel(double x, double y, double z) {
	glPushMatrix();
	glTranslated(x, y, z);
	//drawOpenCylinder(1, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x-1, y, z);
	glScaled(2, 1, 10);
	drawWall(0.02);
	glPopMatrix();
}
void drawHurdle(double x, double y, double z) {
	glPushMatrix();
	glTranslated(x, y+0.2, z);
	glScaled(3, 1, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(x-0.1, y + 0.1, z);
	glScaled(0.5, 2.5, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(x+0.1, y + 0.1, z);
	glScaled(0.5, 2.5, 1);
	glutSolidCube(0.1);
	glPopMatrix();
}
void drawTrainBasMshRotated3shanSlebMsh3awezye3melScaling(double x, double y, double z) {

	glPushMatrix();
	glTranslated(x , y+0.1  ,z);
	glScaled(5, 5, 10);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y+0.35, z-0.5);
	drawClosedCylinder(0.25, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x+0.25, y-0.1 , z - 0.4);
	glRotated(90, 0, 1, 0);
	drawClosedCylinder(0.1, 0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.3, y - 0.1, z + 0.4);
	glRotated(90, 0, 1, 0);
	drawClosedCylinder(0.1, 0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.25, y - 0.1, z + 0.4);
	glRotated(90, 0, 1, 0);
	drawClosedCylinder(0.1, 0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.3, y - 0.1, z - 0.4);
	glRotated(90, 0, 1, 0);
	drawClosedCylinder(0.1, 0.05);
	glPopMatrix();
	
}
void drawTrain(double x, double y, double z) {
	glPushMatrix();
	
	glScaled(0.65, 0.65, 0.65);
	drawTrainBasMshRotated3shanSlebMsh3awezye3melScaling(x+0.25, y, z);
	glPopMatrix();

}
void drawPlayer(double x , double y, double z) {
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(90, 1, 0, 0);
	glScaled(0.1, 0.1, 0.2);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();

	
	glPushMatrix();
	glTranslated(x , y-0.1 , z);
	glRotated(90, 0, 1, 0);
	glRotated(70, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	//glRotated(-45, 0, 1, 0);
	drawClosedCylinder(0.01,0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y - 0.1, z);
	glRotated(270, 0, 1, 0);
	glRotated(70, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	//glRotated(-45, 0, 1, 0);
	drawClosedCylinder(0.01, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x+0.07, y + 0.07, z);
	glRotated(90, 0, 1, 0);
	glRotated(70, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	//glRotated(-45, 0, 1, 0);
	drawClosedCylinder(0.01, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x-0.07, y + 0.07, z);
	glRotated(270, 0, 1, 0);
	glRotated(70, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	//glRotated(-45, 0, 1, 0);
	drawClosedCylinder(0.01, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x , y + 0.17, z);
	glRotated(65, 1, 0, 0);
	drawClosedCylinder(0.14, 0.01);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y+0.18, z);
	glRotated(90, 1, 0, 0);
	glScaled(0.06, 0.05, 0.1);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();


}
void Display() {
	setupCamera();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	drawTunnel(1, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	//drawHurdle(1, 0, 1.5);
	glPopMatrix();

	glPushMatrix();
	drawHurdle(0.5, 0, 1.5);
	glPopMatrix();

	glPushMatrix();
	drawHurdle(1.5, 0, 1.5);
	glPopMatrix();

	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	drawTrain(0.5, 0.25, 1);
	glPopMatrix();

	glPushMatrix();
	drawPlayer(1, 0.45, 3);
	glPopMatrix();

	glFlush();
}


void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	//PlaySound(TEXT("sounds/carol.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	frwd = true;
	ffrwd = false;
	s = 1;
	glutCreateWindow("Philo's Project");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
