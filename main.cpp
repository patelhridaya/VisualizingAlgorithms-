//
//  main.cpp
//  Visualizing Algorithms
//
//  Created by Hridaya Patel on 5/8/17.
//  Copyright © 2017 Hridaya Patel. All rights reserved.
//

#include <iostream>
#include "window_app.h"


//Main function
int main(int argc, char** argv)
{
    //Init freeglut library:
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    
    AppWindow* w = new AppWindow("Visulaizing Algorithms Animation", 500, 500, 840, 680); //creates sizing of window and name
    
    
    w->run(); //this will start the main loop
}
