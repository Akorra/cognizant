#ifndef __COGNIZANT_UTILS_H__
#define __COGNIZANT_UTILS_H__

namespace cog::utils{
    /*
    * This class implements a scoped timer, i.e. it marks the starting time on creation
    * and reveals elapsed time on destrucion, meant to be stack allocated.
    */
    struct Timer{

        const char* process_name;
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

        Timer(const char* name="") : process_name(name)
        {
            start = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            end = std::chrono::high_resolution_clock::now();
            float milis = (end-start).count()*1000.0f;

            if(process_name == "")
                std::cout << "Elapsed Time: " << milis << "ms\n";
            else
                std::cout << "Elapsed Time [" << process_name << "]: " << milis << "ms\n";
        }
    };
}

#endif
