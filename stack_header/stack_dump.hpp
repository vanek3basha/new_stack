#ifndef _SH_STACK_DUMP__HPP_
#define _SH_STACK_DUMP__HPP_

template <typename elem_stk_T>
sh_stack_error_t sh_stack_dump(stack_flag_of_err_t byte_flag, shablon_stack_t<elem_stk_T>* sh_stack, int line, const char* file, const char* func)
{
    if(sh_stack->calls_level < MAX_CALLS_IN_HISTORY)
    {
        sh_stack->info[sh_stack->calls_level] = {line, file, func};
        sh_stack->calls_level += 1;
    }

    FILE* dump_file = fopen("sh_stack_dumpfile.log", "a+");
    if(dump_file == NULL)
    {
        perror("DUMP_FILE OPEN ERROR\n");
        sh_stack->calls_level -= 1;
        return DUMP_FILE_OPEN_ERROR;
    }
    sh_stack_error_t flag = NOT_ERROR;

    char* type_of_stack = abi::__cxa_demangle(typeid(elem_stk_T).name(), NULL, NULL, NULL);
    fprintf(dump_file, "---------------------------STACK DUMP---------------------------\n");
    
    for(size_t i = sh_stack->calls_level; i > 0; i--)
    {
        fprintf(dump_file, "IN FILE:%s   \nLINE:%d   \nFUNC:%s \n", sh_stack->info[i - 1].file, sh_stack->info[i - 1].line, sh_stack->info[i - 1].func);
        fprintf(dump_file, "^\n");
        fprintf(dump_file, "|\n");
    }

    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "                      TYPE OF STACK: %s\n", type_of_stack);

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
        fprintf(dump_file, "LEFT  STRUCT CANAREYKA: %lu\n", sh_stack->left_struct_canar);
        fprintf(dump_file, "RIGHT STRUCT CANAREYKA: %lu\n", sh_stack->right_struct_canar);
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
            fprintf(dump_file, "%2lu ELEMENT: ", (i + 1));
            for (size_t j = 0; j < sizeof(elem_stk_T); j++) 
            {
            fprintf(dump_file, "0x%02X ", byte_ptr[j]);
            }
            fprintf(dump_file, "\n");
        }
    }

    size_t count_of_errors = 0;
    fprintf(dump_file, "\n--------------------------LIST OF ERROR-------------------------\n");
    if(byte_flag != 0)
    {
        stack_flag_of_err_t mask = 0;
        for(size_t i = 1; i < 31; i++)
        {
            mask = 1 << i;
            if((byte_flag & mask) != 0)
            {
            count_of_errors += 1;
            fprintf(dump_file, "ERROR %lu: %s\n", count_of_errors, NAME_OF_ERROR());
            }
        }
    }
    else
    {
        fprintf(dump_file, "NOT_ERRORS\n");
    }
    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "                        COUNT OF ERRORS: %lu\n", count_of_errors);

    fprintf(dump_file, "\n----------------------------------------------------------------\n");
    fprintf(dump_file, "-------------------------STACK DUMP END-------------------------\n");
    fclose(dump_file);
    free(type_of_stack);
    sh_stack->calls_level -= 1;
    return SH_STACK_NULL_ERROR;
}

#endif