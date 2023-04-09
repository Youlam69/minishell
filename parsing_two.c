/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:06:33 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 00:10:38 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmp_env(char *str, t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (!env->var)
			return (NULL);
		if (ft_strcmp(str, env->var) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

int	check_neg(int nbr)
{
	if (nbr < 0)
		return (-1);
	return (1);
}

char	*ft_itoa(int nbr)
{
	char	*tab;
	int		len;
	int		tmp;

	len = (nbr <= 0);
	tmp = nbr;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	tab = malloc(sizeof(char) * (len + 1));
	tab[len] = '\0';
	if (nbr < 0)
		tab[0] = '-';
	else if (nbr == 0)
		tab[0] = '0';
	tmp = nbr;
	while (tmp)
	{
		len--;
		tab[len] = tmp % 10 * check_neg(nbr) + '0';
		tmp /= 10;
	}
	return (tab);
}

void	dollar_start(char **str, t_data *data, t_rdr *tmp)
{
	tmp->t1 = ft_substr(*str, tmp->i + 1, tmp->j - tmp->i - 1);
	tmp->t2 = cmp_env(tmp->t1, data->env);
	free(tmp->t1);
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t3 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
	if ((*str)[tmp->i + 1] == '\?')
		tmp->t2 = strjoin(tmp->t1, ft_itoa(data->exit_status));
	else
		tmp->t2 = strjoin(tmp->t1, tmp->t2);
	free(*str);
	tmp->j = ft_strlen(tmp->t2);
	free(tmp->t1);
	tmp->t1 = NULL;
	*str = strjoin(tmp->t2, tmp->t3);
	free(tmp->t2);
	tmp->t2 = NULL;
	free(tmp->t3);
	tmp->t3 = NULL;
}

char	*check_dollars(char *str, t_data *data)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 1;
		if (str[tmp.i] == '$')
		{
			if (str[tmp.j] == DQ || str[tmp.j] == SQ || str[tmp.j] == '\?')
				tmp.j++;
			else
				while (str[tmp.j] && valid_var(str[tmp.j]))
					tmp.j++;
			if (tmp.i < tmp.j - 1)
				dollar_start(&str, data, &tmp);
		}
		tmp.i = tmp.j;
	}
	return (str);
}
