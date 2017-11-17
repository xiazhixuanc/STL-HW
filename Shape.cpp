／／author： Yujie Ren  10415719
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

class Shape {
public:
    virtual string print() = 0;
};
class Cylinder : public Shape {
private:
    double r, h;
    int facets;
    double vArray[3];
public:
    Cylinder(double x, double y, double z, double r, double h, int facets): r(r), h(h), facets(facets) {
        vArray[0] = x;
        vArray[1] = y;
        vArray[2] = z;
    }
    string print1(double x1,double y1,double z1) {
        ostringstream s;
        s << " " << vArray[0] + x1 << " " << vArray[1] + y1 << " " << vArray[2] + z1 << "\n";
        return s.str();
    }
    string print2(double x1,double y1,double z1) {
        ostringstream s;
        s << " " << vArray[0] + x1 << " " << vArray[1] + y1  << " " << vArray[2] + z1 << "\n";
        return s.str();
    }
    string angle_print(double n) {
        double angle1 = (n*360*3.14159265)/(180*facets);
        double angle2 = ((n+1)*360*3.14159265)/(180*facets);
        string str = "";
        str = "  facet normal" + str + print1(cos(angle1+360/facets), sin(angle1+360/facets), 0)+"    outer loop\n"+
                      "      vertex" + print1(r*cos(angle2), r*sin(angle2),h)+
                      "      vertex" + print1(r*cos(angle1), r*sin(angle1),h)+
                      "      vertex" + print1(r*cos(angle1), r*sin(angle1),0)+
                      "    endloop\n  endfacet\n"+
                      "  facet normal" + print2(cos(angle1+360/facets),sin(angle1+360/facets),0)+"    outer loop\n"+
                      "      vertex"  + print1(r*cos(angle2), r*sin(angle2),h)+
                      "      vertex"  + print1(r*cos(angle1), r*sin(angle1),0)+
                      "      vertex" + print1(r*cos(angle2), r*sin(angle2),0)+
                      "    endloop\n  endfacet\n"+
                      "  facet normal"+ print1(0,0,1) + "    outer loop\n"+
                      "      vertex" + print1(0,0,h)+
                      "      vertex" + print1(r*cos(angle1), r*sin(angle1),h)+
                      "      vertex" + print1(r*cos(angle2), r*sin(angle2),h)+
                      "    endloop\n  endfacet\n"+
                      "  facet normal"+ print1(0,0,-1)+"    outer loop\n"+
                      "      vertex" + print1(0,0,0)+
                      "      vertex" + print1(r*cos(angle2), r*sin(angle2),0)+
                      "      vertex" + print1(r*cos(angle1), r*sin(angle1),0)+
                      "    endloop\n  endfacet\n";
        return str;
    };
    string print() {                         //print the whole Cylinder
        string str = "";
        if (facets < 3)
            cout<<"Face is less than 3, Can not print";
        else
            for (int indexofvector=0;indexofvector<facets;indexofvector++)
                str = str + angle_print(indexofvector);
        return str;
    }
};

class Cube: public Shape {
private:
    double size;
    double vArray[3];
public:
    Cube(double x, double y, double z, double size) : size(size) {
        vArray[0] = x;
        vArray[1] = y;
        vArray[2] = z;
    };

    string facet_vector(double vector_direction, uint8_t vector_location) {
        ostringstream s;
        for (uint8_t temp = 0; temp < 3; temp++)
            if (temp == vector_location)
                s << " " << vector_direction;
            else
                s << " 0";
        s << "\n";
        return s.str();
    }

    string vertex_base(double vector_direction, uint8_t vector_location,double else_value) {
        ostringstream s;
        for (uint8_t temp = 0; temp < 3; temp++)
            if (temp == vector_location)
                s << " " << ((vector_direction+1)/2)*size + vArray[temp];
            else
                s << " " << else_value*size + vArray[temp];
        s << "\n";
        return  s.str();
    }

    //Define the third point of the triangle
    string vertex_third_point(double vector_direction, uint8_t vector_location,double else_value) {
        ostringstream s;
        for (uint8_t temp = 0; temp < 3; temp++)
            if (temp == vector_location)
                s << " " << ((vector_direction+1)/2)*size + vArray[temp];
            else{
                s << " " << abs(else_value)*size + vArray[temp];
                else_value++;
            }
        s << "\n";
        return s.str();
    }

    string triangle_print(double vector_direction, uint8_t vector_location) {
        string str = "";
        str = "  facet normal" + str + facet_vector(vector_direction, vector_location) +
                        "    outer loop\n" +
                        "      vertex" + vertex_base(vector_direction, vector_location, 0) +
                        "      vertex" + vertex_base(vector_direction, vector_location, 1) +
                        "      vertex" + vertex_third_point(vector_direction, vector_location, 0) +
                        "    endloop\n  endfacet\n" +
                        "  facet normal" + facet_vector(vector_direction, vector_location) + "    outer loop\n" +
                        "      vertex" + vertex_base(vector_direction, vector_location, 1) +
                        "      vertex" + vertex_base(vector_direction, vector_location, 0) +
                        "      vertex" + vertex_third_point(vector_direction, vector_location, -1) +
                        "    endloop\n  endfacet\n";
        return str;
    }
    //Print two triangle for one face reverse
    string triangle_print_reverse(double vector_direction, uint8_t vector_location){
        string str = "";
        str = "  facet normal"+ str + facet_vector(vector_direction,vector_location) +"    outer loop\n"+
                        "      vertex" + vertex_base(vector_direction,vector_location,1)+
                        "      vertex" + vertex_base(vector_direction,vector_location,0)+
                        "      vertex" + vertex_third_point(vector_direction,vector_location,0)+
                        "    endloop\n  endfacet\n"+
                        "  facet normal"+ facet_vector(vector_direction,vector_location)+"    outer loop\n"+
                        "      vertex" + vertex_base(vector_direction,vector_location,0)+
                        "      vertex" + vertex_base(vector_direction,vector_location,1)+
                        "      vertex" + vertex_third_point(vector_direction,vector_location,-1)+
                        "    endloop\n  endfacet\n";
        return str;
    }
    string print(){
        string str="";
        str = triangle_print(1, 0) + triangle_print_reverse(-1, 0)+
                      triangle_print_reverse(1, 1) + triangle_print(-1, 1)+
                      triangle_print(1, 2) + triangle_print_reverse(-1, 2);
        return str;
    }
};


class CAD {
private:
    vector<Shape*> shapes;
public:
    void add(Shape *p){
        shapes.push_back(p);
    }
    void write(string filename){
        fstream fin(filename, fstream::out);
        fin<< "solid OpenSCAD_Model\n";
        for(int indexofvector=0;indexofvector<shapes.size();indexofvector++)
            fin << shapes[indexofvector]->print();
        fin<<"endsolid OpenSCAD_Model\n";
        cout<<"Successfully finished.\n";
    }
};

int main() {
    CAD c;
    c.add(new Cube(0,0,0,   5));
    c.add(new Cylinder(100,0,0,    3, 10, 10));
    c.write("test.stl");
}