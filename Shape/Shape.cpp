#include <iostream>
#include <string>
#define PI 3.14 //宏定义
using namespace std;

//抽象类
class Shape 
{
public:
    virtual float area() const          // 计算面积
    {
        return 0.0;
    }
    virtual float volume() const        // 计算体积
    {
        return 0.0;
    }
    virtual void shapeName() const = 0; // 纯虚函数 ——形状名
};
// 声明点类
class Point : public Shape
{
public:
    Point(float px = 0, float py = 0)   //默认参数构造。若初始化时没有传入数值，则默认 x , y 为0。
    {
        x = px;
        y = py;
    }
    void setPoint(float px, float py)   //设置坐标 x , y
    {
        x = px;
        y = py;
    }
    float getX() const                  // 获取 x 坐标
    {
        return x;
    }
    float getY() const                  // 获取 y 坐标
    {
        return y;
    }
    virtual void shapeName() const      //继承自基类的纯虚函数,并添加了具体实现
    {
        cout << "Point: ";
    }
    // 重载操作符 <<，使得能够用 cout<< 来输出成员变量
    friend ostream &operator<<(ostream &output, const Point &p)
    {
        output << "x: " << p.x << " y: " << p.y << endl;
        return output;
    }

protected:
    float x, y;                         // 点的坐标x,y
};

// 声明圆类
class Circle : public Point
{
public:
    //默认参数构造
    Circle(float x = 0, float y = 0, float r = 0)   
    {
        this->x = x;
        this->y = y;
        this->radius = r;
    }
    void setRadius(float r)             //设置半径 radius
    {
        radius = r;
    }
    float GetRadius() const             //获得半径 radius
    {
        return radius;
    }
    virtual float area() const          //获得面积area
    {
        return PI * radius * radius;
    }
    virtual void shapeName() const      //继承自基类的纯虚函数,并添加了具体实现
    {
        cout << "Circle: ";
    }
    // 重载操作符 <<，使得能够用 cout<< 来输出成员变量
    friend ostream &operator<<(ostream &output, const Circle &c) 
    {
        output << "x: " << c.x << " y: " << c.y << " radius: " << c.radius << endl;
        return output;
    }

protected:
    float radius;                       // 圆的半径
};

// 声明圆柱类
class Cylinder : public Circle
{
public:
    //默认参数构造
    Cylinder(float x = 0, float y = 0, float r = 0, float h = 0) 
    {
        this->x = x;
        this->y = y;
        this->radius = r;
        this->height = h;
    }
    void setHeight(float h)             //设置高度 height
    {
        height = h;
    }
    virtual float area() const          //获得圆柱表面积
    {
        return PI * radius * radius * 2 + PI * radius * height * 2;
    }
    virtual float volume() const        //获得圆柱体积
    {
        return PI * radius * radius * height;
    }
    virtual void shapeName() const      //继承自基类的纯虚函数,并添加了具体实现
    {
        cout << "Cylinder: ";
    }
    // 重载操作符 <<，使得能够用 cout<< 来输出成员变量
    friend ostream &operator<<(ostream &output, const Cylinder &c) 
    {
        output << "x: " << c.x << " y: " << c.y << " radius: " << c.radius << " height: " << c.height << endl;
        return output;
    }

protected:
    float height;                       // 圆柱的高度
};

int main()
{
    Point point(1.1, 2.2);
    Circle circle(3.3, 4.4, 5.5);
    Cylinder cylinder(6.6, 7.7, 8.8, 9.9);
    // 补全调用部分，静态关联，直接调用各个 shapeName，输出各个成员变量（直接用 cout）
    point.shapeName();
    cout << point;

    circle.shapeName();
    cout << circle;

    cylinder.shapeName();
    cout << cylinder;

    Shape *pt;
    // 补全调用部分，使用基类指针进行动态关联
    pt = &point;
    pt->shapeName();
    cout << (Point &)*pt;

    pt = &circle;
    pt->shapeName();
    cout << (Circle &)*pt;

    pt = &cylinder;
    pt->shapeName();
    cout << (Cylinder &)*pt;

    //在运行结果中署名
    cout<<"------21302010069zsq"<<endl;

    return 0;
}
