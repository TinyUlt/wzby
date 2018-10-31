#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <mutex>

template <typename T>
class ObjectPool
{
public:
	ObjectPool(size_t size = 1) {
		chunk_size_ = size;
		if (chunk_size_ <= 0)
		{
			std::cout << "Object size invalid" << std::endl;
		}
		else
		{
			allocate_chunk();
		}
	}
	~ObjectPool()
	{
		//mutex_.lock();
		std::for_each(all_objects_.begin(), all_objects_.end(), ObjectPool<T>::array_delete_object);
		//mutex_.unlock();
	}

	T* acquire_object() {
		//mutex_.lock();

		if (free_list_.empty())
		{
			allocate_chunk();
		}
		T *obj = free_list_.front();
		free_list_.pop();

		//mutex_.unlock();

		return obj;
	}

	void release_object(T* obj) {
		//mutex_.lock();
		free_list_.push(obj);
		//mutex_.unlock();
	}

protected:
	void allocate_chunk() {
		
		for (int i = 0; i < chunk_size_; ++i)
		{
			T* new_objects = new T();
			all_objects_.push_back(new_objects);
			free_list_.push(new_objects);
		}
	}
	static void array_delete_object(T* obj) {
		delete obj;
	}

private:
	//std::mutex mutex_;

	std::queue<T*> free_list_;
	std::vector<T*> all_objects_;
	int chunk_size_;                            //对象池中预分配对象个数
	//static const size_t kdefault_size = 1;    //默认对象池大小

	ObjectPool(const ObjectPool<T>& src);
	ObjectPool<T>& operator=(const ObjectPool<T>& rhs);
};