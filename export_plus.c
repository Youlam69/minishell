/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:43:42 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:46:36 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_and_prnit(char **arg)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	tmp.i = -1;
	while (arg[tmp.s])
		tmp.s++;
	while (++tmp.i < tmp.s - 1)
	{
		tmp.j = -1;
		while (++tmp.j < tmp.s - tmp.i - 1)
		{
			if (strcmp(arg[tmp.j], arg[tmp.j + 1]) > 0)
			{
				tmp.t1 = arg[tmp.j];
				arg[tmp.j] = arg[tmp.j + 1];
				arg[tmp.j + 1] = tmp.t1;
			}
		}
	}
	tmp.i = 0;
	while (arg[tmp.i])
		printf("declare -x %s\n", arg[tmp.i++]);
	free_after_split(arg);
}

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	join_and_free_env(char **tab, int i, t_env *tmp)
{
	char	*tp;

	tab[i] = strjoin(tmp->var, "=");
	tp = tab[i];
	tab[i] = strjoin(tp, "\'");
	free(tp);
	tp = tab[i];
	tab[i] = strjoin(tp, tmp->val);
	free(tp);
	tp = tab[i];
	tab[i] = strjoin(tab[i], "\'");
	free(tp);
}

void	print_env(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * ft_lstsize_env(env) + 1);
	tmp = env;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->var)
		{
			if (!tmp->val)
				tab[i] = strjoin(NULL, tmp->var);
			else
				join_and_free_env(tab, i, tmp);
			i++;
			tab[i] = NULL;
		}
		tmp = tmp->next;
	}
	sort_and_prnit(tab);
}

void	export(t_data	*data, char	**val)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->env;
	while (val[++i])
	{
		if (sheegal(val[i]) == ft_strlen(val[i]))
			data->env = add_to_env(val[i], NULL, data->env, 0);
		else
			data->env = split_export(val[i], data->env);
	}
	if (i == 1)
		print_env(env);
}
