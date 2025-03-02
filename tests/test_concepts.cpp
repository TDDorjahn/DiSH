#define CATCH_CONFIG_MAIN

#include "concepts.hpp"
#include "types.hpp"
#include "tools.hpp"
#include <catch2/catch_all.hpp>

using namespace dsh;

struct test_fundamental_types {

    //TRUE TEST CASES
    i8          test_i8 = 0;
    i16         test_i16 = 0;
    i32         test_i32 = 0;
    i64         test_i64 = 0;

    ui8         test_ui8 = 0;
    ui16        test_ui16 = 0;
    ui32        test_ui32 = 0;
    ui64        test_ui64 = 0;

    f32         test_f32 = 0.0f;
    f64         test_f64 = 0.0;
    f128        test_f128 = 0.0Q;

    c8          test_c8 = 'a';
    uc8         test_uc8 = '1';
    c16         test_c16 = 'z';

    nullptr_t   test_nullptr = nullptr;

    //FALSE TEST CASES
    i8          * test_i8_ptr       = new i8(0);
    i16         * test_i16_ptr      = new i16(0);
    i32         * test_i32_ptr      = new i32(0);
    i64         * test_i64_ptr      = new i64(0);

    ui8         * test_ui8_ptr      = new ui8(0);
    ui16        * test_ui16_ptr     = new ui16(0);
    ui32        * test_ui32_ptr     = new ui32(0);
    ui64        * test_ui64_ptr     = new ui64(0);

    f32         * test_f32_ptr      = new f32(0.0f);
    f64         * test_f64_ptr      = new f64(0.0);
    f128        * test_f126_ptr     = new f128(0.0Q);

    c8          * test_c8_ptr       = new c8('b');
    uc8         * test_uc8_ptr      = new uc8('2');
    c16         * test_c16_ptr      = new c16('y');

    void_ptr    * test_void_ptr     = nullptr;
    void_c_ptr  * test_void_c_ptr   = nullptr;


    ~test_fundamental_types() {

        delete test_i8_ptr;
        delete test_i16_ptr;
        delete test_i32_ptr;
        delete test_i64_ptr;
        delete test_ui8_ptr;
        delete test_ui16_ptr;
        delete test_ui32_ptr;
        delete test_ui64_ptr;

    }


};

TEST_CASE("[TEST] Fundamental Concept", "[concept-fundamental]") {

    test_fundamental_types types;



}