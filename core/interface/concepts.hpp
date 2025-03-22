#pragma once

#include <concepts> //for general concepts
#include <string> //for string like object concepts
#include <string_view> //for string like object concepts
#include <filesystem> //for path and shell path concepts
#include <future> //for thread and future concepts
#include <ranges> //ranges
#include "osdef.hpp" //for architecture deduction

#ifdef DSH_LINUX
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <signal.h>
#elif defined(DSH_WIN)
    #include <windows.h>
#endif

#if defined(DSH_64)
    constexpr int ARCH_BYTES = 8;
#elif defined(DSH_32)
    constexpr int ARCH_BYTES = 4;
#else
    constexpr int ARCH_BYTES = 2;
#endif

using std::string, std::string_view;

namespace fs = std::filesystem;

namespace dsh { //BEGIN namespace dsh
/**
 * GROUP_START
 * @defgroup dsh_concepts
 * @brief Contains concepts for desired type traits / constraints
 * @{
 * 
 * @par Notation
 * Let @c C be the concept name and evaluator that either returns true or false, @c O be the object type or primitive type,
 *  @c E be the trait evaluator, and @c D be the desired trait.
 * Let @c E_D(O) be the evaluator looking for trait @c D in object @c O where
 * C -> E_D(O) where C is true if E_D(O) evaluates to true, false where E_D(O) evaluates to false.
 */

/**
 * @brief Evaluates @c Base_Type for @c fundamental_v type trait.
 * @tparam Base_Type A type that's checked for fundamental traits.
 * 
 */
template<typename Base_Type>
concept Fundamental = std::is_fundamental_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c trivial_v type trait.
 * @note Fundamental Types = {bool, char, wchar_t, char8_t, char16_t, char32_t, short, int, long, long long, float, double, long double, void, nullptr_t}.
 * 
 * @tparam Base_Type A type that's checked for trivial traits.
 */
template<typename Base_Type>
concept Trivial = std::is_trivial_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c object_v type trait.
 * @note Object Type = Types that occupy memory (every type, excluding void).
 * 
 * @tparam Base_Type A type that's checked for object traits.
 */
template<typename Base_Type>
concept Object = std::is_object_v<Base_Type>;

/**
 * @brief Evaluates @c Ptr_Type for @c pointer_v type trait.
 * 
 * @tparam Ptr_Type A type that's checked for pointer traits.
 */
template<typename Base_Type>
concept Pointer = std::is_pointer_v<Base_Type>;

/**
 * @brief Evaluates @c Ref_Type for @c reference_v type trait.
 * 
 * @tparam Ref_Type A type that's checked for reference traits.
 */
template <typename Base_Type>
concept Reference = std::is_reference_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c null_pointer_v type trait.
 * 
 * @tparam Base_Type A type that's checked for nullptr traits.
 */
template <typename Base_Type>
concept Nullptr = std::is_null_pointer_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c void_v type trait.
 * 
 * @tparam Base_Type A type that's checked for void type traits.
 */
template <typename Base_Type>
concept VoidType = std::is_void_v<Base_Type>;

/**
 * @brief Evaluates @b Base_Type for @b{VoidType and Pointer}
 * 
 * @tparam Base_Type A type that's checked for void pointer type traits
 */
template <typename Base_Type>
concept VoidPtrType = VoidType<Base_Type> && Pointer<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c const_v type trait.
 * 
 * @tparam Base_Type A type that's checked for const type traits.
 */
template <typename Base_Type>
concept Const = std::is_const_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c signed_v type trait.
 * 
 * @tparam Base_Type A type that's checked for signed type traits.
 */
template <typename Base_Type>
concept Signed = std::is_signed_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c unsigned_v type trait.
 * 
 * @tparam Base_Type A type that's checked for unsigned type traits.
 */
template <typename Base_Type>
concept Unsigned = std::is_unsigned_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c arithmetic_v type trait.
 * 
 * @tparam Base_Type A type that's checked for arithmetic traits.
 */
template <typename Base_Type>
concept Arithmetic = std::is_arithmetic_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c scalar_v type trait.
 * 
 * @tparam Base_Type A type that's checked for scalar traits.
 */
template <typename Base_Type>
concept Scalar = std::is_scalar_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c integral_v type trait.
 * 
 * @tparam Base_Type A type that's checked for integral type traits.
 */
template <typename Base_Type>
concept Integral = std::is_integral_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c floating_point_v type trait.
 * 
 * @tparam Base_Type A type that's checked for floating point type traits.
 */
template <typename Base_Type>
concept Floating = std::is_floating_point_v<Base_Type>;

/**
 * @brief Checks if @b First_Type and @b Second_Type have the exact same type and qualifiers.
 * @details Whether something is const, a reference, or volatile is considered.
 * @tparam First_Type First type to be compared.
 * @tparam Second_Type Second type to be compared.
 */
template <typename First_Type, typename Second_Type>
concept Same = std::same_as<First_Type, Second_Type>;

/**
 * @brief Checks if @b First_Type and @b Second_Type 
 * 
 * @tparam First_Type 
 * @tparam Second_Type 
 */
template <typename First_Type, typename Second_Type>
concept SameBase = Same<std::remove_cvref_t<First_Type>, std::remove_cvref_t<Second_Type>>;

template <typename First_Type, typename Second_Type>
concept SimilarTo = Same<std::remove_cvref_t<First_Type>, Second_Type>;

template <typename Base_Type>
concept AddressLike = Unsigned<Base_Type> && requires(Base_Type v) {

    { sizeof(v) == ARCH_BYTES };
    { !(v > INT_MAX || v < INT_MIN) };

};

/**
 * @brief Evalutes @c Base_Type for properties of an address.
 * @details Determines whether Base_Type is an address-like object, checking for:
 *                          i. Whether Base_Type is a pointer, reference, or integral*. (*further deduction needed)
 *                              a. If Base_Type is integral (a primitive integer representing an address location), then it must be addressable and meet the
 *                                  criterion of an address of ARCH_TYPE byte sized architecture.
 *                          ii. If the sizeof(Base_Type) is the size of the architecture in bytes.
 *          
 * 
 * @tparam Base_Type 
 */
template <typename Base_Type>
concept Address = (Pointer<Base_Type> || Reference<Base_Type> || (AddressLike<Base_Type> && Integral<Base_Type>)) 
                    && sizeof(Base_Type) == ARCH_BYTES;

/**
 * @brief Evaluates @c Base_Type for @c array_v type trait.
 * 
 * @tparam Base_Type A type that's checked for array type traits.
 */
template <typename Base_Type>
concept Array = std::is_array_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c class_v type trait.
 * 
 * @tparam Base_Type A type that's checked for class traits.
 */
template <typename Base_Type>
concept ClassType = std::is_class_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c enum_v type trait.
 * 
 * @tparam Base_Type A type that's checked for enum traits.
 */
template <typename Base_Type>
concept EnumType = std::is_enum_v<Base_Type>;

/**
 * @brief Evaluates @b Base_Type and @b Returnable_Type for @e enum traits and that they are the same type.
 * @details To avoid @b std::is_enum_v<decltype(__value__)>; with the original EnumType concept
 * @tparam Base_Type The base type to be compared against
 * @tparam Returnable_Type The type returned by a function or from a member of an object that compares against Base_Type
 */
template <typename Base_Type, typename Returnable_Type>
concept GenericEnumType = EnumType<Base_Type> && EnumType<Returnable_Type> && Same<Base_Type, Returnable_Type>;

/**
 * @brief Evaluates @c Base_Type for @c function_v type trait.
 * 
 * @tparam Base_Type A type that's checked for function traits.
 */
template <typename Base_Type>
concept Function = std::is_function_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c bounded_array_v type trait.
 * 
 * @tparam Base_Type A type that's checked for bounded array traits.
 */
template <typename Base_Type>
concept BoundedArray = std::is_bounded_array_v<Base_Type>;

/**
 * @brief Evaluates @c Base_Type for @c unbounded_array_v type trait.
 * 
 * @tparam Base_Type A type that's checked for unbounded array traits.
 */
template <typename Base_Type>
concept UnboundedArray = std::is_unbounded_array_v<Base_Type>;

/**
 * @brief Evaluates @b Range_Type for @b{ranges::begin() and ranges::end()} required types.
 * 
 * @tparam Range_Type A type that's checked for range traits
 */
template <typename Range_Type>
concept Range = requires(Range_Type& r) {

    std::ranges::begin(r);
    std::ranges::end(r);

};

/**
 * @brief Evaluates @c Base_Type to see if it is @e workable (either fundamental, trivial, or reference type).
 * 
 * @tparam Base_Type A type that's checked for @e workable traits.
 */
template <typename Base_Type>
concept Workable = Fundamental<Base_Type> || Trivial<Base_Type> || Reference<Base_Type>;

/**
 * @brief Evaluates @e Base_Type to check if it has @e StringLike traits.
 * @details Checks @e Base_Type for convertibility to std::string or std::string_view.
 * @note Avoids implicit conversions to a @e string or @e string_view from unrelated types,
 *       enforcing function parameters to only accept string-like objects. @n
 *       e.g., void process_input(StringLike auto &&input);
 * 
 * @tparam Base_Type A type that's checked for convertibility.
 */
template <typename Base_Type>
concept StringLike = std::is_convertible_v<Base_Type, string> || std::is_convertible_v<Base_Type, string_view>;

/**
 * @brief Evaluates @e Base_Type to check if it has @e Character traits.
 * @details Checks @e Base_Type and compares them against types @e char and @e wchar_t.
 * @note Avoids implicit conversion to a @e char from unrelated types. @n
 *       e.g., char to_upper(Character auto &&c);
 * @tparam Base_Type A type that's checked for char traits.
 */
template <typename Base_Type>
concept Character = Same<Base_Type, char> || Same<Base_Type, wchar_t>;

#ifdef __SIZEOF_FLOAT128__
    template <typename Float>
    concept QuadPrecision = Same<Float, __float128> && requires(Float f) { sizeof(f) == 16; };
#else
    template <typename Float>
    concept QuadPrecision = Same<Float, long double> || Same<Float, double> || Same<Float, float>;
#endif

/**
 * @brief Evaluates a @b function of type @b Callable_Type to check if it behaves like a function.
 * @details Calls @b{Callable_Type func} to see if it behaves like a callable / function.
 * @note Ensures callbacks and command handlers are valid (for shell or builtin commands).
 * @tparam Callable_Type A type that's used for function @b{Callable_Type func}.
 */
template <typename Callable_Type>
concept Callable = requires(Callable_Type func) { func(); };

/**
 * @brief Evaluates @e Base_Type to check if an object is a @e file @e descriptor.
 * @details Checks @e Base_Type is an integral type and that a @e file @e descriptor @b fd is valid.
 * @note Ensures functions expecting file descriptors don't accept arbitrary values.
 * @tparam Base_Type A type that's checked for integral traits.
 */
template <typename Base_Type>
concept FileDescriptor = Integral<Base_Type> && requires(Base_Type fd) { {fd >= 0 }; };

/**
 * @brief Evaluates @e Base_Type to check if an object is a @e PID.
 * @details Checks @e Base_type is an integral type and that a @b PID is valid.
 * @note Enures functions that interact with processes only accept valid PIDs.
 * @tparam Base_Type A type that's checked for integral traits.
 */
template <typename Base_Type>
concept PID = Integral<Base_Type> && requires(Base_Type pid) { {pid > 0}; };

/**
 * @brief Evaluates @e Base_Type to check if an object of type Base_Type qualifies as @b iterable.
 * @details Checks @e Base_Type's @b begin() and @b end() function return the same type.
 * @note Ensures arguments, history, and environment variables are handled properly.
 * @tparam Base_Type A type that's used to type a variable @b _type to get the types of @b begin() and @b end().
 */
template <typename Base_Type>
concept Iterable = requires(Base_Type _type) { { std::begin(_type) } -> Same<decltype(std::end(_type))>; };

/**
 * @brief Evaluates @e Base_Type to check if an object of type Base_Type qualifies as an @b AssociativeContainer
 * @details Uses @e Base_Type's type to check of the object @b _type is an @b AssociativeContiner
 * @note Ensures arguments, history, and environment variables are handled properly.
 * @tparam Base_Type A type used to make an object @b{Base_Type _type}.
 */
template <typename Base_Type>
concept AssociativeContainer = requires(Base_Type _type) {

    typename Base_Type::key_type;
    typename Base_Type::mapped_type;

};

/**
 * @brief Evaluates @b object @e _type of type @e Base_Type to see if the object is RAII managed.
 * @details @b{Base_Type _type} is checked for an @b ::element_type, checks if @b _type is the same type
 *          as @b Base_Type::element_type*.
 * @note Enforce correct memory management in functions requiring heap-allocated objects
 * @tparam Base_Type A type used to create an object @b _type.
 */
template <typename Base_Type>
concept RAIIManaged = requires(Base_Type _type) {

    typename Base_Type::element_type;
    { _type.get() } -> Same<typename Base_Type::element_type*>;

};

/**
 * @brief A generic shell command concept that evaluates whether the @b Command_Type is @b StringLike or a @b Callable.
 * @note Ensures that shell commands are either strings (external commands) or functions (built-in commands).
 * @tparam Command_Type The type to determine if it can be handled like a command.
 */
template <typename Command_Type>
concept ShellCmd = StringLike<Command_Type> || Callable<Command_Type>;

/**
 * @brief Evaluates @b{ Command_Type cmd } to see if it is a builtin command on the shell.
 * @details @b{ Command_Type cmd} is used to see if the @b cmd.name() is a string and @b cmd.execute() returns an integer.
 * @note Ensures that only valid builtin shell commands are executed in the shell loop.
 * @tparam Command_Type A type used to determine whether a command is external or internal.
 */
template <typename Command_Type>
concept BuiltinCmd = Callable<Command_Type> && requires (Command_Type cmd) {

    { cmd.name() } -> Same<string>;
    { cmd.execute() } -> Same<int>;

};

/**
 * @brief Checks whether type @b List_Type is a valid list of arguments
 * @details Checks if @b List_Type is @b Iterable and that @b{List_Type::value_type} is @b StringLike
 * @note Ensures that lists of strings are only passed as arguments to commands.
 * @tparam List_Type A list type (vector, array, char *) is @b StringLike and is @b Iterable
 */
template <typename List_Type>
concept ArgumentList = Iterable<List_Type> && requires(List_Type args) {

    typename List_Type::value_type;
    requires StringLike<typename List_Type::value_type>;

};

/**
 * @brief Checks if @b Environment_Name_Type is @b StringLike and not empty.
 * 
 * @tparam Environment_Name_Type 
 */
template <typename Environment_Name_Type>
concept EnvironmentVariable = StringLike<Environment_Name_Type> && requires(Environment_Name_Type var) {

    { var.empty() == false } -> Same<bool>;

};

/**
 * @brief Checks if @b PID_Type is a valid PID and that the PID of GID of FD is a foreground process.
 * @details Differentiates between background and foreground processes.
 * @tparam PID_Type A type that's checked for valid pid types.
 */
template <typename PID_Type>
concept ForegroundJob = PID<PID_Type> && requires() { { tcgetpgrp(STDIN_FILENO) == getpgrp() }; };

/**
 * @brief Checks if @b PID_Type is a valid PID and that PID of GID of FD is a background process.
 * @details Differentiates between background and foreground processes.
 * @tparam PID_Type A type that's checked for valid pid types.
 */
template <typename PID_Type>
concept BackgroundJob = PID<PID_Type> && requires() { { tcgetpgrp(STDIN_FILENO) != getpgrp() }; };
/**
 * @brief Ensures @b Signal_Type is a valid POSIX signal to be handled.
 * 
 * @tparam Signal_Type A type that's checked for being integral and POSIX compliant.
 */
template <typename Signal_Type>
concept Signal = Integral<Signal_Type> && requires(Signal_Type signal) { { signal >= 1 && signal <= 31 }; };

/**
 * @brief Generic Path concept that evaluates if @b Path_Type is a valid path.
 * 
 * @tparam Path_Type A type that's checked for valid paths.
 */
template <typename Path_Type>
concept Path = StringLike<Path_Type> && requires(Path_Type path) {

    { !path.empty() };
    { fs::exists(path) };
    { fs::is_directory(path) };

};

/**
 * @brief Specialization of Path for shell's root directory
 * 
 * @tparam Path_Type 
 */
template <typename Path_Type>
concept ShellPath = Path<Path_Type>;

/**
 * @brief Ensures @b Object is redirectable.
 * 
 * @tparam Object an @b Object that is determined redirectable or not.
 */
template <typename Object>
concept Redirectable = StringLike<Object> || FileDescriptor<Object>;

/**
 * @brief Ensures job control functions operate on valid jobs.
 * 
 * @tparam Job_Type A type specific to jobs in Linux / MacOS.
 */
template <typename Job_Type>
concept Job = requires(Job_Type job) { 

    { job.pid } -> PID; 
    { job.command } -> StringLike;
    { job.status } -> GenericEnumType<Job_Type>;
};

/**
 * @brief Checks whether a @b Thread_Type is thread safe.
 * 
 * @tparam Thread_Type 
 */
template <typename Thread_Type>
concept ThreadSafe = Same<Thread_Type, std::thread> || Same<Thread_Type, std::future<void>>;
/** @} */ //GROUP_END dsh_concepts

} //END namespace dsh