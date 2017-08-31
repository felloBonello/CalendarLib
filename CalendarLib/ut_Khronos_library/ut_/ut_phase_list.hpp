#if !defined(GUARD_ut_phase_list_header)
#define GUARD_ut_phase_list_header

/** @file ut_phase_list.hpp
	@author Garth Santor
	@date 2014-05-02
	@version 1.0.0
	@note C++ 11/vc14
	@brief Unit Test Phase Tracking
	*/

#include "ut_test_phase.hpp"

#include <set>
#include <memory>
#include <iostream>


class PhaseList {
	std::set<unsigned> phases;
	static std::unique_ptr<PhaseList> ptr;

public:
	PhaseList() {
		for (unsigned i = 1; i <= TEST_PHASE; ++i)
			phases.insert(i);
	}

	~PhaseList() {
		if (phases.empty())
			std::cout << "\nAll "<< TEST_PHASE << " phases implemented." << std::endl;
		else {
			std::cout << "\nPhases not implemented: ";
			auto it = phases.begin();
			std::cout << *it;
			while (++it != phases.end())
				std::cout << ", " << *it;
			std::cout << std::endl;
		}
	}
public:
	static PhaseList& instance() { 
		if (!ptr)
			ptr.reset(new PhaseList);
		return *ptr; 
	}

	void implements(unsigned _phase) {
		phases.erase(_phase);
	}
};


/*============================================================================

Revision History

Version 1.0.0: 2014-05-02

==============================================================================
Copyright Garth Santor, 2014

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/
#endif // GUARD_ut_phase_list_header