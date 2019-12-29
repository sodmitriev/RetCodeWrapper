# Copyright 2019 Sviatoslav Dmitriev
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

add_executable(RetCodeWrapperTest Test.cpp RetCodeWrapper.h RetCodeWrapper.tcc)
add_test(RetCodeWrapperTest RetCodeWrapperTest)
