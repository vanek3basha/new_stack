#ifndef SH_STACK_HPP_
#define SH_STACK_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <typeinfo>                              
#include <cxxabi.h>
#include <math.h>

#define MAX_CALLS_IN_HISTORY 127
#define CAPACITY_WITH_CANAR (capacity + 3)
#define NEW_CAPACITY_WITH_CANAR (new_capacity + 3)
#define INDEX_OF_LEFT_CANAR  0
#define INDEX_OF_RIGHT_CANAR (sh_stack->capacity_of_sh_stack + 1)
#define FLAG_NOT_ERROR 0
#define FLAG_CHECK_LEFT_CANAR 1
#define FLAG_CHECK_RIGHT_CANAR 2
#define FLAG_TWO_CANAR_ERROR 3

typedef uint32_t stack_flag_of_err_t;
typedef uint64_t hash_t;
typedef uint64_t canareyka_const_t;
typedef uint64_t poison_const_t;

struct stack_history_calls
{
    int         line;
    const char* file;
    const char* func;
};

template <typename elem_stk_T> 
struct shablon_stack_t
{
    size_t               left_struct_canar;
    elem_stk_T*          sh_stack_massive;
    size_t               capacity_of_sh_stack;
    size_t               size_of_sh_stack;
    hash_t               sh_stack_hash;
    hash_t               sh_struct_hash;
    stack_history_calls* info;
    size_t               calls_level;
    size_t               right_struct_canar;
};

// 0xB16B00B5
// 0xBADA55
#define LEFT_CANAREYKA     0xEBA10
#define RIGHT_CANAREYKA    0xBABAC4A1
#define POISON             0xD1B11
#define LEFT_STRUCT_CANAR  1488
#define RIGHT_STRUCT_CANAR 322
#define INDEX_OF_LEFT_CANAR  0
#define INDEX_OF_RIGHT_CANAR (sh_stack->capacity_of_sh_stack + 1)

#define SH_STACK_ERROR_LIST(X)             \
    X(NOT_ERROR)                           \
    X(SH_STACK_NULL_ERROR)                 \
    X(SH_STACK_MASSIVE_NULL_ERROR)         \
    X(SH_STACK_SIZE_LESS_ZERO_ERROR)       \
    X(SH_STACK_SIZE_LARGER_CAPACITY_ERROR) \
    X(SIZE_OF_ELEMENTS_ERROR)              \
    X(LEFT_CANAR_ERROR)                    \
    X(RIGHT_CANAR_ERROR)                   \
    X(TWO_CANAR_ERROR)                     \
    X(POISON_ERROR)                        \
    X(LEFT_STRUCT_CANAR_ERROR)             \
    X(RIGHT_STRUCT_CANAR_ERROR)            \
    X(HASH_CHANGE_ERROR)                   \
    X(DUMP_FILE_OPEN_ERROR)                \
    X(PIZDEC)                              \
    X(COUNT_OF_ERRORS)

typedef enum
{
    #define MAKE_ENUM(name) name,
    SH_STACK_ERROR_LIST(MAKE_ENUM)
    #undef MAKE_ENUM
} sh_stack_error_t;

#define STRING_DEF(name) #name,
static const char* ShStackErrorNames[] = {
    SH_STACK_ERROR_LIST(STRING_DEF)
};

#define FIRST_ERROR 1
#define NUMBER_OF_POSSIBLE_ERRORS COUNT_OF_ERRORS

template <typename elem_stk_T> 
shablon_stack_t<elem_stk_T>* sh_stack_init(size_t capacity, int line, const char* file, const char* func);

template <typename elem_stk_T> 
stack_flag_of_err_t sh_stack_free(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename elem_stk_T> 
stack_flag_of_err_t sh_stack_push(elem_stk_T value, shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename elem_stk_T>
elem_stk_T sh_stack_pop(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename elem_stk_T>
shablon_stack_t<elem_stk_T>* sh_stack_realloc(shablon_stack_t<elem_stk_T>* sh_stack, size_t new_capacity, \
    int line, const char* file, const char* func);

template <typename elem_stk_T>
sh_stack_error_t canareyka_create(shablon_stack_t<elem_stk_T>* sh_stack);

template <typename elem_stk_T>
sh_stack_error_t poison_create(shablon_stack_t<elem_stk_T>* sh_stack);

template <typename elem_stk_T> 
hash_t massive_hash_counting(shablon_stack_t<elem_stk_T>* sh_stack);

template <typename elem_stk_T> 
hash_t struct_hash_counting(shablon_stack_t<elem_stk_T>* sh_stack);

template <typename elem_stk_T>
size_t get_bytes_sum(const elem_stk_T* value);

template <typename elem_stk_T>
stack_flag_of_err_t sh_stack_check(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename elem_stk_T>
sh_stack_error_t check_canareyka(shablon_stack_t<elem_stk_T>* sh_stack);

template <typename elem_stk_T>
sh_stack_error_t check_poison(shablon_stack_t<elem_stk_T>* sh_stack, int line);

template <typename elem_stk_T>
sh_stack_error_t sh_stack_dump(stack_flag_of_err_t byte_flag, shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func);

#define SH_STACK_INIT(type, capacity)               sh_stack_init<type>(capacity, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_FREE(stack)                        sh_stack_free(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_PUSH(value, stack)                 sh_stack_push(value, stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_POP(stack)                         sh_stack_pop(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_REALLOC(stack, new_capacity)       sh_stack_realloc(stack, new_capacity, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_CHECK(stack)                       sh_stack_check(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_DUMP(byte_flag, stack)             sh_stack_dump(byte_flag, stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)

#include "stack_header/stack_func.hpp"
#include "stack_header/stack_secure.hpp"           
#include "stack_header/stack_check.hpp"            
#include "stack_header/stack_dump.hpp"

#endif




