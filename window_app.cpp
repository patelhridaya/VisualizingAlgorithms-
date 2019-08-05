//
//  window_app.cpp
//  Visualizing Algorithms
//
//  Created by Hridaya Patel on 5/8/17.
//  Copyright © 2017 Hridaya Patel. All rights reserved.
//


#include <iostream> //input and output
#include "window_app.h"
#include <stdlib.h> //use of library algorithms
#include <time.h> //to clock our program and keep track of the delay after each step
#include <utility>//objects can hold two values of different types

const double AppWindow::LEFT = -0.5; //the x-position of the left boundary of the animation
const double AppWindow::RIGHT = 0.5; //the x-position of the right boundary of the animation
const double AppWindow::BOTTOM = -0.5; //the y-position of the bottom boundary of the animation
const double AppWindow::TOP = 0.5; //the y-position of the top boundary of the animation

// fills the array of numbers with random values, sets default values of algorithm variables
void AppWindow::init()
{
    // fill the array with random values in the range <1-20>
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        _numbers[i] = (rand() % 20) + 1;
    }
    
    //set default values
    _firstUnsorted = 0;
    _current = -1;
    _running = false; //wait for the user to start it
    _algorithm = INSERTION_SORT;
}

AppWindow::AppWindow(const char* label, int x, int y, int w, int h)
    :GlutWindow(label, x, y, w, h)
{
    // create menu items
    addMenuEntry("Fill Array with Random Integers", evInit); //fills the array with random values and initializes the algorithm
    addMenuEntry("Run the Insertion Sort", evRunInsertion); //this menu item starts the insertion sort
    addMenuEntry("Run the Selection Sort", evRunSelection); //this menu item starts the selection sort
    addMenuEntry("Run the Bubble Sort", evRunBubble); //this menu item starts the bubble sort,
    srand(time(NULL)); //initializes and generates random numbers
    
    init(); //initializes the array and algorithm variables when window opens
}


void AppWindow::windowToScene(float& x, float &y)
{
    x = (2.0f*(x / float(_w))) - 1.0f;
    y = 1.0f - (2.0f*(y / float(_h)));
}

// Called every time there is a window event
void AppWindow::handle(const Event& e)
{
    bool rd = true;
    
    if (e.type == Keyboard)
    {
        switch (e.key)
        {
            case 27: // Esc was pressed
                exit(1);
                break;
                
            case 'r': // r was pressed
            case 'R': // R was pressed
                init(); //call to intialize array with random ints
                break;
                
            case 'i':
            case 'I':
                
                //this will start Insertion Sort
                if (_running == false)
                {
                    _running = true;
                    _algorithm = INSERTION_SORT;
                }
                break;
                
            case 's': // s was pressed
            case 'S': // S was pressed
                
                //this will start Selection Sort
                if (_running == false)
                {
                    _running = true;
                    _algorithm = SELECTION_SORT;
                }
                break;
                
            case 'b': // b was pressed
            case 'B': // B was pressed
                
                //this will start Bubble Sort
                if (_running == false)
                {
                    _running = true;
                    _algorithm = BUBBLE_SORT;
                }
                break;
            default:
                break;
        }
    }
    
    else if (e.type == Menu)
    {
        switch (e.menuev)
        {
            case evInit: // menu item "Fill Array with Random Integers" was selected
                init(); //initialize the array and algorithm variables
                break;
            case evRunInsertion: //"Run the Insertion Sort" was selected
                
                if (_running == false)
                {
                    _running = true;
                    _algorithm = INSERTION_SORT;
                }
                break;
            case evRunSelection: //"Run the Selection Sort" was selected
                
                if (_running == false)
                {
                    _running = true;
                    _algorithm = SELECTION_SORT;
                }
                break;
            case evRunBubble: //"Run the Bubble Sort" was selected
                
                if (_running == false)
                {
                    _running = true;
                    _algorithm = BUBBLE_SORT;
                }
                break;
            default:
                rd = false; // no need to redraw
                break;
        }
    }
    
    if (rd) redraw();
}

