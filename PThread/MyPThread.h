#ifndef __MYPTHREAD__
#define __MYPTHREAD__

#include<pthread.h>
#include<iostream>

class MyPThread {
    public:
    MyPThread() {}
    virtual void run() {
        
    }

    void start() {
        pthread_create(&m_thread, &thread_attr, &MyPThread::thread_run, this);
    }

    void join() {
        pthread_join(m_thread, NULL);
    }

    private:
    pthread_t m_thread;
    pthread_attr_t thread_attr;

    static void* thread_run(void* t_obj) {
        MyPThread *p_obj = (MyPThread*) t_obj;
        p_obj->run();
        return 0;
    }
};

#endif