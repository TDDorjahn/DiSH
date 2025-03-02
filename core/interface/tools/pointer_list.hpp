#pragma once
#include "generic_pointer.hpp"

namespace dsh {

    /**
     * @brief A vector of generic_pointer that facilitates most and additional member methods of std::vector<_Tp>\n
     * @note Usage: 
     * 
     */
    struct pointer_list {

        using value_type                    = _generic_pointer_base;
        using pointer                       = value_type *;
        using const_pointer                 = const value_type *;
        using reference                     = value_type &;
        using const_reference               = const value_type &;
        using iterator                      = value_type *;
        using const_iterator                = const value_type *;
        using reverse_iterator              = std::reverse_iterator<iterator>;
        using const_reverse_iterator        = std::reverse_iterator<const_iterator>;
        using size_type                     = size_t;
        using difference_type               = ptrdiff_t;

        using vec_it                        = vector<pointer>::iterator;
        using const_vec_it                  = vector<pointer>::const_iterator;
        using reverse_vec_it                = vector<pointer>::reverse_iterator;
        using const_reverse_vec_it          = vector<pointer>::const_reverse_iterator;

        using allocator_type                = allocator<pointer>;

        public:

            ///BEGIN Member Functions

            pointer_list() = default;

            pointer_list(vector<pointer> vec) : ptr_list(vec) {}

            pointer_list(pointer value) { ptr_list.emplace_back(value); }

            ~pointer_list() { cleanup(); }

            pointer_list& operator=(const pointer_list& other) { ptr_list = other.ptr_list; return *this; }
            
#if __cplusplus <= 201103L
            pointer_list& operator=(pointer_list&& other) { ptr_list = other.ptr_list; return *this; }
#else
            pointer_list& operator=(pointer_list&& other) noexcept(allocator_type::propagate_on_container_move_assignment::value) { ptr_list = other.ptr_list; return *this; }
#endif
            pointer_list& operator=(std::initializer_list<pointer> ilist) { ptr_list = ilist; return *this; }

            ///END Member Functions

            //START Non-member Functions

            constexpr friend bool operator==(const pointer_list &lhs, const pointer_list &rhs) { return lhs.ptr_list == rhs.ptr_list; }

            constexpr friend bool operator!=(const pointer_list &lhs, const pointer_list &rhs) { return lhs.ptr_list != rhs.ptr_list; }

            constexpr friend bool operator<(const pointer_list &lhs, const pointer_list &rhs) { return lhs.ptr_list < rhs.ptr_list; }

            constexpr friend bool operator<=(const pointer_list &lhs, const pointer_list &rhs) { return lhs.ptr_list <= rhs.ptr_list; }

            constexpr friend bool operator>(const pointer_list &lhs, const pointer_list &rhs) { return lhs.ptr_list > rhs.ptr_list; }

            constexpr friend bool operator>=(const pointer_list &lhs, const pointer_list &rhs) { return lhs.ptr_list >= rhs.ptr_list; }

            constexpr friend void swap(pointer_list& lhs, pointer_list &rhs) { lhs.ptr_list.swap(rhs.ptr_list); }

            constexpr friend vec_it erase(pointer_list &list, const_vec_it it) { 

                return list.ptr_list.erase(it);

            }

            constexpr friend vec_it erase(pointer_list &list, vec_it first, vec_it last) {

                return list.ptr_list.erase(first, last);

            }

            //END Non-member Functions

            //BEGIN Capacity

            __attribute__((__always_inline__))
            constexpr size_t capacity() const noexcept { return ptr_list.capacity(); }

            __attribute__((__always_inline__))
            constexpr bool empty() const noexcept { return ptr_list.empty(); }

            __attribute__((__always_inline__))
            constexpr size_t max_size() const noexcept { return ptr_list.max_size(); }

            __attribute__((__always_inline__))
            constexpr void reserve(size_t new_capacity) { return ptr_list.reserve(new_capacity); }

            __attribute__((__always_inline__))
            constexpr void shrink_to_fit() { return ptr_list.shrink_to_fit(); }

            __attribute__((__always_inline__))
            constexpr size_t size() const noexcept { return ptr_list.size(); }

            //END Capacity

            //BEGIN Element Access
            __attribute__((__always_inline__))
            constexpr pointer & at(size_type pos) { return ptr_list.at(pos); }

            __attribute__((__always_inline__))
            constexpr const_pointer at(size_type pos) const { return ptr_list.at(pos); }

            __attribute__((__always_inline__))
            constexpr pointer operator[](size_type pos) { return ptr_list[pos]; }

            __attribute__((__always_inline__))
            constexpr const_pointer operator[](size_type pos) const { return ptr_list[pos]; }

            __attribute__((__always_inline__))
            constexpr pointer front() { return ptr_list.front(); }

            __attribute__((__always_inline__))
            constexpr const_pointer front() const { return ptr_list.front(); }

            __attribute__((__always_inline__))
            constexpr pointer back() { return ptr_list.back(); }

            __attribute__((__always_inline__))
            constexpr const_pointer back() const { return ptr_list.back(); }

            constexpr pointer * data() { return ptr_list.data(); }

            constexpr const pointer * data() const { return ptr_list.data(); }

            //END Element Access

            //START Iterators

            __attribute__((__always_inline__))
            constexpr vec_it begin() noexcept { return ptr_list.begin(); }

            __attribute__((__always_inline__))
            constexpr const_vec_it begin() const noexcept { return ptr_list.begin(); }

            __attribute__((__always_inline__))
            constexpr const_vec_it cbegin() const noexcept { return ptr_list.cbegin(); }

