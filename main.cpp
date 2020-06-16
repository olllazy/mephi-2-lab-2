#include <iostream>
#include <string>
#include <limits>

#include "LinkedList.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "Vector.h"



enum Type { INT, COMPLEX };

struct TypedVector {

	Type type;
	void* value;

	Vector<int>* asInt() const {
		return static_cast<Vector<int>*>(value);
	}

	Vector<complexf>* asComplex() const {
		return static_cast<Vector<complexf>*>(value);
	}

	TypedVector(Type type, int dim) : type(type) {
		if (type == INT)
			value = new Vector<int>(dim);
		else { 
			value = new Vector<complexf>(dim); 
		}
	}

	TypedVector(Type type, void* value)
		: type(type), value(value) {}

	~TypedVector() {
		if (type == INT)
			delete asInt();
		else if (type == COMPLEX)
			delete asComplex();
	}


	int getDim() const {
		if (type == INT)
			return asInt()->getDim();
		else if (type == COMPLEX)
			return asComplex()->getDim();
		else
			return -1;
	}

	
	void print() const {
		for (int i = 0; i < this->getDim(); i++) {

			if (this->type == INT) {
				std::cout << this->asInt()->get(i) << " ";
			}
			else if (this->type == COMPLEX) {
				std::cout << '('+ std::to_string(this->asComplex()->get(i).real())+','+ std::to_string(this->asComplex()->get(i).imag())+')';
			}
		}
		std::cout << "\n";
		
	}

	TypedVector* operator+(const TypedVector& vector) const {
		TypedVector* newVector;
		Type type;
		void* value;

		if (this->type == INT && vector.type == INT) {
			type = INT;
			value = *asInt() + *vector.asInt();
		}
		else if (this->type == INT && vector.type == COMPLEX) {
			type = COMPLEX;
			value = *vector.asComplex() + *asInt();
		}
		else if (this->type == COMPLEX && vector.type == INT) {
			type = COMPLEX;
			value = *asComplex() + *vector.asInt();
		}
		else {
			type = COMPLEX;
			value = *asComplex() + *vector.asComplex();
		}

		newVector = new TypedVector(type, value);
		return newVector;
	}

	TypedVector* operator*(float val) const {
		TypedVector* newVector;
		Type type;
		void* value;

		if (this->type == INT) {
			type = INT;
			value = *asInt() * val;
		}
		else {
			type = COMPLEX;
			value = *asComplex() * val;
		}

		newVector = new TypedVector(type, value);
		return newVector;
	}

	float getNorm() {
		if (this->type == INT) {
			return this->asInt()->getNorm<float>();
		}
		else if (this->type == COMPLEX) {
			return this->asComplex()->getNorm<float>();
		}

		return -1;
	}

};


void print(std::string str) {
	if (str.empty()) return;

	if (str.back() == ':')
		std::cout << str << "\n";
	else
		std::cout << str << "\n\n";

	std::cout.flush();
}

int readInt(int from = std::numeric_limits<int>::min(), int to = std::numeric_limits<int>::max()) {
	while (true) {
		try {
			std::string line;
			std::getline(std::cin, line);
			if (line.empty()) throw std::exception();

			int read = std::stoi(line);
			if (read < from || read > to) throw std::exception();

			std::cout << "\n";
			return read;
		}
		catch (...) {
			print("Please, enter a number from " + std::to_string(from) + " to " + std::to_string(to) + ":");
		}

	}
}

float readFloat(float from = std::numeric_limits<float>::lowest(), float to = std::numeric_limits<float>::max()) {
	while (true) {
		try {
			std::string line;
			std::getline(std::cin, line);
			if (line.empty()) throw std::exception();

			float read = std::stof(line);
			if (read < from || read > to) throw std::exception();

			std::cout << "\n";
			return read;
		}
		catch (...) {
			print("Please, enter a float number from " + std::to_string(from) + " to " + std::to_string(to) + ":");
		}

	}
}


TypedVector* readVector() {
	print("1. integer\n2. complex");
	int choice = readInt(1, 2);

	print("Enter dim:");
	int dim = readInt(1);
	   
	if (choice == 1) {
		TypedVector* vector = new TypedVector(INT, dim);

		for (int i = 0; i < dim; i++) {
			print("Enter coordinate (" + std::to_string(i + 1)+"):");
			int read = readInt();
			vector->asInt()->set(read, i);
		}

		return vector;
	}
	else if (choice == 2) {
		TypedVector* vector = new TypedVector(COMPLEX,dim);

		for (int i = 0; i < dim; i++) {
			print("Enter element (" + std::to_string(i + 1) + ") real part:");
			float real = readFloat();
			print("Enter element (" + std::to_string(i + 1)+ ") imag part:");
			float imag = readFloat();

			complexf read(real, imag);
			vector->asComplex()->set(read,i);
		}

		return vector;
	}

	return nullptr;

}



void printMenu() {
	print("1. set A\n2. set B\n3. set c\n4. get A+B\n5. get c*A\n6. get norm of A\n7. exit");
}

void menu() {
	TypedVector* A = nullptr;
	TypedVector* B = nullptr;
	float c = 0;

	while (true) {
		printMenu();
		int choice = readInt(1, 7);

		switch (choice) {
		case 1:
			delete A;
			A = readVector();
			break;
		case 2:
			delete B;
			B = readVector();
			break;
		case 3:
			print("enter c:");
			c = readFloat();
			break;
		case 4:
		{
			if (!A || !B) {
				print("A or B isn't set");
				break;
			}

			TypedVector* D = nullptr;
			try {
				D = *A + *B;
				D->print();
			}
			catch (...) {
				print("A and B have different size");
			}
			delete D;
			break;
		}
		case 5:
		{
			if (!A) {
				print("A isn't set");
				break;
			}

			TypedVector* D = nullptr;
			D = *A * c;
			D->print();
			delete D;
			break;
		}
		case 6:
		{
			if (!A) {
				print("A isn't set");
				break;
			}

			float norm = A->getNorm();
			print(std::to_string(norm));
			break;
		}
		case 7:
			return;
		}
	}
}


int main() {
	menu();

	return 0;
}