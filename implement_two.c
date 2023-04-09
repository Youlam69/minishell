/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:54:02 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:56:19 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_data *data, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j] && is_good(cmd[i][j]))
			j++;
		if (cmd[i][j])
		{
			ft_putstr_3d("minishell: unset: `", cmd[i], "': \
				not a valid identifier", NULL);
			data->exit_status = 1;
			continue ;
		}
		unset_var(&data->env, cmd[i]);
	}
	data->exit_status = 0;
}

int	check_implmnt(t_data *data)
{
	t_list	*cmd;

	cmd = data->cmd;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (2);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (3);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (4);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (5);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (6);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (7);
	return (0);
}

void	env(t_env *env)
{
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
	exit(0);
}

void	pwd(char *pwd)
{
	printf("%s\n", pwd);
}

void	echo(char **cmd)
{
	int	i;
	int	j;
	int	del_nl;

	i = 1;
	del_nl = 0;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j])
			break ;
		del_nl = 1;
		i++;
	}
	while (cmd[i] && cmd[i + 1])
		printf("%s ", cmd[i++]);
	if (cmd[i])
		printf("%s", cmd[i]);
	if (!del_nl)
		printf("\n");
}
