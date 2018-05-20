#include "utility.h"

void Utility::renderString(int pos1, int pos2, const char *str)
{
    int strLength;
    glRasterPos2i(pos1,pos2);
    strLength = static_cast<int>(strlen(str));
    for (int i = 0 ; i < strLength ; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
}

void Utility::drawingAxis(int x, int y, vector<float> color_line,
                          vector<float> color_label, float xscale, float yscale)
{
    glColor3f(color_line[0],color_line[1],color_line[2]);
    glBegin(GL_LINES);
        // Y-Axis
        glVertex2i(175,50);
        glVertex2i(175,y+175);
        // X-Axis
        glVertex2i(50,175);
        glVertex2i(x+175,175);
    glEnd();
    // Drawing unit
    int unit_y = (y)/10;
    int number_of_step_y = unit_y*12;
    char text[10];
    for(int i = 0 ; i < number_of_step_y ; i += unit_y){
        if( i != 0){
             renderString(165,i+170,"-");
        }
        itoa(i*yscale,text,10);
        if(i != 0){
            glColor3f(color_label[0],color_label[1],color_label[2]);
            renderString(110,i+170,text);
        }
    }
    // Drawing unit and number on x axis
    int unit_x = (x)/10;
    int number_of_step_x = unit_x*12;
    for(int i = 0 ; i < number_of_step_x ; i+= unit_x){
        if( i != 0 ){
            renderString(i+170,165,"|");
        }
        itoa(i*xscale,text,10);
        if(i != 0){
            glColor3f(color_label[0],color_label[1],color_label[2]);
            renderString(i+170,110,text);
        }
    }
}

void Utility::plot2D(vector<Point2D> _data, vector<float> color_ori, vector<float> color_inter,
                     GEO_TYPE p, float xscale, float yscale)
{
//    glColor3f(color[0],color[1],color[2]);
    switch(p){
    case _LINE:
        glBegin(GL_LINES);
        break;
    case _POINT:
        glBegin(GL_POINTS);
        break;
    }
    for(size_t i = 0 ; i < _data.size() ; i++ ){
        //cout<<"Scale Point"<<ScaleCenter(_data.at(i))._x<<" "<<ScaleCenter(_data.at(i))._y<<endl;
        if(_data.at(i)._color == _none){
            glColor3f(color_ori[0],color_ori[1],color_ori[2]);
        }else{
            glColor3f(color_inter[0],color_inter[1],color_inter[2]);
        }
        glVertex2f(TranslateCenter(ScaleCenter(_data.at(i),xscale,yscale))._x,
                   TranslateCenter(ScaleCenter(_data.at(i),xscale,yscale))._y);
    }
    glEnd();
}

vector<Point2D> Utility::interpolate(vector<Point2D> _data, vector<float> interpolate_point)
{
    vector<Point2D> p;
    size_t original_size = _data.size();
    size_t interpolation_size = interpolate_point.size();
    for(size_t i = 0,j=0 ; i < original_size ; i++){
        p.push_back(_data.at(i));
        if( j < interpolation_size ){
            if(interpolate_point.at(j) > _data.at(i)._x && interpolate_point.at(j) < _data.at(i+1)._x){
                float slope = (_data.at(i)._y - _data.at(i+1)._y)/(_data.at(i)._x - _data.at(i+1)._x);
                float y = _data.at(i)._y + slope*(interpolate_point.at(j)-_data.at(i)._x);
                Point2D u = Point2D(interpolate_point.at(j),y,_blue);
                p.push_back(u);
                j++;
            }
        }
    }
    return p;
}

Point2D Utility::TranslateCenter(Point2D p)
{
    return Point2D(p._x+175,p._y + 175,p._color);
}

Point2D Utility::ScaleCenter(Point2D p, float xscale, float yscale)
{
    return Point2D(static_cast<float>(p._x/xscale) ,p._y/yscale,p._color);
}

vector<Point2D> Utility::readString(const char *filename)
{
    FILE *file = fopen(filename,"r");
    float data[2][AMOUNT_DATA];
    vector<Point2D> point;
    if(file == NULL)
    {
        cout<<"File not found"<<endl;
        fclose(file);
    }else{

        for(int i = 0 ; i < AMOUNT_DATA ; i++){
            fscanf(file,"%f %f", &data[0][i], &data[1][i]);
            Point2D p = Point2D(data[0][i],data[1][i],_none);
            point.push_back(p);
        }
    }
    fclose(file);
    return point;
}

vector<float> Utility::readInterpolationPoint(const char *filename)
{
    FILE *file = fopen(filename,"r");
    float data[AMOUNT_POINT];
    vector<float> point;
    if(file == NULL)
    {
        cout<<"File not found"<<endl;
        fclose(file);
    }else{

        for(int i = 0 ; i < AMOUNT_POINT ; i++){
            fscanf(file,"%f", &data[i]);
            point.push_back(data[i]);
        }
    }
    fclose(file);
    return point;
}
