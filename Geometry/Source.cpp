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
		cout << "������� �������� ������ ���������������� x � y ����� ������: ";
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
			cout << "������� �������������� = " << x * y << endl;
		}
		else
		{
			cout << "C������ �������������� �� ����� ���� �����!" << endl;
		}
	}
	void get_perimeter()
	{
		if (x != y)
		{
			return ((x + y) * 2);
			cout << "�������� �������������� = " << (x+y)*2 << endl;
		}
		else
		{
			cout << "C������ �������������� �� ����� ���� �����! " << endl;
		}
	}
	void drow()
	{
		cout << "������� �������������� " << endl;
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
			cout << "������� �������� = " << x * x << endl;
		}
		else
		{
			cout << "C������ �������� ����� ���� �����!" << endl;
		}
	}
	void get_perimeter()
	{
		if (x = y)
		{
			cout << "�������� �������� = " << 4*x << endl;
		}
		else
		{
			cout << "C������ �������� ����� ���� �����! " << endl;
		}
	}
	void drow()
	{
		cout << "������� �������� " << endl;
	}
};



void main()
{
	setlocale(LC_ALL, "");

}