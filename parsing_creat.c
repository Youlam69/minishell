/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_creat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:14:26 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 08:55:11 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_node(int debu, int siz, char *str, int index)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	else
	{
		ptr->index = index;
		ptr->content = ft_substr(str, debu, siz);
		ptr->cmd = NULL;
		ptr->cmdp = NULL;
		ptr->fdinout[0] = 0;
		ptr->fdinout[1] = 1;
		ptr->next = NULL;
	}
	return (ptr);
}

void	add_back_node(t_list **head, t_list *new)
{
	t_list	*ptr;

	if (!*head)
	{
		*head = new;
		new = NULL;
	}
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

int	skeap_space(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

char	*check_attched_quoets(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == DQ && str[i + 1] == DQ) \
			|| (str[i] == SQ && str[i + 1] == SQ))
		{
			str[i] = -127;
			str[i + 1] = -127;
		}
	}
	return (str);
}

char	*anex_del_qs(char *str, int len)
{	
	int		i;
	int		j;
	char	*tab;

	i = -1;
	j = 0;
	tab = malloc(sizeof(char) * len);
	if (!tab)
		return (NULL);
	tab[len - 1] = '\0';
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != DQ && str[i] != SQ)
		{
			tab[j] = str[i];
			j++;
			tab[j] = '\0';
		}
	}
	return (tab);
}

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

t_list  *my_token(char *str)
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
