/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:45:00 by ylamraou          #+#    #+#             */
/*   Updated: 2022/06/08 11:45:01 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**splitpath(char **env)
{
	char	*path;
	char	**splited;
	int		i;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
		{
			path = ft_strtrim(path, "PATH=");
			break ;
		}
		i++;
	}
	splited = ft_split(path, ':');
	free(path);
	return (splited);
}

void	splitav(char **av, t_cp *cmdp)
{
	int	i;

	i = -1;
	while (++i < cmdp->nbrcmd)
		cmdp[i].cmd = ft_split(av[i + 2 + cmdp->her_exist], ' ');
}

int	accs(char *path)
{
	if (access(path, F_OK))
		return (1);
	if (open(path, O_DIRECTORY) < 0)
	{
		if (!(access(path, X_OK)))
			return (0);
		else
			return (2);
	}
	return (3);
}

void	joinpath(t_cp *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	j = -1;
	while (++j < cmd->nbrcmd && cmd[j].cmd[0])
	{
		i = -1;
		while (cmd->splitedp[++i])
		{
			tmp = ft_strjoin(cmd->splitedp[i], "/");
			cmd[j].cmdp = ft_strjoin(tmp, (cmd[j].cmd[0]));
			free(tmp);
			if (accs(cmd[j].cmdp) == 0)
				break ;
			free(cmd[j].cmdp);
		}
		if (!cmd->splitedp[i])
			cmd[j].cmdp = strdup(cmd[j].cmd[0]);
	}
}
