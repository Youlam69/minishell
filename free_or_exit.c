/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_or_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 07:05:01 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:47:46 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_after_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

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

void	free_env(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

void	free_all_exit(t_data *data, int ref)
{
	free_list(data->cmd);
	free_after_split(data->splitedp);
	free(data->envc);
	if (ref)
	{
		free_env(data->env);
		free(data->pwd);
		ft_putstr_fd("exit\n", 1);
		exit(data->exit_status);
	}
}

void	annex_exit(t_data *data, char *cmd, int i)
{
	if (i == 0)
	{
		data->exit_status = 0;
		free_all_exit(data, 1);
	}
	else if (i > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		data->exit_status = 512;
	}
	else
	{
		data->exit_status = ft_atoi(cmd);
		free_all_exit(data, 1);
	}
}
