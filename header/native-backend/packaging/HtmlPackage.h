//
// Created by a_mod on 10.05.2018.
//

#ifndef NATIVE_BACKEND_HTMLPACKAGE_H
#define NATIVE_BACKEND_HTMLPACKAGE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <unordered_map>

namespace nvb{
    class HtmlPackage {
    public:
        static boost::shared_ptr<nvb::HtmlPackage> createShared();

        void load(std::string path);
        void loadRawHtml(std::string html);
        void addChild(std::string key, boost::shared_ptr<nvb::HtmlPackage> htmlPackage);
        std::string get();

    private:
        HtmlPackage() = default;
        std::unordered_map<std::string, boost::shared_ptr<nvb::HtmlPackage>> children_;

        std::string data_;
    };
}



#endif //NATIVE_BACKEND_HTMLPACKAGE_H
