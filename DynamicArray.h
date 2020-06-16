
#include <stdexcept>
#include <string>

//const std::string INDEX_OUT_OF_RANGE_MESSAGE = "index out of range";
//const std::string NEGATIVE_SIZE_MESSAGE = "size is negative";
//const std::string ZERO_SIZE_MESSAGE = "size is 0";


template <typename T> class DynamicArray {
private:
	T* data = nullptr; // указатель на первые данные 
	int size = 0; // по умолчанию массив пустой
public:
	// пустой конструктор, size = 0
	DynamicArray() : size(0) {}

	// пустой конструктор определЄнного размера 
	DynamicArray(int size) : size(size) {
		if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		this->data = new T[size];
	}

	//  опировать элементы из переданного массива
	DynamicArray(T* data, int size) : DynamicArray(size) {
		for (int i = 0; i < size; i++)
			this->data[i] = data[i];
	}

	//  опирующий конструктор (определЄнной длины)
	DynamicArray(const DynamicArray<T>& array, int size) : DynamicArray(size) {
		if (size > array.size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		for (int i = 0; i < size; i++)
			this->data[i] = array.data[i];
	}

	//  опирующий конструктор
	DynamicArray(const DynamicArray<T>& array) :
		DynamicArray(array.data, array.size) {}

	// ƒеструктор
	virtual ~DynamicArray() {
		delete[] this->data;
		this->size = 0;
	}


	T get(int index) const {
		if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		return this->data[index];
	}

	// ƒекомпозици€

	// ѕолчуить размер массива 
	int getSize() const { return this->size; }

	// изменить значение по индексу 
	void set(const T& value, int index) {
		if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->data[index] = value;
	}

	// изменить размер
	void resize(int size) {
		if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		T* newData = new T[size]; //создаЄм новый массив нужного размера

		// если переданный больше данного, то переданный, иначе данный
		for (int i = 0; i < (this->size > size ? size : this->size); i++)
			newData[i] = data[i]; // перемещаем данные 

		delete[] data; //удал€ем старый массив
		this->data = newData; //замен€ем новым

		this->size = size; // не забываем мен€ть размер!!
	}

	// сравнение массивов на равенство
	bool operator==(const DynamicArray<T>& arr) const {
		if (this->size != arr.size) return false;

		for (int i = 0; i < this->size; i++)
			if (this->get(i) != arr.get(i)) return false;


		return true;
	}

	// приравниваем массив к другому
	DynamicArray<T>& operator=(const DynamicArray& array) {
		delete[] this->data;

		this->size = array.size;
		this->data = new T[this->size];

		for (int i = 0; i < size; i++)
			this->data[i] = array.data[i];

		return *this;
	}

};