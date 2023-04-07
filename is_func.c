

#include "minishell.h"


int is_dq(char c)
{
    return (c == DQ);
}

int is_dlr(char c)
{
    return (c == DLR);
}
int is_q(char c)
{
    return (c == SQ);
}
int is_pipe(char c)
{
    return(c == PIPE);
}

int is_rinp(char c)
{
    return(c == RINPUT);
}

int is_routp(char c)
{
    return(c == ROUTPUT);
}

int is_special(char c)
{
    return(is_pipe(c) || is_rinp(c) || is_routp(c) || c == ' ');
}