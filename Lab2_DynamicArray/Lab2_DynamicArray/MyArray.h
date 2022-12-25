#ifndef MY_ARRAY_H

#include <iostream>

#define MY_ARRAY_H
#define DEFAULT_CAPACITY 8
#define MEMORY_MULT 2

template <typename T>
class MyArray final
{
private:

	T* dataptr_ = nullptr;
	int capacity_ = DEFAULT_CAPACITY;
	int size_ = 0;

	class ConstIterator
	{

	protected:

		MyArray<T>* arrptr_;
		T* elemptr_;
		int pos_;
		bool isDirect_;

	public:

		ConstIterator(MyArray<T>* arrptr, bool isDirect)
		{
			arrptr_ = arrptr;
			isDirect_ = isDirect;
			if (isDirect) pos_ = 0;
			else pos_ = arrptr_->size() - 1;
			elemptr_ = arrptr_->dataptr_ + pos_;
		}

		bool hasNext()
		{
			if (isDirect_) return !(pos_ == arrptr_->size());
			else return !(pos_ == -1);
		}

		void next()
		{
			if (isDirect_) pos_++;
			else pos_--;
			elemptr_ = arrptr_->dataptr_ + pos_;
		}

		const T& get() const
		{
			return *elemptr_;
		}
	};

	class Iterator : public ConstIterator
	{

	public:

		Iterator(MyArray<T>* arrptr, bool isDirect) : ConstIterator(arrptr, isDirect)
		{
			
		}

		void set(const T& value)
		{
			*(ConstIterator::elemptr_) = value;
		}
	};

public:

	MyArray()
	{
		dataptr_ = (T*) malloc(DEFAULT_CAPACITY * sizeof(T));
	}

	MyArray(int capacity)
	{
		dataptr_ = (T*) malloc(capacity * sizeof(T));
		capacity_ = capacity;
	}

	MyArray(const MyArray& otherArr)
	{
		capacity_ = otherArr.capacity_;
		size_ = otherArr.size_;
		dataptr_ = (T*)malloc(capacity_ * sizeof(T));
		for (int i = 0; i < size_; i++) {
			new(dataptr_ + i) T(otherArr.dataptr_[i]);
		}
	}

	MyArray(MyArray&& otherArr)
	{
		capacity_ = otherArr.capacity_;
		size_ = otherArr.size_;
		free(dataptr_);
		dataptr_ = otherArr.dataptr_;
		otherArr.size_ = 0;
		otherArr.capacity_ = DEFAULT_CAPACITY;
		otherArr.dataptr_ = nullptr;
	}

	~MyArray()
	{
		for (int i = 0; i < size_; i++) dataptr_[i].~T();
		free(dataptr_);
	}

	int insert(const T& value) 
	{
		if (size_ == capacity_)
		{
			T* ndataptr_ = dataptr_;
			dataptr_ = (T*) malloc(capacity_ * MEMORY_MULT * sizeof(T));
			for (int i = 0; i < capacity_; i++) new (dataptr_[i]) T(std::move(ndataptr_[i]));
			capacity_ *= MEMORY_MULT;
			for (int i = 0; i < size_; i++) ndataptr_[i].~T();
			ndataptr_ = nullptr;
		}
		new (dataptr_ + size_) T(value);
		size_++;
		return size_ - 1;
	}

	int insert(int index, const T& value)
	{
		if (index < capacity_ - 1)
		{
			if (size_ == capacity_)
			{
				T* ndataptr_ = dataptr_;
				dataptr_ = (T*)malloc(capacity_ * MEMORY_MULT * sizeof(T));
				for (int i = capacity_ - 1; i >= index; i--) new (dataptr_ + i + 1) T(std::move(ndataptr_[i]));
				for (int i = 0; i < index; i++) new (dataptr_ + i) T(std::move(ndataptr_[i]));
				capacity_ *= MEMORY_MULT;
				for (int i = 0; i < size_; i++) ndataptr_[i].~T();
				ndataptr_ = nullptr;
			}
			else for (int i = size_ - 1; i >= index; i--)
			{
				dataptr_[i + 1].~T();
				new (dataptr_ + i + 1) T(std::move(dataptr_[i]));
			}
			new (dataptr_ + index) T(value);
			size_++;
			return size_ - 1;
		}
		else return -1;
	}

	void remove(int index)
	{
		if (index < size_ - 1)
		{
			for (int i = index; i < size_ - 1; i++)
			{
				dataptr_[i].~T();
				new (dataptr + i) T(std::move(dataptr_[i + 1]);
			}
			dataptr_[size_ - 1].~T();
			size_--;
		}
	}

	int size() const
	{
		return size_;
	}

	Iterator iterator() { return Iterator(this, true); }
	ConstIterator cIterator() { return ConstIterator(this, true); }

	Iterator reverseIterator() { return Iterator(this, false); }
	ConstIterator cReverseIterator() { return ConstIterator(this, false); }

	const T& operator[](int index) const
	{
		return (dataptr_[index]);
	}

	T& operator[](int index)
	{
		return (dataptr_[index]);
	}

	MyArray<T>& operator=(MyArray<T> otherArray)
	{
		std::swap(dataptr_, otherArray.dataptr_);
		std::swap(size_, otherArray.size_);
		std::swap(capacity_, otherArray.capacity_);

		return *this;
	}

	MyArray<T>& operator=(MyArray<T>&& otherArray)
	{
		if (this != &otherArray)
		{
			for (int i = 0; i < size_; i++) dataptr_[i].~T();
			free(dataptr_);

			capacity_ = otherArray.capacity_;
			size_ = otherArray.size_;
			dataptr_ = otherArray.dataptr_;

			otherArray._itemsArray = nullptr;
			otherArray._currentCapacity = 0;
			otherArray._currentSize = 0;
		}
		return *this;
	}

	// вспомогательные методы, используются для тестирования

	T* getPointer()
	{
		return dataptr_;
	}

	int getCapacity()
	{
		return capacity_;
	}
};

#endif