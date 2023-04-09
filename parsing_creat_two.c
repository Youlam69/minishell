/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_creat_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:12:07 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 00:12:13 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_del_qs(char *str)
{
	int		i;
	char	*tab;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == DQ || str[i] == SQ)
			j++;
		i++;
	}
	i = ft_strlen(str) - j;
	tab = anex_del_qs(str, i + 1);
	free(str);
	str = tab;
	return (str);
}

int	ft_autre_carac(char *str, int n, t_list **ptr)
{
	int	i;

	i = n;
	while (str[n] && str[n] != '|')
		n++;
	add_back_node(ptr, new_node(i, (n - i), str, 128));
	return (n);
}

t_list	*my_token(char *str)
{
	t_list	*ptr;
	int		i;

	ptr = NULL;
	i = -1;
	while (str[++i])
	{
		i = skeap_space(str, i);
		i = ft_autre_carac(str, i, &ptr);
		if (!str[i])
			return (ptr);
	}
	return (ptr);
}
