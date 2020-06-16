#include <stdexcept>


template <typename T> class Sequence {
public:

	virtual T getFirst() const = 0;
	virtual T getLast() const = 0;
	virtual T get(int index) const = 0;
	virtual int getSize() const = 0;


	virtual Sequence<T>* getSubsequence(int start, int end) const = 0; //end excluding

	virtual void set(const T& item, int index) = 0;
	virtual void append(const T& item) = 0;
	virtual void prepend(const T& item) = 0;
	virtual void insertAt(const T& item, int index) = 0;

	virtual Sequence<T>* concat(const Sequence<T>& seq) const = 0;

	virtual bool operator==(const Sequence<T>& seq) const {
		if (this->getSize() != seq.getSize()) return false;

		for (int i = 0; i < this->getSize(); i++) {
			if (this->get(i) != seq.get(i)) return false;
		}

		return true;
	}

};


template <typename T> class ArraySequence : public Sequence<T> {
protected:
	DynamicArray<T>* array;

public:
	// пустой конструктор
	ArraySequence() {
		this->array = new DynamicArray<T>();
	}

	// Копирующий конструктор
	ArraySequence(const ArraySequence<T>& seq) {
		this->array = new DynamicArray<T>(*seq.array);
	}

	// Копирующий DynamicArray конструктор 
	ArraySequence(DynamicArray<T>* array) {
		this->array = array;
	}

	// Копировать элементы из переданного массива
	ArraySequence(T* items, int size) {
		this->array = new DynamicArray<T>(items, size);
	}

	// пустой конструктор определённого размера 
	ArraySequence(int size) {
		this->array = new DynamicArray<T>(size);
	}

	// Деструктор
	virtual ~ArraySequence() {
		delete this->array;
	}

	//Получить первый элемент в очереди
	virtual T getFirst() const override {
		return this->array->get(0);
	}

	// Получить последний элемент в очереди
	virtual T getLast() const override {
		return this->array->get(this->getSize() - 1);
	}

	// Получить элемент по индексу
	virtual T get(int index) const override {
		return this->array->get(index);
	}

	// Получить длину очереди
	virtual int getSize() const override {
		return this->array->getSize();
	}

	// Изменить элемент по индексу
	virtual void set(const T& item, int index) override {
		if (index < 0 || index >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->array->set(item, index);
	}

	// Получить очередь из всех элементов, с startIndex по endIndex (включительно)
	virtual ArraySequence<T>* getSubsequence(int start, int end) const override {
		if (start < 0 || start >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if (end < 0 || end >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if (start > end) throw std::logic_error("Quack! End must be not less than start.");


		T subArray[end - start + 1];
		for (int i = 0; i < end - start + 1; i++)
			subArray[i] = this->array->get(i + start);

		ArraySequence<T>* subSequence = new ArraySequence<T>(subArray, end - start);

		return subSequence;
	}

	//Добавляет элемент в конец очереди
	virtual void append(const T& item) override {
		this->array->resize(this->getSize() + 1);
		this->array->set(item, this->getSize() - 1);
	}

	// Добавляет элемент в начало очереди
	virtual void prepend(const T& item) override {
		this->array->resize(this->getSize() + 1);
		T t1 = this->array->get(0);
		T t2;
		for (int i = 0; i < this->getSize() - 1; i++) {
			t2 = t1;
			t1 = this->array->get(i + 1);
			this->array->set(t2, i + 1);
		}
		this->array->set(item, 0);
	}

	// Вставляет элемент в заданную позицию
	virtual void insertAt(const T& item, int index) override {
		if (index < 0 || index > this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->array->resize(this->getSize() + 1);
		T t1 = this->array->get(index);
		T t2;
		for (int i = index; i < this->getSize() - 1; i++) {
			t2 = t1;
			t1 = this->array->get(i + 1);
			this->array->set(t2, i + 1);
		}
		this->array->set(item, index);
	}

	//Сцепляет двe очереди
	virtual ArraySequence<T>* concat(const Sequence<T>& seq) const override {
		DynamicArray<T>* array = new DynamicArray<T>(this->getSize() + seq.getSize());
		ArraySequence<T>* newSequence = new ArraySequence<T>(array);
		for (int i = 0; i < this->getSize(); i++)
			newSequence->set(this->get(i), i);

		for (int i = 0; i < seq.getSize(); i++)
			newSequence->set(seq.get(i), i + this->getSize());

		return newSequence;
	}

};


template <typename T> class ListSequence : public Sequence<T> {
protected:
	LinkedList<T>* list;
public:
	// пустой конструктор
	ListSequence() {
		this->list = new LinkedList<T>();
	}

	// Копирующий конструктор
	ListSequence(const ListSequence<T>& seq) {
		this->list = new LinkedList<T>(*seq.list);
	}

	// Копирующий LinkedList конструктор
	ListSequence(LinkedList<T>* list) {
		this->list = list;
	}

	// Копировать элементы из переданного массива
	ListSequence(T* items, int size) {
		this->list = new LinkedList<T>(items, size);
	}

	// пустой конструктор определённого размера 
	ListSequence(int size) {
		this->list = new LinkedList<T>(size);
	}

	// деструктор 
	virtual ~ListSequence() {
		delete this->list;
	}

	//Получить первый элемент в очереди
	virtual T getFirst() const override {
		return this->list->getFirst();
	}

	// Получить последний элемент в очереди
	virtual T getLast() const override {
		return this->list->getLast();
	}

	// Получить элемент по индексу
	virtual T get(int index) const override {
		return this->list->get(index);
	}

	// Получить длину очереди
	virtual int getSize() const override {
		return this->list->getSize();
	}

	// Получить очередь из всех элементов, с startIndex по endIndex (включительно)
	virtual ListSequence<T>* getSubsequence(int start, int end) const override {
		LinkedList<T>* subList = this->list->getSublist(start, end);
		ListSequence<T>* seq = new ListSequence<T>(subList);
		return seq;
	}

	// Изменить элемент по индексу
	virtual void set(const T& item, int index) override {
		this->list->set(item, index);
	}

	//Добавляет элемент в конец очереди
	virtual void append(const T& item) override {
		this->list->append(item);
	}

	// Добавляет элемент в начало очереди
	virtual void prepend(const T& item) override {
		this->list->prepend(item);
	}

	// Вставляет элемент в заданную позицию
	virtual void insertAt(const T& item, int index) override {
		this->list->insertAt(item, index);
	}

	//Сцепляет две очереди
	virtual ListSequence<T>* concat(const Sequence<T>& seq) const override {
		ListSequence<T>* newSequence = new ListSequence<T>();

		for (int i = 0; i < this->getSize(); i++)
			newSequence->append(this->get(i));

		for (int i = 0; i < seq.getSize(); i++)
			newSequence->append(seq.get(i));

		return newSequence;
	}


};