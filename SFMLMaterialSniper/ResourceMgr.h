#pragma once
#include "stdafx.h"

template<typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;
protected:
	std::unordered_map<std::string, T*> resources;
	ResourceMgr() = default;
	~ResourceMgr() override;
	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr& operator=(const ResourceMgr&) = delete;

	static T Empty;
	void unloadAll();
public:
	bool load(const std::string& id);
	bool unload(const std::string& id);
	T& get(const std::string& id);
};

template<typename T>
inline ResourceMgr<T>::~ResourceMgr()
{
	unloadAll();
}

template<typename T>
inline void ResourceMgr<T>::unloadAll()
{
	for (auto& pair : resources)
	{
		delete pair.second;
	}
	resources.clear();
}

template<typename T>
inline bool ResourceMgr<T>::load(const std::string& id)
{
	auto it = resources.find(id);
	if (it != resources.end())
	{
		return false;
	}
	T* resource = new T();
	bool success = resource->loadFromFile(id);
	if (success)
	{
		resources.insert({ id, resource });
	}
	else
	{
		delete resource;
	}

	return success;
}

template<typename T>
inline bool ResourceMgr<T>::unload(const std::string& id)
{
	auto it = resources.find(id);
	if (it != resources.end())
	{
		return false;
	}
	delete it->second;

	resources.erase(it);

	return true;
}

template<typename T>
inline T& ResourceMgr<T>::get(const std::string& id)
{
	auto it = resources.find(id);
	if (it == resources.end())
	{
		return Empty;
	}
	return *(it->second);
}

template<typename T>
T ResourceMgr<T>::Empty;
