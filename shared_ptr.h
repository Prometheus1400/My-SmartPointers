#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <iostream>

namespace my{

	template<typename T>
	class shared_ptr {
		std::size_t* refCount;
		T* ptr;

		//always assign refcount smth after calling
		void detatch() {
			--(*refCount);
			refCount = nullptr;
			ptr = nullptr;
		}

	public:
		// default initialization is nullptr
		shared_ptr() : refCount(new std::size_t(0)), ptr(nullptr) {}
		explicit shared_ptr(T val) : refCount(new std::size_t(1)), ptr(new T(val)) {}
		shared_ptr(const shared_ptr& other) : refCount(other.refCount), ptr(other.ptr) { ++(*refCount); }

		shared_ptr& operator=(const shared_ptr& other) {
			if (*refCount == 0) {
				delete refCount;
			} else if (*refCount == 1) {
				delete refCount;
				delete ptr;
			} else {
				detatch();
			}
			refCount = other.refCount;
			ptr = other.ptr;
			++(*refCount);
			return *this;
		}

		shared_ptr& operator=(T* newptr) {
			if (*refCount == 0) {
				ptr = newptr;
				*refCount = 1;
			} else if (*refCount == 1) {
				delete ptr;
				ptr = newptr;
			} else {
				detatch();
				ptr = newptr;
				refCount = new std::size_t(1);
			}
			return *this;
		}

		~shared_ptr() {
			if (*refCount == 0) {
				delete refCount;
			} else if (*refCount == 1) {
				delete ptr;
				delete refCount;
			} else {
				--(*refCount);
			}
		}

		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
		bool isNULL() { return !ptr; }
		void reset() {
			if (*refCount != 0) {
				if (*refCount == 1) {
					delete ptr;
					ptr = nullptr;
					*refCount = 0;
				} else {
					detatch();
					refCount = new std::size_t(0);
				}
			}
		}

		template<typename Q>
		friend std::ostream& operator<<(std::ostream& os, shared_ptr<Q>& smrtptr);

		// for debugging mainly
		std::size_t getRef() { return *refCount; }
	};
	template<typename Q>
	std::ostream& operator<<(std::ostream& os, shared_ptr<Q>& smrtptr) {
		os << smrtptr.ptr;
		return os;
	}
}

#endif