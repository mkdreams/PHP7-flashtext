#pragma once
template<typename T>
class CarrayList
{
public:
	CarrayList(int arrayLength);
	~CarrayList();
public:
	void clear();
	bool isEmpty();
	int length();
	T get(int i);
	void insert(int i, T& m_element);
	void replace(int i, T &m_element);
	void add(T &m_element);
	void remove(int i);
	int indexOf(T &m_element);
private:
	T* element;
	int arrayLength{0};
	int listSize{0};
};


template<typename T>
CarrayList<T>::CarrayList(int length) {
	arrayLength = length;
	element = new T[length];
}

template<typename T>
void CarrayList<T>::clear() {
	listSize = 0;
}

template<typename T>
bool CarrayList<T>::isEmpty() {
	if (listSize == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
int CarrayList<T>::length() {
	return listSize;
}

template<typename T>
T CarrayList<T>::get(int i) {
	return element[i];
}

template<typename T>
int CarrayList<T>::indexOf(T &m_element) {
	int index = (int)(find(element, element + listSize, m_element) - element);

	if (index == listSize)
		return -1;
	return index;
}

template<typename T>
void CarrayList<T>::add(T &m_element) {
	//判断与进行扩容
	if (listSize >= arrayLength)
	{
		T* temp = new T[arrayLength * 2];
		for (int j = 0; j < arrayLength; j++)
		{
			temp[j] = element[j];
		}
		delete[]element;
		element = temp;
		arrayLength = arrayLength * 2;
	}

	element[listSize] = m_element;
	listSize++;
}

template<typename T>
void CarrayList<T>::insert(int i, T &m_element) {
	//判断与进行扩容
	if (listSize >= arrayLength)
	{
		T* temp = new T[arrayLength * 2];
		for (int j = 0; j < arrayLength; j++)
		{
			temp[j] = element[j];
		}
		delete[]element;
		element = temp;
		arrayLength = arrayLength * 2;
	}

	//往后移动一个
	copy_backward(element + i, element + listSize, element + listSize + 1);
	element[i] = m_element;
	listSize++;
}

template<typename T>
void CarrayList<T>::replace(int i, T& m_element) {
	element[i] = m_element;
}

template<typename T>
void CarrayList<T>::remove(int i) {
	copy(element + i + 1, element + listSize, element + i);
	listSize--;
}


template<typename T>
CarrayList<T>::~CarrayList() {
	delete[] element;
}

