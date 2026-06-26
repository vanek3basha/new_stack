#include <stdlib.h>
#include <stdio.h>

typedef enum
{
    NOT_ERROR,
    SH_STACK_NULL_ERROR
} ShStackError;

template <typename stk_T> 
struct shablon_stack_t
{
    stk_T* sh_stack_massive;
    size_t capacity_of_sh_stack;
    size_t size_of_sh_stack;
};

template <typename stk_T> 
shablon_stack_t<stk_T>* sh_stack_init(size_t capacity)
{
    shablon_stack_t<stk_T>* sh_stack = (shablon_stack_t<stk_T>*)calloc(1, sizeof(shablon_stack_t<stk_T>));
    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        return NULL;
    }

    sh_stack->capacity_of_sh_stack = capacity;
    sh_stack->size_of_sh_stack = 0;

    sh_stack->sh_stack_massive = (stk_T*)calloc(capacity, sizeof(stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE ERROR\n");
        free(sh_stack);
        return NULL;
    }

    return sh_stack;
}

template <typename stk_T> 
ShStackError sh_stack_free(shablon_stack_t<stk_T>* sh_stack)
{
    free(sh_stack->sh_stack_massive);
    sh_stack->capacity_of_sh_stack = 0;
    sh_stack->size_of_sh_stack = 0;
    free(sh_stack);
    return NOT_ERROR;
}

template <typename stk_T> 
ShStackError sh_stack_push(stk_T value, shablon_stack_t<stk_T>* sh_stack)
{
    if(sh_stack->size_of_sh_stack + 1 >= sh_stack->capacity_of_sh_stack)
    {
        sh_stack_realloc(sh_stack, sh_stack->capacity_of_sh_stack * 2);
        if(sh_stack == NULL)
        {
            perror("SH_STACK == NULL\n");
            return SH_STACK_NULL_ERROR;
        }
    }

    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack] = value;
    sh_stack->size_of_sh_stack += 1;
    return NOT_ERROR;
}

template <typename stk_T>
stk_T sh_stack_pop(shablon_stack_t<stk_T>* sh_stack)
{
    if(sh_stack->size_of_sh_stack == 0)
    {
        perror("SIZE OF STACK == 0, POP ELEMENT IS NULL\n");
        return NULL;
    }
    stk_T element =  sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack - 1];
    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack - 1] = 0;
    sh_stack->size_of_sh_stack -= 1;
    return element;
}

template <typename stk_T>
shablon_stack_t<stk_T>* sh_stack_realloc(shablon_stack_t<stk_T>* sh_stack, size_t new_capacity)
{
    sh_stack->sh_stack_massive = (stk_T*)realloc(sh_stack->sh_stack_massive ,new_capacity * sizeof(stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        return NULL;
    }
    sh_stack->capacity_of_sh_stack = new_capacity;
    return sh_stack;
}