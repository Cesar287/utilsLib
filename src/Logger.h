/**
 * 
 * 
 * 
 * 
 * */

#ifndef UTILS_LOGGER_H_
#define UTILS_LOGGER_H_

#include <sstream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <time.h>
#include <syslog.h>
#include <iomanip>

namespace utils
{

enum VerbosityLevel {
    eERROR          = 0      ,
    eWARNING        = 1      ,   
    eINFO           = 2      ,
    eDEBUG          = 3      ,
    eDEBUGMAX       = 4
};

template<typename T>
class Logger
{
public:
    Logger();
    virtual ~Logger();
    std::ostringstream& Get(VerbosityLevel level = eINFO, std::string sourceFile = "", unsigned int sourceLine = 0);
    std::ostringstream& getOutputStream(){return outStream;}
protected:
    std::ostringstream outStream;
private:
    // Copy and assingmment private 
    Logger(const Logger&);
    Logger& operator=(const Logger&);
};


template <typename T>
Logger<T>::Logger()
{
}


/*
Once the destructor is called we call flush of the different output type to output the stream
*/
template<typename T>
Logger<T>::~Logger(){
    outStream << std::endl;
    T::FFlush(outStream.str());
}


template <typename T>
std::ostringstream& Logger<T>::Get(VerbosityLevel level, std::string sourceFile, unsigned int sourceLine){
    static const char* verbosityLevelNames[] = {"ERROR", "WARNING", "INFO", "DEBUG", "DEBUGMAX"};
    if(level > VerbosityLevel::eDEBUGMAX) level = VerbosityLevel::eDEBUGMAX;

    outStream << std::setw(20) << sourceFile.substr(sourceFile.find_last_of("/")+1) << " ["<< std::setw(4)  << sourceLine << "]" << verbosityLevelNames[level] << " : "; 

    return outStream;
}




/*
 * Class for output to syslog
 */
class FlushToSyslog{
    public:
    static void FFlush(const std::string& message);    
};

inline void FlushToSyslog::FFlush(const std::string& message){
    syslog(LOG_USER,"%s", message.c_str());
}

/*
 * Class for output to syslog
 */
class FlushToScreen{
    public:
    static void FFlush(const std::string& message);    
};

inline void FlushToScreen::FFlush(const std::string& message){
    printf("%s", message.c_str());
}



class DEFAULTlogger : public Logger<FlushToScreen>{};
class DEFAULTlogger : public Logger<FlushToScreen>{};


#define MAINLOG(verbLevel) \
    if(verbLevel > logVebosityMain); \
    else DEFAULTlogger().Get(verbLevel, __FILE__, __LINE__)








} // namespace utils














#endif







