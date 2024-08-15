// Name: Babak Ghafourigivi
// Seneca Student ID: 165118233
// Seneca email: bghafourigivi@myseneca.ca
// Date of completion: 03 August 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        Utilities temp_util;
        std::string eachLine = "", cur_Wstation = "", next_Wstation = "";
        size_t pos = 0u;
        bool more = false;
        std::vector<std::string> v_cur_Wstation, v_next_Wstation;

        std::ifstream read_file(file);
        if (!read_file)
            throw std::string("\n**Failed to open file ") + file + std::string(" **\n");

        try {
            while (std::getline(read_file, eachLine)) {
                if (!eachLine.empty()) {
                    pos = 0;
                    more = true;
                    cur_Wstation = temp_util.extractToken(eachLine, pos, more);
                    v_cur_Wstation.push_back(cur_Wstation);

                    if (more) {
                        next_Wstation = temp_util.extractToken(eachLine, pos, more);
                    }
                    else {
                        next_Wstation = "";
                    }
                    v_next_Wstation.push_back(next_Wstation);

                    auto cur_err_check = std::any_of(stations.begin(), stations.end(), [&](Workstation* first_src) {
                        if (first_src->getItemName() == cur_Wstation) {
                            if (!next_Wstation.empty()) {
                                auto next_err_check = std::any_of(stations.begin(), stations.end(), [&](Workstation* sec_src) {
                                    if (sec_src->getItemName() == next_Wstation) {
                                        first_src->setNextStation(sec_src);
                                        return true;
                                    }
                                    return false;
                                    });

                                if (!next_err_check)
                                    throw std::string("\n\n**Next Workstation is not found**\n\n");
                            }
                            m_activeLine.push_back(first_src);
                            return true;
                        }
                        return false;
                        });

                    if (!cur_err_check)
                        throw std::string("\n\n**Current Workstation is not found**\n\n");
                }
            }

            read_file.close();

            for (auto* first_src : m_activeLine) {
                auto start = std::none_of(stations.begin(), stations.end(), [&](Workstation* sec_src) {
                    return sec_src->getNextStation() == first_src;
                    });

                if (start)
                    m_firstStation = first_src;
            }

            m_cntCustomerOrder = g_pending.size();
        }
        catch (...) {
            read_file.close();
            throw;
        }
    }

    void LineManager::reorderStations() {

        Workstation* next_Wstation = m_firstStation;

        std::vector<Workstation*>  v_Wstation;

        while (next_Wstation) {

            v_Wstation.push_back(next_Wstation);
            next_Wstation = next_Wstation->getNextStation();
        }

        m_activeLine = v_Wstation;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t count = 0u;

        os << "Line Manager Iteration: " << ++count << std::endl;

        if (!g_pending.empty()) {
            *m_activeLine.front() += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto src : m_activeLine)
            src->fill(os);

        for (auto src : m_activeLine)
            src->attemptToMoveOrder();

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

    void LineManager::display(std::ostream& os) const {

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* src) {
            src->display(os);
            });
    }
}