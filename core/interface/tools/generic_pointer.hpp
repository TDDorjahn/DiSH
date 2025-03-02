#pragma once

#include "concepts.hpp"
#include "types.hpp"

#include <vector>
#include <memory>

namespace dsh
{

    using std::pointer_traits;
    using std::vector;
    using std::allocator_traits;
    using std::allocator;

    /**
     * @brief Type Eraser struct for generic_pointer
     * @struct _generic_pointer_base
     */
    struct _generic_pointer_base {

        virtual ~_generic_pointer_base() = default;
        virtual constexpr void free() = 0;

    };

    /**
     * @brief generic_pointer implementation
     * @extends _generic_pointer_base
     * 
     * @tparam Ptr Pointer type to be stored
     */
    template<Pointer Ptr>
    struct generic_pointer : public _generic_pointer_base {

        using traits            = pointer_traits<Ptr>; /** @typedef pointer_traits<Ptr> traits */
        using pointer_type      = typename traits::pointer; /** @typedef typename traits::pointer pointer_type */
        using value_type        = typename traits::element_type; /** @typedef typename traits::element_type value_type */
        using type              = generic_pointer; /** @typedef generic_pointer type */

        pointer_type ptr; /** @var pointer_type ptr */
        value_type value; /** @var value_type value */

        generic_pointer(pointer_type ptr, value_type value) : ptr{ptr}, value{value} {}; /** @fn constructor generic_pointer(pointer_type ptr, value_type value) */

        constexpr value_type get() const noexcept { return value; } /** @fn generic_pointer::get() @returns value */
        constexpr pointer_type base() const noexcept { return ptr; } /** @fn generic_pointer::base() @returns ptr */

        /** @fn free() @returns void
         *  @brief deletes and frees @b generic_pointer::ptr
         *  @implements virtual _generic_pointer_base::free() = 0
         */
        constexpr void free() override { delete ptr; /*---*/ ptr = nullptr;}

    };

/**
 * @brief Evaluates @b Base_Type for @b generic_pointer type traits.
 * @details Checks if Base_Type is derived from _generic_pointer_base,
 * Base_Type::value_type * is the same as Base_Type::pointer_type,
 * and that Base_Type::base(), Base_Type::get(), and Base_Type::free()
 * return proper types.
 * 
 * @tparam Base_Type The type checked for generic_pointer traits.
 */
template <typename Base_Type>
concept GenericPointer = std::derived_from<Base_Type, _generic_pointer_base> &&
                        Same<typename Base_Type::value_type *, typename Base_Type::pointer_type> &&
                        requires(Base_Type value) {

                            typename Base_Type::traits;
                            { value.base() }    -> Same<typename Base_Type::pointer_type>;
                            { value.get() }     -> Same<typename Base_Type::value_type>;
                            { value.free() }    -> Same<void>;

                        };

}