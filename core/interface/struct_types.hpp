#include <iterator>
#include <ostream>

using std::ostream;

namespace dsh {

#if __cplusplus < 201703L

    /**
     * @defgroup Legacy Iterator Types
     * Abstractions from underlying pointer types
     * @warning Legacy Iterators deprecated since C++17. Legacy Iterators are enabled or disabled via a cpp versioning macro.
     */
    ///START Group Legacy Iterator Types
    ///@{
    template<typename IterType>
    using input_it = std::iterator<std::input_iterator_tag, IterType>;

    template<typename IterType>
    using output_it = std::iterator<std::output_iterator_tag, IterType>;

    ///@}
    ///END Group Legacy Iterator Types
#endif

/**
 * @defgroup General Iterator Types
 * Abstractions from underlying pointer types via pointer_traits.
 * Iterators aren't classes or structs and are implemented via concepts.
 */
///START Group General Iterator Types
///@{

/**
 * @brief Customized input iterator type for containers.
 * @details Adds types that reference the struct itself
 * @code {.cpp}
 * using iterator_type = input_it<Type>;
 * using iterator_pointer = input_it<Type> *;
 * using iterator_reference = input_it<Type> &;
 * using const_iterator_reference = const input_it<Type> &;
 * @endcode
 * 
 * 
 * @tparam Type: The type that will be pointed to.
 */
template <typename Type>
struct input_it
{

    using iterator_category             = std::input_iterator_tag;
    using difference_type               = ptrdiff_t;
    using value_type                    = Type;
    using pointer                       = Type *;
    using reference                     = Type &;
    using iterator_type                 = input_it<Type>;
    using iterator_pointer              = input_it<Type> *;
    using iterator_reference            = input_it<Type> &;
    using const_iterator_reference      = const input_it<Type> &;

    pointer m_ptr;

    explicit input_it(Type * ptr) : m_ptr(ptr) {}

    __attribute__((__always_inline__))
    constexpr reference operator*() const noexcept { return *m_ptr; }

    __attribute__((__always_inline__))
    constexpr pointer operator->() const noexcept { return m_ptr; }

    __attribute__((__always_inline__))
    constexpr iterator_reference operator++()
    {
        m_ptr++;
        return *this;
    }

    __attribute__((__always_inline__))
    constexpr iterator_type operator++(int)
    {

        iterator_type temp = *this;
        ++(*this);
        return temp;
    }

    constexpr bool operator==(const_iterator_reference rhs) { return m_ptr == rhs.m_ptr; }
    constexpr bool operator!=(const_iterator_reference rhs) { return !(*this == rhs); }

};

/**
 * @brief Customized output iterator type for containers.
 * @details Adds types that reference the struct itself
 * @code {.cpp}
 * using iterator_type = output_it<Type>;
 * using iterator_pointer = output_it<Type> *;
 * using iterator_reference = output_it<Type> &;
 * using const_iterator_reference = const output_it<Type> &;
 * @endcode
 * 
 * 
 * @tparam Type: The type that will be pointed to.
 */
template <typename Type>
struct output_it
{

    using out                           = ostream;
    using iterator_category             = std::output_iterator_tag;
    using difference_type               = void;
    using value_type                    = Type;
    using pointer                       = void;
    using reference                     = void;
    using iterator_type                 = output_it<Type>;
    using iterator_pointer              = output_it<Type> *;
    using iterator_reference            = output_it<Type> &;
    using const_iterator_reference      = const output_it<Type> &;

    out * os;

    explicit output_it(std::ostream& os) : os(&os) {}

    /*
    * Output iterators can only output, so how can they increment or dereference an output object?
    */

    constexpr iterator_reference operator*()      { return *this; }
    constexpr iterator_reference operator++()     { return *this; }
    constexpr iterator_reference operator++(int)  { return *this; }

    iterator_reference operator=(const Type& value) { *os << value << " "; return *this; }

};

/**
 * @brief Customized forward iterator type for containers.
 * @details Adds types that reference the struct itself
 * @code {.cpp}
 * using iterator_type = forward_it<Type>;
 * using iterator_pointer = forward_it<Type> *;
 * using iterator_reference = forward_it<Type> &;
 * using const_iterator_reference = const forward_it<Type> &;
 * @endcode
 * 
 * 
 * @tparam Type: The type that will be pointed to.
 */
template <typename Type>
struct forward_it {

    using iterator_category                 = std::forward_iterator_tag;
    using value_type                        = Type;
    using difference_type                   = ptrdiff_t;
    using pointer                           = value_type *;
    using reference                         = value_type &;
    using iterator_type                     = forward_it<Type>;
    using iterator_reference                = forward_it<Type> &;
    using iterator_pointer                  = forward_it<Type> *;

    pointer m_ptr;

    forward_it(pointer ptr) : m_ptr(ptr) {}

    constexpr reference operator*() const noexcept { return *m_ptr; }
    pointer operator->() const { return m_ptr; }

    iterator_reference operator++() { ++m_ptr; return *this; }
    iterator_type operator++(int) {

        iterator_type temp = *this;
        ++(*this);
        return temp;

    }

    constexpr bool operator==(const iterator_reference rhs) const { return m_ptr == rhs.m_ptr; }
    constexpr bool operator!=(const iterator_reference rhs) const {return !(*this == rhs); }

};

///@}
///END Group General Iterator Types

/**
 * @defgroup Iterator Types
 * Abstract the structs away from the user and give the types a meaningful name.
 */
///START Group Iterator Types
///@{

/**
 * @brief Gives meaningful names to struct input_it<Type>;
 * 
 * @tparam Type: The type that will be pointed to.
 */
template<typename Type>
using input_iter = struct input_it<Type>;

/**
 * @brief Gives meaningful names to struct output_it<Type>;
 * 
 * @tparam Type: The type that will be pointed to.
 */
template<typename Type>
using output_iter = struct output_it<Type>;

/**
 * @brief Gives meaningful names to struct forward_it<Type>;
 * 
 * @tparam Type: The type that will be pointed to.
 */
template<typename Type>
using forward_iter = struct forward_it<Type>;

///@}
///END Group Iterator Types

}