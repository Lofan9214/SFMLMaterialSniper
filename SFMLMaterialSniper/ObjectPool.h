#pragma once

template<typename T>
class ObjectPool
{
protected:
	std::list<T*> unused;
	std::list<T*> used;
	std::string strResourceId = "";

	ObjectPool(const ObjectPool&) = delete;
	ObjectPool& operator=(const ObjectPool&) = delete;

public:

	ObjectPool(int initSize = 10)
	{
		for (int i = 0;i < initSize;++i)
		{
			auto obj = new T(strResourceId, typeid(T).name());
			obj->init();
			unused.push_back(obj);
		}
	}

	virtual ~ObjectPool()
	{
		for (auto obj : unused)
		{
			delete obj;
		}
		for (auto obj : used)
		{
			delete obj;
		}
	}

	T* take()
	{
		T* obj = nullptr;
		if (unused.empty())
		{
			obj = new T(strResourceId, typeid(T).name());
			obj->init();
		}
		else
		{
			obj = unused.front();
			unused.pop_front();
		}
		used.push_back(obj);
		obj->reset();
		return obj;
	}

	void Return(T* obj)
	{
		auto found = std::find(used.begin(), used.end(), obj);
		if (found == used.end())
		{
			std::cout << "ObjectPool : Invailed Obj" << std::endl;
			return;
		}

		used.erase(found);
		obj->setActive(false);
		unused.push_back(obj);
	}

	std::list<T*> update(float dt)
	{
		std::list<T*> lstremove;
		auto it = used.begin();
		while (it != used.end())
		{
			if (!(*it)->getActive())
			{
				unused.push_back(*it);
				lstremove.push_back(*it);
				it = used.erase(it);
			}
			else
			{
				++it;
			}
		}
		return lstremove;
	}

	void setResourceId(const std::string& resId)
	{
		strResourceId = resId;

		for (auto obj : unused)
		{
			obj->setResourceId(strResourceId);
		}
		for (auto obj : used)
		{
			obj->setResourceId(strResourceId);
		}
	}

	std::list<T*> getListUsing() const { return used; }
	std::list<T*> getListUnusing() const { return unused; }
};