#if !defined(UNIT_TEST_UTIILITY_GUARD)
#define UNIT_TEST_UTIILITY_GUARD


#include <boost/test/auto_unit_test.hpp>


auto boost_compare(char const* lhs, char const* rhs)->boost::test_tools::predicate_result;

template<typename T>
inline T round(T value, int places) {
	return (T) floor(value * pow(T(10.0), T(places))+0.5) / pow(T(10.0), T(places));
}

#endif // UNIT_TEST_UTIILITY_GUARD