#include "ut_utilities.hpp"



auto boost_compare(char const* lhs, char const* rhs) -> boost::test_tools::predicate_result {
	if (strcmp(lhs, rhs)) {
		boost::test_tools::predicate_result res(false);
		res.message() << "No match [" << lhs << " != " << rhs << "]";
		return res;
	}
	return true;
};
