/* londo_hw5.c
 * Laura Londo
 * 31 March 2014
 * HW #6:
 *
 * program demonstrates the use of lighting on spheres using a caterpillar
 *
 * Directions
 * 		use W A S D keys to rotate the caterpillar.
 *			W and S rotate on the x-axis
 *			A and D rotate on the y-axis
 *
 *		use arrow keys to make the worm crawl around
 *			rotations are reset upon crawling because it
 *			is dificult to control the caterpillar if it is
 *			rotated at an awkward angle
 *
 *		use keys 1 2 and 3 to toggle the three lights on and off
 */

 #include <GL/glut.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <math.h>

#define numSegs 10
#define screenWidth 1000
#define screenHeight 720
#define sphereSegs 40
#define PI 3.1415


float xpos = 0, ypos=0, zpos = 0;				//worm position
float xrot= -40, yrot=0;						//worm angle

float xLocs[numSegs] = {0.0, 0.5, 1.0, 1.5, 2.0,//x locations for each worm segment
						2.5, 3.0, 3.5, 4.0, 4.5};
float yLocs[numSegs];							//y locations for each worm segment
float zLocs[numSegs];							//z locations for each worm segment
float radii[numSegs] = {0.3,0.25,0.25,0.25,0.25,//radius of each worm segment
						0.25,0.23,0.2,0.15,0.1};
float rot[numSegs];								//rotation for each segment

float lightPos[3][3] = { 	{ 0.2, -0.2,-4.0},	//position for each light
							{-1.5, 0.0, -6.0},
							{ 0.2, 1.0,-5.0} };

//light toggles (1 = on)
int light0on = 1;
int light1on = 1;
int light2on = 1;


//initialize starting worm segment positions
void initSegs(void) {
	for(int i=0; i<numSegs; i++) {
		yLocs[i] = 0;
		zLocs[i] = 0;
		rot[i] = 0;
	}
}


//define the current drawing material
void material(float red, float green, float blue, float shine) {
	float mat_specular[]={red, green, blue, 1.0};
	float mat_diffuse[] ={red, green, blue, 1.0};
	float mat_ambient[] ={red, green, blue, 1.0};
	float mat_shininess={shine};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}


//define light 0
void light0(void) {
	GLfloat light_ambient0[]={0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse0[]={0.0, 0.0, 0.0, 1.0};
	GLfloat light_specular0[]={0.2, 0.2, 1,0, 1.0};
	GLfloat position0[] = { lightPos[0][0], lightPos[0][1], lightPos[0][2], 1.0 };
	/* Set up ambient, diffuse, and specular components for light 0 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv (GL_LIGHT0, GL_POSITION, position0);
}


//define light 1
void light1(void) {
	GLfloat light_ambient1[]={0.1, 0.0, 0.0, 1.0};
	GLfloat light_diffuse1[]={1.0, 0.0, 0.0, 1.0};
	GLfloat light_specular1[]={0.5, 0.0, 0.0, 1.0};
	GLfloat position1[] = { lightPos[1][0], lightPos[1][1], lightPos[1][2], 1.0};
	/* Set up ambient, diffuse, and specular components for light 0 */
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv (GL_LIGHT1, GL_POSITION, position1);
}


//define light 2
void light2(void) {
	GLfloat light_ambient1[]={0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse1[]={0.0, 0.5, 0.5, 1.0};
	GLfloat light_specular1[]={0.0, 0.5, 0.5, 1.0};
	GLfloat position1[] = { lightPos[2][0], lightPos[2][1], lightPos[2][2], 1.0};
	/* Set up ambient, diffuse, and specular components for light 0 */
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular1);
	glLightfv (GL_LIGHT2, GL_POSITION, position1);
}


//draw the worm's head
void wormHead(void) {
	//head
	material(0.3,1,0.2, 100);
	glutSolidSphere(radii[0],sphereSegs,sphereSegs);


	material(1.0, 0.5, 0.5, 100);
	//left eye
	glPushMatrix();
	glTranslatef(-0.2,-0.15,0.1);
	glutSolidSphere(0.17,sphereSegs,sphereSegs);
	glPopMatrix();

	//right eye
	glPushMatrix();
	glTranslatef(0.2,-0.15,0.1);
	glutSolidSphere(0.17,sphereSegs,sphereSegs);
	glPopMatrix();
}


//draw the worm
void worm(void) {
	//draw head
	glPushMatrix();
	glTranslatef(xLocs[0],yLocs[0],zLocs[0]);
	glRotatef(rot[1],0,0,1);
	wormHead();
	glPopMatrix();

	//draw body segments
	for(int i=1; i<numSegs; i++){	//for each segment,
		glPushMatrix();
			//main segment
			material(0.3,1,0.2, 100);
			glTranslatef(xLocs[i],yLocs[i],zLocs[i]);
			glRotatef(rot[i],0,0,1);
			glutSolidSphere(radii[i],sphereSegs,sphereSegs);

			material(0.8,0.8,0.2, 100);
			//leg
			glPushMatrix();
				glTranslatef(-radii[i],0.0,-0.1);
				glutSolidSphere(radii[i]/3.0,sphereSegs,sphereSegs);
			glPopMatrix();

			//leg
			glPushMatrix();
				glTranslatef(radii[i],0.0,-0.1);
				glutSolidSphere(radii[i]/3.0,sphereSegs,sphereSegs);
			glPopMatrix();

		glPopMatrix();
	}
}


//makes worm body segmets follow the movement of the head.
void snakeMovement(void){
	float xdif,ydif,zdif,dist;
	float xvec,yvec,zvec;
	for(int i=1; i<numSegs; i++){			//for each segment,
		//getting vector from the segment in front to this segment
		xdif = xLocs[i-1]-xLocs[i];
		ydif = yLocs[i-1]-yLocs[i];
		zdif = zLocs[i-1]-zLocs[i];
		//distance between the centers of the two segments
		dist = sqrt(xdif*xdif + ydif*ydif + zdif*zdif);
		//while the segment is too far from the one in front of it,
		while(dist > (radii[i-1]+radii[i])/2.0){
			//get vector from the segment in front to this segment
			xdif = xLocs[i-1]-xLocs[i];
			ydif = yLocs[i-1]-yLocs[i];
			zdif = zLocs[i-1]-zLocs[i];
			//move this segment towards the segment in front of it
			xLocs[i] += xdif/8.0;
			yLocs[i] += ydif/8.0;
			zLocs[i] += zdif/8.0;
			//get new distance
			dist = sqrt(xdif*xdif + ydif*ydif + zdif*zdif);
		}
		//update segment rotation so they face forward
		rot[i] = (atan2(ydif, xdif) * 180.0 / PI) + 90.0;
	}
}


//display callback
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt (	0.0, 0.0, 5.0,
			   	0.0, 0.0, 0.0,
			  	0.0, 1.0, 0.0);

	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);
	//draw sphere for light 0
	glPushMatrix();
	glTranslatef(lightPos[0][0],lightPos[0][1],lightPos[0][2]+5.0);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();
	//draw sphere for light 1
	glPushMatrix();
	glTranslatef(lightPos[1][0],lightPos[1][1],lightPos[1][2]+5.0);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();
	//draw sphere for light 2
	glPushMatrix();
	glTranslatef(lightPos[2][0],lightPos[2][1],lightPos[2][2]+5.0);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();
	glEnable(GL_LIGHTING);



	//draw worm
	glPushMatrix();
		glRotatef(xrot, 1,0,0);			//worm x rotation
		glRotatef(yrot, 0,1,0);			//worm y rotation
	 	glTranslatef(xpos, ypos, zpos);	//worm position
		snakeMovement();				//calculates worm segment positions
		worm();							//draw worm
	glPopMatrix();

	glutSwapBuffers();
}


