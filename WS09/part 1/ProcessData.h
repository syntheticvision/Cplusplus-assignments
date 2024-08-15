//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           July 28, 2024
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================

// Workshop 9 - Multi-Threading, Thread Class

#ifndef SENECA_PROCESSDATA_H
#define SENECA_PROCESSDATA_H

#include <string>

namespace seneca
{
	void computeAvgFactor(const int*, int, int, double&);
	void computeVarFactor(const int*, int, int, double, double&);

	class ProcessData
	{
		int total_items{};
		int* data{};
	public:
		ProcessData(const std::string&);
		ProcessData(const ProcessData&) = delete;
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();
		operator bool() const;
		int operator()(const std::string&, double&, double&);
	};
}

#endif
