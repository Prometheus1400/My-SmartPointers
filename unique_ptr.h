#ifndef UNIQUE_PTR__H
#define UNIQUE_PTR__H
#include <iostream>

namespace my {
	template<typename T>
	class unique_ptr {
		T* ptr;
	public:
		unique_ptr() : ptr(nullptr) {}
		unique_ptr(T* newptr) : ptr(newptr) {}
		unique_ptr& operator=(T* newptr) {
			if (ptr == nullptr) {
				ptr = newptr;
			} else {
				throw std::invalid_argument("cannot reassign unique_ptr");
			}
			return *this;
		}
		~unique_ptr() { delete ptr; }
		// deletes ability to copy
		unique_ptr(unique_ptr& smrtptr) = delete;
		unique_ptr& operator=(unique_ptr& smrtptr) = delete;

		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
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