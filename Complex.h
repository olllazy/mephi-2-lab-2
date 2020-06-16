// класс комплексных чисел
template <typename T>
class complex {
private:
	T realPart; // действительная часть
	T imagPart; // мнимая часть

public:
	complex(T realPart = T(), T imagPart = T())
		: realPart(realPart), imagPart(imagPart) {}

	// получение действительной части
	T real() const {
		return this->realPart;
	}

	// получение мнимой части
	T imag() const {
		return this->imagPart;
	}

	complex operator+(int val) const {
		return complex(this->realPart + val, this->imagPart);
	}

	complex operator+(const complex<T>& val) const {
		return complex(this->realPart + val.realPart, this->imagPart + val.imagPart);
	}

	template <typename U>
	void operator+=(const complex<U>& val) {
		this->realPart += val.real();
		this->imagPart += val.imag();
	}

	// переопределение оператора * с числом
	template <typename U>
	complex operator*(U val) const {
		return complex(this->realPart * val, this->imagPart * val);
	}

	// переопределение оператора * с числом
	template <typename U>
	complex operator*(complex<U> val) const {
		return complex(this->real() * val.real() - this->imag() * val.imag(), this->real() * val.imag() + this->imag() * val.real());
	}

	// сравнение комплексных на равенство
	template <typename U>
	bool operator==(const complex<U>& val) const {
		return this->realPart == val.real() && this->imagPart == val.imag();
	}

	// сравнение комплексных на неравенство
	template <typename U>
	bool operator!=(const complex<U>& val) const {
		return !this->operator==(val);
	}

	// получение сопряженного
	complex conj() const {
		return complex(this->realPart, -this->imagPart);
	}

};

using complexf = complex<float>;