#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
typedef enum
{
    NOT_ERROR,
    SH_STACK_NULL_ERROR,
    SIZE_OF_ELEMENTS_ERROR
} ShStackError;

template <typename stk_T> 
struct shablon_stack_t
{
    stk_T* sh_stack_massive;
    size_t capacity_of_sh_stack;
    size_t size_of_sh_stack;
};

template <typename stk_T>
ShStackError left_canareyka_create(stk_T* left_element, size_t size_of_canareyka);

template <typename stk_T>
ShStackError right_canareyka_create(stk_T* right_element, size_t size_of_canareyka);



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

    sh_stack->sh_stack_massive = (stk_T*)calloc(capacity + 3, sizeof(stk_T));  //если написать 0 то прога не сломается, 
                                                                                //хватит места для 2ух канареек и \0
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE ERROR\n");
        free(sh_stack);
        return NULL;
    }
    left_canareyka_create(sh_stack->sh_stack_massive, sizeof(stk_T));
    right_canareyka_create(sh_stack->sh_stack_massive + capacity + 1, sizeof(stk_T)); 
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

    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack + 1] = value;
    sh_stack->size_of_sh_stack += 1;
    return NOT_ERROR;
}

template <typename stk_T>
stk_T sh_stack_pop(shablon_stack_t<stk_T>* sh_stack)
{
    if(sh_stack->size_of_sh_stack == 0)
    {
        perror("SIZE OF STACK == 0, POP ELEMENT IS NULL\n");
        return stk_T();
    }
    stk_T element =  sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack];
    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack] = stk_T();
    sh_stack->size_of_sh_stack -= 1;
    return element;
}

template <typename stk_T>
shablon_stack_t<stk_T>* sh_stack_realloc(shablon_stack_t<stk_T>* sh_stack, size_t new_capacity)
{
    sh_stack->sh_stack_massive = (stk_T*)realloc(sh_stack->sh_stack_massive ,(new_capacity + 3) * sizeof(stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        return NULL;
    }
    sh_stack->sh_stack_massive[sh_stack->capacity_of_sh_stack + 1] = 0;
    sh_stack->capacity_of_sh_stack = new_capacity;
    right_canareyka_create(sh_stack->sh_stack_massive + new_capacity + 1, sizeof(stk_T)); 
    printf("here- realloc \n");
    return sh_stack;
}



/**********************************************************************************************/

template <typename stk_T>
ShStackError left_canareyka_create(stk_T* left_element, size_t size_of_canareyka)
{
    if(size_of_canareyka > 8)
    {
        perror("WARNING SIZE OF YOUR TYPE BIGGER THEN 8 BYTES\n");
        return SIZE_OF_ELEMENTS_ERROR;
    }
    uint64_t left_canareyka = 0b0101110010101111010111011011001101011100101011110101110110110011;
    // printf("canar -> %lu\nsize_of_int -> %lu\n", left_canareyka, sizeof(int));
    uint64_t* ptr_of_left_canareyka = (uint64_t*)&left_canareyka;
    memcpy(left_element, ptr_of_left_canareyka, size_of_canareyka);
    return NOT_ERROR;
}

template <typename stk_T>
ShStackError right_canareyka_create(stk_T* right_element, size_t size_of_canareyka)
{
    if(size_of_canareyka > 8)
    {
        perror("WARNING SIZE OF YOUR TYPE BIGGER THEN 8 BYTES\n");
        return SIZE_OF_ELEMENTS_ERROR;
    }
    uint64_t right_canareyka = 0b0101110010111110010011011011001101011100101010110101110110110011;
    // printf("canar -> %lu\nsize_of_int -> %lu\n", right_canareyka, sizeof(int));
    uint64_t* ptr_of_right_canareyka = (uint64_t*)&right_canareyka;
    memcpy(right_element, ptr_of_right_canareyka, size_of_canareyka);
    return NOT_ERROR;
}