#ifndef _SH_STACK_SECURE__HPP_
#define _SH_STACK_SECURE__HPP_

template <typename elem_stk_T>
sh_stack_error_t canareyka_create(shablon_stack_t<elem_stk_T>* sh_stack)
{
    if(sizeof(elem_stk_T) > 8)
    {
        perror("WARNING SIZE OF YOUR TYPE BIGGER THEN 8 BYTES\n");
        return SIZE_OF_ELEMENTS_ERROR;
    }
    
    sh_stack->sh_stack_massive[INDEX_OF_LEFT_CANAR]  = (elem_stk_T)LEFT_CANAREYKA;
    sh_stack->sh_stack_massive[INDEX_OF_RIGHT_CANAR] = (elem_stk_T)RIGHT_CANAREYKA;

    return NOT_ERROR;
}

template <typename elem_stk_T>
sh_stack_error_t poison_create(shablon_stack_t<elem_stk_T>* sh_stack)
{   
    if(sizeof(elem_stk_T) > 8)
    {
        perror("WARNING SIZE OF YOUR TYPE BIGGER THEN 8 BYTES\n");
        return SIZE_OF_ELEMENTS_ERROR;
    }

    poison_const_t poison = POISON;
    poison_const_t* ptr_of_poison = (poison_const_t*)&poison;

    for(size_t i = sh_stack->size_of_sh_stack; i < sh_stack->capacity_of_sh_stack; i++)
    {
        memcpy(sh_stack->sh_stack_massive + i + 1, ptr_of_poison, sizeof(elem_stk_T));
    }

    return NOT_ERROR;
}

template <typename elem_stk_T> 
hash_t massive_hash_counting(shablon_stack_t<elem_stk_T>* sh_stack)
{
    hash_t hash_for_massive = 0;
    for(size_t i = 0; i <= sh_stack->capacity_of_sh_stack; i++)
    {
        hash_for_massive += get_bytes_sum(sh_stack->sh_stack_massive + i);
    }
    // printf("stack hash: %ld\n", sh_stack->sh_stack_hash);
    // printf("struct hash: %ld\n", sh_stack->sh_struct_hash);
    return hash_for_massive;
}


template <typename elem_stk_T> 
hash_t struct_hash_counting(shablon_stack_t<elem_stk_T>* sh_stack)
{
    hash_t hash_for_struct = 0;
    for(size_t i = 0; i <= sh_stack->capacity_of_sh_stack; i++)
    {
        hash_for_struct += get_bytes_sum(sh_stack->sh_stack_massive + i);
    }
    // printf("stack hash: %ld\n", sh_stack->sh_stack_hash);
    // printf("struct hash: %ld\n", sh_stack->sh_struct_hash);
    hash_for_struct += get_bytes_sum(&sh_stack->capacity_of_sh_stack);
    hash_for_struct += get_bytes_sum(&sh_stack->size_of_sh_stack);
    hash_for_struct += get_bytes_sum(&sh_stack->left_struct_canar);
    hash_for_struct += get_bytes_sum(&sh_stack->right_struct_canar);
    return hash_for_struct;
}   

template <typename elem_stk_T>
hash_t get_bytes_sum(const elem_stk_T* value) 
{
    const uint8_t* byte_ptr = (const uint8_t*)(value);
    hash_t sum = 0;

    for (size_t i = 0; i < sizeof(elem_stk_T); ++i) 
    {
        sum += byte_ptr[i];
    }

    return sum;
}

#endif