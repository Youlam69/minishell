/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:33:40 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 10:34:46 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*anxsplt_path(t_env *env, char **path)
{
	while (env)
	{
		if (env->var)
		{
			if (!ft_strcmp(env->var, "PATH"))
			{
				*path = env->val;
				break ;
			}
		}
		env = env->next;
	}
	return (env);
}

char	**splitpath(t_env *env)
{
	char	*path;
	char	**splited;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	if (!env->var)
		return (NULL);
	env = anxsplt_path(env, &path);
	if (!env)
		return (NULL);
	splited = ft_split(env->val, ':');
	i = 0;
	while (splited[i])
	{
		path = splited[i];
		splited[i] = strjoin(path, "/");
		free(path);
		path = NULL;
		i++;
	}
	return (splited);
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

void	anx_joinpath(t_data *data)
{
	t_list	*cmd;
	int		i;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->cmd && cmd->cmd[0])
		{
			i = -1;
			while (data->splitedp[++i])
			{
				cmd->cmdp = strjoin(data->splitedp[i], cmd->cmd[0]);
				if (accs(cmd->cmdp) == 0)
					break ;
				free(cmd->cmdp);
			}
			if (!data->splitedp[i])
				cmd->cmdp = ft_strdup(cmd->cmd[0]);
		}
		cmd = cmd->next;
	}
}

void	joinpath(t_data *data)
{
	t_list	*cmd;

	cmd = data->cmd;
	if (!data->splitedp)
	{
		cmd->cmdp = ft_strdup(cmd->cmd[0]);
		return ;
	}
	anx_joinpath(data);
}