#ifndef _SH_STACK_FUNC__HPP_
#define _SH_STACK_FUNC__HPP_

template <typename elem_stk_T> 
shablon_stack_t<elem_stk_T>* sh_stack_init(size_t capacity, int line, const char* file, const char* func)
{
    shablon_stack_t<elem_stk_T>* sh_stack = (shablon_stack_t<elem_stk_T>*)calloc(1, sizeof(shablon_stack_t<elem_stk_T>));
    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        return NULL;
    }

    sh_stack->info = (stack_history_calls*)calloc(MAX_CALLS_IN_HISTORY, sizeof(stack_history_calls));
    if(sh_stack->info == NULL)
    {
        perror("SH_STACK->INFO == NULL\n");
        free(sh_stack);
        return NULL;
    }

    sh_stack->calls_level = 0;

    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    if((ssize_t)capacity < 0)         // (ssize_t)capasity < 0
    {
        perror("INPUT CAPACITY < 0\n");
        sh_stack->calls_level -= 1;
        return NULL;
    }
    
    // TODO: define CAP_WITH_CONAR...
    sh_stack->sh_stack_massive = (elem_stk_T*)calloc(CAPACITY_WITH_CANAR, sizeof(elem_stk_T));  //если написать 0 то прога не сломается, 
    //хватит места для 2ух канареек и \0
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE ERROR\n");
        free(sh_stack->info);
        sh_stack->calls_level = 0;
        free(sh_stack);
        return NULL;
    }
    
    sh_stack->capacity_of_sh_stack = capacity;
    sh_stack->size_of_sh_stack = 0;
    
    canareyka_create(sh_stack);
    poison_create(sh_stack);
    
    sh_stack->left_struct_canar = LEFT_STRUCT_CANAR;
    sh_stack->right_struct_canar = RIGHT_STRUCT_CANAR;

    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    if(SH_STACK_CHECK(sh_stack) == NOT_ERROR)
    {
        sh_stack->calls_level -= 1;
        return sh_stack;
    } 
    else
    {
        sh_stack->calls_level -= 1;
        return NULL;
    }
}

template <typename elem_stk_T> 
stack_flag_of_err_t sh_stack_free(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    stack_flag_of_err_t flag = SH_STACK_CHECK(sh_stack);
    if(sh_stack != 0)
    {
    free(sh_stack->sh_stack_massive);
    sh_stack->capacity_of_sh_stack = 0;
    sh_stack->size_of_sh_stack = 0;
    sh_stack->left_struct_canar = 0;
    sh_stack->right_struct_canar = 0;
    sh_stack->sh_stack_hash = 0;
    sh_stack->sh_struct_hash = 0;
    free(sh_stack->info);
    sh_stack->calls_level = 0;
    }
    free(sh_stack);
    return flag;
}

template <typename elem_stk_T> 
stack_flag_of_err_t sh_stack_push(elem_stk_T value, shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    stack_flag_of_err_t flag = SH_STACK_CHECK(sh_stack);
    if(flag != 0)
    {
        sh_stack->calls_level -= 1;
        return flag;
    }

    if(sh_stack->size_of_sh_stack + 1 >= sh_stack->capacity_of_sh_stack)
    {
        SH_STACK_REALLOC(sh_stack, sh_stack->capacity_of_sh_stack * 2 + 1);
        //ну я пытался какое то логичное название для "* 2 + 1" придумать, но это просто 
        // рандом функция для реаллокации
        if(sh_stack == NULL)
        {
            perror("SH_STACK == NULL\n");
            sh_stack->calls_level -= 1;
            return SH_STACK_NULL_ERROR;
        }
    }

    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack + 1] = value;
    sh_stack->size_of_sh_stack += 1;
    
    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    flag = SH_STACK_CHECK(sh_stack);
    
    sh_stack->calls_level -= 1;
    return flag;
}

template <typename elem_stk_T>
elem_stk_T sh_stack_pop(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    stack_flag_of_err_t flag = SH_STACK_CHECK(sh_stack);
    if(flag != 0)
    {
        sh_stack->calls_level -= 1;
        return elem_stk_T();
    }

    if(sh_stack->size_of_sh_stack == 0)
    {
        perror("SIZE OF STACK == 0, POP ELEMENT IS NULL\n");
        sh_stack->calls_level -= 1;
        return elem_stk_T();
    }

    elem_stk_T element =  sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack];
    sh_stack->size_of_sh_stack -= 1;
    canareyka_create(sh_stack);
    poison_create(sh_stack);
    
    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    flag = SH_STACK_CHECK(sh_stack);

    if(flag != NOT_ERROR)
    {
        sh_stack->calls_level -= 1;
        return elem_stk_T();
    }
    else
    {
        sh_stack->calls_level -= 1;
        return element;
    }

}

template <typename elem_stk_T>
shablon_stack_t<elem_stk_T>* sh_stack_realloc(shablon_stack_t<elem_stk_T>* sh_stack, size_t new_capacity, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    stack_flag_of_err_t flag = SH_STACK_CHECK(sh_stack);
    if(flag != 0)
    {
        sh_stack->calls_level -= 1;
        return NULL;
    }

    sh_stack->sh_stack_massive = (elem_stk_T*)realloc(sh_stack->sh_stack_massive ,(NEW_CAPACITY_WITH_CANAR) * sizeof(elem_stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        sh_stack->calls_level -= 1;
        return NULL;
    }

    // sh_stack->sh_stack_massive[sh_stack->capacity_of_sh_stack + 1] = elem_stk_T();
    sh_stack->capacity_of_sh_stack = new_capacity;
    canareyka_create(sh_stack); 
    poison_create(sh_stack);
    
    sh_stack->sh_stack_hash = massive_hash_counting(sh_stack);
    sh_stack->sh_struct_hash = struct_hash_counting(sh_stack);

    flag = SH_STACK_CHECK(sh_stack);
    if(flag != 0)
    {
        sh_stack->calls_level -= 1;
        return NULL;
    }
    else
    {
        sh_stack->calls_level -= 1;
        return sh_stack;
    }
}

#endif