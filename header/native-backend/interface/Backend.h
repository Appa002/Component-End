//
// Created by a_mod on 13.06.2018.
//

#ifndef NATIVE_BACKEND_BACKEND_H
#define NATIVE_BACKEND_BACKEND_H

#include <native-backend/server/Server.h>

#include <boost/move/unique_ptr.hpp>

namespace nvb{
    class Backend {
    private:
        Backend(unsigned short port);

        boost::asio::io_context io_context;
        boost::movelib::unique_ptr<nvb::Server> server_;
    public:
        static boost::movelib::unique_ptr<nvb::Backend> create(unsigned short port);

        void run();
    };
}



#endif //NATIVE_BACKEND_BACKEND_H
