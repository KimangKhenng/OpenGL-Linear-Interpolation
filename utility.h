/////////////////////
// Linear Interpolation
// By Kheang Kimang
// Utility sotres function for computation
//////////////////////
#ifndef UNILITY_H
#define UNILITY_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <string.h>

#define AMOUNT_DATA 8
#define AMOUNT_POINT 6
#define INCRE_UNIT 0.001
using namespace std;
////////////////
/// \brief The GEO_TYPE enum
/// Enum to define geometry type
enum GEO_TYPE{_POINT,_LINE};

//////////////
/// \brief The COLOR enum
/// Enum to define color for selcting on menu
enum COLOR{RED,GREEN,BLUE};

///////////////
/// \brief The PLOT_COLOR enum
/// Enum to define plot color
enum PLOT_COLOR{_R_B,_R_G,_G_R,_G_B,_B_R,_B_G};

//////////////
// Static Predefined Variable
static vector<float> _red = {1.0f,0.0f,0.0f};
static vector<float> _blue= {0.0f,0.0f,1.0f};
static vector<float> _green = {0.0f,1.0f,0.0f};
static vector<float> _none = {1.0f,1.0f,1.0f};
/////////////

/////////////
/// \brief The Point2D class
/// Class to represent Point
class Point2D{
public:
    float _x;
    float _y;
    vector<float> _color;
    Point2D(float x,float y,vector<float> color):_x(x),_y(y),_color{color}{

    }
};
////////////
/// \brief The Utility class
/// Class for utility Function
class Utility
{
public:
    //////////////
    /// \brief renderString
    /// \param pos1 = x coordinate on screen
    /// \param pos2 = y coordinate on screen
    /// \param str = string value
    /// Function to render string on screen
    static void renderString(int pos1, int pos2, const char *str);
    /////////////
    /// \brief drawingAxis
    /// \param x = prefered x length from 0
    /// \param y = prefered y length from 0
    /// \param color_line = line color ( apply to both x and y)
    /// \param color_label = label color ( apply to number on each coordinate)
    /// A function to draw axis on screen
    static void drawingAxis(int x, int y, vector<float> color_line,vector<float> color_label,float xscale,float yscale);
    /////////////
    /// \brief plot2D
    /// \param _data = data to plot in vector format
    /// \param color_ori = color of original point before performing interpolation
    /// \param color_inter = color of interpolated point
    /// \param p = Primitive type to render ( Lines or Points)
    /// A function to plot point of screen
    static void plot2D(vector<Point2D> _data, vector<float> color_ori,vector<float> color_inter, GEO_TYPE p,float xscale,float yscale);
    ////////////
    /// \brief interpolate
    /// \param _data = data to be interpolated
    /// \param interpolate_point = point to interpolate
    /// \return new data ( origial + interpolated)
    /// A function to calculate interpolation point
    static vector<Point2D> interpolate(vector<Point2D> _data,vector<float> interpolate_point);
    ////////////
    /// \brief TranslateCenter
    /// \param p = point to transform
    /// \return new transformed point
    /// Transform data's coordinate to local coordinate system to be ploted correctly
    static Point2D TranslateCenter(Point2D p);
    /////////////
    /// \brief ScaleCenter
    /// \param p = point to scale
    /// \return new transformed point
    /// A function to perform when we need to scale axis
    static Point2D ScaleCenter(Point2D p,float xscale,float yscale);
    ////////////
    /// \brief readString
    /// \param filename = data file
    /// \return vector of point
    /// A function to extract data from text file
    static vector<Point2D> readString(const char* filename);
    ////////////
    /// \brief readInterpolationPoint
    /// \param filename = data file
    /// \return vector of interpolation point
    /// A function to extract interpolation point from text file
    static vector<float> readInterpolationPoint(const char* filename);

};

#endif // UNILITY_H
