#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "tools.hpp"

namespace dsh
{

    /**
     * @brief Collection of pointers to test
     */
    struct test_generic_pointer_types {
        
        i8_ptr              test_i8_ptr             = new i8(0);
        i16_ptr             test_i16_ptr            = new i16(0);
        i32_ptr             test_i32_ptr            = new i32(0);
        i64_ptr             test_i64_ptr            = new i64(0);
    
        ui8_ptr             test_ui8_ptr            = new ui8(0);
        ui16_ptr            test_ui16_ptr           = new ui16(0);
        ui32_ptr            test_ui32_ptr           = new ui32(0);
        ui64_ptr            test_ui64_ptr           = new ui64(0);

        i8_ptr_c            test_i8_ptr_c           = new i8(0);
        i16_ptr_c           test_i16_ptr_c          = new i16(0);
        i32_ptr_c           test_i32_ptr_c          = new i32(0);
        i64_ptr_c           test_i64_ptr_c          = new i64(0);
    
        ui8_ptr_c           test_ui8_ptr_c          = new ui8(0);
        ui16_ptr_c          test_ui16_ptr_c         = new ui16(0);
        ui32_ptr_c          test_ui32_ptr_c         = new ui32(0);
        ui64_ptr_c          test_ui64_ptr_c         = new ui64(0);
    
        f32_ptr             test_f32_ptr            = new f32(0.0f);
        f64_ptr             test_f64_ptr            = new f64(0.0);
        f128_ptr            test_f128_ptr           = new f128(0.0Q);

        f32_ptr_c           test_f32_ptr_c          = new f32(0.0f);
        f64_ptr_c           test_f64_ptr_c          = new f64(0.0);
        f128_ptr_c          test_f128_ptr_c         = new f128(0.0Q);
    
        raw_str             test_c8_ptr             = new c8('b');
        u_raw_str           test_uc8_ptr            = new uc8('2');
        raw_w_str           test_c16_ptr            = new c16('y');
    
        void_ptr            test_void_ptr           = nullptr;
        void_c_ptr          test_void_c_ptr         = nullptr;
        
    };

