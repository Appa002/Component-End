//
// Created by a_mod on 10.05.2018.
//

#include "native-backend/packaging/HtmlPackage.h"
#include <native-backend/parsing/TextProcessor.h>
#include <fstream>
#include <exception>

boost::shared_ptr<nvb::HtmlPackage> nvb::HtmlPackage::createShared() {
    return boost::shared_ptr<nvb::HtmlPackage>(new HtmlPackage());
}

void nvb::HtmlPackage::load(std::string path) {
    std::ifstream ifstream;
    ifstream.open(path.c_str(), std::ifstream::in);

    ifstream.seekg(std::ifstream::end);
    std::streamsize size = ifstream.tellg();
    ifstream.seekg(0);

    ifstream.read(&data_.at(0), size);
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
        replacements[child.first] = child.second->get();
    }

    std::string out = data_;
    TextProcessor::process(&out, replacements);
    return out;
}
