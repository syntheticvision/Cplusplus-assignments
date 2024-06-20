//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           May 26, 2024
//I declare that this submission is the result of my own work and I only copied the code 
//that my professor provided to complete my workshops and assignments. 
//This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================

#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H
#include <chrono>
#include <string>
namespace seneca
{
    const int MAX_OBJ = 10;
    class TimedTask
    {
        size_t m_recordNum = 0;
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_endTime;
        struct
        {
            std::string m_task;
            std::string m_timeUnit;
            std::chrono::steady_clock::duration m_duration;
        } taskList[MAX_OBJ]{};

    public:
        TimedTask();
        virtual ~TimedTask();
        void startClock();
        void stopClock();
        void addTask(const char *taskName);
        friend std::ostream &operator<<(std::ostream &os, const TimedTask & src);
    };
}
#endif // !SENECA_TIMEDTASK_H