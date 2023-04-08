/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inparsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:56:44 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 11:56:45 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_dq(char *str, t_data *data)
{
	int	i;
	int	q;
	int	dq;

	dq = 0;
	q = 0;
	i = -1;
	while (str[++i])
	{
		if (is_q(str[i]) && (dq % 2) == 0)
			q++;
		else if (is_dq(str[i]) && (q % 2) == 0)
			dq++;
		if (((dq % 2) != 0) && (is_special(str[i]) || is_q(str[i])))
			str[i] *= -1;
	}
	if ((dq % 2) != 0)
	{
		ft_syntax_err(data);
		free(str);
		return (NULL);
	}
	return (str);
}

char	*check_q(char *str, t_data *data)
{
	int	i;
	int	q;
	int	dq;

	dq = 0;
	i = -1;
	q = 0;
	while (str[++i])
	{
		if (is_dq(str[i]) && (q % 2) == 0)
			dq++;
		else if (is_q(str[i]) && (dq % 2) == 0)
			q++;
		if (((q % 2) != 0) && (is_special(str[i]) \
			|| is_dq(str[i]) || is_dlr(str[i])))
			str[i] *= -1;
	}
	if ((q % 2) != 0)
	{
		ft_syntax_err(data);
		free(str);
		return (NULL);
	}
	return (str);
}

int	annex_d_pp(t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '|')
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] == '|')
			{
				ft_syntax_err(data);
				free(str);
				return (1);
			}
		}
		i = j;
	}
	return (0);
}

char	*check_d_pip(char *str, t_data *data)
{
	int	i;
	int	j;

	if (annex_d_pp(data, str))
		return (NULL);
	if (str[0] == '|' || str[i - 1] == '|')
	{
		ft_syntax_err(data);
		free(str);
		return (NULL);
	}
	return (str);
}

void	change_nl_tabs_to_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
