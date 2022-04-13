#ifndef __DEBUG__
#define __DEBUG__

#include<iostream>
#include<stdio.h>
#include "SingleTon.h"

using namespace std;

typedef enum _LogLevel {
    LOG_LEVEL_LOW = 0,
    LOG_LEVEL_MED,
    LOG_LEVEL_HIGH,
    LOG_LEVEL_NO_LOG
} LogLevel;

class Debug:public Singleton<Debug> {
    public:

    Debug() {
        debug_level = LOG_LEVEL_NO_LOG;
    }

    void SetDebugLevel(LogLevel level) {
        debug_level = level;
    }

template<typename ... Types> void Log(LogLevel level, char* format, Types&& ... args) {
        if(level >= debug_level) {
            printf(format, (args)...);
            printf("\n");
        }
    }

    private:
    LogLevel debug_level;
};

#endif