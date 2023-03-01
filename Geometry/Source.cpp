#include<Windows.h>
#include<iostream>
using namespace std;
#define delimeter "______________________________________________"

enum Color
{
	console_blue = 0x99,
	console_green = 0xAA,
	console_red = 0xCC,
	console_default = 0x07
};


class Shape
{
protected:
	Color color;
public:
	Shape(Color color) :color(color) {};
	virtual ~Shape() {}

	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side < 5)side = 5;
		if (side > 20)side = 20;
		this->side = side;
	}
	//Constructors
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	 }
	~Square() {}
	double get_area()const
	{
		return side * side;
	}
	double get_perimeter()const
	{
		return side * 4;
	}
	void draw()const
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_default);
	}
	void info()const
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны квадрата:\t" << side << endl;
		Shape::info();
	}
};
class Rectangle :public Shape
{
	double side_1, side_2;
public:
	double get_side_1()const
	{
		return side_1;
	}
	double get_side_2()const
	{
		return side_2;
	}
	void set_side_1(double side_1)
	{
		if (side_1 < 5)side_1 = 5;
		if (side_1 > 20) side_1 = 20;
		this->side_1 = side_1;
	}
	void set_side_2(double side_2)
	{
		if (side_2 < 5)side_2 = 5;
		if (side_2 > 20) side_2 = 20;
		this->side_2 = side_2;
	}
	Rectangle(double side_1, double side_2, Color color) :Shape(color)
	{
		set_side_1(side_1);
		set_side_2(side_2);
	}
	~Rectangle() {};
	double get_area()const override
	{
		return side_1 * side_2;
	}
	double get_perimeter()const override
	{
		return (side_1 + side_2) * 2;
	}


};

/
void main()
{
	setlocale(LC_ALL, "");

	Square square(-100, Color::console_red);
	square.info();

	Rectangle rect(5, 12), Color::console_blue);
	rect.info();
}