template <typename elem_stk_T>
sh_stack_error_t left_canareyka_create(elem_stk_T* left_element, size_t size_of_canareyka)
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

template <typename elem_stk_T>
sh_stack_error_t right_canareyka_create(elem_stk_T* right_element, size_t size_of_canareyka)
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

template <typename elem_stk_T>
sh_stack_error_t poison_create(shablon_stack_t<elem_stk_T>* sh_stack, size_t size_of_poison)
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
        memcpy(sh_stack->sh_stack_massive + i + 1, ptr_of_poison, size_of_poison);
    }

    return NOT_ERROR;
}

template <typename elem_stk_T> 
uint64_t massive_hash_counting(shablon_stack_t<elem_stk_T>* sh_stack)
{
    uint64_t hash_for_massive = 0;
    for(size_t i = 0; i <= sh_stack->capacity_of_sh_stack; i++)
    {
        hash_for_massive += get_bytes_sum(sh_stack->sh_stack_massive + i);
    }
    // printf("stack hash: %ld\n", sh_stack->sh_stack_hash);
    // printf("struct hash: %ld\n", sh_stack->sh_struct_hash);
    return hash_for_massive;
}


template <typename elem_stk_T> 
uint64_t struct_hash_counting(shablon_stack_t<elem_stk_T>* sh_stack)
{
    uint64_t hash_for_struct = 0;
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
uint64_t get_bytes_sum(const elem_stk_T* value) 
{
    const uint8_t* byte_ptr = (const uint8_t*)(value);
    size_t sum = 0;

    for (size_t i = 0; i < sizeof(elem_stk_T); ++i) 
    {
        sum += byte_ptr[i];
    }

    return sum;
}