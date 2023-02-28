#include<iostream>
using namespace std;

enum Color
{
	console_blue = 0x99,
	console_green = 0xAA,
	console_red = 0xCC,
	console_default = 0x07
};


class Shape
{
	Color color;
public:
	Shape(Color color) :color(color) {};
	virtual ~Shape() {}

	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
};

class Rectangle : public Shape
{
public:
	double x, y;
	void set_sides()
	{
		cout << "Введите значения сторон четырехугольника x и y через пробел: ";
		cin >> x;
		cin >> y;
	}
	Rectangle(double x, double y) 
	{
		this->x = x;
		this->y = y;
	}
	~Rectangle();

		double get_area()
	{
		if (x != y)
		{
			return (x * y);
			cout << "Площадь прямоугольника = " << x * y << endl;
		}
		else
		{
			cout << "Cтороны прямоугольника не могут быть равны!" << endl;
		}
	}
	void get_perimeter()
	{
		if (x != y)
		{
			return ((x + y) * 2);
			cout << "Периметр прямоугольника = " << (x+y)*2 << endl;
		}
		else
		{
			cout << "Cтороны прямоугольника не могут быть равны! " << endl;
		}
	}
	void drow()
	{
		cout << "Рисунок прямоугольника " << endl;
	}
};

class Quadrate : public Rectangle
{
public:
	Quadrate(double side): Rectangle(side,side){}
	void get_area()
	{
		if (x = y)
		{
			cout << "Площадь квадрата = " << x * x << endl;
		}
		else
		{
			cout << "Cтороны квадрата долны быть равны!" << endl;
		}
	}
	void get_perimeter()
	{
		if (x = y)
		{
			cout << "Периметр квадрата = " << 4*x << endl;
		}
		else
		{
			cout << "Cтороны квадрата долны быть равны! " << endl;
		}
	}
	void drow()
	{
		cout << "Рисунок квадрата " << endl;
	}
};



void main()
{
	setlocale(LC_ALL, "");

}