#include <stdexcept>
#include <cmath>
#include "Complex.h"


template <typename T>
class Vector {
private:
	Sequence<T>* data; // инкапсулируем класс Sequence

	int dim = 0; //diagonality
	

public:

	// конструктор
	Vector(int dim) : dim(dim) {
		if (dim <= 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		data = (Sequence<T>*) new ListSequence<T>(dim);
				
	}

	// получить размерность
	int getDim() const {
		return this->dim;
	}

	// получить координату
	T get(int index) const  {
		return this->data->get(index);
	}

	// изменить вектор (координату)
	void set(const T& item, int index)  {
		this->data->set(item, index);
	}

	// сложение векторов
	template <typename U>
	Vector<T>* operator+(const Vector<U>& vector) const {
		if (this->dim != vector.getDim()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		Vector<T>* newVector = new Vector<T>(this->dim);
		for (int i = 0; i < this->dim; i++) 
		{
			newVector->set(this->get(i) + vector.get(i), i);
		}

		return newVector;
	}

	// умножение на скаляр 
	template <typename U>
	Vector<T>* operator*(U k) const {
		Vector<T>* newVector = new Vector<T>(this->dim);
		for (int i = 0; i < this->dim; i++)
			newVector->set(this->get(i) * k, i);

		return newVector;
	}

	// получение нормы (длины вектора)
	template <typename U>
	U getNorm() const {
		U sum = U();
		for (int i = 0; i < this->dim; i++)
			sum +=  (this->get(i)) * (this->get(i));

		return static_cast<U>(std::sqrt(sum));
	}

	template <typename U>
	U Scalar(const Vector<U>& vector) const {
		if (this->dim != vector.getDim()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		U sum = U();
		for (int i = 0; i < this->dim; i++)
		{
			sum = sum + this->get(i) * vector.get(i);
		}

		return static_cast<U>(sum);
	}

	bool operator==(const Vector<T>& vector) const {
		if (this->dim != vector.dim) return false;

		for (int i = 0; i < this->dim; i++)
			if (this->get(i) != vector.get(i)) return false;


		return true;
	}

};

template<>
template<>
float Vector<complexf>::getNorm<float>() const {
	complexf sum = 0;
	for (int i = 0; i < this->getDim(); i++) {
			sum += this->get(i) * this->get(i).conj();
		}

	return std::sqrt(sum.real());
}