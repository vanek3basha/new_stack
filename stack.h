    #ifndef STACK_H
    #define STACK_H


    #include <stdlib.h>
    #include <stdio.h>

    typedef enum
    {
        STACK_TYPE_INT,
        STACK_TYPE_DOUBLE
    } StackType;

    typedef enum
    {
        NOT_ERROR,
        STACK_NULL_ERROR,
        STACK_TYPE_ERROR,
        POP_FROM_SIZE_ZERO_STACK_ERROR,
        NEW_STACK_IS_NULL_ERROR,
        REALLOC_STACK_ERROR
    } StackError;

    typedef union
    {
        int int_value;
        double double_value;
    } StackValue;

    struct stack_t 
    { 
        size_t size_of_stack;
        size_t capacity_of_stack;
        StackType type;
        union 
        {
            int* int_stack;
            double* double_stack;
        } stack_massive;
    };

    stack_t* stack_init(size_t capacity, StackType type);
    StackError int_stack_push(stack_t* stack, int value);
    StackError double_stack_push(stack_t* stack, double value);
    int int_stack_pop(stack_t* stack);
    double double_stack_pop(stack_t* stack);
    StackError stack_realloc(stack_t* stack, size_t new_capacity);
    StackError stack_free(stack_t* stack);
    template <typename T> StackError stack_push(stack_t* stack, T value);

    #endif