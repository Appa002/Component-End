#define BOOST_TEST_MODULE interface_Backend_tests
#include <boost/test/unit_test.hpp>

#include <native-backend/interface/Backend.h>

BOOST_AUTO_TEST_SUITE(interface_Backend_tests)

BOOST_AUTO_TEST_CASE( first ){
    auto b = nvb::Backend::create(8080);
    b->run();
}

BOOST_AUTO_TEST_SUITE_END()