//reset the rotation in case the worm is rotated at a weird angle
//(its dificult to control the worm if it's upside-down)
void resetRot(void) {
	xrot = -40;
	yrot = 0;
}


//callback for keyboard presses. used to rotate the worm and toggle lights
void keyboard(unsigned char key, int x, int y) {
   	if((int)key == 27) exit(0);		//exit program

   	//rotate worm
   	if(key == 'w') xrot+=10.0;
   	if(key == 's') xrot-=10.0;
   	if(key == 'a') yrot+=10.0;
   	if(key == 'd') yrot-=10.0;

   	//toggle lights on or off
   	if(key == '1') {
   		if(light0on) {
   			glDisable(GL_LIGHT0);
   			light0on = 0;
   		}
   		else {
   			glEnable(GL_LIGHT0);
   			light0on = 1;
   		}
   	}
   	if(key == '2') {
   		if(light1on) {
   			glDisable(GL_LIGHT1);
   			light1on = 0;
   		}
   		else {
   			glEnable(GL_LIGHT1);
   			light1on = 1;
   		}
   	}
   	if(key == '3') {
   		if(light2on) {
   			glDisable(GL_LIGHT2);
   			light2on = 0;
   		}
   		else {
   			glEnable(GL_LIGHT2);
   			light2on = 1;
   		}
   	}


   	glutPostRedisplay();
}


//arrow keys used to move the worm
void specialKey(int key, int x, int y) {
	//make worm crawl (moves the head only. other segments follow)
   	//also resets the rotation
   	if(key == GLUT_KEY_UP) {
   		resetRot();
   		yLocs[0] += 0.1;
   	}
   	if(key == GLUT_KEY_DOWN) {
		resetRot();
   		yLocs[0] -= 0.1;
   	}
   	if(key == GLUT_KEY_RIGHT) {
   		resetRot();
   		xLocs[0] += 0.1;
   	}
   	if(key == GLUT_KEY_LEFT) {
   		resetRot();
   		xLocs[0] -= 0.1;
   	}
   	glutPostRedisplay();
}

//reshape callback
void reshape (int w, int h) {
   	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   	glMatrixMode (GL_PROJECTION);
   	glLoadIdentity();
   	gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}


//main method
int main(int argc, char **argv) {
	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 	glutInitWindowSize(screenWidth, screenHeight);
 	glutCreateWindow("Caterpillar!");
 	glEnable(GL_DEPTH_TEST);
 	glClearColor(0,0,0,0);
 	glShadeModel (GL_SMOOTH);			//smooth shading

 	//define the three lights
 	light0();
 	light1();
 	light2();
 	//enable lighting
   	glEnable(GL_LIGHTING);
   	//enble all three lights
   	glEnable(GL_LIGHT0);
   	glEnable(GL_LIGHT1);
   	glEnable(GL_LIGHT2);

 	//function callbacks
 	glutDisplayFunc(display);			//displays the world
 	glutReshapeFunc(reshape);			//reshape window
 	glutKeyboardFunc(keyboard);			//keyboard buttons
 	glutSpecialFunc(specialKey);

 	initSegs();							//initialize caterpillar segments

 	glutMainLoop();
	return 0;
}