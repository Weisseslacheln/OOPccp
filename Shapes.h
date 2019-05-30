#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Base.h"
#include "Container.h"

class Shape : public Named {

public:
	Shape() : Named( "" ) {
		sm_count++;
	}

	Shape( std::string name) : Named( name ) {
		sm_count++;
	}

	~Shape() {
		sm_count--;
	}

	virtual void Print( std::ostream & out ) {
		out << std::endl;
	}

	static int GetCount() {
		return sm_count;
	}

private:
	static int sm_count;
};

int Shape::sm_count;

static std::ostream & operator<< ( std::ostream & out, Shape * obj ) {
	obj -> Print( out );
	return out;
}

class Point : public Shape {
public:
	Point() : Shape( "Point" ) {
		m_x = 0;
		m_y = 0;
	}

	Point( double const & x, double const & y ) : Shape( "Point" ) {
		m_x = x;
		m_y = y;
	}

	Point operator = (Point const & first) {
		if (this != & first) {
			m_x = first.m_x;
			m_y = first.m_y;
		}
		return *this;
	}

	double GetX() const {
		return m_x;
	}

	double GetY() const {
		return m_y;
	}

	void Print( std::ostream & out ) {
		out << m_figure_name << std::endl;
		out << "( " << m_x << ", "<< m_y <<" )"<< std::endl;
	}

private:
	double m_x;
	double m_y;
};

class Circle : public Shape {
public: 
	Circle( Point const & center, double const & radius ) : Shape( "Circle" ) {
		if ( radius <= 0 )
			throw ErrorMessage{ "Circle has a negative radius.", -4 };
		m_circle_center = center;
		m_circle_radius = radius;
	}

	double Perimetr() {
		return 2 * m_circle_radius * M_PI;
	}

	double Area() {
		return M_PI * pow( m_circle_radius, 2 );
	}

	void Print( std::ostream & out ) {
		out << m_figure_name << std::endl;
		out << "Center: " << "( "<< m_circle_center.GetX() << ", " << m_circle_center.GetY()<<" )" << std::endl;
		out << "Radius = " << m_circle_radius << std::endl;
		out << "Length = " << Perimetr() << std::endl;
		out << "Area = " << Area() << std::endl;
	}

private:
	Point m_circle_center = Point( 0, 0 );
	double m_circle_radius;
};

class Rect : public Shape {
public:
	Rect ( Point const & first, Point const & second) : Shape( "Rect" ) {
		if ( ( first.GetX() == second.GetX() ) || ( first.GetY() == second.GetY() ) )
			throw ErrorMessage{ "The points are not suitable for creating a rectangle.", -5 };
		m_rect_width = abs(first.GetX() - second.GetX());
		m_rect_length = abs(first.GetY() - second.GetY());
		m_rect_first = first;
		m_rect_second = second;
	}

	double Perimetår() {
		return 2 * m_rect_width + 2 * m_rect_length;
	}

	double Area() {
		return m_rect_width * m_rect_length;
	}

	void Print( std::ostream & out ) {
		out << m_figure_name << std::endl;
		out << "Coordinats: ";
		out << "( " << m_rect_first.GetX() << ", " << m_rect_first.GetY() << " ), ";
		out << "( " << m_rect_first.GetX() << ", " << m_rect_second.GetY() << " ), ";
		out << "( " << m_rect_second.GetX() << ", " << m_rect_second.GetY() << " ), ";
		out << "( " << m_rect_second.GetX() << ", " << m_rect_first.GetY() << " )" << std::endl;
		out << "Wight = " << m_rect_width << std::endl;
		out << "Length = " << m_rect_length << std::endl;
		out << "Perimetr = " << Perimetår() << std::endl;
		out << "Area = " << Area() << std::endl;
	}

protected:
	Point m_rect_first = Point( 0, 0 );
	Point m_rect_second = Point( 0, 0 );
	double m_rect_width;
	double m_rect_length;
};

class Square : public Rect {
public: 
	Square( Point const & first, double const & side ) : Rect( first, Point( first.GetX()+ side,  first.GetY() +  side ) ) {
		if ( side <= 0 )
			throw ErrorMessage{ "Square has a negative length.", -6 };
		m_figure_name = "Square";
		m_square_side = side;
		m_square_first = first;
	}

	void Print( std::ostream & out ) {
		out << m_figure_name << std::endl;
		out << "Coordinats: ";
		out << "( " << m_square_first.GetX() << ", " << m_square_first.GetY() << " ), ";
		out << "( " << m_square_first.GetX() << ", " << m_square_first.GetY() + m_square_side << " ), ";
		out << "( " << m_square_first.GetX() + m_square_side << ", " << m_square_first.GetY() << " ), ";
		out << "( " << m_square_first.GetX() + m_square_side << ", " << m_square_first.GetY() + m_square_side << " )" << std::endl;
		out << "Side = " << m_square_side << std::endl;
		out << "Perimetr = " << Perimetår() << std::endl;
		out << "Area = " << Area() << std::endl;
	}

private:
	Point  m_square_first = Point( 0, 0 );
	double m_square_side;
};

class Polyline : public Shape {
public:
	Polyline( Point const & first ) : Shape( "Polyline" ) {
		m_polyline_points.PushLast( first );
	}
	void AddPoint( Point const & first) {
		m_polyline_points.PushLast( first );
	}

	double Distance( Point const & first, Point const & second ) const {
		return sqrt( pow( first.GetX() - second.GetX(), 2.0 ) + pow( first.GetY() - second.GetY(), 2.0 ) );
	}

	double Length() {
		double l = 0;
		int size = m_polyline_points.Current_Size() - 1;
		for( int i = 0; i < size; i++ ) {
			l += Distance(m_polyline_points[ i ], m_polyline_points[ i + 1 ] );
		}
		return l;
	}

	void Print( std::ostream & out ) {
		int size = m_polyline_points.Current_Size();
		out << m_figure_name << std::endl;	
		out << "Number of vertices: " << m_polyline_points.Current_Size() << std::endl;
		for( int i = 0; i < size; i++ ) {
			out << "( " << m_polyline_points[ i ].GetX() << ", " << m_polyline_points[ i ].GetY() << " )" << std::endl;
		}
		out << "Length = " << Length() << std::endl;
	}

protected:
	Container<Point> m_polyline_points;
};

class Polygone : public Polyline {
public: 
	Polygone( Point const & first, Point const & second, Point const & third ) : Polyline( first ) {
		m_figure_name = "Polygone";
		m_polyline_points.PushLast( second );
		m_polyline_points.PushLast(	third );
	}

	double Perimeter() {
		return Length() + Distance(m_polyline_points.First(), m_polyline_points.Last() );
	}

	void Print( std::ostream & out ) {
		int size = m_polyline_points.Current_Size();
		out << m_figure_name << std::endl;
		out << "Number of vertices : " << m_polyline_points.Current_Size() << std::endl;
		for( int i = 0; i < size ; i++ ) {
			out << "( " << m_polyline_points[ i ].GetX() << ", " << m_polyline_points[ i ].GetY() << " )" << std::endl;
		}
		out << "Perimeter = " << Perimeter() << std::endl;
	}
};