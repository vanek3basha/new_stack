#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <typeinfo>
#include <cxxabi.h>

template <typename stk_T> 
struct shablon_stack_t
{
    size_t left_struct_canar;
    stk_T* sh_stack_massive;
    size_t capacity_of_sh_stack;
    size_t size_of_sh_stack;
    size_t right_struct_canar;
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


template <typename stk_T> 
shablon_stack_t<stk_T>* sh_stack_init(size_t capacity);

template <typename stk_T> 
ShStackError sh_stack_free(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T> 
ShStackError sh_stack_push(stk_T value, shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
stk_T sh_stack_pop(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
shablon_stack_t<stk_T>* sh_stack_realloc(shablon_stack_t<stk_T>* sh_stack, size_t new_capacity);

template <typename stk_T>
ShStackError left_canareyka_create(stk_T* left_element, size_t size_of_canareyka);

template <typename stk_T>
ShStackError right_canareyka_create(stk_T* right_element, size_t size_of_canareyka);

template <typename stk_T>
ShStackError poison_create(shablon_stack_t<stk_T>* sh_stack, size_t size_of_poison);

template <typename stk_T>
ShStackError sh_stack_check(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
ShStackError check_left_canareyka(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
ShStackError check_right_canareyka(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
ShStackError check_poison(shablon_stack_t<stk_T>* sh_stack);

template <typename stk_T>
ShStackError sh_stack_dump(ShStackError* massive_of_error, shablon_stack_t<stk_T>* sh_stack, size_t count_of_errors);



template <typename stk_T> 
shablon_stack_t<stk_T>* sh_stack_init(size_t capacity)
{
    if(capacity > 1000)
    {
        perror("INPUT CAPACITY < 0 OR > 1000\n");
        return NULL;
    }

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
    poison_create(sh_stack, sizeof(stk_T));
    
    sh_stack->left_struct_canar = LEFT_STRUCT_CANAR;
    sh_stack->right_struct_canar = RIGHT_STRUCT_CANAR;

    if(sh_stack_check(sh_stack) == NOT_ERROR)
    {
        return sh_stack;
    } 
    else
    {
        return NULL;
    }
}

template <typename stk_T> 
ShStackError sh_stack_free(shablon_stack_t<stk_T>* sh_stack)
{
    ShStackError flag = sh_stack_check(sh_stack);
    if(sh_stack != NULL)
    {
    free(sh_stack->sh_stack_massive);
    sh_stack->capacity_of_sh_stack = 0;
    sh_stack->size_of_sh_stack = 0;
    sh_stack->left_struct_canar = 0;
    sh_stack->right_struct_canar = 0;
    }
    free(sh_stack);
    return flag;
}

template <typename stk_T> 
ShStackError sh_stack_push(stk_T value, shablon_stack_t<stk_T>* sh_stack)
{
    ShStackError flag = sh_stack_check(sh_stack);
    if(flag != NOT_ERROR)
    {
        return flag;
    }

    if(sh_stack->size_of_sh_stack + 1 >= sh_stack->capacity_of_sh_stack)
    {
        sh_stack_realloc(sh_stack, sh_stack->capacity_of_sh_stack * 2 + 1);
        if(sh_stack == NULL)
        {
            perror("SH_STACK == NULL\n");
            return SH_STACK_NULL_ERROR;
        }
    }

    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack + 1] = value;
    sh_stack->size_of_sh_stack += 1;

    flag = sh_stack_check(sh_stack);

    if(flag != NOT_ERROR)
    {
        return flag;
    }
    else
    {
        return NOT_ERROR;
    }
}

template <typename stk_T>
stk_T sh_stack_pop(shablon_stack_t<stk_T>* sh_stack)
{
    ShStackError flag = sh_stack_check(sh_stack);
    if(flag != NOT_ERROR)
    {
        return stk_T();
    }

    if(sh_stack->size_of_sh_stack == 0)
    {
        perror("SIZE OF STACK == 0, POP ELEMENT IS NULL\n");
        return stk_T();
    }

    stk_T element =  sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack];
    sh_stack->size_of_sh_stack -= 1;
    poison_create(sh_stack, sizeof(stk_T));
    flag = sh_stack_check(sh_stack);

    if(flag != NOT_ERROR)
    {
        return stk_T();
    }
    else
    {
        return element;
    }

}

template <typename stk_T>
shablon_stack_t<stk_T>* sh_stack_realloc(shablon_stack_t<stk_T>* sh_stack, size_t new_capacity)
{
    ShStackError flag = sh_stack_check(sh_stack);
    if(flag != NOT_ERROR)
    {
        return NULL;
    }

    sh_stack->sh_stack_massive = (stk_T*)realloc(sh_stack->sh_stack_massive ,(new_capacity + 3) * sizeof(stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        return NULL;
    }
    sh_stack->sh_stack_massive[sh_stack->capacity_of_sh_stack + 1] = 0;
    sh_stack->capacity_of_sh_stack = new_capacity;
    right_canareyka_create(sh_stack->sh_stack_massive + new_capacity + 1, sizeof(stk_T)); 
    poison_create(sh_stack, sizeof(stk_T));

    flag = sh_stack_check(sh_stack);
    if(flag != NOT_ERROR)
    {
        return NULL;
    }
    else
    {
        return sh_stack;
    }
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
    uint64_t left_canareyka = LEFT_CANAREYKA;
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
    uint64_t right_canareyka = RIGHT_CANAREYKA;
    uint64_t* ptr_of_right_canareyka = (uint64_t*)&right_canareyka;
    memcpy(right_element, ptr_of_right_canareyka, size_of_canareyka);
    return NOT_ERROR;
}

template <typename stk_T>
ShStackError poison_create(shablon_stack_t<stk_T>* sh_stack, size_t size_of_poison)
{   
    if(size_of_poison > 8)
    {
        perror("WARNING SIZE OF YOUR TYPE BIGGER THEN 8 BYTES\n");
        return SIZE_OF_ELEMENTS_ERROR;
    }

    uint64_t poison = POISON;
    uint64_t* ptr_of_poison = (uint64_t*)&poison;

    for(size_t i = sh_stack->size_of_sh_stack; i < sh_stack->capacity_of_sh_stack; i++)
    {
        printf("here -> poison\n");
        memcpy(sh_stack->sh_stack_massive + i + 1, ptr_of_poison, size_of_poison);
    }

    return NOT_ERROR;
}

/**********************************************************************************************/

template <typename stk_T>
ShStackError sh_stack_check(shablon_stack_t<stk_T>* sh_stack)
{
    ShStackError massive_of_errors[20] = {};
    size_t count_of_errors = 0;

    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        massive_of_errors[count_of_errors] = SH_STACK_NULL_ERROR;
        count_of_errors += 1;
        sh_stack_dump<stk_T>(massive_of_errors, sh_stack, count_of_errors);
        return SH_STACK_NULL_ERROR;
    }

    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        massive_of_errors[count_of_errors] = SH_STACK_MASSIVE_NULL_ERROR;
        count_of_errors += 1; 
    }

    if(sh_stack->size_of_sh_stack < 0)
    {
        perror("SIZE OF SH_STACK < 0\n");
        massive_of_errors[count_of_errors] = SH_STACK_SIZE_LESS_ZERO_ERROR;
        count_of_errors += 1;
    }

    if(sh_stack->size_of_sh_stack > sh_stack->capacity_of_sh_stack)
    {
        perror("SIZE OF SH_STACK > CAPACITY\n");
        massive_of_errors[count_of_errors] = SH_STACK_SIZE_LARGER_CAPACITY_ERROR;
        count_of_errors += 1;
    }

    if(check_left_canareyka(sh_stack))
    {
        perror("LEFT CANAREYKA HAS BEEN CHANGE\n");
        massive_of_errors[count_of_errors] = LEFT_CANAR_ERROR;
        count_of_errors += 1;
    }

    if(check_right_canareyka(sh_stack))
    {
        perror("RIGHT CANAREYKA HAS BEEN CHANGE\n");
        massive_of_errors[count_of_errors] = RIGHT_CANAR_ERROR;
        count_of_errors += 1;
    }

    if(check_poison(sh_stack))
    {
        perror("ONE OF NOT USED ELEMENT HAS BEEN CHANGE\n");
        massive_of_errors[count_of_errors] = POISON_ERROR;
        count_of_errors += 1;
    }

    if(sh_stack->left_struct_canar != LEFT_STRUCT_CANAR)
    {
        perror("LEFT STRUCT CANAREYKA HAS BEEN CHANGE");
        massive_of_errors[count_of_errors] = LEFT_STRUCT_CANAR_ERROR;
        count_of_errors += 1;
    }

    if(sh_stack->right_struct_canar != RIGHT_STRUCT_CANAR)
    {
        perror("RIGHT STRUCT CANAREYKA HAS BEEN CHANGE");
        massive_of_errors[count_of_errors] = RIGHT_STRUCT_CANAR_ERROR;
        count_of_errors += 1;
    }

    if(count_of_errors == 0)
    {
        return NOT_ERROR;
    }
    else
    {
        sh_stack_dump<stk_T>(massive_of_errors ,sh_stack, count_of_errors);
        return massive_of_errors[count_of_errors - 1];
    }
}

template <typename stk_T>
ShStackError check_left_canareyka(shablon_stack_t<stk_T>* sh_stack)
{
    uint64_t left_canareyka = LEFT_CANAREYKA;
    uint64_t* ptr_of_left_canareyka = (uint64_t*)&left_canareyka;
    if(memcmp(sh_stack->sh_stack_massive, ptr_of_left_canareyka, sizeof(stk_T)) == 0)
    {
        return NOT_ERROR;
    }
    else
    {
        return LEFT_CANAR_ERROR;
    }
}

template <typename stk_T>
ShStackError check_right_canareyka(shablon_stack_t<stk_T>* sh_stack)
{
    uint64_t right_canareyka = RIGHT_CANAREYKA;
    uint64_t* ptr_of_right_canareyka = (uint64_t*)&right_canareyka;
    if(memcmp(sh_stack->sh_stack_massive + sh_stack->capacity_of_sh_stack + 1, ptr_of_right_canareyka, sizeof(stk_T)) == 0)
    {
        return NOT_ERROR;
    }
    else
    {
        return RIGHT_CANAR_ERROR;
    }
}

template <typename stk_T>
ShStackError check_poison(shablon_stack_t<stk_T>* sh_stack)
{
    uint64_t poison = POISON;
    uint64_t* ptr_of_poison = (uint64_t*)&poison;
    for(size_t i = sh_stack->size_of_sh_stack; i < sh_stack->capacity_of_sh_stack; i++)
    {
        if(memcmp(sh_stack->sh_stack_massive + i + 1, ptr_of_poison, sizeof(stk_T)) != 0)
        {
            return POISON_ERROR;
        }
    }
    return NOT_ERROR;
}


template <typename stk_T>
ShStackError sh_stack_dump(ShStackError* massive_of_error, shablon_stack_t<stk_T>* sh_stack, size_t count_of_errors)
{
    FILE* dump_file = fopen("sh_stack_dumpfile.txt", "a+");
    if(dump_file == NULL)
    {
        perror("DUMP_FILE OPEN ERROR\n");
        return DUMP_FILE_OPEN_ERROR;
    }
    ShStackError flag = NOT_ERROR;

    char* type_of_stack = abi::__cxa_demangle(typeid(stk_T).name(), NULL, NULL, NULL);
    fprintf(dump_file, "---------------------------STACK DUMP---------------------------\n");
    
    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "                       TYPE OF STACK: %s\n", type_of_stack);

    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "              ADDRESS OF SH_STACK STRUCT: %p\n", sh_stack);
    if(sh_stack == NULL)
    {
        fprintf(dump_file, "----------------------------------------------------------------\n");
        fprintf(dump_file, "            SH_STACK IS NULL - FURTHER DUMP ISN'T POSSIBLE\n");
        flag = SH_STACK_NULL_ERROR;        
    }
    
    if(flag == NOT_ERROR)
    {
        fprintf(dump_file, "           ADDRESS OF SH_STACK_MASSIVE STRUCT: %p\n", sh_stack->sh_stack_massive);
        fprintf(dump_file, "\n----------------------------------------------------------------\n");
        fprintf(dump_file, "                        SIZE OF STACK: %lu\n", sh_stack->size_of_sh_stack);
        fprintf(dump_file, "                      CAPACITY OF STACK: %lu\n", sh_stack->capacity_of_sh_stack);
        
        if(sh_stack->sh_stack_massive == NULL)
        {
            fprintf(dump_file, "SH_STACK IS NULL - FURTHER DUMP ISN'T POSSIBLE\n");
            flag = SH_STACK_MASSIVE_NULL_ERROR;
        }
    }

    if(flag == NOT_ERROR)
    {
        fprintf(dump_file, "\n------------------------ELEMENTS OF STACK-----------------------\n");

        for(size_t i = 0; i < sh_stack->capacity_of_sh_stack + 2; i++)
        {
            uint8_t* byte_ptr = reinterpret_cast<uint8_t*>(&sh_stack->sh_stack_massive[i]);
            fprintf(dump_file, "%lu ELEMENT: ", (i + 1));
            for (size_t j = 0; j < sizeof(stk_T); j++) 
            {
            fprintf(dump_file, "%02X ", byte_ptr[j]);
            }
            fprintf(dump_file, "\n");
        }
    }

    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "                        COUNT OF ERRORS: %lu\n", count_of_errors);
    
    fprintf(dump_file, "\n--------------------------LIST OF ERROR-------------------------\n");
    if(count_of_errors != 0)
    {
        for(size_t i = 0; i < count_of_errors; i++)
        {
            fprintf(dump_file, "ERROR 1: %s\n", ShStackErrorNames[massive_of_error[i]]);
        }
    }
    else
    {
        fprintf(dump_file, "NOT_ERRORS\n");
    }

    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "-------------------------STACK DUMP END-------------------------\n");
    fclose(dump_file);
    free(type_of_stack);
    return SH_STACK_NULL_ERROR;
}