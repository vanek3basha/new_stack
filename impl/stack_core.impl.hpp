template <typename stk_T> 
shablon_stack_t<stk_T>* sh_stack_init(size_t capacity, int line, const char* file, const char* func)
{
    if(level_in_history < MAX_CALLS_IN_HISTORY)
    {
        call_history[level_in_history] = {line, file, func};
        level_in_history += 1;
    }

    if(capacity > 1000)
    {
        perror("INPUT CAPACITY < 0 OR > 1000\n");
        level_in_history -= 1;
        return NULL;
    }

    shablon_stack_t<stk_T>* sh_stack = (shablon_stack_t<stk_T>*)calloc(1, sizeof(shablon_stack_t<stk_T>));
    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        level_in_history -= 1;
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
        level_in_history -= 1;
        return NULL;
    }
    
    left_canareyka_create(sh_stack->sh_stack_massive, sizeof(stk_T));
    right_canareyka_create(sh_stack->sh_stack_massive + capacity + 1, sizeof(stk_T));
    poison_create(sh_stack, sizeof(stk_T));
    
    sh_stack->left_struct_canar = LEFT_STRUCT_CANAR;
    sh_stack->right_struct_canar = RIGHT_STRUCT_CANAR;

    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    if(SH_STACK_CHECK(sh_stack) == NOT_ERROR)
    {
        level_in_history -= 1;
        return sh_stack;
    } 
    else
    {
        level_in_history -= 1;
        return NULL;
    }
}

template <typename stk_T> 
ShStackError sh_stack_free(shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(level_in_history < MAX_CALLS_IN_HISTORY)
    {
        call_history[level_in_history] = {line, file, func};
        level_in_history += 1;
    }

    ShStackError flag = SH_STACK_CHECK(sh_stack);
    if(sh_stack != NULL)
    {
    free(sh_stack->sh_stack_massive);
    sh_stack->capacity_of_sh_stack = 0;
    sh_stack->size_of_sh_stack = 0;
    sh_stack->left_struct_canar = 0;
    sh_stack->right_struct_canar = 0;
    sh_stack->sh_stack_hash = 0;
    sh_stack->sh_struct_hash = 0;
    }
    free(sh_stack);
    level_in_history -= 1;
    return flag;
}

template <typename stk_T> 
ShStackError sh_stack_push(stk_T value, shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(level_in_history < MAX_CALLS_IN_HISTORY)
    {
        call_history[level_in_history] = {line, file, func};
        level_in_history += 1;
    }

    ShStackError flag = SH_STACK_CHECK(sh_stack);
    if(flag != NOT_ERROR)
    {
        level_in_history -= 1;
        return flag;
    }

    if(sh_stack->size_of_sh_stack + 1 >= sh_stack->capacity_of_sh_stack)
    {
        SH_STACK_REALLOC(sh_stack, sh_stack->capacity_of_sh_stack * 2 + 1);
        if(sh_stack == NULL)
        {
            perror("SH_STACK == NULL\n");
            level_in_history -= 1;
            return SH_STACK_NULL_ERROR;
        }
    }

    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack + 1] = value;
    sh_stack->size_of_sh_stack += 1;
    
    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    flag = SH_STACK_CHECK(sh_stack);

    if(flag != NOT_ERROR)
    {
        level_in_history -= 1;
        return flag;
    }
    else
    {
        level_in_history -=1;
        return NOT_ERROR;
    }
}

template <typename stk_T>
stk_T sh_stack_pop(shablon_stack_t<stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(level_in_history < MAX_CALLS_IN_HISTORY)
    {
        call_history[level_in_history] = {line, file, func};
        level_in_history += 1;
    }

    ShStackError flag = SH_STACK_CHECK(sh_stack);
    if(flag != NOT_ERROR)
    {
        level_in_history -= 1;
        return stk_T();
    }

    if(sh_stack->size_of_sh_stack == 0)
    {
        perror("SIZE OF STACK == 0, POP ELEMENT IS NULL\n");
        level_in_history -= 1;
        return stk_T();
    }
    stk_T element =  sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack];
    sh_stack->size_of_sh_stack -= 1;
    right_canareyka_create(sh_stack->sh_stack_massive + sh_stack->capacity_of_sh_stack + 1, sizeof(stk_T));
    poison_create(sh_stack, sizeof(stk_T));
    
    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    flag = SH_STACK_CHECK(sh_stack);

    if(flag != NOT_ERROR)
    {
        level_in_history -= 1;
        return stk_T();
    }
    else
    {
        level_in_history -=1;
        return element;
    }

}

template <typename stk_T>
shablon_stack_t<stk_T>* sh_stack_realloc(shablon_stack_t<stk_T>* sh_stack, size_t new_capacity, int line, const char* file, const char* func)
{
    if(level_in_history < MAX_CALLS_IN_HISTORY)
    {
        call_history[level_in_history] = {line, file, func};
        level_in_history += 1;
    }

    ShStackError flag = SH_STACK_CHECK(sh_stack);
    if(flag != NOT_ERROR)
    {
        level_in_history -= 1;
        return NULL;
    }

    sh_stack->sh_stack_massive = (stk_T*)realloc(sh_stack->sh_stack_massive ,(new_capacity + 3) * sizeof(stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        level_in_history -= 1;
        return NULL;
    }

    sh_stack->sh_stack_massive[sh_stack->capacity_of_sh_stack + 1] = 0;
    sh_stack->capacity_of_sh_stack = new_capacity;
    right_canareyka_create(sh_stack->sh_stack_massive + new_capacity + 1, sizeof(stk_T)); 
    poison_create(sh_stack, sizeof(stk_T));
    
    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    flag = SH_STACK_CHECK(sh_stack);
    if(flag != NOT_ERROR)
    {
        level_in_history -= 1;
        return NULL;
    }
    else
    {
        level_in_history -= 1;
        return sh_stack;
    }
}
