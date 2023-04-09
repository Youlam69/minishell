/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:44:59 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 00:10:11 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(t_list *tmp)
{
	while (tmp)
	{
		tmp->fdinout[0] = 0;
		tmp->fdinout[1] = 1;
		tmp->her_exist = 0;
		tmp->content = check_heredoc(tmp, tmp->content);
		if (!tmp->content)
			return (-1);
		tmp->content = check_outapend(tmp, tmp->content);
		if (!tmp->content)
			return (-1);
		tmp->content = check_redirection_in(tmp, tmp->content);
		if (!tmp->content)
			return (-1);
		tmp->content = check_redirection_out(tmp, tmp->content);
		if (!tmp->content)
			return (-1);
		tmp->cmd = ft_split(tmp->content, ' ');
		tmp = tmp->next;
	}
	return (0);
}

int	is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

int	is_alpha(char c)
{
	if (c <= 'z' && c >= 'a')
		return (1);
	else if (c <= 'Z' && c >= 'A')
		return (1);
	return (0);
}

int	is_good(char c)
{
	if (is_digit(c) || is_alpha(c))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	valid_var(char c)
{
	if (is_good(c))
		return (1);
	return (0);
}