void AppWindow::resize(int w, int h)
{
    
    glViewport(0, 0, w, h); //defines that OpenGL should use the whole window for rendering
    _w = w; _h = h;
}

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw()
{
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //start drawing the rectangles
    glBegin(GL_QUADS);
    
    //one rectangle for each array element
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (i == _current) //we are drawing the element that is currently being sorted
        {
            glColor3d(1.0, 0.0, 0.0); //red
        }
        else if (i < _firstUnsorted) //we are drawing an element from the sorted part of the array
        {
            glColor3d(0.0909804*i, .6, 0.952941); //gradient
            
            
        }
        else //we are drawing an element from the unsorted part of the array
        {
            glColor3d(0.752941, 0.752941, 0.752941); //Gray color for rectangles
        }
        
        //draw the rectangle
        double leftX = LEFT + (i * ((RIGHT - LEFT) / ARRAY_SIZE)); //left boundary of the rectangle
        double rightX = leftX + (((RIGHT - LEFT) / ARRAY_SIZE) / 2); //right boundary of the rectangle
        double bottomY = BOTTOM; //bottom boundary of the rectangle
        double topY = bottomY + (_numbers[i] * ((TOP - BOTTOM) / ARRAY_SIZE)); //top boundary of the rectangle
        
        glVertex2d(leftX, bottomY); //bottom left corner of the rectangle
        glVertex2d(rightX, bottomY); //bottom right corner of the rectangle
        glVertex2d(rightX, topY); //top right corner of the rectangle
        glVertex2d(leftX, topY); //top left corner of the rectangle
    }
    
    glEnd();
    
    if (_current >= 0 && _current < ARRAY_SIZE) //if the current position is within the array
    {
        
        //arrow pointing to the current element
        glBegin(GL_TRIANGLES);
        glColor3d(1.0, 0.0, 0.0); //red color for arrow
        
        //draw the arrow
        //it's position is based on the index of the current element
        glVertex2d(-0.5 + (_current * 0.025 * 2) - 0.0125, -0.575); //bottom left corner of the arrow
        glVertex2d(-0.5 + (_current * 0.025 * 2) + 0.025 + 0.0125, -0.575); //bottom right corner of the arrow
        glVertex2d(-0.5 + (_current * 0.025 * 2) + 0.0125, -0.525); //top corner of the arrow
        glEnd();
    }
    
    // Swap buffers
    glFlush();         //ensures that the previous command flushes pipeline and finishes in finite time.
    glutSwapBuffers(); //drawing to the back buffer, now brings it to the front
}

//performs one step of the insertion sort algorithm
void AppWindow::insertionSort()
{
    //if the algorithm just started
    //the insertion sort starts at the second element of the array
    if (_current == -1)
    {
        _firstUnsorted = 1;
        _current = _firstUnsorted;
    }
    
    //if all is sorted, stop the algorithm
    else if (_firstUnsorted == ARRAY_SIZE && _current == ARRAY_SIZE)
    {
        _running = false;
        _current = -1;
    }
    
    //we got all the way to the beginning, return to the first unsorted element
    else if (_current == 0)
    {
        _current = _firstUnsorted;
    }
    
    //if the element that is currently being sorted is smaller than it's predecessor
    else if (_numbers[_current] < _numbers[_current - 1])
    {
        //swap them
        std::swap(_numbers[_current], _numbers[_current - 1]);
        
        if (_current == _firstUnsorted) _firstUnsorted++;
        
        _current--;
    }
    
    //if the element that is currently being sorted isn't smaller than it's predecessor
    else
    {
        
        if (_current == _firstUnsorted) _firstUnsorted++;
        //we move to the next unsorted element
        _current = _firstUnsorted;
    }
}

