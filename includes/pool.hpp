#ifndef POOL_HPP
#define POOL_HPP

#include <cstddef>
#include <vector>

template <typename TType>
class Pool {
private:
	std::vector<TType> m_objects;

public:
	Pool() : m_objects() {};
	Pool(const Pool& rhs) { *this = rhs;};
	Pool& operator=(const Pool& rhs) {
		if (this != &rhs) {
			m_objects = rhs.m_objects;
		}
		return *this;
	};
	~Pool() {};

	void resize(const size_t& numberOfObjectStored) {};

	TType* operator->() { return nullptr; };

	template<typename... TArgs>
	class Object {
	public:
		Object();
		Object(const Object&);
		Object& operator=(const Object&);
		~Object();

		Object<TType> acquire(TArgs&&... p_args) {};
	};
};

#endif // !POOL_HPP
