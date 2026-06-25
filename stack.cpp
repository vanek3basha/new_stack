#include "stack.h"


/*********************************************************************************/

stack_t* stack_init(size_t capacity, StackType type)
{
    stack_t* stack = (stack_t*)calloc(1, sizeof(stack_t));
    if(stack == NULL)
    {
        perror("ERROR IN INIT NEW STACK\n");
        return NULL;
    }

    stack->size_of_stack = 0;
    stack->capacity_of_stack = capacity;
    stack->type = type;

    switch (type)
    {
    case STACK_TYPE_INT:
        stack->stack_massive.int_stack = (int*)calloc(capacity + 1, sizeof(int));
        if(stack->stack_massive.int_stack == NULL)
        {
            perror("ERROR IN INIT INT MASSIVE\n");
            free(stack);
            return NULL;
        }
        break;
    case STACK_TYPE_DOUBLE:
        stack->stack_massive.double_stack = (double*)calloc(capacity + 1, sizeof(double));
        if(stack->stack_massive.double_stack == NULL)
        {
            perror("ERROR IN INIT DOUBLE MASSIVE\n");
            free(stack);
            return NULL;
        }
        break;
    default:
        perror("THIS STACK TYPE DON'T INIT\n");
        free(stack);
        return NULL;
        break;
    }

    return stack;
}

/*********************************************************************************/

StackError int_stack_push(stack_t* stack, int value)
{
    if(stack && stack->size_of_stack + 1 >= stack->capacity_of_stack)
    {
        stack_realloc(stack, stack->capacity_of_stack * 2);
        if(stack == NULL)
        {
            perror("STACK == NULL\n");
            return STACK_NULL_ERROR;
        }
    }

    else if (stack == NULL)
    {
        perror("STACK == NULL\n");
        return STACK_NULL_ERROR;
    }

    stack->stack_massive.int_stack[stack->size_of_stack] = value;
    stack->size_of_stack += 1;
    return NOT_ERROR;
}

StackError double_stack_push(stack_t* stack, double value)
{
    if(stack && stack->size_of_stack + 1 >= stack->capacity_of_stack)
    {
        stack_realloc(stack, stack->capacity_of_stack * 2);
        if(stack == NULL)
        {
            perror("STACK == NULL\n");
            return STACK_NULL_ERROR;
        }
    }

    else if (stack == NULL)
    {
        perror("STACK == NULL\n");
        return STACK_NULL_ERROR;
    }
    stack->stack_massive.double_stack[stack->size_of_stack] = value;
    stack->size_of_stack += 1;
    return NOT_ERROR;

}

template <typename T> StackError stack_push(stack_t* stack, T value) 
{
    if (stack == NULL) {
        return STACK_NULL_ERROR;
    }

    if (stack->type == STACK_TYPE_INT) {
        return int_stack_push(stack, static_cast<int>(value));
    } 
    else if (stack->type == STACK_TYPE_DOUBLE) {
        return double_stack_push(stack, static_cast<double>(value));
    } 
    
    perror("THIS STACK TYPE DON'T INIT\n");
    return STACK_TYPE_ERROR;
}


/*********************************************************************************/

int int_stack_pop(stack_t* stack)
{
    if(stack->size_of_stack == 0)
    {
        perror("SIZE == 0, POP NOT DEFINED\n");
        return POP_FROM_SIZE_ZERO_STACK_ERROR;
    }
    stack->size_of_stack = stack->size_of_stack - 1;
    int element = (int)stack->stack_massive.int_stack[stack->size_of_stack];
    return element;
} 

double double_stack_pop(stack_t* stack)
{
    if(stack->size_of_stack == 0)
    {
        perror("SIZE == 0, POP NOT DEFINED\n");
        return POP_FROM_SIZE_ZERO_STACK_ERROR;
    }
    stack->size_of_stack = stack->size_of_stack - 1;
    double element = (double)stack->stack_massive.double_stack[stack->size_of_stack];
    return element;
}

#define stack_pop(STACK, RESULT_VAR)                                                    \
{                                                                                       \
    if ((STACK)->type == STACK_TYPE_INT) {                                              \
        (RESULT_VAR) = int_stack_pop(STACK);                                            \
    }                                                                                   \
    else if ((STACK)->type == STACK_TYPE_DOUBLE) {                                      \
        (RESULT_VAR) = double_stack_pop(STACK);                                         \
    }                                                                                   \
}

/*********************************************************************************/

StackError stack_realloc(stack_t* stack, size_t new_capacity)
{
    if (stack == NULL)
    {
        return STACK_NULL_ERROR;
    }

    void* new_massive = NULL;

    switch (stack->type)
    {
    case STACK_TYPE_INT:
        // Используем realloc, он автоматически копирует старые данные
        new_massive = realloc(stack->stack_massive.int_stack, (new_capacity + 1) * sizeof(int));
        if (new_massive == NULL) {
            perror("ERROR IN REALLOC INT MASSIVE\n");
            return REALLOC_STACK_ERROR;
        }
        stack->stack_massive.int_stack = (int*)new_massive;
        break;

    case STACK_TYPE_DOUBLE:
        new_massive = realloc(stack->stack_massive.double_stack, (new_capacity + 1) * sizeof(double));
        if (new_massive == NULL) {
            perror("ERROR IN REALLOC DOUBLE MASSIVE\n");
            return  REALLOC_STACK_ERROR;
        }
        stack->stack_massive.double_stack = (double*)new_massive;
        break;

    default:
        perror("THIS STACK TYPE DON'T INIT\n");
        return STACK_TYPE_ERROR;
    }

    stack->capacity_of_stack = new_capacity;
    return NOT_ERROR;
}

/*********************************************************************************/

StackError stack_free(stack_t* stack)
{
    StackError Flag = NOT_ERROR;
    switch (stack->type)
    {
    case STACK_TYPE_INT:
        free(stack->stack_massive.int_stack);
        break;
    case STACK_TYPE_DOUBLE:
        free(stack->stack_massive.double_stack);
        break;
    default:
        perror("UNKNOWN STACK TYPE IN FREE\n");
        break;
        Flag = STACK_TYPE_ERROR;
    }
    stack->size_of_stack = 0;
    stack->capacity_of_stack = 0;

    free(stack);
    return Flag;
}

/*********************************************************************************/
int main() {
    stack_t *stack_test = stack_init(1, STACK_TYPE_DOUBLE);
    if (stack_test == NULL) return 1;

    stack_push(stack_test, 20);  
    printf("size - %zu  capacity - %zu\n", stack_test->size_of_stack, stack_test->capacity_of_stack);
    stack_push(stack_test, 10);      
    printf("size - %zu  capacity - %zu\n", stack_test->size_of_stack, stack_test->capacity_of_stack);
    stack_push(stack_test, 15);      
    printf("size - %zu  capacity - %zu\n", stack_test->size_of_stack, stack_test->capacity_of_stack);
    stack_push(stack_test, 15.5); 
    printf("size - %zu  capacity - %zu\n", stack_test->size_of_stack, stack_test->capacity_of_stack);

    double val_1 = 0;
    double val_2 = 0;

    stack_pop(stack_test, val_1);
    stack_pop(stack_test, val_1);

    stack_pop(stack_test, val_2);

    printf("Извлечен верхний элемент: %f\n", val_1);

    printf("Извлечен следующий элемент: %f\n", val_2);

    stack_free(stack_test);
    return 0;
}
