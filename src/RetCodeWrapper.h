// Copyright 2019 Sviatoslav Dmitriev
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#ifndef RETCODEWRAPPER_RETCODEWRAPPER_H
#define RETCODEWRAPPER_RETCODEWRAPPER_H

#include <memory>
#include <optional>

/*!
 * Classes used to pass return values from various methods
 * @tparam ValT Type of return value
 * @tparam ErrT Type of error value (int by default, can be reference)
 */
template<class ValT, class ErrT = int>
class RetCodeWrapper
{
    ErrT _error;
    mutable std::optional<ValT> _value;

public:


    /*!
     * Constructor
     */
    RetCodeWrapper() = default;

    
    /*!
     * Constructor
     * @param value Value to return
     * @param error Error to return
     */
    RetCodeWrapper(const ErrT & error, const ValT & value);


    /*!
     * Constructor
     * @param value Value to return
     * @param error Error to return
     */
    RetCodeWrapper(const ErrT & error, ValT && value);

    /*!
     * In place constructor
     * @param args Arguments passed to returned value constructor
     * @param error Error to return
     */
    template<class ... Args>
    RetCodeWrapper(const ErrT & error, std::in_place_t, Args&& ... args);


    /*!
     * Constructor without value, allows implicit cast from ErrT
     * @param error Error to return
     */
    RetCodeWrapper(const ErrT & error);


    /*!
     * Copy constructor
     * @param o Object to copy
     */
    RetCodeWrapper(const RetCodeWrapper &o);


    /*!
     * Move constructor
     * @param o Object to move
     */
    RetCodeWrapper(RetCodeWrapper &&o) noexcept;


    /*!
     * Copy assignment
     * @param o Object to copy
     */
    RetCodeWrapper& operator=(const RetCodeWrapper &o);


    /*!
     * Move assignment
     * @param o Object to move
     */
    RetCodeWrapper&operator=(RetCodeWrapper &&o) noexcept;


    /*!
     * Conversion operator
     * @return Converted error
     */
    operator const ErrT&() const;


    /*!
     * Get returned error
     * @return Passed error
     */
    const ErrT & getError() const;


    /*!
     * Get returned value
     * @return Passed value
     */
    const ValT & getValue() const;


    /*!
     * Move returned value
     * @return Passed value
     */
    ValT moveValue();


    /*!
     * Checks if contains value
     * @return True if contains value
     */
     bool hasValue() const;

};


/*!
 * Specialization for reference
 */
template<class ValT, class ErrT>
class RetCodeWrapper<ValT&, ErrT>
{
    ErrT _error;
    ValT* _value;
public:


    /*!
     * Constructor
     */
    RetCodeWrapper() = default;


    /*!
     * Constructor
     * @param value Value to return
     * @param error Error to return
     */
    RetCodeWrapper(const ErrT & error, ValT & value);


    /*!
     * Constructor without value, allows implicit cast from ErrT
     * @param error Error to return
     */
    RetCodeWrapper(const ErrT & error);


    /*!
     * Copy constructor
     * @param o Object to copy
     */
    RetCodeWrapper(const RetCodeWrapper&o);


    /*!
     * Move constructor
     * @param o Object to move
     */
    RetCodeWrapper(RetCodeWrapper &&o) noexcept;


    /*!
     * Copy assignment
     * @param o Object to copy
     */
    RetCodeWrapper& operator=(const RetCodeWrapper &o);


    /*!
     * Move assignment
     * @param o Object to move
     */
    RetCodeWrapper&operator=(RetCodeWrapper &&o) noexcept;


    /*!
     * Conversion operator
     * @return Converted error
     */
    operator const ErrT&() const;


    /*!
     * Get returned error
     * @return Passed error
     */
    const ErrT & getError() const;


    /*!
     * Get reference to passed value
     * @return Reference to passed value
     */
    ValT &getValue();


    /*!
     * Get constant reference to passed value
     * @return Constant reference to passed value
     */
    const ValT &getValue() const;


    /*!
     * Checks if contains value
     * @return True if contains value
     */
    bool hasValue() const;
};

/*!
 * Specialization for only error return
 */
template<class ErrT>
class RetCodeWrapper<void, ErrT>
{
    ErrT _error;
public:


    /*!
     * Constructor
     */
    RetCodeWrapper() = default;


    /*!
     * Constructor without value, allows implicit cast from ErrT
     * @param error Error to return
     */
    RetCodeWrapper(const ErrT & error);


    /*!
     * Copy constructor
     * @param o Object to copy
     */
    RetCodeWrapper(const RetCodeWrapper&o);


    /*!
     * Move constructor
     * @param o Object to move
     */
    RetCodeWrapper(RetCodeWrapper &&o) noexcept;


    /*!
     * Copy assignment
     * @param o Object to copy
     */
    RetCodeWrapper& operator=(const RetCodeWrapper &o);


    /*!
     * Move assignment
     * @param o Object to move
     */
    RetCodeWrapper&operator=(RetCodeWrapper &&o) noexcept;


    /*!
     * Conversion operator
     * @return Converted error
     */
    operator const ErrT&() const;


    /*!
     * Get returned error
     * @return Passed error
     */
    const ErrT & getError() const;


    /*!
     * Checks if contains value
     * @return True if contains value
     */
    constexpr bool hasValue() const;
};

//! Shorter alias to improve code quality
template<class ValT, class ErrT = int>
using RetWrap = RetCodeWrapper<ValT, ErrT>;

#include "RetCodeWrapper.tcc"

#endif //RETCODEWRAPPER_RETCODEWRAPPER_H
