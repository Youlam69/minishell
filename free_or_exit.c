#include "minishell.h"

void free_after_split(char **tab)
{
	int i = 0;
	if(!tab)
		return;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void free_list(t_list *lst)
{
	t_list *tmp;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_after_split(tmp->cmd);
		free(tmp->cmdp);
		free(tmp->content);
		free(tmp);
	}
}

void free_env(t_env *lst)
{
	t_env *tmp;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

void    free_all_exit(t_data *data, int ref)
{
    free_list(data->cmd);
    free_after_split(data->splitedp);
    free(data->envc);
    // free(data->cmd);
    if(ref)
    {
        free_env(data->env);
        free(data->pwd);
        ft_putstr_fd("exit\n", 1);
        exit(data->exit_status);
    }
    // free(data->env);
    // free(data->exit_status);
}


void	ft_exit(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[0] && is_digit(cmd[0][i]))
		i++;
	if (cmd[0] && cmd[0][i])
	{
		ft_putstr_fd("minishell: exit: ",2);
        ft_putstr_fd(cmd[0],2);
        ft_putstr_fd(": numeric argument required", 2);
        ft_putstr_fd("\n", 2);
        data->exit_status = 255;
		free_all_exit(data, 1);
	}
	i = 0;
	while (cmd[i])
		i++;
	if (i == 0)
    {
        data->exit_status = 0;
        free_all_exit(data, 1);
    }
	else if (i > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		data->exit_status= 512;
	}
	else
    {
        data->exit_status = ft_atoi(cmd[0]);
        free_all_exit(data, 1);
    }
}