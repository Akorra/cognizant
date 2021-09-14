#ifndef __COGNIZANT_PROFILING_H__
#define __COGNIZANT_PROFILING_H__

#include <fstream>
#include <algorithm>
#include <chrono>

namespace cog::utils{
    /*
    * This class implements a scoped timer, i.e. it marks the starting time on creation
    * and reveals elapsed time on destrucion, meant to be stack allocated.
    */
    class Timer
    {
    public:
        Timer(const char* name) : m_Name(name), m_Stopped(false) { m_StartTimePoint = std::chrono::high_resolution_clock::now(); }
        ~Timer();
        void Stop();

    private:
        bool m_Stopped;
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
        
    };


    struct ProfileResult
    {
        uint32_t    threadID;
        const char* name;
        long long   start, end;
    };

    struct InstrumentationSession
    {
        const char* name;
    };

    /*
    * This class implements profiling operations, producing a .json file that can be plugged into chrome tracing
    * to access visual Benchmarking.
    */
    class Instrumentor
    {
    private:
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;

    private:
        void WriteHeader();
        void WriteFooter();

    public:
        Instrumentor() : m_CurrentSession(nullptr), m_ProfileCount(0) { }

        void BeginSession(const char* name, const char* filepath = "results.json");
        void EndSession();
        
        void WriteProfile(const ProfileResult& result);
        
        static Instrumentor& Get()
        {
            static Instrumentor* instance = new Instrumentor();
            return *instance;
        }
    };

    /*
    * This class implements profiling and timing operations, producing a .json file that can be plugged into chrome tracing
    * to access visual Benchmarking, while providing timing of processes.
    */
    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name) : m_Name(name), m_Stopped(false) {  m_StartTimepoint = std::chrono::high_resolution_clock::now(); }
        ~InstrumentationTimer() { if(!m_Stopped) Stop(); }
        void Stop();
        
    private:
        bool        m_Stopped; 
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    };

    static void run_benchmarks_for(void (*function)())
    {
        InstrumentationTimer timer("RunBenchmarks");
        std::cout << "Runing benchmarks...\n";
        function();
    }
}
#endif