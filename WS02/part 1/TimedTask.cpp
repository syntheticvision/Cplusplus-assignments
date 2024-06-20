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

#include <iostream>
#include "TimedTask.h"
namespace seneca
{
    TimedTask::TimedTask()
    {
        // empty
    }
    TimedTask::~TimedTask()
    {
        // empty
    }
    void TimedTask::startClock()
    {
        m_startTime = std::chrono::steady_clock::now();
    }
    void TimedTask::stopClock()
    {
        m_endTime = std::chrono::steady_clock::now();
    }
    void TimedTask::addTask(const char *taskName)
    {
        if (m_recordNum < MAX_OBJ)
        {
            taskList[m_recordNum].m_task = taskName;
            taskList[m_recordNum].m_timeUnit = "nanoseconds";
            taskList[m_recordNum].m_duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime -
                                                                     m_startTime);
            m_recordNum++;
        }
    }
    std::ostream &operator<<(std::ostream &os, const TimedTask &src)
    {
        if (os)
        {
            os << "--------------------------" << std::endl;
            os << "Execution Times:" << std::endl;
            os << "--------------------------" << std::endl;
            for (size_t i = 0; i < src.m_recordNum; i++)
            {
                os.width(21);
                os.setf(std::ios::left);
                os << src.taskList[i].m_task << " ";
                os.width(21);
                os.unsetf(std::ios::left);
                os << src.taskList[i].m_duration.count() << " ";
                os << src.taskList[i].m_timeUnit << std::endl;
            }
            os << "--------------------------" << std::endl;
        }
        return os;
    }
}