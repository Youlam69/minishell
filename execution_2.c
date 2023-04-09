/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:39:48 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:40:05 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close(int in, int out )
{
	dup2(in, 0);
	if (in != 0)
		close(in);
	dup2(out, 1);
	if (out != 1)
		close(out);
}

void	exec_imp(t_data *data, int imp, int ref)
{
	data->exit_status = 0;
	if (imp == 1)
		echo(data->cmd->cmd);
	else if (imp == 2)
		pwd(data->pwd);
	else if (imp == 3)
		env(data->env);
	else if (imp == 4)
		ft_exit(data, &data->cmd->cmd[1]);
	else if (imp == 5)
		cd(data);
	else if (imp == 6)
		export(data, data->cmd->cmd);
	else if (imp == 7)
		unset(data, data->cmd->cmd);
	if (ref)
		exit (data->exit_status);
}

void	hadler_quit(int sig)
{
	(void)sig;
}

void	handler_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		exit(130);
	}
}

void	child_help(t_list *cmd, t_data *data, int *fdp, int fd2)
{
	if (ft_lstsize(cmd) == data->nbrcmd)
	{
		if (cmd->fdinout[1] > 1)
			dup_close(cmd->fdinout[0], cmd->fdinout[1]);
		else
			dup_close(cmd->fdinout[0], fdp[1]);
	}
	else
	{	
		if (cmd->fdinout[0] > 1)
			dup2(cmd->fdinout[0], 0);
		else
			dup2(fd2, 0);
		if (cmd->fdinout[1] > 1)
			dup2(cmd->fdinout[1], 1);
		else
			dup2(fdp[1], 1);
	}
}