    TEST_CASE("[TEST] generic_pointer construction", "[generic-pointer-constructor]") {

        using test = test_generic_pointer_types;
        test ptrs;

        //BEGIN generic_pointer test objects

        generic_pointer<i8_ptr>         i8_test     (ptrs.test_i8_ptr, *ptrs.test_i8_ptr);
        generic_pointer<i16_ptr>        i16_test    (ptrs.test_i16_ptr, *ptrs.test_i16_ptr);
        generic_pointer<i32_ptr>        i32_test    (ptrs.test_i32_ptr, *ptrs.test_i32_ptr);
        generic_pointer<i64_ptr>        i64_test    (ptrs.test_i64_ptr, *ptrs.test_i64_ptr);

        generic_pointer<i8_ptr_c>       i8_c_test   (ptrs.test_i8_ptr_c, *ptrs.test_i8_ptr_c);
        generic_pointer<i16_ptr_c>      i16_c_test  (ptrs.test_i16_ptr_c, *ptrs.test_i16_ptr_c);
        generic_pointer<i32_ptr_c>      i32_c_test  (ptrs.test_i32_ptr_c, *ptrs.test_i32_ptr_c);
        generic_pointer<i64_ptr_c>      i64_c_test  (ptrs.test_i64_ptr_c, *ptrs.test_i64_ptr_c);

        generic_pointer<ui8_ptr>        ui8_test    (ptrs.test_ui8_ptr, *ptrs.test_ui8_ptr);
        generic_pointer<ui16_ptr>       ui16_test   (ptrs.test_ui16_ptr, *ptrs.test_ui16_ptr);
        generic_pointer<ui32_ptr>       ui32_test   (ptrs.test_ui32_ptr, *ptrs.test_ui32_ptr);
        generic_pointer<ui64_ptr>       ui64_test   (ptrs.test_ui64_ptr, *ptrs.test_ui64_ptr);

        generic_pointer<ui8_ptr_c>      ui8_c_test  (ptrs.test_ui8_ptr_c, *ptrs.test_ui8_ptr_c);
        generic_pointer<ui16_ptr_c>     ui16_c_test (ptrs.test_ui16_ptr_c, *ptrs.test_ui16_ptr_c);
        generic_pointer<ui32_ptr_c>     ui32_c_test (ptrs.test_ui32_ptr_c, *ptrs.test_ui32_ptr_c);
        generic_pointer<ui64_ptr_c>     ui64_c_test (ptrs.test_ui64_ptr_c, *ptrs.test_ui64_ptr_c);

        generic_pointer<f32_ptr>        f32_test    (ptrs.test_f32_ptr, *ptrs.test_f32_ptr);
        generic_pointer<f64_ptr>        f64_test    (ptrs.test_f64_ptr, *ptrs.test_f64_ptr);
        generic_pointer<f128_ptr>       f128_test   (ptrs.test_f128_ptr, *ptrs.test_f128_ptr);

        generic_pointer<f32_ptr_c>      f32_c_test  (ptrs.test_f32_ptr_c, *ptrs.test_f32_ptr_c);
        generic_pointer<f64_ptr_c>      f64_c_test  (ptrs.test_f64_ptr_c, *ptrs.test_f64_ptr_c);
        generic_pointer<f128_ptr_c>     f128_c_test (ptrs.test_f128_ptr_c, *ptrs.test_f128_ptr_c);

        generic_pointer<raw_str>        c8_test     (ptrs.test_c8_ptr, *ptrs.test_c8_ptr);
        generic_pointer<u_raw_str>      uc8_test    (ptrs.test_uc8_ptr, *ptrs.test_uc8_ptr);
        generic_pointer<raw_w_str>      c16_test    (ptrs.test_c16_ptr, *ptrs.test_c16_ptr);

        //END generic_pointer test objects

        //BEGIN pointer type comparison

        REQUIRE(Same<i8_ptr, decltype(i8_test.ptr)>);
        REQUIRE(Same<i16_ptr, decltype(i16_test.ptr)>);
        REQUIRE(Same<i32_ptr, decltype(i32_test.ptr)>);
        REQUIRE(Same<i64_ptr, decltype(i64_test.ptr)>);

        REQUIRE(Same<ui8_ptr, decltype(ui8_test.ptr)>);
        REQUIRE(Same<ui16_ptr, decltype(ui16_test.ptr)>);
        REQUIRE(Same<ui32_ptr, decltype(ui32_test.ptr)>);
        REQUIRE(Same<ui64_ptr, decltype(ui64_test.ptr)>);

        REQUIRE(Same<i8_ptr_c, decltype(i8_c_test.ptr)>);
        REQUIRE(Same<i16_ptr_c, decltype(i16_c_test.ptr)>);
        REQUIRE(Same<i32_ptr_c, decltype(i32_c_test.ptr)>);
        REQUIRE(Same<i64_ptr_c, decltype(i64_c_test.ptr)>);

        REQUIRE(Same<ui8_ptr_c, decltype(ui8_c_test.ptr)>);
        REQUIRE(Same<ui16_ptr_c, decltype(ui16_c_test.ptr)>);
        REQUIRE(Same<ui32_ptr_c, decltype(ui32_c_test.ptr)>);
        REQUIRE(Same<ui64_ptr_c, decltype(ui64_c_test.ptr)>);

        REQUIRE(Same<f32_ptr, decltype(f32_test.ptr)>);
        REQUIRE(Same<f64_ptr, decltype(f64_test.ptr)>);
        REQUIRE(Same<f128_ptr, decltype(f128_test.ptr)>);

        REQUIRE(Same<f32_ptr_c, decltype(f32_c_test.ptr)>);
        REQUIRE(Same<f64_ptr_c, decltype(f64_c_test.ptr)>);
        REQUIRE(Same<f128_ptr_c, decltype(f128_c_test.ptr)>);

        REQUIRE(Same<raw_str, decltype(c8_test.ptr)>);
        REQUIRE(Same<u_raw_str, decltype(uc8_test.ptr)>);
        REQUIRE(Same<raw_w_str, decltype(c16_test.ptr)>);

        //END pointer type comparison

        //BEGIN value type comparison

        REQUIRE(Same<i8, decltype(i8_test.value)>);
        REQUIRE(Same<i16, decltype(i16_test.value)>);
        REQUIRE(Same<i32, decltype(i32_test.value)>);
        REQUIRE(Same<i64, decltype(i64_test.value)>);

        REQUIRE(Same<ui8, decltype(ui8_test.value)>);
        REQUIRE(Same<ui16, decltype(ui16_test.value)>);
        REQUIRE(Same<ui32, decltype(ui32_test.value)>);
        REQUIRE(Same<ui64, decltype(ui64_test.value)>);

        REQUIRE(Same<i8_c, decltype(i8_c_test.value)>);
        REQUIRE(Same<i16_c, decltype(i16_c_test.value)>);
        REQUIRE(Same<i32_c, decltype(i32_c_test.value)>);
        REQUIRE(Same<i64_c, decltype(i64_c_test.value)>);

        REQUIRE(Same<ui8_c, decltype(ui8_c_test.value)>);
        REQUIRE(Same<ui16_c, decltype(ui16_c_test.value)>);
        REQUIRE(Same<ui32_c, decltype(ui32_c_test.value)>);
        REQUIRE(Same<ui64_c, decltype(ui64_c_test.value)>);

        REQUIRE(Same<f32, decltype(f32_test.value)>);
        REQUIRE(Same<f64, decltype(f64_test.value)>);
        REQUIRE(Same<f128, decltype(f128_test.value)>);

        REQUIRE(Same<f32_c, decltype(f32_c_test.value)>);
        REQUIRE(Same<f64_c, decltype(f64_c_test.value)>);
        REQUIRE(Same<f128_c, decltype(f128_c_test.value)>);

        REQUIRE(Same<c8, decltype(c8_test.value)>);
        REQUIRE(Same<uc8, decltype(uc8_test.value)>);
        REQUIRE(Same<c16, decltype(c16_test.value)>);

        //END value type comparison

    }

    TEST_CASE("[TEST] pointer_list construction", "[pointer-list-constructor]") {

        pointer_list list;

    }

}