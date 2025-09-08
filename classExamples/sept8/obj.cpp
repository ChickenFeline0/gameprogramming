#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <fstream>
#include <sstream> 
#include <map>

using namespace std;

// Base Shape class
class Shape {
public:
    virtual double area() = 0;      // Pure virtual function
    virtual double perimeter() = 0; // Pure virtual function
    virtual void display() = 0;     // Pure virtual function
    virtual ~Shape() {}             // Virtual destructor
};

// Circle class
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() override {
        return M_PI * radius * radius;
    }
    
    double perimeter() override {
        return 2 * M_PI * radius;
    }
    
    void display() override {
        cout << "Circle - Radius: " << radius 
             << ", Area: " << area() 
             << ", Perimeter: " << perimeter() << endl;
    }
};

// Rectangle class
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() override {
        return width * height;
    }
    
    double perimeter() override {
        return 2 * (width + height);
    }
    
    void display() override {
        cout << "Rectangle - Width: " << width 
             << ", Height: " << height
             << ", Area: " << area() 
             << ", Perimeter: " << perimeter() << endl;
    }
};

// Square class (inherits from Shape)
class Square : public Shape {
private:
    double side;
    
public:
    Square(double s) : side(s) {}
    
    double area() override {
        return side * side;
    }
    
    double perimeter() override {
        return 4 * side;
    }
    
    void display() override {
        cout << "Square - Side: " << side 
             << ", Area: " << area() 
             << ", Perimeter: " << perimeter() << endl;
    }
};



unique_ptr<Shape> circleFactory(double radius)
{
    return make_unique<Circle>(radius);
}

unique_ptr<Shape> rectangleFactory(double width, double height)
{
    return make_unique<Rectangle>(width, height);
}

unique_ptr<Shape> squareFactory(double side)
{
    return make_unique<Square>(side);
}

unique_ptr<Shape> shapeFactory(string line)
{
    stringstream stringIn(line);
    string type;
    stringIn >> type;
    
    if(type == "CIRCLE") {
        double radius;
        stringIn >> radius;
        return circleFactory(radius);
    }
    if(type == "RECTANGLE") {
        double width, height;
        stringIn >> width >> height;
        return rectangleFactory(width, height);
    }
    if(type == "SQUARE") {
        double side;
        stringIn >> side;
        return squareFactory(side);
    }
    
    throw runtime_error("Unknown shape type: " + type);
}

int main() {
    // Create shapes from file using factory functions
    vector<unique_ptr<Shape>> shapes;
    
    fstream fin("shapes.txt");
    string line;
    while(getline(fin, line)) {
        cout << "Reading: " << line << endl;
        try {
            auto shape = shapeFactory(line);
            shapes.push_back(move(shape));
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << " in line: " << line << endl;
        }
    }
    
    // Display all shapes created from file
    cout << "\nShape Information:" << endl;
    cout << "==================" << endl;
    for (const auto& shape : shapes) {
        shape->display();
    }
    
    // Calculate total area
    double totalArea = 0;
    for (const auto& shape : shapes) {
        totalArea += shape->area();
    }
    cout << "\nTotal area of all shapes: " << totalArea << endl;
    
    return 0;
}
