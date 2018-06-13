//
// Created by a_mod on 10.05.2018.
//

#include "native-backend/packaging/HtmlPackage.h"
#include <native-backend/parsing/TextProcessor.h>
#include <native-backend/errors/errors.h>
#include <fstream>
#include <exception>


boost::shared_ptr<nvb::HtmlPackage> nvb::HtmlPackage::createShared() {
    return boost::shared_ptr<nvb::HtmlPackage>(new HtmlPackage());
}

void nvb::HtmlPackage::load(std::string path) {
    std::ifstream ifstream;
    ifstream.open(path.c_str(), std::ios::binary | std::ios::ate);

    if(!ifstream.good())
        throw nvb::error::invalid_argument_error("The file at path + \"" + path + "\" could not be loaded!");

    std::streamsize size = ifstream.tellg();
    ifstream.seekg(0);

    char buf[size + 1] {0};
    ifstream.read(buf, size);
    data_ = std::string(buf);
    ifstream.close();
}

void nvb::HtmlPackage::loadRawHtml(std::string html) {
    data_ = html;
}

void nvb::HtmlPackage::addChild(std::string key, boost::shared_ptr<nvb::HtmlPackage> htmlPackage) {
    children_[key] = htmlPackage;
}

std::string nvb::HtmlPackage::get() {
    std::unordered_map<std::string, std::string> replacements;
    for(auto& child : children_){
        replacements["{{" + child.first + "}}"] = child.second->get();
    }

    std::string out = data_;
    TextProcessor::process(&out, replacements);
    return out;
}
