/*
* **********************************
* @file     ThWrap.h
* @author   cesar
* @class    ThWrap
* @version  1.0
* @date     4/2/21
* ***********************************
*/
#ifndef UTILS_THWRAP_H
#define UTILS_THWRAP_H

#include <thread>
#include <memory>
#include <functional>
#include <system_error>


class ThWrap {
    public:
    // Use of variadic template and forwarding to pass a callable object and parameters
    template<typename F, typename... Args>
    ThWrap(F&& f, Args&&... args):
    t(std::unique_ptr<std::thread>(new std::thread(std::forward<F>(f), std::forward<Args>(args)...))),
    endFunction(nullptr){

    }

    virtual ~ThWrap(){
        if(endFunction!=nullptr) endFunction();
        if(t->joinable()) t->join();
    }

    void setEndFunction(std::function<void()> f){
        endFunction = f;
    }

    private:
    std::unique_ptr<std::thread> t;
    std::function<void()> endFunction;

};


#endif //LOGTEST_THWRAP_H
