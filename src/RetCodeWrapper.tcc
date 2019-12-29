// Copyright 2019 Sviatoslav Dmitriev
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#ifndef RETCODEWRAPPER_RETCODEWRAPPER_TCC
#define RETCODEWRAPPER_RETCODEWRAPPER_TCC

#include <cassert>

//Return by value

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT>::RetCodeWrapper(const ErrT & error, const ValT & value) :
        _error(error), _value(ValT(value))
{
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT>::RetCodeWrapper(const ErrT &error, ValT &&value) :
        _error(error), _value(std::move(value))
{}

template<class ValT, class ErrT>
template<class... Args>
RetCodeWrapper<ValT, ErrT>::RetCodeWrapper(const ErrT &error, std::in_place_t, Args &&... args) :
        _error(error), _value(std::in_place, std::forward<Args>(args)...)
{}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT>::RetCodeWrapper(const ErrT & error) :
        _error(error), _value(std::nullopt)
{}

template<class ValT, class ErrT>
const ErrT & RetCodeWrapper<ValT, ErrT>::getError() const
{
    return _error;
}

template<class ValT, class ErrT>
const ValT & RetCodeWrapper<ValT, ErrT>::getValue() const
{
    assert(_value);
    return *_value;
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT>::operator const ErrT&() const
{
    return _error;
}

template<class ValT, class ErrT>
bool RetCodeWrapper<ValT, ErrT>::hasValue() const
{
    return _value.has_value();
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT>::RetCodeWrapper(const RetCodeWrapper &o) :
        _error(o._error), _value(o._value)
{}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT>::RetCodeWrapper(RetCodeWrapper &&o) noexcept :
        _error(std::move(o._error)), _value(std::move(o._value))
{}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT> &RetCodeWrapper<ValT, ErrT>::operator=(const RetCodeWrapper<ValT, ErrT> &o)
{
    _error = o._error;
    _value = o._value;
    return *this;
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT, ErrT> &RetCodeWrapper<ValT, ErrT>::operator=(RetCodeWrapper<ValT, ErrT> &&o) noexcept
{
    std::swap(_error, o._error);
    std::swap(_value, o._value);
    return *this;
}

template<class ValT, class ErrT>
ValT RetCodeWrapper<ValT, ErrT>::moveValue()
{
    auto ret = std::move(*_value);
    _value.reset();
    return ret;
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT>::RetCodeWrapper(const ErrT & error, ValT & value) :
        _error(error), _value(&value)
{
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT>::RetCodeWrapper(const ErrT & error) :
        _error(error), _value(nullptr)
{
}

//Return by reference

template<class ValT, class ErrT>
const ErrT & RetCodeWrapper<ValT&, ErrT>::getError() const
{
    return _error;
}

template<class ValT, class ErrT>
ValT &RetCodeWrapper<ValT&, ErrT>::getValue()
{
    assert(_value != nullptr);
    return *_value;
}

template<class ValT, class ErrT>
const ValT &RetCodeWrapper<ValT&, ErrT>::getValue() const
{
    assert(_value != nullptr);
    return *_value;
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT>::RetCodeWrapper(const RetCodeWrapper & o) :
        _error(o._error), _value(o._value)
{}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT>::RetCodeWrapper(RetCodeWrapper<ValT&, ErrT> &&o) noexcept :
        _error(std::move(o._error)), _value(o._value)
{}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT> &RetCodeWrapper<ValT&, ErrT>::operator=(const RetCodeWrapper<ValT&, ErrT> &o)
{
    _error = o._error;
    _value = o._value;
    return *this;
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT> &RetCodeWrapper<ValT&, ErrT>::operator=(RetCodeWrapper<ValT&, ErrT> &&o) noexcept
{
    std::swap(_error, o._error);
    std::swap(_value, o._value);
    return *this;
}

template<class ValT, class ErrT>
RetCodeWrapper<ValT&, ErrT>::operator const ErrT&() const
{
    return _error;
}

template<class ValT, class ErrT>
bool RetCodeWrapper<ValT&, ErrT>::hasValue() const
{
    return _value != nullptr;
}

//Return only error

template<class ErrT>
const ErrT & RetCodeWrapper<void, ErrT>::getError() const
{
    return _error;
}

template<class ErrT>
RetCodeWrapper<void, ErrT>::RetCodeWrapper(const ErrT & error):
        _error(error)
{}

template<class ErrT>
RetCodeWrapper<void, ErrT>::RetCodeWrapper(const RetCodeWrapper & o) :
        _error(o._error)
{}

template<class ErrT>
RetCodeWrapper<void, ErrT>::RetCodeWrapper(RetCodeWrapper<void, ErrT> &&o) noexcept :
        _error(std::move(o._error))
{}

template<class ErrT>
RetCodeWrapper<void, ErrT> &RetCodeWrapper<void, ErrT>::operator=(const RetCodeWrapper<void, ErrT> &o)
{
    _error = o._error;
    return *this;
}

template<class ErrT>
RetCodeWrapper<void, ErrT> &RetCodeWrapper<void, ErrT>::operator=(RetCodeWrapper<void, ErrT> &&o) noexcept
{
    std::swap(_error, o._error);
    return *this;
}

template<class ErrT>
RetCodeWrapper<void, ErrT>::operator const ErrT&() const
{
    return _error;
}

template<class ErrT>
constexpr bool RetCodeWrapper<void, ErrT>::hasValue() const
{
    return false;
}

#endif //RETCODEWRAPPER_RETCODEWRAPPER_TCC
