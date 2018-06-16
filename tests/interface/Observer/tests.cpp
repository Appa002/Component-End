#define BOOST_TEST_MODULE interface_Observer_tests
#include <boost/test/unit_test.hpp>

#include <native-backend/interface/Backend.h>
#include <native-backend/interface/Observer.h>

int testVar = 0;

void foo(int i){
    testVar = i;
}

BOOST_AUTO_TEST_SUITE(interface_Observer_tests)

BOOST_AUTO_TEST_CASE( simple_behavior_test ){
    nvb::Observer<int> a;
    a.connect(foo);
    a = 2;
    BOOST_ASSERT(testVar == 2);
    a++;
    BOOST_ASSERT(testVar == 3);
    BOOST_ASSERT(3 == a);
}

BOOST_AUTO_TEST_SUITE_END()