//does one step of selection sort
void AppWindow::selectionSort()
{
    //index of smallest sorted element
    static int smallest;
    
    
    if (_current == -1)
    {
        _firstUnsorted = 0;
        _current = _firstUnsorted;
        smallest = _firstUnsorted;
    }
    
    //if all is sorted, stop the algorithm
    else if (_firstUnsorted == ARRAY_SIZE)
    {
        _running = false;
        _current = -1;
    }
    
    //if the current element is smaller than the previous smallest unsorted element
    else if (_numbers[_current] < _numbers[smallest])
    {
        //update the index of the smallest element
        smallest = _current;
        
        //if we reached the end of the array
        if (_current == ARRAY_SIZE - 1)
        {
            //swap the smallest unsorted element and the first unsorted element
            std::swap(_numbers[smallest], _numbers[_firstUnsorted]);
            
            //move the unsorted part of the array one position to the right
            _firstUnsorted++;
            
            //start again from the new beginning of the unsorted array
            _current = _firstUnsorted;
            
            //reset the smallest element
            smallest = _firstUnsorted;
        }
        
        //if we didn't reach the end of the array
        else
        {
            //just move one position to the right
            _current++;
        }
    }
    
    //if the current element isn't smaller than the smallest unsorted element
    else
    {
        //if we reached the end of the array
        if (_current == ARRAY_SIZE - 1)
        {
            //swap the smallest unsorted element and the first unsorted element
            std::swap(_numbers[smallest], _numbers[_firstUnsorted]);
            
            //move the unsorted part of the array one position to the right
            _firstUnsorted++;
            
            //start again from the new beginning of the unsorted array
            _current = _firstUnsorted;
            
            //reset the smallest element
            smallest = _firstUnsorted;
        }
        
        //if we didn't reach the end of the array
        else
        {
            //just move one position to the right
            _current++;
        }
    }
}

//performs one step of the bubble sort algorithm
void AppWindow::bubbleSort()
{
    //here we record whether a swap occurred in the current iteration
    static bool swapped;
    
    //if the algorithm just started, initialize the variables
    if (_current == -1)
    {
        _firstUnsorted = 0;
        _current = ARRAY_SIZE - 1;
        swapped = false;
    }
    //if all is sorted, stop the algorithm
    else if (_firstUnsorted == ARRAY_SIZE)
    {
        _running = false;
        _current = -1;
    }
    //we are at the end of the current iteration
    else if (_current == _firstUnsorted)
    {
        //if no swap occurred, its done, stop the algorithm
        if (!swapped)
        {
            _running = false;
            _firstUnsorted = ARRAY_SIZE;
            _current = -1;
        }
        //else if swap occurred, move to the next iteration
        else
        {
            _firstUnsorted++;
            _current = ARRAY_SIZE - 1;
            swapped = false;
        }
    }
    //if the current element is smaller than the preceding element
    else if (_numbers[_current] < _numbers[_current - 1])
    {
        //swap them and continue left 
        std::swap(_numbers[_current], _numbers[_current - 1]);
        swapped = true;
        _current--;
    }
    //if the current element isn't smaller than the preceding element
    else
    {
        //continue left
        _current--;
    }
}

// this method is continuously called when events are not being received
// each execution of this method performs one step of the currently running algorithm (if any) and then redraws the window
void AppWindow::idle()
{
    static int lastTime = glutGet(GLUT_ELAPSED_TIME); //last time we were here
    int nowTime = glutGet(GLUT_ELAPSED_TIME); //current time
    
    if (nowTime - lastTime < DELAY) //if DELAY ms haven't elapsed, do nothing
    {
        return;
    }
    
    lastTime = nowTime;
    
    if (_running == true) //algorithm is running
    {
        switch (_algorithm) //call the proper method
        {
            case INSERTION_SORT:
                insertionSort();
                break;
            case SELECTION_SORT:
                selectionSort();
                break;
            case BUBBLE_SORT:
                bubbleSort();
                break;
            default:
                break;
        }
    }
    
    redraw(); //redraw the window
}

