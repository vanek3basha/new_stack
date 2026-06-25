#include "stack.h"


/*********************************************************************************/

stack_t* stack_init(size_t capacity, StackType type)
{
    stack_t* stack = (stack_t*)calloc(1, sizeof(stack_t));
    if(stack == NULL)
    {
        perror("ERROR IN INIT NEW STACK");
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
            perror("ERROR IN INIT INT MASSIVE");
            return NULL;
        }
        break;
    case STACK_TYPE_DOUBLE:
        stack->stack_massive.double_stack = (double*)calloc(capacity + 1, sizeof(double));
        if(stack->stack_massive.double_stack == NULL)
        {
            perror("ERROR IN INIT DOUBLE MASSIVE");
            return NULL;
        }
        break;
    default:
        perror("THIS STACK TYPE DON'T INIT");
        break;
    }

    return stack;
}

/*********************************************************************************/

size_t int_stack_push(stack_t* stack, int value)
{
    if(stack && stack->size_of_stack + 1 < stack->capacity_of_stack)
    {
        stack->stack_massive.int_stack[stack->size_of_stack] = value;
        stack->size_of_stack += 1;
        return NOT_ERROR;
    }
    else
    {
        perror("STACK == NULL OR size limit");
        return STACK_NULL_ERROR;
    }

}

size_t double_stack_push(stack_t* stack, double value)
{
    if(stack && stack->size_of_stack + 1 < stack->capacity_of_stack)
    {
        stack->stack_massive.double_stack[stack->size_of_stack] = value;
        stack->size_of_stack += 1;
        return NOT_ERROR;
    }
    else
    {
        perror("STACK == NULL OR size limit");
        return STACK_NULL_ERROR;
    }

}


#define stack_push(STACK, VAL)                                                   \
{                                                                                \
    if((STACK)->type == STACK_TYPE_INT)                                          \
    {                                                                            \
        int_stack_push(STACK, (int)(VAL));                                              \
    }                                                                            \
    else if((STACK)->type == STACK_TYPE_DOUBLE)                                  \
    {                                                                            \
        double_stack_push(STACK, (double)(VAL));                                          \
    }                                                                            \
    else                                                                         \
    {                                                                            \
        perror("THIS STACK TYPE DON'T INIT\n");                                  \
        return STACK_TYPE_ERROR;                                                 \
    }                                                                            \
}

/*********************************************************************************/

int int_stack_pop(stack_t* stack)
{
    if(stack->size_of_stack == 0)
    {
        perror("SIZE == 0, POP NOT DEFINED");
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
        perror("SIZE == 0, POP NOT DEFINED");
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

stack_t* stack_realloc(stack_t* stack, size_t new_capacity)
{
    stack_t* new_stack = (stack_t*)calloc(1, sizeof(stack_t));
    if(new_stack == NULL)
    {
        perror("STACK REALLOC ERROR - NEW_STACK IS NULL");
        return NULL;
    }
    
    new_stack->size_of_stack = stack->size_of_stack;
    new_stack->capacity_of_stack = new_capacity;
    new_stack->type = stack->type;

    return NULL;
}

/*********************************************************************************/

int main() {
    stack_t *stack_test = stack_init(5, STACK_TYPE_DOUBLE);
    if (stack_test == NULL) return 1;

    stack_push(stack_test, 20);      
    stack_push(stack_test, (15.5 + 5)); 

    double val_1;
    double val_2;

    stack_pop(stack_test, val_1);
    stack_pop(stack_test, val_2);

    printf("Извлечен верхний элемент: %f\n", val_1);

    printf("Извлечен следующий элемент: %f\n", val_2);

    free(stack_test->stack_massive.double_stack);
    free(stack_test);
    return 0;
}
