/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:00:10 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 08:00:48 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chdir_anex(t_data *data, char **cmd)
{
	if (!cmd[1])
		chdir("/home");
	else if (cmd[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		data->exit_status = 1;
		return (1);
	}
	else if (chdir(cmd[1]) < 0)
	{
		ft_putstr_fd("Minishell : ", 2);
		perror(cmd[1]);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

void	cd(t_data *data)
{
	char	*tmp;
	char	**cmd;

	cmd = data->cmd->cmd;
	if (chdir_anex(data, cmd))
		return ;
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_putstr_fd("cd: error retrieving current directory: \
			getcwd: cannot access parent directories: No such file \
			or directory\n", 2);
		return ;
	}
	else
	{
		free(data->pwd);
		data->pwd = tmp;
	}
	data->exit_status = 0;
}
