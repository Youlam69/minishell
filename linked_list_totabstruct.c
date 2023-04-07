# include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list *convert(t_list *cmnd, data.ls)
{

    t_list *cmd;
    t_list *tmp;
    int i = 0;

    cmd = malloc(sizeof(t_list) * ft_lstsize(cmnd) + 1);
    tmp = cmnd;
    while(tmp)
    {
        	char			*tmp;
	// int				nbrcmd;
	cmd[i].her_exist = tmp->her_exist;
	// ccmd[i].cmdp = c ;


        cmd[i].index =  tmp->index;
        cmd[i]input = tmp->input ;
        cmd[i].output = tmp->output ;
        // cmd[i].content = tmp->content ;
        cmd[i].cmd = tmp->cmd;
        cmd[i].cmdp = tmp->cmdp;
        cmd[i].cmdp = tmp->cmdp;
        tmp = tmp->next;
        i++;
    }
    // cmd[i] = NULL;
    return cmd;
}