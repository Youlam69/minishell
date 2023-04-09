/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:53:22 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:55:39 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((i < n) && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

void	ft_putndl_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
}

void	free_unset(t_env **env, t_env *tmp_env)
{
	if (tmp_env->next)
	{
		*env = tmp_env->next;
		frfr(tmp_env->var, tmp_env->val);
		free(tmp_env);
	}
	else
	{
		frfr(tmp_env->var, tmp_env->val);
		free(tmp_env);
		*env = NULL;
	}
}

void	unset_var(t_env **env, char *var)
{
	t_env	*tmp_env;
	t_env	*prev;

	tmp_env = *env;
	prev = NULL;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->var, var) == 0)
		{
			if (prev)
			{
				prev->next = tmp_env->next;
				frfr(tmp_env->var, tmp_env->val);
				free(tmp_env);
			}
			else
				free_unset(env, tmp_env);
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
}
