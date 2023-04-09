/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:38:41 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:40:17 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_data *data, int *fdp, int fd2)
{
	t_list	*cmd;
	int		imp;

	cmd = data->cmd;
	if (cmd->fdinout[1] < 0 || cmd->fdinout[0] < 0)
		exit(1);
	close(fdp[0]);
	if (cmd->next)
		child_help(cmd, data, fdp, fd2);
	else
	{
		if (ft_lstsize(cmd) == data->nbrcmd)
			dup_close(cmd->fdinout[0], cmd->fdinout[1]);
		else
			dup_close(fd2, cmd->fdinout[1]);
	}
	imp = check_implmnt(data);
	if (imp)
		exec_imp(data, imp, 1);
	if (!cmd->cmdp[0])
		exit(0);
	execve(cmd->cmdp, cmd->cmd, data->envc);
	ft_putstr_3d("command not found: ", cmd->cmd[0], NULL, NULL);
	exit(127);
}

void	parent(t_data *data, int *fdp)
{
	t_list	*cmd;

	cmd = data->cmd;
	close(fdp[1]);
	data->cmd = cmd->next;
	if (data->cmd)
		tofork(data, fdp[0]);
	if (fdp[0] != 0)
		close(fdp[0]);
}

void	tofork_plus(int *pid, t_data *data, int *fdp)
{
	if (pipe(fdp) < 0)
	{
		perror("Error");
		return ;
	}
	if (!data->cmd->next && data->nbrcmd == ft_lstsize(data->cmd) \
				&& check_implmnt(data) >= 4)
		exec_imp(data, check_implmnt(data), 0);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		*pid = fork();
	}
}

void	tofork(t_data *data, int fd2)
{
	pid_t	pid;
	int		ext_s;
	int		fdp[2];

	ext_s = 0;
	pid = -3;
	tofork_plus(&pid, data, fdp);
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, handler_c);
		signal(SIGQUIT, hadler_quit);
		child(data, fdp, fd2);
	}
	else
		parent(data, fdp);
	if (fdp[0] > 0)
		close(fdp[0]);
	waitpid(-1, &ext_s, 0);
	if (!data->cmd)
		if (WIFEXITED(ext_s))
			data->exit_status = WEXITSTATUS(ext_s);
}
