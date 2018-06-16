//
// Created by a_mod on 16.06.2018.
//

#ifndef NATIVE_BACKEND_OBSERVER_H
#define NATIVE_BACKEND_OBSERVER_H

#include <functional>

#include <native-backend/interface/Signal.h>
#include <native-backend/utils/Types.h>

namespace nvb {

    /*! \brief A Special Signal which automatically calls Signal::emit if it's value changes.
     * One cannot call emit on an observer from the out side.
     * All operators are overloaded so one can use it like it's just an object of type T.
     * Other wise the behavior is indistinguishable from a Signal.
     * */
    template<class T>
    class Observer : public nvb::Signal<T> {
    private:
        T value;
    public:
        Observer() = default;

        Observer(const Observer<T> &other) {
            value = other.value;
        }

        //modifiers
        Observer &operator=(T v) {
            if(value != v)
                static_cast<nvb::Signal<T> *>(this)->emit(v);
            value = v;
            return *this;
        }

        Observer &operator+=(T v) {
            value += v;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator-=(T v) {
            value -= v;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator*=(T v) {
            value *= value;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator/=(T v) {
            value /= value;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator%=(T v) {
            value %= value;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator++() {
            value++;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator--() {
            value--;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        const Observer operator++(int) {
            Observer<T> temp = *this;
            this->operator++();
            return temp;
        }

        const Observer operator--(int) {
            Observer<T> temp = *this;
            this->operator--();
            return temp;
        }

        Observer &operator&=(T v) {
            value &= v;
            return *this;
        }

        Observer &operator|=(T v) {
            value |= v;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator^=(T v) {
            value ^= v;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator<<=(T v) {
            value <<= v;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        Observer &operator>>=(T v) {
            value >>= v;
            static_cast<nvb::Signal<T> *>(this)->emit(this->value);
            return *this;
        }

        //accessors
        Observer operator+() const {
            return Observer(+value);
        }

        Observer operator-() const {
            return Observer(-value);
        }

        Observer operator!() const {
            return Observer(!value);
        }

        Observer operator~() const {
            return Observer(~value);
        }

        //friends
        friend Observer operator+(Observer iw, Observer v) { return iw += v; }

        friend Observer operator+(Observer iw, T v) { return iw += v; }

        friend Observer operator+(T v, Observer iw) { return Observer(v) += iw; }

        friend Observer operator-(Observer iw, Observer v) { return iw -= v; }

        friend Observer operator-(Observer iw, T v) { return iw -= v; }

        friend Observer operator-(T v, Observer iw) { return Observer(v) -= iw; }

        friend Observer operator*(Observer iw, Observer v) { return iw *= v; }

        friend Observer operator*(Observer iw, T v) { return iw *= v; }

        friend Observer operator*(T v, Observer iw) { return Observer(v) *= iw; }

        friend Observer operator/(Observer iw, Observer v) { return iw /= v; }

        friend Observer operator/(Observer iw, T v) { return iw /= v; }

        friend Observer operator/(T v, Observer iw) { return Observer(v) /= iw; }

        friend Observer operator%(Observer iw, Observer v) { return iw %= v; }

        friend Observer operator%(Observer iw, T v) { return iw %= v; }

        friend Observer operator%(T v, Observer iw) { return Observer(v) %= iw; }

        friend Observer operator&(Observer iw, Observer v) { return iw &= v; }

        friend Observer operator&(Observer iw, T v) { return iw &= v; }

        friend Observer operator&(T v, Observer iw) { return Observer(v) &= iw; }

        friend Observer operator|(Observer iw, Observer v) { return iw |= v; }

        friend Observer operator|(Observer iw, T v) { return iw |= v; }

        friend Observer operator|(T v, Observer iw) { return Observer(v) |= iw; }

        friend Observer operator^(Observer iw, Observer v) { return iw ^= v; }

        friend Observer operator^(Observer iw, T v) { return iw ^= v; }

        friend Observer operator^(T v, Observer iw) { return Observer(v) ^= iw; }

        friend Observer operator<<(Observer iw, Observer v) { return iw <<= v; }

        friend Observer operator<<(Observer iw, T v) { return iw <<= v; }

        friend Observer operator<<(T v, Observer iw) { return Observer(v) <<= iw; }

        friend Observer operator>>(Observer iw, Observer v) { return iw >>= v; }

        friend Observer operator>>(Observer iw, T v) { return iw >>= v; }

        friend Observer operator>>(T v, Observer iw) { return Observer(v) >>= iw; }

        friend inline bool operator==(const Observer<T>& lhs, const T& rhs){ return lhs.value == rhs; }
        friend inline bool operator==(const T& lhs, const Observer<T>& rhs){ return lhs == rhs.value; }
        friend inline bool operator==(const Observer<T>& lhs, const Observer<T>& rhs){ return lhs.value == rhs.value; }

        friend inline bool operator!=(const Observer<T>& lhs, const T& rhs){ return lhs.value != rhs; }
        friend inline bool operator!=(const T& lhs, const Observer<T>& rhs){ return lhs != rhs.value; }
        friend inline bool operator!=(const Observer<T>& lhs, const Observer<T>& rhs){ return lhs.value != rhs.value; }

        friend inline bool operator<(const Observer<T>& lhs, const T& rhs){ return lhs.value < rhs; }
        friend inline bool operator<(const T& lhs, const Observer<T>& rhs){ return lhs < rhs.value; }
        friend inline bool operator<(const Observer<T>& lhs, const Observer<T>& rhs){ return lhs.value < rhs.value; }

        friend inline bool operator>(const Observer<T>& lhs, const T& rhs){ return lhs.value > rhs; }
        friend inline bool operator>(const T& lhs, const Observer<T>& rhs){ return lhs > rhs.value; }
        friend inline bool operator>(const Observer<T>& lhs, const Observer<T>& rhs){ return lhs.value > rhs.value; }

        friend inline bool operator<=(const Observer<T>& lhs, const T& rhs){ return lhs.value <= rhs; }
        friend inline bool operator<=(const T& lhs, const Observer<T>& rhs){ return lhs <= rhs.value; }
        friend inline bool operator<=(const Observer<T>& lhs, const Observer<T>& rhs){ return lhs.value <= rhs.value; }

        friend inline bool operator>=(const Observer<T>& lhs, const T& rhs){ return lhs.value >= rhs; }
        friend inline bool operator>=(const T& lhs, const Observer<T>& rhs){ return lhs >= rhs.value; }
        friend inline bool operator>=(const Observer<T>& lhs, const Observer<T>& rhs){ return lhs.value >= rhs.value; }

        template<typename BOOL = bool>
        void emit(T parameter) {
            /* Static Assert fails if one calls Observer::emit. This is so Signal::emit is only called if the value changes.*/
            static_assert(FailIfDefined<BOOL>::value, "Observer's \"emit\" function mustn't be triggered manually");
        }
    };
}


#endif //NATIVE_BACKEND_OBSERVER_H
