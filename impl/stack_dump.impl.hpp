template <typename stk_T>
ShStackError sh_stack_dump(ShStackError* massive_of_error, shablon_stack_t<stk_T>* sh_stack, size_t count_of_errors, int line, const char* file, const char* func)
{
    if(level_in_history < MAX_CALLS_IN_HISTORY)
    {
        call_history[level_in_history] = {line, file, func};
        level_in_history += 1;
    }

    FILE* dump_file = fopen("sh_stack_dumpfile.txt", "a+");
    if(dump_file == NULL)
    {
        perror("DUMP_FILE OPEN ERROR\n");
        level_in_history -= 1;
        return DUMP_FILE_OPEN_ERROR;
    }
    ShStackError flag = NOT_ERROR;

    char* type_of_stack = abi::__cxa_demangle(typeid(stk_T).name(), NULL, NULL, NULL);
    fprintf(dump_file, "---------------------------STACK DUMP---------------------------\n");
    
    for(size_t i = level_in_history; i > 0; i--)
    {
        fprintf(dump_file, "IN FILE:%s   \nLINE:%d   \nFUNC:%s \n", call_history[i - 1].file, call_history[i - 1].line, call_history[i - 1].func);
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
    level_in_history -= 1;
    return SH_STACK_NULL_ERROR;
}
