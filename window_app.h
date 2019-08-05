//
//  window_app.h
//  Visualizing Algorithms
//
//  Created by Hridaya Patel on 5/8/17.
//  Copyright © 2017 Hridaya Patel. All rights reserved.
//


#ifndef window_app_h
#define window_app_h

#include "window_glut.h"

class AppWindow : public GlutWindow
{
private:
    static const int ARRAY_SIZE = 25; //size of the array
    static const int DELAY = 85; //delay in milliseconds from each step
    static const double LEFT; //the x-position of the left boundary
    static const double RIGHT; //the x-position of the right boundary
    static const double BOTTOM; //the y-position of the bottom boundary
    static const double TOP; //the y-position of the top boundary
    
    enum MenuEv //menu items (will appear with right click)
    {
        evInit,     //fills array with rand int's and stops any running algorithm
        evRunInsertion,  //starts Insertion sort
        evRunSelection,  //starts Selection sort
        evRunBubble      //starts Bubble sort
    };
    
    enum Algorithm
    {
        INSERTION_SORT,
        SELECTION_SORT,
        BUBBLE_SORT
    };
    
    int _w, _h; // the width and height of the window
    int _numbers[ARRAY_SIZE]; //array filled with intgers for sorting
    
    
    int _firstUnsorted;
    
    //index of the position in the array where the currently running algorithm is at
    int _current;
    
    bool _running; // true if one of the algorithms is currently running
    
    Algorithm _algorithm; 
    
    void init(); // fills the array of numbers with random values, sets default values of algorithm variables
    
public:
    AppWindow(const char* label, int x, int y, int w, int h);
    void windowToScene(float& x, float &y);
    
private: //inhertited functions derived from base class
    virtual void handle(const Event& e);
    virtual void draw();
    virtual void resize(int w, int h);
    virtual void idle();
    
    
    void insertionSort(); //calls insertion sort algorithm
    
    
    void selectionSort(); //calls selection sort algorithm
    
    
    void bubbleSort(); //calls bubble sort algorithm
};

#endif // APP_WINDOW_H

