/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:42:08 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:44:15 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_export(char *var, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->var = var;
		new->val = val;
		new->print_env = 0;
		new->next = NULL;
	}
	return (new);
}

int	check_var(char *var, char *arg)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (!is_good(var[i]) || var[0] == '=' || is_digit(var[0]))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	add_to_env_plus(t_envv *tmp, char *var, char *val, t_env **env)
{
	tmp->vl = strjoin(var, val);
	if (check_var(var, tmp->vl))
		return (0);
	free(tmp->vl);
		tmp->vl = NULL;
	if (!env)
	{
		*env = ft_lstnew_export(var, val);
		return (0);
	}
	tmp->tmp = *env;
	return (1);
}

t_env	*add_to_env(char *var, char *val, t_env *env, int j)
{
	t_envv	tmp;

	if (!add_to_env_plus(&tmp, var, val, &env))
		return (env);
	while (tmp.tmp)
	{
		if (!ft_strcmp(var, tmp.tmp->var))
		{
			if (!val)
				return (env);
			tmp.vl = tmp.tmp->val;
			if (j)
				tmp.tmp->val = strjoin(tmp.tmp->val, val);
			else
				tmp.tmp->val = val;
			free(tmp.vl);
			tmp.vl = NULL;
			return (env);
		}
		tmp.tmp2 = tmp.tmp;
		tmp.tmp = tmp.tmp->next;
	}
	if (!tmp.tmp)
		tmp.tmp2->next = ft_lstnew_export(var, val);
	return (env);
}

t_env	*split_export(char *arg, t_env *env)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	tmp.i = sheegal(arg);
	if (tmp.i == 0)
	{
		check_var(arg, arg);
		return (env);
	}
	if (tmp.i > 1 && arg[tmp.i - 1] == '+')
		tmp.j = 1;
	tmp.t1 = ft_substr(arg, 0, tmp.i - tmp.j);
	tmp.t2 = ft_substr(arg, tmp.i + 1, ft_strlen(arg) - tmp.i);
	if (!tmp.t2)
	{
		tmp.t2 = malloc(sizeof(char));
		tmp.t2[0] = '\0';
	}
	if (check_var(tmp.t1, arg))
		return (frfr(tmp.t1, tmp.t2), NULL);
	else
		env = add_to_env(tmp.t1, tmp.t2, env, tmp.j);
	return (env);
}
