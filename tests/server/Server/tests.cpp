#define BOOST_TEST_MODULE server_Server_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/server/Server.h>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>
#include <native-backend/routing/Router.h>
#include <boost/move/unique_ptr.hpp>
#include <native-backend/errors/HttpStatusCode.h>
#include <native-backend/parsing/RequestInformation.h>
#include <native-backend/packaging/HtmlPackage.h>

using boost::asio::ip::tcp;
using namespace nvb;

BOOST_AUTO_TEST_SUITE(server_Server_tests)

    BOOST_AUTO_TEST_CASE(server_existents_check) {

    }

BOOST_AUTO_TEST_SUITE_END()