            __attribute__((__always_inline__))
            constexpr vec_it end() noexcept { return ptr_list.end(); }

            __attribute__((__always_inline__))
            constexpr const_vec_it end() const noexcept { return ptr_list.end(); }

            __attribute__((__always_inline__))
            constexpr const_vec_it cend() const noexcept { return ptr_list.cend(); }

            __attribute__((__always_inline__))
            constexpr reverse_vec_it rbegin() noexcept { return ptr_list.rbegin(); }

            __attribute__((__always_inline__))
            constexpr const_reverse_vec_it rbegin() const noexcept { return ptr_list.rbegin(); }

            __attribute__((__always_inline__))
            constexpr const_reverse_vec_it rcbegin() const noexcept { return ptr_list.crbegin(); }

            __attribute__((__always_inline__))
            constexpr reverse_vec_it rend() noexcept { return ptr_list.rend(); }

            __attribute__((__always_inline__))
            constexpr const_reverse_vec_it rend() const noexcept { return ptr_list.rend(); }

            __attribute__((__always_inline__))
            constexpr const_reverse_vec_it rcend() const noexcept { return ptr_list.crend(); }

            //END Iterators

            //BEGIN Modifiers
#ifdef __cpp_lib_containers_range
            template<Object cont>
            constexpr void append_range(cont container) { ptr_list.append_range(container); }
#else
            template<Object cont>
            constexpr void append_range(cont container) { ptr_list.insert(ptr_list.end(), container.cbegin(), container.cend()); }
#endif

            __attribute__((noreturn, __always_inline__))
            constexpr void clear() { cleanup(); }

            __attribute__((noreturn, __always_inline__))
            constexpr void cleanup() {

                for(auto& ptr : ptr_list) {

                    ptr->free();

                }

                ptr_list.clear();

            }

            template<typename ... Args>
            __attribute__((__always_inline__))
            constexpr vec_it emplace(const_vec_it pos, Args&&... ptrs) {

                return ptr_list.emplace(pos, std::forward<Args>(ptrs) ...);

            }

            template<Pointer ... Ptrs>
            __attribute__((noreturn, __always_inline__))
            constexpr void emplace_back(Ptrs&& ... ptrs) {

                ptr_list.emplace_back(std::forward<Ptrs>(ptrs) ...);

            }

            vec_it erase(vec_it pos) { return ptr_list.erase(pos); }

            vec_it erase(const_vec_it pos) { return ptr_list.erase(pos); }

            vec_it erase(vec_it first, vec_it last) { return ptr_list.erase(first, last); }

            vec_it erase(const_vec_it first, const_vec_it last) { return ptr_list.erase(first, last); }

            template<Pointer Ptr>
            __attribute__((__always_inline__))
            constexpr vec_it insert(Ptr pointer, typename pointer_traits<Ptr>::element_type value) {

                return ptr_list.insert(ptr_list.begin(), generic_pointer<Ptr>(pointer, value));

            }

            template<Pointer Ptr>
            __attribute__((__always_inline__))
            constexpr vec_it insert_at(index in, Ptr pointer, typename pointer_traits<Ptr>::element_type value) {

                auto iterator = ptr_list.begin() + in;
                return ptr_list.insert(iterator, generic_pointer<Ptr>(pointer, value));

            }

            template<Pointer Ptr>
            __attribute__((__always_inline__))
            constexpr vec_it insert_back(Ptr pointer, typename pointer_traits<Ptr>::element_type value) {

                return insert_at(ptr_list.end(), generic_pointer<Ptr>(pointer, value));

            }

            template<Pointer Ptr>
            __attribute__((__always_inline__))
            constexpr vec_it insert_front(Ptr pointer, typename pointer_traits<Ptr>::element_type value) {

                return insert(generic_pointer<Ptr>(pointer, value));

            }

#ifdef __dsh_lib_ranges
            template<pointer, typename InputIt>
            __attribute__((__always_inline__))
            constexpr vec_it insert_range(
                const_vec_it pos,
                input_iter<pointer> first,
                input_iter<pointer> last
            ) 
            {

                if(first == last)
                    return vec_it(); //empty iterator to make compiler happy.

                size_t n = std::distance(first, last);

                ptr_list.insert(pos, first, last);

            }
#else

            template<Range R>
            constexpr auto insert_range(const auto pos, R && ranges) {

                ptr_list.insert_range(pos, ranges);

            }
#endif

            constexpr void pop_back() noexcept { ptr_list.pop_back(); }

            constexpr void push_back(pointer &value) { ptr_list.push_back(value); }

            __attribute__((noreturn, __always_inline__))
            constexpr void resize(size_type count) { ptr_list.resize(count); }

            __attribute__((noreturn, __always_inline__))
            constexpr void resize(size_type count, pointer value) { ptr_list.resize(count, value); }

#if __cplusplus < 201703L

            __attribute__((noreturn, __always_inline__))
            void swap(pointer_list &other.ptr_list) { ptr_list.swap(other); }

#elif __cplusplus == 202002L

            void swap(pointer_list& other) noexcept
            (std::allocator_traits<Allocator>::propagate_one_container_swap::value || std::allocator_traits<Allocator>::is_always_equal::value) {
                ptr_list.swap(other.ptr_list);
            }

#else

            __attribute__((noreturn, __always_inline__))
            constexpr void swap(pointer_list &other) noexcept
            (std::allocator_traits<allocator_type>::propagate_on_container_swap::value || std::allocator_traits<allocator_type>::is_always_equal::value) {
                ptr_list.swap(other.ptr_list);
            }

#endif

            //END Modifiers

        private:
            vector<pointer> ptr_list;

    };

}