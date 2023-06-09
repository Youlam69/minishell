/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 06:39:21 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:57:09 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_q(char c)
{
	return (c == SQ);
}

int	is_pipe(char c)
{
	return (c == PIPE);
}

int	is_rinp(char c)
{
	return (c == RINPUT);
}

int	is_routp(char c)
{
	return (c == ROUTPUT);
}

int	is_special(char c)
{
	return (is_pipe(c) || is_rinp(c) || is_routp(c) || c == ' ');
}
