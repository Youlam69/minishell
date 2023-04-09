/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:31:43 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:36:30 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrrcmp(char *str1, char *str2)
{
	int	j;

	j = 0;
	while (str1[j] || str2[j])
	{
		if (str1[j] != str2[j])
			return (1);
		j++;
	}
	return (0);
}

int	sheegal(char *conten)
{
	int	i;

	i = 0;
	while (conten[i])
	{
		if (conten[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	*ft_variab(char *content)
{
	char	*str;
	int		i;

	i = sheegal(content);
	str = ft_substr(content, 0, i);
	return (str);
}

char	*ft_valu(char *content)
{
	char	*str;
	int		i;

	i = sheegal(content);
	str = ft_substr(content, i + 1, ft_strlen(content) - i);
	return (str);
}

t_env	*ft_lstnew(char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->var = ft_variab(content);
		new->val = ft_valu(content);
		new->print_env = 0;
		new->next = NULL;
	}
	return (new);
}
