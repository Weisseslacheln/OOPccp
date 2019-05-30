#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include "Container.h"
#include "Shapes.h"
#include "Factory.h"

int main() {
	Container< Shape * > container;
	srand( unsigned( time( 0 ) ) );
	for( int i = 0; i < 20; i++ ) {
		Factory factory;
		try {
			Shape * new_shape = factory.RandomShape((int)(rand() % 6));
			container.PushLast( new_shape );
		}
		catch (ErrorMessage & err) {
			return err.Send_error();
		}
	}

	std::cout << "Number of current shapes: " << Shape::GetCount() << std::endl << std::endl;
	int size = container.Current_Size();

	try {
		for( int i = 0; i < size; i++ ) {
			Shape * shape = container.RemoveAndGetFirst();
			std::cout << shape << std::endl;
			delete shape;
		}
	} 
	catch (ErrorMessage & err) {
		return err.Send_error();
	}

	container.Clear();
	std::cout << "Number of current shapes: " << Shape::GetCount() << std::endl;

	return 0;
}