//
// Created by a_mod on 13.06.2018.
//

#ifndef NATIVE_BACKEND_SIGNAL_H
#define NATIVE_BACKEND_SIGNAL_H



#include <functional>
#include <map>
#include <boost/shared_ptr.hpp>

namespace nvb{
    template <typename... Args>
    class Signal {
        boost::movelib::unique_ptr<std::map<int, std::function<void(Args...)>>> connected_slots_;
        int current_id_ = 0;

    public:
        typedef boost::shared_ptr<Signal<Args...>> signal_t;

        Signal(){
            connected_slots_ = boost::movelib::unique_ptr<std::map<int, std::function<void(Args...)>>>(new std::map<int, std::function<void(Args...)>>());
        }

        void connect(std::function<void(Args...)> slot_to_add){
            connected_slots_->insert(std::make_pair(++current_id_, slot_to_add));
        }
        void disconnect(int id){
            connected_slots_->erase(id);
        }
        void emit(Args... parameter){
            for(auto& slot : *connected_slots_){
                slot.second(parameter...);
            }
        }

        static boost::shared_ptr<Signal<Args...>> createShared(){
            return boost::shared_ptr<nvb::Signal<Args...>>(new Signal<Args...>());
        }
    };
}



#endif //NATIVE_BACKEND_SIGNAL_H
