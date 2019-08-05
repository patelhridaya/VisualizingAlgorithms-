//
//  window_glut.cpp
//  Visualizing Algorithms
//
//  Created by Hridaya Patel on 5/8/17.
//  Copyright © 2017 Hridaya Patel. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "window_glut.h"


static GlutWindow* Singleton;      // we make it static so this pointer is hidden from other source files
static GlutWindow::Event CurEvent; // global event to speed-up event creation and keep track of events



GlutWindow::GlutWindow(const char* label, int x, int y, int w, int h)
{
    
    Singleton = this;
    
    // Set window position (from top corner), and size (width and height)
    glutInitWindowPosition(x, y);
    glutInitWindowSize(w, h);
    glutCreateWindow(label);
    
    // Initialize OpenGL settings as we want
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(6);
    glLineWidth(4);
    
    // Set up GLUT callback functions to receive events:
    ::glutKeyboardFunc(glutKeyboardCB);
    ::glutSpecialFunc(glutSpecialCB);
    ::glutMouseFunc(glutMouseCB);
    ::glutMotionFunc(glutMotionCB);
    
    // Set up idle callback for background processing if needed:
    ::glutIdleFunc(glutIdleCB);
    
    // Set up GLUT callback function for resizing window:
    ::glutReshapeFunc(glutReshapeCB);
    
    // Set up GLUT callback for drawing the scene:
    ::glutDisplayFunc(glutDisplayCB);
    
    // GLUT also supports a simple menu system, you may try this:
    int id = ::glutCreateMenu(glutMenuCB); // the returned id could be used for adding submenus if needed
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//callbacks for glut


void GlutWindow::glutSpecialCB(int key, int x, int y)
{
    CurEvent.type = SpecialKey;
    CurEvent.key = key;
    CurEvent.mx = x;
    CurEvent.my = y;
    Singleton->handle(CurEvent);
}

void GlutWindow::glutKeyboardCB(unsigned char key, int x, int y)
{
    CurEvent.type = Keyboard;
    CurEvent.key = key;
    CurEvent.mx = x;
    CurEvent.my = y;
    Singleton->handle(CurEvent);
}

void GlutWindow::glutMotionCB(int x, int y)
{
    // use this to ignore a mouse event right after menu selection:
    //if ( CurEvent.type==Menu ) return;
    CurEvent.type = Motion;
    CurEvent.mx = x;
    CurEvent.my = y;
    Singleton->handle(CurEvent);
}

void GlutWindow::glutMouseCB(int b, int s, int x, int y)
{
    CurEvent.type = s == GLUT_UP ? MouseUp : MouseDown;
    CurEvent.button = b;
    CurEvent.mx = x;
    CurEvent.my = y;
    Singleton->handle(CurEvent);
}


void GlutWindow::glutMenuCB(int m)
{
    CurEvent.type = Menu;
    CurEvent.menuev = m;
    Singleton->handle(CurEvent);
}

void GlutWindow::glutIdleCB()
{
    Singleton->idle();
}

void GlutWindow::glutReshapeCB(int w, int h)
{
    Singleton->resize(w, h);
}

void GlutWindow::glutDisplayCB()
{
    Singleton->draw();
}


