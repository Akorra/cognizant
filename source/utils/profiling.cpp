#include "profiling.h"

#include <functional>
#include <thread>

using namespace cog::utils;

/** Timer Methods **********************************************************************/
Timer::~Timer()
{ 
    if(!m_Stopped) 
        Stop(); 
}

void Timer::Stop()
{
    auto endTimePoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

    std::cout << m_Name << ": " << (end - start) << "ms\n";

    m_Stopped = true;
}

/***************************************************************************************/
/** Instrumentor methods ***************************************************************/

void Instrumentor::WriteHeader()
{
    m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
    m_OutputStream.flush();
}

void Instrumentor::WriteFooter()
{
    m_OutputStream << "]}";
    m_OutputStream.flush();
}

void Instrumentor::BeginSession(const char *name, const char *filepath)
{
    m_OutputStream.open(filepath);
    WriteHeader();

    m_CurrentSession = new InstrumentationSession{name};
}

void Instrumentor::EndSession()
{
    WriteFooter();
    m_OutputStream.close();

    delete m_CurrentSession;
    m_CurrentSession = nullptr;
    m_ProfileCount = 0;
}

void Instrumentor::WriteProfile(const ProfileResult &result)
{
    if (m_ProfileCount++ > 0)
        m_OutputStream << ",";

    std::string name(result.name);
    std::replace(name.begin(), name.end(), '"', '\'');

    m_OutputStream << "{";
    m_OutputStream << "\"cat\":\"function\",";
    m_OutputStream << "\"dur\":" << (result.end - result.start) << ',';
    m_OutputStream << "\"name\":\"" << name << "\",";
    m_OutputStream << "\"ph\":\"X\",";
    m_OutputStream << "\"pid\":0,";
    m_OutputStream << "\"tid\":" << result.threadID << ",";
    m_OutputStream << "\"ts\":" << result.start;
    m_OutputStream << "}";

    m_OutputStream.flush();
}

/***************************************************************************************/
/** InstrumentorTimer methods **********************************************************/

void InstrumentationTimer::Stop()
{
    auto endTimePoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    uint32_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::Get().WriteProfile({thread_id, m_Name, start, end});

    m_Stopped = true;
}

/***************************************************************************************/
/** Example Usage **********************************************************************/
/*
#include "utils/profiling.h"

#include <cmath>
#include <thread>

#define PROFILING 1 
#if PROFILING
#define PROFILE_SCOPE(name) cog::utils::InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__) // or __FUNCTION__ or __FUNCSIG__ (not all platforms)
#else
#define PROFILE_SCOPE(name)
#endif

void PrintFunction(int value)
{
    PROFILE_FUNCTION();

    for(int i=0; i<1000; i++)
        std::cout << "Hello World #" << (i+value) << std::endl;
}

void PrintFunction1()
{
    PROFILE_FUNCTION();

    for(int i=0; i<1000; i++)
        std::cout << "Hello World #" << sqrt(i) << std::endl;
}

int main()
{
    cog::utils::Timer timer("main");
    cog::utils::Instrumentor::Get().BeginSession("Profile");
    cog::utils::run_benchmarks_for([](){
        std::thread a( PrintFunction, 2 ); 
        
        PrintFunction1();  

        a.join();
    });
    cog::utils::Instrumentor::Get().EndSession();

    return 0;
}
*/
/***************************************************************************************/