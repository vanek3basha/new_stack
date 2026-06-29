#ifndef SH_STACK_HPP_
#define SH_STACK_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <typeinfo>
#include <cxxabi.h>

template <typename stk_T> 
struct shablon_stack_t
{
    size_t   left_struct_canar;
    stk_T*   sh_stack_massive;
    size_t   capacity_of_sh_stack;
    size_t   size_of_sh_stack;
    size_t   right_struct_canar;
    uint64_t sh_stack_hash;
    uint64_t sh_struct_hash;
};

struct StackHistoryCalls
{
    int line;
    const char* file;
    const char* func;
};

#define LEFT_CANAREYKA     0b0101110010101111010111011011001101011100101011110101110110110011
#define RIGHT_CANAREYKA    0b0101110010111110010011011011001101011100101010110101110110110011
#define POISON             0b0101110011001011001010110101101101101001101101011011100101010111
#define LEFT_STRUCT_CANAR  1488
#define RIGHT_STRUCT_CANAR 322

typedef enum
{
    NOT_ERROR,
    SH_STACK_NULL_ERROR,
    SH_STACK_MASSIVE_NULL_ERROR,
    SH_STACK_SIZE_LESS_ZERO_ERROR,
    SH_STACK_SIZE_LARGER_CAPACITY_ERROR,
    SIZE_OF_ELEMENTS_ERROR,
    LEFT_CANAR_ERROR,
    RIGHT_CANAR_ERROR,
    POISON_ERROR,
    LEFT_STRUCT_CANAR_ERROR,
    RIGHT_STRUCT_CANAR_ERROR,
    HASH_CHANGE_ERROR,
    DUMP_FILE_OPEN_ERROR
} ShStackError;

static const char* ShStackErrorNames[] = 
{
    "NOT_ERROR",
    "SH_STACK_NULL_ERROR",
    "SH_STACK_MASSIVE_NULL_ERROR",
    "SH_STACK_SIZE_LESS_ZERO_ERROR",
    "SH_STACK_SIZE_LARGER_CAPACITY_ERROR",
    "SIZE_OF_ELEMENTS_ERROR",
    "LEFT_CANAR_ERROR",
    "RIGHT_CANAR_ERROR",
    "POISON_ERROR",
    "LEFT_STRUCT_CANAR_ERROR",
    "RIGHT_STRUCT_CANAR_ERROR",
    "DUMP_FILE_OPEN_ERROR"
};

#define MAX_CALLS_IN_HISTORY 127
static StackHistoryCalls call_history[MAX_CALLS_IN_HISTORY] = {};
static size_t level_in_history = 0 ;

template <typename stk_T> 
shablon_stack_t<stk_T>* sh_stack_init(size_t capacity, int line, const char* file, const char* func);

template <typename stk_T> 
ShStackError sh_stack_free(shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename stk_T> 
ShStackError sh_stack_push(stk_T value, shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename stk_T>
stk_T sh_stack_pop(shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename stk_T>
shablon_stack_t<stk_T>* sh_stack_realloc(shablon_stack_t<stk_T>* sh_stack, size_t new_capacity, \
    int line, const char* file, const char* func);

template <typename stk_T>
ShStackError left_canareyka_create(stk_T* left_element, size_t size_of_canareyka);

template <typename stk_T>
ShStackError right_canareyka_create(stk_T* right_element, size_t size_of_canareyka);

template <typename stk_T>
ShStackError poison_create(shablon_stack_t<stk_T>* sh_stack, size_t size_of_poison);

template <typename stk_T> 
uint64_t massive_hash_counting(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T> 
uint64_t struct_hash_counting(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
size_t get_bytes_sum(const stk_T* value);

template <typename stk_T>
ShStackError sh_stack_check(shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func);

template <typename stk_T>
ShStackError check_left_canareyka(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
ShStackError check_right_canareyka(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
ShStackError check_poison(shablon_stack_t<stk_T>* sh_stack, int line);

template <typename stk_T>
ShStackError sh_stack_dump(ShStackError* massive_of_error, shablon_stack_t<stk_T>* sh_stack, size_t count_of_errors, int line, const char* file, const char* func);

#define SH_STACK_INIT(type, capacity)               sh_stack_init<type>(capacity, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_FREE(stack)                        sh_stack_free(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_PUSH(value, stack)                 sh_stack_push(value, stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_POP(stack)                        sh_stack_pop(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_REALLOC(stack, new_capacity)       sh_stack_realloc(stack, new_capacity, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_CHECK(stack)                       sh_stack_check(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__)
#define SH_STACK_DUMP(massive, stack, count)        sh_stack_dump(massive, stack, count, __LINE__, __FILE__, __PRETTY_FUNCTION__)

#include "impl/stack_core.impl.hpp"
#include "impl/stack_secure.impl.hpp"
#include "impl/stack_check.impl.hpp"
#include "impl/stack_dump.impl.hpp"

#endif




