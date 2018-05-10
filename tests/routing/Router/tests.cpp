#define BOOST_TEST_MODULE routing_Router_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/routing/Router.h>
#include <native-backend/errors/errors.h>
#include <native-backend/parsing/RequestInformation.h>
#include <iostream>
#include <functional>

std::string testRequestWithGet = "GET /test?a=1&b=2 HTTP/1.1\n"
                                "Host: localhost:8080\n"
                                "User-Agent: Mozilla/5.0 Firefox/58.0\n"
                                "Accept: text/html\n"
                                "Accept-Language: en-US,en;q=0.5\n"
                                "Accept-Encoding: gzip, deflate\n"
                                "Connection: keep-alive\n"
                                "Upgrade-Insecure-Requests: 1\n"
                                "Pragma: no-cache\n"
                                "Cache-Control: no-cache";

std::string testRequestWithPost = "POST /test?a=1&b=2 HTTP/1.1\n"
                                 "Host: localhost:8080\n"
                                 "User-Agent: Mozilla/5.0 Firefox/58.0\n"
                                 "Accept: text/html\n"
                                 "Accept-Language: en-US,en;q=0.5\n"
                                 "Accept-Encoding: gzip, deflate\n"
                                 "Connection: keep-alive\n"
                                 "Upgrade-Insecure-Requests: 1\n"
                                 "Pragma: no-cache\n"
                                 "Cache-Control: no-cache";

BOOST_AUTO_TEST_SUITE(routing_Router_tests)

    BOOST_AUTO_TEST_CASE( incorrect_route_test ) {
        using namespace nvb;
        try{
            auto requestInformation = RequestInformation::create(testRequestWithGet);
            Router::getInstance()->evaluateRoute(requestInformation);
        }catch(error::invalid_route_error e){
            BOOST_ASSERT(true);
            return;
        }
        BOOST_ASSERT(false);
    }

    BOOST_AUTO_TEST_CASE( incorrect_http_verb_test ) {
        using namespace nvb;
        try{
            Router::getInstance()->addRoute(HttpVerb::Verb::get, "/test",
                                            std::function<boost::shared_ptr<nvb::HtmlPackage> (boost::shared_ptr<RequestInformation>)>(
                                                    [](boost::shared_ptr<nvb::RequestInformation>){
                                                        return HtmlPackage::createShared();
                                                    }));

            auto requestInformation = RequestInformation::create(testRequestWithPost);
            Router::getInstance()->evaluateRoute(requestInformation);
        }catch(error::invalid_route_error e){
            BOOST_ASSERT(true);
            return;
        }
        BOOST_ASSERT(false);
    }

    BOOST_AUTO_TEST_CASE( simple_evalulation_test ) {
        using namespace nvb;
        bool* pModified = new bool(false);

        try{
            Router::getInstance()->addRoute(HttpVerb::Verb::get, "/test",
                                            std::function<boost::shared_ptr<nvb::HtmlPackage>(boost::shared_ptr<nvb::RequestInformation>)>(
                                                    [&](boost::shared_ptr<nvb::RequestInformation>) {
                                                        *pModified = true;
                                                        return HtmlPackage::createShared();
                                                    }));

            auto requestInformation = RequestInformation::create(testRequestWithGet);
            Router::getInstance()->evaluateRoute(requestInformation);
        }catch(std::exception e){
            BOOST_TEST_MESSAGE(e.what());
            BOOST_ASSERT(false);
            return;
        }

        BOOST_ASSERT(pModified);
        delete pModified;
    }

BOOST_AUTO_TEST_SUITE_END()
