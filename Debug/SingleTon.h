#ifndef __SINGLETON__
#define __SINGLETON__
#include <mutex>

template <typename A>
class Singleton {
    public:
    static A* GetInstance() {
        m_mutex.lock();
        if(instance == NULL) {
            instance = new A();
        }
        m_mutex.unlock();
        return instance;
    }
    private:
    static A *instance;
    static std::mutex m_mutex;
};

template<typename T> T* Singleton<T>::instance = NULL;
template<typename T> std::mutex Singleton<T>::m_mutex;

#endif