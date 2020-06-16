
#include <stdexcept>
#include <string>

//const std::string INDEX_OUT_OF_RANGE_MESSAGE = "index out of range";
//const std::string NEGATIVE_SIZE_MESSAGE = "size is negative";
//const std::string ZERO_SIZE_MESSAGE = "size is 0";


template <typename T> class DynamicArray {
private:
	T* data = nullptr; // ��������� �� ������ ������ 
	int size = 0; // �� ��������� ������ ������
public:
	// ������ �����������, size = 0
	DynamicArray() : size(0) {}

	// ������ ����������� ������������ ������� 
	DynamicArray(int size) : size(size) {
		if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		this->data = new T[size];
	}

	// ���������� �������� �� ����������� �������
	DynamicArray(T* data, int size) : DynamicArray(size) {
		for (int i = 0; i < size; i++)
			this->data[i] = data[i];
	}

	// ���������� ����������� (����������� �����)
	DynamicArray(const DynamicArray<T>& array, int size) : DynamicArray(size) {
		if (size > array.size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		for (int i = 0; i < size; i++)
			this->data[i] = array.data[i];
	}

	// ���������� �����������
	DynamicArray(const DynamicArray<T>& array) :
		DynamicArray(array.data, array.size) {}

	// ����������
	virtual ~DynamicArray() {
		delete[] this->data;
		this->size = 0;
	}


	T get(int index) const {
		if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		return this->data[index];
	}

	// ������������

	// �������� ������ ������� 
	int getSize() const { return this->size; }

	// �������� �������� �� ������� 
	void set(const T& value, int index) {
		if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->data[index] = value;
	}

	// �������� ������
	void resize(int size) {
		if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		T* newData = new T[size]; //������ ����� ������ ������� �������

		// ���� ���������� ������ �������, �� ����������, ����� ������
		for (int i = 0; i < (this->size > size ? size : this->size); i++)
			newData[i] = data[i]; // ���������� ������ 

		delete[] data; //������� ������ ������
		this->data = newData; //�������� �����

		this->size = size; // �� �������� ������ ������!!
	}

	// ��������� �������� �� ���������
	bool operator==(const DynamicArray<T>& arr) const {
		if (this->size != arr.size) return false;

		for (int i = 0; i < this->size; i++)
			if (this->get(i) != arr.get(i)) return false;


		return true;
	}

	// ������������ ������ � �������
	DynamicArray<T>& operator=(const DynamicArray& array) {
		delete[] this->data;

		this->size = array.size;
		this->data = new T[this->size];

		for (int i = 0; i < size; i++)
			this->data[i] = array.data[i];

		return *this;
	}

};