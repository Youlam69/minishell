/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:32:09 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:37:35 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*ptr;

	if (alst)
	{
		if (*alst == NULL)
		{
			*alst = new;
			new = NULL;
		}
		else
		{
			ptr = *alst;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}

int	ft_isdigit(char c)
{
	return (c <= '0' || c >= '9');
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*str == ' ') || (*str >= 7 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res * sign);
}

void	shlvl_anex(t_env *ev)
{	
	int		i;
	char	*tmp;

	i = ft_atoi(ev->val);
	if (i >= 999)
	{
		printf("warning: shell level (1000) too high\
			, resetting to 1\n");
	}
	else if (i < 0)
	i = 0;
	else
		i++;
	tmp = ev->val;
	ev->val = ft_itoa(i);
	free(tmp);
}

void	shlvl(t_env *ev)
{
	if (!ev || !ev->var)
		return ;
	while (ev)
	{
		if (!ft_strcmp(ev->var, "SHLVL" ))
		{
			shlvl_anex(ev);
			break ;
		}
		ev = ev->next;
	}
}
