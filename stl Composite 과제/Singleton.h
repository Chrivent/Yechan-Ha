#pragma once

template<typename T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	static T* GetInstance()
	{
		if (instance == NULL)
			instance = new T;

		return instance;
	}
};

template<typename T> T* Singleton<T>::instance = NULL;