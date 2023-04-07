
#include "minishell.h"


t_list *new_node(int debu, int siz, char *str, int index)
{
    t_list *ptr;

    ptr = malloc(sizeof(t_list));
    if(!ptr)
        return (NULL);
    else
    {
        ptr->index = index;
        ptr->content = ft_substr(str, debu, siz);
        ptr->cmd = NULL;
        ptr->cmdp = NULL;
        ptr->fdinout[0] = 0;
        ptr->fdinout[1] = 1;
        ptr->next = NULL;
    }
    return (ptr);
}


void add_back_node(t_list **head, t_list *new)
{
    t_list *ptr;
    
    if (!*head)
    {
        *head = new;
        new = NULL;
    }
    else
    {
        ptr = *head;
        while(ptr->next)
            ptr = ptr->next;
        ptr->next = new;
    }
}

int skeap_space(char *str, int i)
{
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}

char *check_attched_quoets(char *str)
{
    int i = -1;
    // char *tmp;
    
    while(str[++i])
    {
        if((str[i] == DQ && str[i + 1] == DQ) || (str[i] == SQ && str[i + 1] == SQ))
        {
            str[i] = -127;
            str[i + 1] = -127;
            // tmp = str;
            // str = ft_strdup(str); // should use ft_strdup
            // free(tmp); 
            // tmp = NULL;
            // return(str);
        }
    }
    return (str);
}

char *ft_del_qs(char *str)
{
    int i;
    char *tab;
    int j = 0;
    
    i = 0;
    while(str[i])
    {   
        if(str[i] == DQ || str[i] == SQ)
            j++;
        i++;
    }
    i = ft_strlen(str) - j;
    tab =  malloc (sizeof(char) * i + 1);
    tab[i] = '\0';

    i = -1;
    j = 0;
    
    while(str[++i])
    {
        if(str[i] != DQ && str[i] != SQ)
        {
            tab[j] = str[i];
            j++;
        }
    }
    free(str);
    str = tab;
    return(str);
    
}

int ft_autre_carac(char *str, int n, t_list **ptr)
{
    int i;
    // while(str[n] && str[n] != '>'
	// 	&& str[n] != '<' && str[n] != '|' && str[n] != ' ')
    //     n++;
    // printf("hada str 9bal lkhadma __%s__\n", str);
    // printf("hada str ba3dlkhadma |%s|\n", str);
    i = n;
    while(str[n] && str[n] != '|')
        n++;
    add_back_node(ptr, new_node(i, (n - i), str, 128));  // 128 == autre caracter
    return (n);
}

t_list *my_token(char *str)
{
    t_list *ptr;
    int i;

    ptr = NULL;
    i = -1;
    while(str[++i])
    {
        i = skeap_space(str, i);
        i = ft_autre_carac(str, i, &ptr);
        if (!str[i])
          return (ptr);
    }
    return (ptr);
}





// int ft_pipe(char *str, int n, t_list **ptr)
// {
//     if(str[n] == '|')
//         add_back_node(ptr, new_node(n, 1, str, PIPE));  // PIPE == |
//     return (n + 1);
// }



// int ft_superier(char *str, int n, t_list **ptr)
// {
//     int i;
//     i = n;
//     if(str[n] == '>' && str[n + 1] == '>')
//     {
//         while(str[n] && str[n] == '>')
//             n++;
//         add_back_node(ptr, new_node(i, (n - i), str, ROUTPUT)); // ROUTPUT == >
//         return (n);  
//     }
//     add_back_node(ptr, new_node(i, 1, str, ROUTPUT));  // ROUTPUT == >
//         return (n + 1);
// }

// int ft_inferieur(char *str, int n, t_list **ptr)
// {
//     int i;
//     i = n;
//     if(str[n] == '>' && str[n + 1] == '>')
//     {
//         while(str[n] && str[n] == '>')
//             n++;
//         add_back_node(ptr, new_node(i, (n - i), str, RINPUT)); // RINPUT == <
//         return (n);  
//     }
//     add_back_node(ptr, new_node(i, 1, str, RINPUT));  // RINPUT == <
//         return (n + 1);
// }



// int ft_double_cout(char *str, int n, t_list **ptr)
// {
//     int i;
    
//     i = 0;
    
//     if(str[n] == '"' && str[n + 1] == '"')
//         add_back_node(ptr, new_node(n, 2, str, DQ));  //  DQ== "
//     else
//     {
//         i = n;
//         n += 1;
//         while(str[n] && str[n] != '"')
//             n++;
//         add_back_node(ptr, new_node(n, (n - i) + 1, str, DQ));  // DQ == "
//         return (n + 1);
//     }
//     return (n + 2);
// }

// int ft_sing_cout(char *str, int n, t_list **ptr)
// {
//     int i;
    
//     i = 0;
    
//     if(str[n] == '\'' && str[n + 1] == '\'')
//         add_back_node(ptr, new_node(n, 2, str, SQ));  //  SQ== '
//     else
//     {
//         i = n;
//         n += 1;
//         while(str[n] && str[n] != '\'')
//             n++;
//         add_back_node(ptr, new_node(n, (n - i) + 1, str, SQ));  // SQ == '
//         return (n + 1);
//     }
//     return (n + 2);
// }
