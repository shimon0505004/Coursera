//MinHeap

#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class MinHeap
{
public:
	MinHeap(int size = 0);
	MinHeap(const std::vector<T>& inputArr);

	T extractMin();

	void insert(const T& input);
	int siftUp(const int& index);
	int siftDown(const int& index);
	void heapify();
	bool isHeap(const int& index);
	~MinHeap();

	void heapSort();
	void displayContents();

private:
	int parent(const int& index);
	int leftChild(const int& index);
	int rightChild(const int& index);
	bool isValid(const int& index);
	void swap(T& left, T& right);


private:
	std::vector<T> heapArr;
	int heapSize;
};


//////////////////////////////////////////////////////////////////////
// insert() adds an element of type T into the min-heap.
// It returns the final position of the inserted element in the heap.
//////////////////////////////////////////////////////////////////////


template<typename T>
void MinHeap<T>::insert(const T& input)
{
	int position = heapArr.size();
	heapArr.push_back(input);
	auto finalPosition = siftUp(position);
	heapSize = heapArr.size();
	return;
}



template<typename T>
int MinHeap<T>::siftUp(const int & index)
{

	int finalPosition = -1;
	if (isValid(index))
	{
		finalPosition = index;
		int parentIndx = parent(index);
		if (isValid(parentIndx))
		{
			if (heapArr.at(index) < heapArr.at(parentIndx))
			{
				swap(heapArr.at(index), heapArr.at(parentIndx));
				finalPosition = siftUp(parentIndx);
			}
		}
	}
	return finalPosition;
}


template<typename T>
void MinHeap<T>::swap(T& left, T& right)
{
	auto temp = left;
	left = right;
	right = temp;
}


template<typename T>
int MinHeap<T>::siftDown(const int & index)
{

	int finalPosition = -1;
	if (isValid(index))
	{
		finalPosition = index;
		int leftChildIndex = leftChild(index);
		int rightChildIndex = rightChild(index);
		if (isValid(leftChildIndex))
		{
			int minChildIndex = leftChildIndex;
			if (isValid(rightChildIndex))
			{
				if (heapArr.at(minChildIndex) > heapArr.at(rightChildIndex))
					minChildIndex = rightChildIndex;
			}

			if (heapArr.at(minChildIndex) < heapArr.at(index))
			{
				swap(heapArr.at(minChildIndex), heapArr.at(index));
				finalPosition = siftDown(minChildIndex);
			}
		}
	}
	return finalPosition;
}


template<typename T>
void MinHeap<T>::heapify()
{
	if (heapSize > 0)
	{
		for (int index = heapSize / 2; index >= 0; index--)
			siftDown(index);
	}
}


template<typename T>
bool MinHeap<T>::isHeap(const int & index)
{
	int isHeap = false;

	if (isValid(index))
	{
		isHeap = true;
		for (int pos = index; pos < heapSize; pos++)
		{
			auto leftChild = leftChild(pos);
			auto rightChild = rightChild(pos);
			if (isValid(leftChild))
			{
				int minChild = leftChild;
				if (isValid(rightChild))
				{
					if (heapArr.at(minChild) > heapArr.at(rightChild))
						minChild = rightChild;
				}

				if (heapArr.at(minChild) < heapArr.at(pos))
				{
					isHeap = false;
					break;
				}
			}
		}
	}

	return isHeap;
}

template<typename T>
MinHeap<T>::~MinHeap()
{
}


template<typename T>
int MinHeap<T>::parent(const int & index)
{
	int parent = -1;
	if (index > 0 && index < heapSize)
		parent = (index - 1) / 2;

	return parent;
}


///////////////////////////////////////////////////////////////////////
// Returns position of left child of node at 'index'.
///////////////////////////////////////////////////////////////////////
template<typename T>
int MinHeap<T>::leftChild(const int & index)
{
	int leftChildIndex = -1;
	bool isValidIndex = isValid(index);
	if (isValidIndex)
	{
		leftChildIndex = (2 * index) + 1;
		if (leftChildIndex >= heapSize)
			leftChildIndex = -1;
	}
	return leftChildIndex;
}


///////////////////////////////////////////////////////////////////////
// Returns position of right child of node at 'index'.
///////////////////////////////////////////////////////////////////////
template<typename T>
int MinHeap<T>::rightChild(const int & index)
{
	int rightChildIndex = -1;
	bool isValidIndex = isValid(index);
	if (isValidIndex)
	{
		rightChildIndex = (2 * index) + 2;
		if (rightChildIndex >= heapSize)
			rightChildIndex = -1;
	}
	return rightChildIndex;
}


///////////////////////////////////////////////////////////////////////
//checking if a given index is valid for the current heap size
///////////////////////////////////////////////////////////////////////
template<typename T>
bool MinHeap<T>::isValid(const int & index)
{
	return ((index >= 0 && index < heapSize)
		&& (heapSize >= 0 && heapSize <= heapArr.size()));
}


template<typename T>
MinHeap<T>::MinHeap(int size)
{
	heapArr = std::vector<T>(size);
	heapSize = heapArr.size();
}


template<typename T>
MinHeap<T>::MinHeap(const std::vector<T>& inputArr)
{
	heapArr = std::vector<T>(inputArr);
	heapSize = heapArr.size();
}


template<typename T>
T MinHeap<T>::extractMin()
{
	auto temp = T();

	if (heapSize > 0)
	{
		int headPos = 0;
		int endPos = heapSize - 1;
		if (endPos>headPos)
			swap(heapArr.at(headPos), heapArr.at(endPos));

		temp = heapArr.at(endPos);
		heapSize = heapSize - 1;
		siftDown(headPos);
	}

	return temp;
}


template<typename T>
void MinHeap<T>::heapSort()
{
	heapSize = heapArr.size();
	if (heapSize > 0)
	{
		heapify();
		std::vector<T> temp = std::vector<T>(0);
		while (heapSize > 0)
			extractMin();

	}
	heapSize = heapArr.size();
}


template<typename T>
void MinHeap<T>::displayContents()
{
	for (auto const& content : heapArr)
		std::cout << content << " ";

	std::cout << std::endl;
}
