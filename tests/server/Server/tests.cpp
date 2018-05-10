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

boost::shared_ptr<HtmlPackage> makeWebsite(boost::shared_ptr<RequestInformation> requestInformation){
    auto textParameterContainer = HtmlPackage::createShared();
    if(requestInformation->params.find("text") == requestInformation->params.cend())
        textParameterContainer->loadRawHtml("Missing text param");
    else
        textParameterContainer->loadRawHtml(requestInformation->params.at("text"));

    auto myPackage = HtmlPackage::createShared();
    myPackage->loadRawHtml("<div>[TEXT PARAMETER]</div>");
    myPackage->addChild("[TEXT PARAMETER]", textParameterContainer);
    return myPackage;

}

BOOST_AUTO_TEST_SUITE(server_Server_tests)

    BOOST_AUTO_TEST_CASE(server_existents_check) {
       nvb::Router::getInstance()->addRoute(HttpVerb::Verb::get, "/", makeWebsite);
       Server::create(8080);
    }

BOOST_AUTO_TEST_SUITE_END()
