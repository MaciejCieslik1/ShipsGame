#ifndef INFO_CONTAINER_IPP
#define INFO_CONTAINER_IPP

#include "InfoContainer.h"

template<class T>
InfoContainer<T>::InfoContainer(const InfoContainer<T>& copy)
{
	content.reserve(copy.size());

	for (const auto& objPtr : copy.content) {
		if (!findObject(*objPtr)) {
			addObject(std::move(objPtr));
		}
	}
}

template<class T>
typename std::vector<std::unique_ptr<T>>::const_iterator InfoContainer<T>::begin() const {
	return content.begin();
}

template<class T>
typename std::vector<std::unique_ptr<T>>::const_iterator InfoContainer<T>::end() const {
	return content.end();
}

template<class T>
void InfoContainer<T>::addObject(std::unique_ptr<T> newObj)
{
	if (findObject(*newObj)) {
		content.push_back(std::move(newObj));
	}
	else { throw object_already_contained("Object is already in the container"); }
}

template<class T>
inline std::unique_ptr<T> InfoContainer<T>::accessObject(const T& c)
{
	auto it = std::find_if(content.begin(), content.end(), [&c] (const std::unique_ptr<T>& obj )
		{ return *obj == c; });

	if (it != content.end()) {
		return **it;
	}

	throw no_object_found("No such object found in the container");
}

template<class T>
inline std::unique_ptr<T> InfoContainer<T>::removeObject(const T& c)
{
	auto it = std::find(content.begin(), content.end(), [&c] (const std::unique_ptr<T>&obj)
	{
		return *obj == c;
	});

	if (it != content.end()) {
		std::unique_ptr<T> removedObject = std::move(*it);
		content.erase(it);
		return removedObject;
	}

	throw no_object_found("No such object found in the container");
}

template<class T>
inline bool InfoContainer<T>::findObject(const T& c) const
{
	auto it = std::find_if(content.begin(), content.end(), [&c] (const std::unique_ptr<T>& obj)
	{ return *obj == c; });
	return it != content.end();
}

template<class T>
inline bool InfoContainer<T>::isEmpty(void) const
{
	return content.empty();
}

template<class T>
inline int InfoContainer<T>::index(const T& c) const
{
	auto it = std::find_if(content.begin(), content.end(), [&c] (const std::unique_ptr<T>& obj)
		{ return *obj == c; });

	if (it != content.end()) {
		return std::distance(content.begin(), it);
	}

	throw no_object_found("No such object found in the container");
}

template<class T>
inline size_t InfoContainer<T>::size(void) const
{
	return content.size();
}

template<class T>
inline T& InfoContainer<T>::get(int idx) const
{
	if (idx > content.size() - 1 || idx < 0) throw index_out_of_range("No such index in the container");
	return *content[idx];
}

template<class T>
inline void InfoContainer<T>::clear(void)
{
	content.clear();
}

template<class T>
inline typename InfoContainer<T>::ContainerType InfoContainer<T>::getClassVector(void) const
{
	return content;
}

template<class T>
inline void InfoContainer<T>::setClassVector(ContainerType& container)
{
	content = container;
}

template<class T>
inline InfoContainer<T>& InfoContainer<T>::operator=(const InfoContainer<T>& other)
{
	if (this != &other) {
		this->content = other.content;
	}
	return *this;
}

template<class T>
inline bool InfoContainer<T>::operator==(const InfoContainer<T>& other) const
{
	if (size() != other.size()){
		return false;
	}

	for (size_t i = 0; i < size(); ++i) {
		if (*(content[i]) != *(other.content[i])) {
			return false;
		}
	}
	return true;
}

template<class T>
inline bool InfoContainer<T>::operator!=(const InfoContainer<T>& other) const
{
	return !(*this == other);
}

template<class T>
inline T& InfoContainer<T>::operator[](int idx) const
{
	return *(content[idx]);
}

template<class U>
std::ostream& operator<<(std::ostream& os, const InfoContainer<U>& container)
{
	for (const auto& objPtr : container.content) {
		os << *objPtr << '\n';
	}
	return os;
}

// template<class U>
// InfoContainer<U>& operator>>(InfoContainer<U>& container, const U& item) {
// 	container.addObject(std::make_unique<U>(item));
// 	return container;
// }

// template<class U>
// U& operator>>(U& item, InfoContainer<U>& container) {
// 	container.addObject(std::make_unique<U>(item));
// 	return item;
// }

#endif
