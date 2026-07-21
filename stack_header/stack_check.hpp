#ifndef _SH_STACK_CHECK__HPP_
#define _SH_STACK_CHECK__HPP_

template <typename elem_stk_T>
stack_flag_of_err_t sh_stack_check(shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    stack_flag_of_err_t byte_flag = 0;

    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        byte_flag += 1 << SH_STACK_NULL_ERROR;
        SH_STACK_DUMP(byte_flag, sh_stack);
        sh_stack->calls_level -= 1;
        return SH_STACK_NULL_ERROR;
    }

    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE == NULL\n");
        byte_flag += 1 << SH_STACK_MASSIVE_NULL_ERROR;
    }

    if(sh_stack->size_of_sh_stack < 0)
    {
        perror("SIZE OF SH_STACK < 0\n");
        byte_flag += 1 << SH_STACK_SIZE_LESS_ZERO_ERROR;
    }

    if(sh_stack->size_of_sh_stack > sh_stack->capacity_of_sh_stack)
    {
        perror("SIZE OF SH_STACK > CAPACITY\n");
        byte_flag += 1 << SH_STACK_SIZE_LARGER_CAPACITY_ERROR;
    }

    sh_stack_error_t flag = check_canareyka(sh_stack);
    if(flag != 0)
    {
        perror("CANAREYKA HAS BEEN CHANGE\n");
        byte_flag += 1 << flag;
    }

    if(check_poison(sh_stack))
    {
        perror("ONE OF NOT USED ELEMENT HAS BEEN CHANGE\n");
        byte_flag = 1 << POISON_ERROR;
    }

    hash_t temp_hash = massive_hash_counting(sh_stack);
    hash_t temp_struct_hash = struct_hash_counting(sh_stack);
    if(temp_hash != sh_stack->sh_stack_hash || temp_struct_hash != sh_stack->sh_struct_hash)
    {
        perror("HASH HAS BEEN CHANGE\n");
        byte_flag = 1 << HASH_CHANGE_ERROR;
    }

    if(sh_stack->left_struct_canar != LEFT_STRUCT_CANAR)
    {
        perror("LEFT STRUCT CANAREYKA HAS BEEN CHANGE");
        byte_flag = 1 << LEFT_STRUCT_CANAR_ERROR;
    }

    if(sh_stack->right_struct_canar != RIGHT_STRUCT_CANAR)
    {
        perror("RIGHT STRUCT CANAREYKA HAS BEEN CHANGE");
        byte_flag = 1 << RIGHT_STRUCT_CANAR_ERROR;
    }

    
    if(byte_flag == 0)
    {
        sh_stack->calls_level -= 1;
        return NOT_ERROR;
    }
    else
    {
        SH_STACK_DUMP(byte_flag ,sh_stack);
        sh_stack->calls_level -= 1;
        return byte_flag;
    }
}

template <typename elem_stk_T>
sh_stack_error_t check_canareyka(shablon_stack_t<elem_stk_T>* sh_stack)
{
    size_t flag = 0;
    canareyka_const_t left_canareyka = LEFT_CANAREYKA;
    canareyka_const_t* ptr_of_left_canareyka = (canareyka_const_t*)&left_canareyka;
    canareyka_const_t right_canareyka = RIGHT_CANAREYKA;
    canareyka_const_t* ptr_of_right_canareyka = (canareyka_const_t*)&right_canareyka;
    if(!memcmp(sh_stack->sh_stack_massive + INDEX_OF_LEFT_CANAR, ptr_of_left_canareyka, sizeof(elem_stk_T)) == 0)
    {
        flag += FLAG_CHECK_LEFT_CANAR;
    }
    if(!memcmp(sh_stack->sh_stack_massive + INDEX_OF_RIGHT_CANAR, ptr_of_right_canareyka, sizeof(elem_stk_T)) == 0)
    {
        flag += FLAG_CHECK_RIGHT_CANAR;
    }
    switch (flag)
    {
    case FLAG_NOT_ERROR:
        return NOT_ERROR;

    case FLAG_CHECK_LEFT_CANAR:
        return LEFT_CANAR_ERROR;
        
    case FLAG_CHECK_RIGHT_CANAR:
        return RIGHT_CANAR_ERROR;
    
    case FLAG_TWO_CANAR_ERROR:
        return TWO_CANAR_ERROR;

    default:
        return PIZDEC;
    }

}

template <typename elem_stk_T>
sh_stack_error_t check_poison(shablon_stack_t<elem_stk_T>* sh_stack)
{
    poison_const_t poison = POISON;
    poison_const_t* ptr_of_poison = (poison_const_t*)&poison;
    for(size_t i = sh_stack->size_of_sh_stack; i < sh_stack->capacity_of_sh_stack; i++)
    {
        if(memcmp(sh_stack->sh_stack_massive + i + 1, ptr_of_poison, sizeof(elem_stk_T)) != 0)
        {
            return POISON_ERROR;
        }
    }
    return NOT_ERROR;
}

#endif