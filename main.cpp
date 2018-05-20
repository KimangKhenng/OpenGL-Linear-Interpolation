#include "utility.h"

void init(void);
void display(void);
void createGLUTMenus();
void selectGeometricType(int option);
void selectAxisColor(int option);
void selectPlotColor(int option);
void keyEvent(unsigned char Key, int x, int y);
void calculateInterpolation();

static vector<Point2D> _point;
static vector<GLfloat> _interpolation_point;
static GEO_TYPE _type = _POINT;
static vector<float> _color_axis = _blue;
static vector<float> _color_ori = _red;
static vector<float> _color_inter = _blue;
static float X_SCALE_UNIT = 0.05;   // 1/25
static float  Y_SCALE_UNIT = 1.0;      // 1/1

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Linear Interpolation");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyEvent);
    createGLUTMenus();
    glutMainLoop();
    return 0;
}
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Utility::drawingAxis(1000,1000,_color_axis,_red,X_SCALE_UNIT,Y_SCALE_UNIT);
    Utility::plot2D(_point,_color_ori,_color_inter,_type,X_SCALE_UNIT,Y_SCALE_UNIT);
    glFlush();
}
void init(void)
{
    //Clear background color to white
        glClearColor(0.0, 0.0, 0.0,0.0);
    //change projection mode
        glMatrixMode(GL_PROJECTION);
    // set current matrix to identiy matrix
        glLoadIdentity();
        gluOrtho2D(0, 1200, 0, 1200);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(10);
        glLineWidth(2);
        cout<<"Linear Interpolation"<<endl;
        cout<<"By Kheang Kimang"<<endl;
        cout<<"Place your data in project directory"<<endl;
        cout<<"Use menu to change color and drawing primitive"<<endl;
        cout<<"Use - + to scale x-axis"<<endl;
        cout<<"use 4 6 to scale scale y-axis"<<endl;
        cout<<"Press 0 to calculate interpolation"<<endl;
        _point = Utility::readString("data.txt");
        _interpolation_point = Utility::readInterpolationPoint("interpolation.txt");
}
void createGLUTMenus() {

    // create the menu and
    // handle the events
    int submenu = glutCreateMenu(selectAxisColor);
    //add entries to our menu
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    // Menu 2
    // handle the events
    int submenu_1 = glutCreateMenu(selectGeometricType);
    //add entries to our menu
    glutAddMenuEntry("Point",_POINT);
    glutAddMenuEntry("Line",_LINE);
    // Menu 3
    int submenu_2 = glutCreateMenu(selectPlotColor);
    glutAddMenuEntry("Red/Blue",_R_B);
    glutAddMenuEntry("Red/Green",_R_G);
    glutAddMenuEntry("Green/Red",_G_R);
    glutAddMenuEntry("Green/Blue",_G_B);
    glutAddMenuEntry("Blue/Red",_B_R);
    glutAddMenuEntry("Blue/Green",_B_G);
    // attach the menu to the right button
    int menu = glutCreateMenu(selectAxisColor);
    glutAddSubMenu("Geometric Type",submenu_1);
    glutAddSubMenu("Axis Color",submenu);
    glutAddSubMenu("Plot Color",submenu_2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void selectGeometricType(int option)
{
    switch (option) {
    case _POINT:
        _type = _POINT;
        glutPostRedisplay();
        break;
    case _LINE:
        _type = _LINE;
        glutPostRedisplay();
        break;
    }

}
void selectAxisColor(int option) {

    switch (option) {
    case RED :
        _color_axis = _red;
        glutPostRedisplay();
        break;
    case GREEN :
        _color_axis = _green;
        glutPostRedisplay();
        break;
    case BLUE :
        _color_axis = _blue;
        glutPostRedisplay();
        break;
    }
}
void selectPlotColor(int option){
    switch (option) {
    case _R_B:
        _color_ori = _red;
        _color_inter = _blue;
        glutPostRedisplay();
        break;
    case _R_G:
        _color_ori = _red;
        _color_inter = _green;
        glutPostRedisplay();
        break;
    case _G_B:
        _color_ori = _green;
        _color_inter = _blue;
        glutPostRedisplay();
        break;
    case _G_R:
        _color_ori = _green;
        _color_inter = _red;
        glutPostRedisplay();
        break;
    case _B_R:
        _color_ori = _blue;
        _color_inter = _red;
        glutPostRedisplay();
        break;
    case _B_G:
        _color_ori = _blue;
        _color_inter = _green;
        glutPostRedisplay();
        break;
    }
}
void keyEvent(unsigned char Key, int x, int y){
    switch (Key) {
    case 43 :
        //+ key
        // Scale up X-Axis
        X_SCALE_UNIT += INCRE_UNIT;
        glutPostRedisplay();
        break;
    case 45:
        // - key
        // Scale down X-Axis
        X_SCALE_UNIT -= INCRE_UNIT;
        glutPostRedisplay();
        break;
    case 54:
        // 6 key
        // Scale Up Y-Axis
        Y_SCALE_UNIT += INCRE_UNIT;
        glutPostRedisplay();
        break;
    case 52:
        // 4 key
        // Scale Down Y-Axis
        Y_SCALE_UNIT -= INCRE_UNIT;
        glutPostRedisplay();
        break;
    case 48:
        // 0 key
        // Calculate Interpolation Points
        calculateInterpolation();
        break;
    }
}
void calculateInterpolation(){
    _point = Utility::interpolate(_point,_interpolation_point);
    glutPostRedisplay();
}
