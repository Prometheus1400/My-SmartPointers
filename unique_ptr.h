#ifndef UNIQUE_PTR__H
#define UNIQUE_PTR__H
#include <iostream>

namespace my {
	template<typename T>
	class unique_ptr {
		T* ptr;
	public:
		unique_ptr() : ptr(nullptr) {}
		unique_ptr(T val) : ptr(new T(val)) {}
		unique_ptr& operator=(T* newptr) {
			if (ptr != nullptr) {
				delete ptr;
			}
			ptr = newptr;
			return *this;
		}
		~unique_ptr() { delete ptr; }

		// deletes ability to copy
		unique_ptr(unique_ptr& smrtptr) = delete;
		unique_ptr& operator=(unique_ptr& smrtptr) = delete;

		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
		bool isNULL() { return !ptr; }
		void reset() {
			delete ptr;
			ptr = nullptr;
		}
		
		template<typename Q>
		friend std::ostream& operator<<(std::ostream& os, unique_ptr<Q>& smrtptr);
	};
	template<typename Q>
	std::ostream& operator<<(std::ostream& os, unique_ptr<Q>& smrtptr) {
		os << smrtptr.ptr;
		return os;
	}
}

#endif