#pragma once
#include <string>
#include <cstdlib>
#include <math.h>
#include "Shapes.h"
#include "Container.h"

class Factory {
public:
	Factory() {}
	Shape * RandomShape(int key) {
			switch (key) {
			case 0:
				return DoPoint();
				break;
			case 1:
				return DoCircle();
				break;
			case 2:
				return DoRect();
				break;
			case 3:
				return DoSquare();
				break;
			case 4:
				return DoPolyline();
				break;
			case 5:
				return DoPolygone();
				break;
			default:
				throw ErrorMessage{ "Invalid request format for RandomShape.", -3 };
			}
	}

	Shape * DoPoint() {
		return new Point(RandomPoint());
	}

	Shape * DoCircle() {
		return new Circle(RandomPoint(), abs(RandomInt()));
	}

	Shape * DoRect() {
		Point first = RandomPoint();
		return new Rect(first, Point(first.GetX() + abs(RandomInt()), first.GetY() + abs(RandomInt())));
	}

	Shape * DoSquare() {
		return new Square(RandomPoint(), abs(RandomInt()));
	}

	Shape * DoPolyline() {
		int size = (int)(rand() % 10 + 4);
		Polyline * new_polyline = new Polyline(RandomPoint());
		for (int i = 0; i < size; i++) {
			new_polyline->AddPoint(RandomPoint());
		}
		return new_polyline;
	}

	Shape * DoPolygone() {
		int size = (int)(rand() % 10 + 4);
		Polygone * new_polygone = new Polygone(RandomPoint(), RandomPoint(), RandomPoint());
		for (int i = 0; i < size; i++) {
			new_polygone->AddPoint(RandomPoint());
		}
		return new_polygone;
	}

	Point RandomPoint() {
		return Point(RandomInt(), RandomInt());
	}

	int RandomInt() {
		return (int)(rand() % 10 + 4);
	}
};