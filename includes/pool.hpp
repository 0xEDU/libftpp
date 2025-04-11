#ifndef POOL_HPP
#define POOL_HPP

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

// This is a memory pool data structure
//
// What happens if we try to acquire more than we have in the pool?
template <typename TType>
class Pool {
	std::vector<std::shared_ptr<TType>> objectRawPool; // Here smart pointers should be a better alternative, still need to know how to use them
public:
	Pool() : objectRawPool() {};
	Pool(const Pool& rhs) { *this = rhs;};
	Pool& operator=(const Pool& rhs) {
		if (this != &rhs) {
		}
		return *this;
	};
	~Pool() {};

	void resize(const size_t& numberOfObjectStored) {
		objectRawPool.resize(numberOfObjectStored);
	};

	class Object {
	private:
		std::unique_ptr<TType> object = nullptr;
	public:
		Object() {};
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
		auto it = std::find_if(objectRawPool.begin(), objectRawPool.end(), [](const std::shared_ptr<TType>& p_object) {
			return p_object.use_count() < 2;
		});
		if (it != objectRawPool.end()) {
			(*it)->~TType();
			*it = std::make_shared<TType>(std::forward<TArgs>(p_args)...);
			return Object();
		}
		else {
			return Object();
		}
	}
};

#endif // !POOL_HPP
