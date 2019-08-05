//
//  window_glut.h
//  Visualizing Algorithms
//
//  Created by Hridaya Patel on 5/8/17.
//  Copyright © 2017 Hridaya Patel. All rights reserved.
//

#ifndef window_glut_h
#define window_glut_h


#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


class GlutWindow
{
public:
    enum EventType { SpecialKey, Keyboard, MouseUp, MouseDown, Motion, Menu, None };
    struct Event
    {
        EventType type;
        int button, key, menuev, mx, my;
        Event() { type = None; button = key = menuev = mx = my = 0; }
    };
    
private: // callback functions internal
    static void glutIdleCB();
    static void glutMenuCB(int m);
    static void glutMouseCB(int b, int s, int x, int y);
    static void glutMotionCB(int x, int y);
    static void glutDisplayCB();
    static void glutKeyboardCB(unsigned char key, int x, int y);
    static void glutSpecialCB(int key, int x, int y);
    static void glutReshapeCB(int w, int h);
    
public:
    
    GlutWindow(const char* label, int x, int y, int w, int h);
    
    //creation of submenus
    void addMenuEntry(const char* label, int menuev) { ::glutAddMenuEntry(label, menuev); }
    
    //redraw the windows
    void redraw() { glutPostRedisplay(); }
    
    
    void run() { glutMainLoop(); }
    

//derived functions from the user class
private:
    virtual void draw() = 0;
    virtual void handle(const Event& e) {}
    virtual void resize(int w, int h) {}
    virtual void idle() {}
};

#endif

