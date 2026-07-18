template <typename elem_stk_T>
sh_stack_error_t sh_stack_check(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    sh_stack_error_t massive_of_errors[20] = {};
    size_t count_of_errors = 0;

    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        massive_of_errors[count_of_errors] = SH_STACK_NULL_ERROR;
        count_of_errors += 1;
        SH_STACK_DUMP(massive_of_errors, sh_stack, count_of_errors);
        sh_stack->calls_level -= 1;
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

    uint64_t temp_hash = massive_hash_counting(sh_stack);
    uint64_t temp_struct_hash = struct_hash_counting(sh_stack);
    if(temp_hash != sh_stack->sh_stack_hash || temp_struct_hash != sh_stack->sh_struct_hash)
    {
        perror("HASH HAS BEEN CHANGE\n");
        massive_of_errors[count_of_errors] = HASH_CHANGE_ERROR;
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
        sh_stack->calls_level -= 1;
        return NOT_ERROR;
    }
    else
    {
        SH_STACK_DUMP(massive_of_errors ,sh_stack, count_of_errors);
        sh_stack->calls_level -= 1;
        return massive_of_errors[count_of_errors - 1];
    }
}

template <typename elem_stk_T>
sh_stack_error_t check_left_canareyka(shablon_stack_t<elem_stk_T>* sh_stack)
{
    uint64_t left_canareyka = LEFT_CANAREYKA;
    uint64_t* ptr_of_left_canareyka = (uint64_t*)&left_canareyka;
    if(memcmp(sh_stack->sh_stack_massive, ptr_of_left_canareyka, sizeof(elem_stk_T)) == 0)
    {
        return NOT_ERROR;
    }
    else
    {
        return LEFT_CANAR_ERROR;
    }
}

template <typename elem_stk_T>
sh_stack_error_t check_right_canareyka(shablon_stack_t<elem_stk_T>* sh_stack)
{
    uint64_t right_canareyka = RIGHT_CANAREYKA;
    uint64_t* ptr_of_right_canareyka = (uint64_t*)&right_canareyka;
    if(memcmp(sh_stack->sh_stack_massive + sh_stack->capacity_of_sh_stack + 1, ptr_of_right_canareyka, sizeof(elem_stk_T)) == 0)
    {
        return NOT_ERROR;
    }
    else
    {
        return RIGHT_CANAR_ERROR;
    }
}

template <typename elem_stk_T>
sh_stack_error_t check_poison(shablon_stack_t<elem_stk_T>* sh_stack)
{
    uint64_t poison = POISON;
    uint64_t* ptr_of_poison = (uint64_t*)&poison;
    for(size_t i = sh_stack->size_of_sh_stack; i < sh_stack->capacity_of_sh_stack; i++)
    {
        if(memcmp(sh_stack->sh_stack_massive + i + 1, ptr_of_poison, sizeof(elem_stk_T)) != 0)
        {
            return POISON_ERROR;
        }
    }
    return NOT_ERROR;
}