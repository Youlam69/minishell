
#include "minishell.h"


void ft_syntax_err(t_data *data)
{
    printf("syntax error\n");
    data->exit_status = 258;
    
}