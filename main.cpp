//
//  main.cpp
//  CS 418 MP1
//
//  Created by Helios on 2/4/14.
//  Copyright (c) 2014 Helios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <math.h>
#include <GLUT/glut.h>

//global variables
int filled =0;
int dancingI;
int value = 0;


//the display function which makes the 'I'
//it takes in a parameter which determines wheter the triangle
//is filled or wired 
void display(int typeOfI){
    
    //the defined amplitude of the sine function
    float amplitude = 0.1;
    
    //flaot values for the interpolation of points
    //Depending on their x-axis of the fucntion
    float a = amplitude *sin(value + 2);
    float b = amplitude*sin(value + 4);
    float c = amplitude*sin(value + 6);
    float d = amplitude *sin(value + 8);
    float e = amplitude *sin(value + 5);

    
    //drawing the 'I' with 15 Points
    glBegin(typeOfI);
        glVertex3f(5.0, 1.0+e, 0.0);
        glVertex3f(2.0, 1.0+a, 0.0);
        glVertex3f(2.0, 3.0+a, 0.0);
        glVertex3f(4.0, 3.0+b, 0.0);
        glVertex3f(4.0, 7.0+b, 0.0);
        glVertex3f(6.0, 7.0+c, 0.0);
        glVertex3f(6.0, 3.0+c, 0.0);
        glVertex3f(8.0, 3.0+d, 0.0);
        glVertex3f(8.0, 1.0+d, 0.0);
    glEnd();
    
    glBegin(typeOfI);
        glVertex3f(2.0, 9.0+a, 0.0); //1
        glVertex3f(2.0, 7.0+a, 0.0); //2
        glVertex3f(4.0, 7.0+b, 0.0); //3
        glVertex3f(6.0, 7.0+c, 0.0); //4
        glVertex3f(8.0, 7.0+d, 0.0); //5
        glVertex3f(8.0, 9.0+d, 0.0); //6
    glEnd();
    
    value++;
    
}


//the fucntion to display the wired fan display
void displayFan(void){
    
    glColor3f(0.9, 0.5, 0.1); // the color is orange
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    display(GL_TRIANGLE_FAN);
    
}

//the fucntion to display both the wires and solid
void displayFilled(void){
    
    glColor3f(0.9, 0.5, 0.1);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    display(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    display(GL_TRIANGLE_FAN);
    
}

//the function to display a solid filled 'I'
void displaySolid(void){
    glColor3f(0.9, 0.5, 0.1);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    display(GL_TRIANGLE_FAN);
}

//The timer function for glut
void timeKeeper(int value){
    glutPostRedisplay();
    glutTimerFunc(33, timeKeeper, value);
}

/*
 the choice function which calles the function to display the I
 */
void choice(){
    
    glClear(GL_COLOR_BUFFER_BIT);

    if (filled == 0)
        displayFan();
    else if (filled ==1)
        displaySolid();
    
	glutSwapBuffers();

}

/*
 The keyboard function. 
 Pressing the key 's' gives a filled solid 'I'
 Pressing the key 'a' gives the wireframe of the 'I'
*/
void keyboardFunction(unsigned char key, int x, int y){
    
    if(key == 'a'){
        filled = 0;
    }
    if (key == 's') {
        filled = 1;
    }
    if (key == 'q') {
        glutDestroyWindow(dancingI);
        exit(0);
    }
}

int main(int argc, char **argv)
{
    //sanity check printout statement
    printf("hello world\n");
    //initializing GLUT
    glutInit(&argc, argv);
    //Initializing the Glut as single, RGB and depth
    glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    //making a window at 200 and 200
    glutInitWindowPosition(200,200);
    //teh window size is 450 x 450
    glutInitWindowSize(1000 ,1000);
    //storing the contect in DancingI
    dancingI = glutCreateWindow ("DancingI");
    
    //glClearColor(0.75, 0.75, 0.75, 0.0);         // grey background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 10.0, 0.0, 10.0, 1, 0);   // setup a 10x10x2 viewing world
    
    //setting up the display function with the function choice
    glutDisplayFunc(choice);
    //setting up the glutTimerFunction to be invoked
    //after ever 33 seconds
    //hence diving the frame rate of 30 frame per seconds
    glutTimerFunc(33, timeKeeper, 0);
    //The glut keyboard control function
    glutKeyboardFunc(keyboardFunction);
    
	glLineWidth(2.0); /* Set the line width to 2 for thicker lines */
    //starting the main glut loop
    glutMainLoop();
    
    return 0;
}
