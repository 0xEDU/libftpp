#ifndef POOL_HPP
#define POOL_HPP

#include <cstddef>

// This is a memory pool data structure
// My current idea is a raw pointer 'pool' and somewhat of a 'ledger' pointer
// to control which memory areas are usable and which aren't
//
// What happens if we try to acquire more than we have in the pool?
template <typename TType>
class Pool {
	TType *objectRawPool = nullptr; // Here smart pointers should be a better alternative, still need to know how to use them
public:
	Pool() {};
	Pool(const Pool& rhs) { *this = rhs;};
	Pool& operator=(const Pool& rhs) {
		if (this != &rhs) {
		}
		return *this;
	};
	~Pool() {};

	void resize(const size_t& numberOfObjectStored) {
		if (objectRawPool != nullptr) {
			// Call destructor for each object in the pool
			delete[] objectRawPool;
		}
		objectRawPool = new TType[numberOfObjectStored];
	};

	class Object {
	private:
		TType *object = nullptr;
	public:
		Object() {};
		Object(TType* p_object) : object(p_object) {};
		Object(const Object& rhs) { *this = rhs; };
		Object& operator=(const Object& rhs) {
			if (this != &rhs) {
			}
			return *this;
		};
		~Object() {};

		TType* operator->() {
			return nullptr;
		};
	};

	template<typename... TArgs>
	Pool::Object acquire(TArgs&&... p_args) {
		if (objectRawPool == nullptr) {
			// Call constructor for the object
			return Object();
		}
		// Need to define how to get the next object in the pool
		// Ledger?
		TType *poolObject = objectRawPool + sizeof(TType);

		return Object();
	}
};

#endif // !POOL_HPP
