#ifndef INFO_CONTAINER_H
#define INFO_CONTAINER_H

#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ShipsExceptions.h"

template<class T>
class InfoContainer
{
	using ContainerType = std::vector<std::unique_ptr<T>>;

	ContainerType content;

	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const InfoContainer<U>& container);
	// template<class U>
	// friend std::istream& operator>>(std::istream& is, InfoContainer<U>& container);

public:
	InfoContainer() = default;
	InfoContainer(const InfoContainer<T>& copy);
	~InfoContainer() = default;

	typename std::vector<std::unique_ptr<T>>::const_iterator begin() const;
    typename std::vector<std::unique_ptr<T>>::const_iterator end() const;

	void addObject(std::unique_ptr<T> newObj);
	std::unique_ptr<T> accessObject(const T& c);
	std::unique_ptr<T> removeObject(const T& c);

	bool findObject(const T& c) const;
	bool isEmpty(void) const;

	int index(const T& c) const;
	size_t size(void) const;
	T& get(int idx) const;
	void clear(void);

	ContainerType getClassVector(void) const;
	void setClassVector(ContainerType& container);

	InfoContainer<T>& operator=(const InfoContainer<T>& other);
	bool operator==(const InfoContainer<T>& other) const;
	bool operator!=(const InfoContainer<T>& other) const;

	T& operator[](int idx) const;
};

#include "InfoContainer.ipp"

#endif