// Copyright 2019 Sviatoslav Dmitriev
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "RetCodeWrapper.h"

template<int v = 0>
int getInt()
{
    return v;
}

RetWrap<std::unique_ptr<int>> gett()
{
    return RetWrap<std::unique_ptr<int>>(1, std::make_unique<int>(1));
}

TEST_CASE("RetWrap tests", "[RetCodeWrapper]") {

    int e = GENERATE(take(1, random(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())));
    int v = GENERATE(take(1, random(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())));
    
    SECTION("ValueAndError_Value", "[value]") {
        RetWrap<int, int> ret(e, v);
        REQUIRE(ret.getError() == e);
        REQUIRE(ret.getValue() == v);
    }

    SECTION("ValueAndError_InplaceConstruct", "[value]") {
        RetWrap<std::tuple<int, int>, int> ret(e, std::in_place, v, v);
        REQUIRE(ret.getError() == e);
        REQUIRE(std::get<0>(ret.getValue()) == v);
        REQUIRE(std::get<1>(ret.getValue()) == v);
    }

    SECTION("ValueAndError_Value_initializer_list", "[value]") {
        RetWrap<int, int> ret = {e, v};
        REQUIRE(ret.getError() == e);
        REQUIRE(ret.getValue() == v);
    }

    SECTION("ValueAndError_Value_initializer_list_return cast", "[value]") {
        auto lambda = [&]() -> RetWrap<int, int> {
            return {e, v};
        };
        RetWrap<int, int> ret = lambda();
        REQUIRE(ret.getError() == e);
        REQUIRE(ret.getValue() == v);
    }

    SECTION("OnlyError_Value", "[value]") {
        RetWrap<int, int> ret(e);
        REQUIRE(ret.getError() == e);
        REQUIRE_FALSE(ret.hasValue());
    }

    SECTION("OnlyError_Value_implicit", "[value]") {
        RetWrap<int, int> ret = e;
        REQUIRE(ret.getError() == e);
        REQUIRE_FALSE(ret.hasValue());
    }

    SECTION("ValueAndError_Reference", "[reference]") {
        RetWrap<int&, int> retRef(e, v);
        REQUIRE(retRef.getError() == e);
        REQUIRE(retRef.getValue() == v);
        ++v;
        REQUIRE(retRef.getError() == e);
        REQUIRE(retRef.getValue() == v);
    }

    SECTION("ValueAndError_Reference_initializer_list", "[reference]") {
        RetWrap<int&, int> retRef = {e, v};
        REQUIRE(retRef.getError() == e);
        REQUIRE(retRef.getValue() == v);
        ++v;
        REQUIRE(retRef.getError() == e);
        REQUIRE(retRef.getValue() == v);
    }

    SECTION("ValueAndError_Reference_initializer_list_return cast", "[reference]") {
        auto lambda = [&]() -> RetWrap<int&, int> {
            return {e, v};
        };
        RetWrap<int&, int> retRef = lambda();
        REQUIRE(retRef.getError() == e);
        REQUIRE(retRef.getValue() == v);
        ++v;
        REQUIRE(retRef.getError() == e);
        REQUIRE(retRef.getValue() == v);
    }

    SECTION("OnlyError_Reference", "[reference]") {
        
        RetWrap<int&, int> retRef(e);
        REQUIRE(retRef.getError() == e);
        REQUIRE_FALSE(retRef.hasValue());
    }

    SECTION("OnlyError_Reference_implicit", "[reference]") {
        
        RetWrap<int&, int> retRef = e;
        REQUIRE(retRef.getError() == e);
        REQUIRE_FALSE(retRef.hasValue());
    }

    SECTION("ValueAndError_ConstReference", "[const-reference]") {
        const RetWrap<int&, int> CretRef(e, v);
        REQUIRE(CretRef.getError() == e);
        REQUIRE(CretRef.getValue() == v);
        ++v;
        REQUIRE(CretRef.getError() == e);
        REQUIRE(CretRef.getValue() == v);
    }

    SECTION("OnlyError_ConstReference", "[const-reference]") {
        const RetWrap<int&, int> CretRef(e);
        REQUIRE(CretRef.getError() == e);
        REQUIRE_FALSE(CretRef.hasValue());
    }

    SECTION("ValueAndReferenceToError_Value", "[value]") {
        RetWrap<int, int&> ret1(e, v);
        REQUIRE(ret1.getError() == e);
        REQUIRE(ret1.getValue() == v);
        ++e;
        REQUIRE(ret1.getError() == e);
        REQUIRE(ret1.getValue() == v);
    }

    SECTION("OnlyReferenceToError_Value", "[value]") {
        RetWrap<int, int&> ret1(e);
        REQUIRE(ret1.getError() == e);
        REQUIRE_FALSE(ret1.hasValue());
        ++e;
        REQUIRE(ret1.getError() == e);
        REQUIRE_FALSE(ret1.hasValue());
    }

    SECTION("ValueAndReferenceToError_Reference", "[reference]") {
        RetWrap<int&, int&> retRef1(e, v);
        REQUIRE(retRef1.getError() == e);
        REQUIRE(retRef1.getValue() == v);
        ++v;
        REQUIRE(retRef1.getError() == e);
        REQUIRE(retRef1.getValue() == v);
        ++e;
        REQUIRE(retRef1.getError() == e);
        REQUIRE(retRef1.getValue() == v);
        ++v;
        REQUIRE(retRef1.getError() == e);
        REQUIRE(retRef1.getValue() == v);
    }

    SECTION("OnlyReferenceToError_Reference", "[reference]") {
        RetWrap<int&, int&> retRef1(e);
        REQUIRE(retRef1.getError() == e);
        REQUIRE_FALSE(retRef1.hasValue());
        ++e;
        REQUIRE(retRef1.getError() == e);
        REQUIRE_FALSE(retRef1.hasValue());
    }

    SECTION("ValueAndReferenceToError_ConstReference", "[const-reference]") {
        const RetWrap<int&, int&> CretRef1(e, v);
        REQUIRE(CretRef1.getError() == e);
        REQUIRE(CretRef1.getValue() == v);
        ++v;
        REQUIRE(CretRef1.getError() == e);
        REQUIRE(CretRef1.getValue() == v);
        ++e;
        REQUIRE(CretRef1.getError() == e);
        REQUIRE(CretRef1.getValue() == v);
        ++v;
        REQUIRE(CretRef1.getError() == e);
        REQUIRE(CretRef1.getValue() == v);
    }

    SECTION("OnlyReferenceToError_ConstReference", "[const-reference]") {
        const RetWrap<int&, int&> CretRef1(e);
        REQUIRE(CretRef1.getError() == e);
        REQUIRE_FALSE(CretRef1.hasValue());
        ++e;
        REQUIRE(CretRef1.getError() == e);
        REQUIRE_FALSE(CretRef1.hasValue());
    }

    SECTION("Assignment_Reference", "[reference]") {
        RetWrap<int&, int> retRef1(e, v);
        RetWrap<int&, int> retRef2(retRef1);
        REQUIRE(retRef1.getValue() == retRef2.getValue());
        ++v;
        REQUIRE(retRef1.getValue() == retRef2.getValue());
        REQUIRE(retRef1.getValue() == v);
        REQUIRE(v == retRef2.getValue());
    }

    SECTION("Conversion_Value", "[value]") {
        RetWrap<int> ret(e, v);
        REQUIRE(e == ret);
    }

    SECTION("Conversion_Reference", "[reference]") {
        RetWrap<int&> ret(e, v);
        REQUIRE(e == ret);
    }

    SECTION("Conversion_ConstReference", "[const-reference]") {
        const RetWrap<int&> ret(e, v);
        REQUIRE(e == ret);
    }

    SECTION("HasValue_Value", "[value]") {
        RetWrap<int> ret(e, v);
        REQUIRE(ret.hasValue());
    }

    SECTION("HasNoValue_Value", "[value]") {
        RetWrap<int> ret(e);
        REQUIRE_FALSE(ret.hasValue());
    }

    SECTION("HasValue_Reference", "[reference]") {
        
        RetWrap<int&> ret(e, v);
        REQUIRE(ret.hasValue());
    }

    SECTION("HasNoValue_Reference", "[reference]") {
        RetWrap<int&> ret(e);
        REQUIRE_FALSE(ret.hasValue());
    }

    SECTION("HasValue_ConstReference", "[const-reference]") {
        const RetWrap<int&> ret(e, v);
        REQUIRE(ret.hasValue());
    }

    SECTION("HasNoValue_ConstReference", "[const-reference]") {
        const RetWrap<int&> ret(e);
        REQUIRE_FALSE(ret.hasValue());
    }

    SECTION("Copy and Move")
    {
        SECTION("Value")
        {
            RetWrap<int> ret1(e, v);
            SECTION("Copy")
            {
                RetWrap<int> ret2(ret1);
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
            }
            SECTION("Move")
            {
                RetWrap<int> ret2(std::move(ret1));
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
            }
        }
        SECTION("Reference")
        {
            RetWrap<int&> ret1(e, v);
            SECTION("Copy")
            {
                RetWrap<int&> ret2(ret1);
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
                auto r = gett();
            }
            SECTION("Move")
            {
                RetWrap<int&> ret2(std::move(ret1));
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
            }
        }
    }

    SECTION("Move value")
    {
        RetWrap<std::unique_ptr<int>> ret(e, std::make_unique<int>(v));
        REQUIRE(ret.hasValue());
        auto ptr = ret.moveValue();
        REQUIRE(*ptr == v);
        REQUIRE_FALSE(ret.hasValue());
    }

    SECTION("Assignments")
    {
        SECTION("Value")
        {
            RetWrap<int> ret1(e, v);
            SECTION("Copy")
            {
                RetWrap<int> ret2;
                ret2 = ret1;
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
            }
            SECTION("Move")
            {
                RetWrap<int> ret2;
                ret2 = std::move(ret1);
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
            }
        }
        SECTION("Reference")
        {
            RetWrap<int&> ret1(e, v);
            SECTION("Copy")
            {
                RetWrap<int&> ret2;
                ret2 = ret1;
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
                auto r = gett();
            }
            SECTION("Move")
            {
                RetWrap<int&> ret2;
                ret2 = std::move(ret1);
                REQUIRE(ret2.hasValue());
                REQUIRE(ret2.getError() == e);
                REQUIRE(ret2.getValue() == v);
            }
        }
    }

    SECTION("Only error")
    {
        SECTION("Default constructor")
        {
            RetWrap<void, int> ret;
            REQUIRE_FALSE(ret.hasValue());
        }

        SECTION("Constructor with error")
        {
            RetWrap<void, int> ret(e);
            REQUIRE_FALSE(ret.hasValue());
            REQUIRE(ret.getError() == e);
        }

        SECTION("Copy")
        {
            RetWrap<void, int> ret1(e);
            REQUIRE_FALSE(ret1.hasValue());
            REQUIRE(ret1.getError() == e);
            RetWrap<void, int> ret2(ret1);
            REQUIRE_FALSE(ret1.hasValue());
            REQUIRE(ret1.getError() == e);
            REQUIRE_FALSE(ret2.hasValue());
            REQUIRE(ret2.getError() == e);
        }

        SECTION("Move")
        {
            RetWrap<void, int> ret1(e);
            REQUIRE_FALSE(ret1.hasValue());
            REQUIRE(ret1.getError() == e);
            RetWrap<void, int> ret2(std::move(ret1));
            REQUIRE_FALSE(ret2.hasValue());
            REQUIRE(ret2.getError() == e);
        }

        SECTION("Assign")
        {
            RetWrap<void, int> ret1(e);
            REQUIRE_FALSE(ret1.hasValue());
            REQUIRE(ret1.getError() == e);
            RetWrap<void, int> ret2(e + 1);
            REQUIRE_FALSE(ret2.hasValue());
            REQUIRE(ret2.getError() == e + 1);
            ret2 = ret1;
            REQUIRE_FALSE(ret1.hasValue());
            REQUIRE(ret1.getError() == e);
            REQUIRE_FALSE(ret2.hasValue());
            REQUIRE(ret2.getError() == e);
        }

        SECTION("Move assign")
        {
            RetWrap<void, int> ret1(e);
            REQUIRE_FALSE(ret1.hasValue());
            REQUIRE(ret1.getError() == e);
            RetWrap<void, int> ret2(e + 1);
            REQUIRE_FALSE(ret2.hasValue());
            REQUIRE(ret2.getError() == e + 1);
            ret2 = std::move(ret1);
            REQUIRE_FALSE(ret2.hasValue());
            REQUIRE(ret2.getError() == e);
        }

        SECTION("Cast to error")
        {
            RetWrap<void, int> ret(e);
            REQUIRE(ret == e);
        }
    }

}
