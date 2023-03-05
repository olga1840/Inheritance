#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
using namespace std;

#define delimiter "\n----------------------------------------\n"

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		white = 0x00FFFFFF,

		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_default = 0x07
	};
	//enum (Enumeration - Перечисление) - это набор именованных констант типа 'int'

	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;
		static const int MIN_START_X = 50;
		static const int MIN_START_Y = 50;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 550;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 550;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 25;

	public:
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(int start_x)
		{
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < MIN_START_Y)start_y = MIN_START_Y;
			if (start_y > MAX_START_Y)start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		Shape(Color color, int start_x, int start_y, int line_width) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
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

	/*class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side > 20)side = 20;
			if (side < 5)side = 5;
			this->side = side;
		}
		//					Constructors:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
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
			cout << "Длина стороны квадрата: " << side << endl;
			Shape::info();
		}
	};*/

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
			if (side_1 < 50)side_1 = 50;
			if (side_1 > 550)side_1 = 550;
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			if (side_2 < 50)side_2 = 50;
			if (side_2 > 550)side_2 = 550;
			this->side_2 = side_2;
		}
		Rectangle(double side_1, double side_2, Color color, int start_x, int start_y, int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}
		~Rectangle() {}

		double get_area()const override
		{
			return side_1 * side_2;
		}
		double get_perimeter()const override
		{
			return (side_1 + side_2) * 2;
		}
		void draw()const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side_1; i++)
			{
				for (int j = 0; j < side_2; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/

			HWND hwnd = GetConsoleWindow();	//Получаем обработчик окна консоли
			HDC hdc = GetDC(hwnd);	//Получаем контекст усройства окна косоли
			//Контекст устройства - это то, на чем мы будем рисовать

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			//Pen (карандаш) рисут контур фигуры,
			//PS_SOLID - сплошная линия
			//5 - толщина линии 5 пикселов

			HBRUSH hBrush = CreateSolidBrush(color);
			//Brush - это кисть, рисует заливку замкнутой фигуры.

			//Выбираем чем и на чем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//Когда все инстументы созданы и выбраны, можно вызывать функцию,
			//для рисования нужной фигуры:

			::Rectangle(hdc, start_x, start_y, start_x + side_1, start_y + side_2);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);	//Освобождаем контекст устройства
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1: " << side_1 << endl;
			cout << "Сторона 2: " << side_2 << endl;
			Shape::info();
		}
	};

	class Square :public Rectangle
	{
	public:
		Square(double side, Color color, int start_x, int start_y, int line_width)
			:Rectangle(side, side, color, start_x, start_y, line_width) {}
		~Square() {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < 50)radius = 50;
			if (radius > 550)radius = 550;
			this->radius = radius;
		}
		Circle(double radius, Color color, int start_x, int start_y, int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const override
		{
			return M_PI * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);


			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << radius << endl;
			Shape::info();
		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(Color color, int start_x, int start_y, int line_width)
			:Shape(color, start_x, start_y, line_width) {}
		~Triangle() {}
		virtual double get_height()const = 0;
		void info()const
		{
			cout <<"Высота треугольника: " << get_height() << endl;
				Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < MIN_SIZE)side = MIN_SIZE;
			if (side > MAX_SIZE)side = MAX_SIZE;
			this->side = side;
		}
		EquilateralTriangle(double side, Color color, int start_x, int start_y, int line_width)
			:Triangle(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		double get_height()const
		{
			return side * sqrt(3) / 2;
		}
		double get_area()const
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const
		{
			return 3 * side;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT point[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, point, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double base;
		double side;
	public:
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}
		void set_base(double base)
		{
			if (base < MIN_SIZE)base = MIN_SIZE;
			if (base > MAX_SIZE)base = MAX_SIZE;
			this->base = base;
		}
		void set_side(double side)
		{
			if (side < MIN_SIZE)side = MIN_SIZE;
			if (side > MAX_SIZE)side = MAX_SIZE;
			this->side = side;
		}
		IsoscelesTriangle(double base, double side, Color color, int start_x, int start_y, int line_width)
			:Triangle(color, start_x, start_y, line_width)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle() {}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area()const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return base + side * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT point[] =
			{
				{start_x, start_y + side},
				{start_x + base, start_y + side},
				{start_x + base / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, point, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание: " << base << endl;
			cout << "Сторона: " << side << endl;
			Triangle::info();
		}
	};
	class RightTriangle : public Triangle
	{
		double cathet_1;
		double cathet_2;
		double hypotenuse;
	public:
		double get_cathet_1()const
		{
			return cathet_1;
		}
		double get_cathet_2()const
		{
			return cathet_2;
		}
		double get_hypotenuse()const
		{
			return sqrt(pow(cathet_1, 2) + pow(cathet_2, 2));
		}
		void set_cathet_1(double cathet_1)
		{
			if (cathet_1 < MIN_SIZE)cathet_1 = MIN_SIZE;
			if (cathet_1 > MAX_SIZE)cathet_1 = MAX_SIZE;
			this->cathet_1 = cathet_1;
		}
		void set_cathet_2(double cathet_2)
		{
			if (cathet_2 < MIN_SIZE)cathet_2 = MIN_SIZE;
			if (cathet_2 > MAX_SIZE)cathet_2 = MAX_SIZE;
			this->cathet_2 = cathet_2;
		}
		void set_hypotenuse(double hypotenuse)
		{
			if (hypotenuse < MIN_SIZE)hypotenuse = MIN_SIZE;
			if (hypotenuse > MAX_SIZE)hypotenuse = MAX_SIZE;
			this->hypotenuse = hypotenuse;
		}
		RightTriangle(double cathet_1, double cathet_2, double hypotenuse, Color color, int start_x, int start_y, int line_width)
			:Triangle(color, start_x, start_y, line_width)
		{
			set_cathet_1(cathet_1);
			set_cathet_2(cathet_2);
			set_hypotenuse(hypotenuse);
		}
		~RightTriangle() {}
		double get_height()const override
		{
			return (cathet_1 * cathet_2) / hypotenuse;
		}
		double get_area()const override
		{
			return (cathet_1 * cathet_2) / 2;
		}
		double get_perimeter()const override
		{
			return cathet_1 + cathet_2 + hypotenuse;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT point[] =
			{
				{start_x, start_y + cathet_1},
				{start_x + hypotenuse, start_y + cathet_2},
				{start_x + hypotenuse / 2, start_y + cathet_1 - get_height()}
			};
			::Polygon(hdc, point, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Гипотенуза: " << hypotenuse << endl;
			cout << "Катеты: " << cathet_1 << " " << cathet_2 << endl;
			Triangle::info();
		}
	};
}

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {};
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	setlocale(LC_ALL, "");

	Geometry::Square square(100, Geometry::Color::red, 300, 10, 5);
	square.info();
	cout << delimiter << endl;

	Geometry::Rectangle rect(120, 75, Geometry::Color::blue, 500, 10, 8);
	rect.info();
	cout << delimiter << endl;

	Geometry::Circle circle(100, Geometry::Color::yellow, 700, 10, 5);
	circle.info();
	cout << delimiter << endl;

	Geometry::EquilateralTriangle equilateral_triangle(75, Geometry::Color::green, 300, 150, 2);
	equilateral_triangle.info();
	cout << delimiter << endl;

	Geometry::IsoscelesTriangle isosceles_triangle(100, 75, Geometry::Color::white, 800, 150, 2);
	isosceles_triangle.info();
	cout << delimiter << endl;
	
	Geometry::RightTriangle right_triangle(50, 112, 113, Geometry::Color::red, 500, 150, 2);
	right_triangle.info();

}