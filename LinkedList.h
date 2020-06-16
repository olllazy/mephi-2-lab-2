#include <stdexcept>
#include <string>

const std::string INDEX_OUT_OF_RANGE_MESSAGE = "Quack! Index out of range.";
const std::string NEGATIVE_SIZE_MESSAGE = "Quack! Size < 0.";
const std::string ZERO_SIZE_MESSAGE = "Quack! Size = 0."; 

template <typename T> class LinkedList {
private:

	struct Record {
		T item; // данные 
		Record* next = nullptr; // указатель на следующий элемент 
	};

	Record* head = nullptr; // указатель на первый элмент, по умолчанию nullptr
	int size = 0; // длина списка, по умолчанию 0

public:
	// пустой конструктор, size = 0
	LinkedList() : size(0) {} 

	// пустой конструктор определённого размера 
	LinkedList(int size) : LinkedList() {
		if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);
		// обработка исключения 

		Record** tmp = &(this->head); 
		for (int i = 0; i < size; i++) {
			*tmp = new Record;
			(*tmp)->item = T();
			tmp = &((*tmp)->next);
		}
		this->size = size;
	}

	// Копировать элементы из переданного массива
	LinkedList(T* items, int size) : LinkedList() {
		if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		Record** ptr = &(this->head);
		for (int i = 0; i < size; i++) {
			*ptr = new Record;
			(*ptr)->item = items[i];
			ptr = &((*ptr)->next);
		}

		this->size = size;
	}


	// Копирующий конструктор
	LinkedList(const LinkedList<T>& list) {
		Record* ptr = list.head;
		Record** newPtr = &(this->head);

		for (int i = 0; i < list.size; i++, ptr = ptr->next) {
			*newPtr = new Record;
			(*newPtr)->item = ptr->item;
			newPtr = &((*newPtr)->next);

		}

		this->size = list.size;
	}

	// деструктор 
	virtual ~LinkedList() {
		Record* ptr = this->head;
		Record* next;
		while (ptr != nullptr) {
			next = ptr->next;
			delete ptr;
			ptr = next;
		}
		this->size = 0;
	}


	// Декомпозиция 

	//Получить первый элемент в списке
	T getFirst() const {
		if (this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

		return this->head->item;
	}

	// Получить последний элемент в списке
	T getLast() const {
		if (this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

		Record* ptr = this->head;
		while (ptr->next != nullptr) ptr = ptr->next;
		return ptr->item;
	}

	// Получить элемент по индексу
	T get(int index) const {
		if ((index < 0) || (index >= this->size)) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		
		Record* ptr;
		{
			int i = 0;
			for (i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}

		return ptr->item;
	}

	// Изменить элемент по индексу
	void set(const T& item, int index) {
		if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record* ptr;
		{
			int i = 0;
			for (i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}

		ptr->item = item;
	}

	// Получить список из всех элементов, с startIndex по endIndex (включительно)
	LinkedList<T>* getSublist(int start, int end) const { //end excluding
		if (start < 0 || start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if (end < 0 || end >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if (start > end) throw std::logic_error("Quack! End must be not less than start.");

		LinkedList<T>* newList = new LinkedList<T>();


		Record* ptr = this->head;
		Record** newPtr = &newList->head;

		for (int i = 0; i <= end; i++, ptr = ptr->next) {
			if (i >= start) {
				*newPtr = new Record;
				(*newPtr)->item = ptr->item;
				newPtr = &((*newPtr)->next);
			}

		}

		newList->size = end - start + 1;

		return newList;
	}

	// Получить длину списка
	int getSize() const { return this->size; }

	//Добавляет элемент в конец списка
	void append(const T& item) {
		Record** ptr = &(this->head);
		while (*ptr != nullptr) ptr = &((*ptr)->next);

		(*ptr) = new Record;
		(*ptr)->item = item;

		this->size++;
	}

	// Добавляет элемент в начало списка
	void prepend(const T& item) {
		Record* ptr = new Record{ item, this->head };
		this->head = ptr;

		this->size++;
	}


	// удаление по индексу
	void removeAt(int index) {
		if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		// элемент, следующий для которого - начало списка
		Record preHead = { this->head->item, this->head };
		Record* ptr;

		// доходим до нужного нам (как следующего)
		{
			int i = 0;
			for (i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}
		
		Record* tmp = ptr->next; // запоминаем 
		ptr->next = ptr->next->next; // сдвигаем список
		delete tmp; // удаляем 

		this->head = preHead.next; // в случае если был удален первый элемент

		this->size--; // не забываем изменить размер списка
	}

	// Вставляет элемент в заданную позицию
	void insertAt(const T& item, int index) {
		if (index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		// аналогично remove, только
		Record preHead = { this->head->item, this->head };
		Record* ptr;

		{
			int i = 0;
			for (i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		ptr->next = new Record{ item, ptr->next }; //создаем и вставляем новый элемент списка
		this->head = preHead.next;

		this->size++; // увеличиваем длину 
	}

	//Сцепляет два списка
	LinkedList<T>* concat(const LinkedList<T>& list) const {
		Record* ptr1 = this->head;
		Record* ptr2 = list.head;

		LinkedList<T>* newList = new LinkedList<T>();
		Record** ptr = &(newList->head);
		// добавляем первый список
		while (ptr1 != nullptr) {
			*ptr = new Record{ //создаём элемент
				ptr1->item,
				ptr1->next
			};
			// переходим на следующую итерацию
			ptr1 = ptr1->next; // в первом списке
			ptr = &((*ptr)->next); // в получаемом списке
		}
		// добавляем второй список (ptr = nullptr), аналогично
		while (ptr2 != nullptr) {
			*ptr = new Record{
				ptr2->item,
				ptr2->next
			};

			ptr2 = ptr2->next;
			ptr = &((*ptr)->next);
		}

		newList->size = this->size + list.size; // не забываем указывать размер 
		return newList;
	}

	// сравнение списков 
	bool operator==(const LinkedList<T>& list) const {
		if (this->size != list.size) return false;

		for (int i = 0; i < this->size; i++) {
			if (this->get(i) != list.get(i)) return false;
		}

		return true;
	}

};

