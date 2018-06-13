//
// Created by a_mod on 13.06.2018.
//

#include <native-backend/interface/Backend.h>
#include <native-backend/packaging/HtmlPackage.h>
#include <native-backend/parsing/RequestInformation.h>
#include <native-backend/routing/Router.h>

boost::shared_ptr<nvb::HtmlPackage> makeWebsite(boost::shared_ptr<nvb::RequestInformation>){
    auto package = nvb::HtmlPackage::createShared();
    package->loadRawHtml("<b> oi </b>");
    return package;
}

void text (int i){
    std::cout << "hi" << std::endl;
}

nvb::Backend::Backend(unsigned short port) {
    server_ = Server::create(port, io_context);

    server_->onNewConnection->connect(text);

    nvb::Router::getInstance()->addRoute(HttpVerb::Verb::get, "/", makeWebsite);
}

boost::movelib::unique_ptr<nvb::Backend> nvb::Backend::create(unsigned short port) {
    return boost::movelib::unique_ptr<nvb::Backend>(new nvb::Backend(port));
}

void nvb::Backend::run() {
    io_context.run();
}
