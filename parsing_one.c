/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:07:00 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 00:07:32 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convet_value(char *str)
{
	int	j;

	j = -1;
	if (!str)
		return (NULL);
	while (str[++j])
	{
		if (str[j] < 0)
		{
			if (str[j] == -127)
				str[j] = '\0';
			else
				str[j] *= -1;
		}
	}
	return (str);
}

void	value_positif(t_list *cmd)
{
	int	i;

	while (cmd)
	{
		i = -1;
		while (cmd->cmd[++i])
			convet_value(cmd->cmd[i]);
		cmd = cmd->next;
	}
}

int	start_parse(char **str, t_data *data)
{
	*str = check_q(*str, data);
	if (!(*str))
		return (0);
	return (1);
}

t_list	*parsing(char *str, t_data *data)
{
	t_list	*ptr;

	if (!start_parse(&str, data))
		return (NULL);
	str = check_dq(str, data);
	if (!str)
		return (NULL);
	change_nl_tabs_to_space(str);
	str = ft_strtrim(str, " ");
	if (!str)
		return (NULL);
	str = check_d_pip(str, data);
	if (!str)
		return (NULL);
	str = check_dollars(str, data);
	if (!str)
		return (NULL);
	str = check_attched_quoets(str);
	str = ft_del_qs(str);
	if (!str)
		return (NULL);
	ptr = my_token(str);
	if (ft_cmd(ptr))
		return (NULL);
	return (value_positif(ptr), ptr);
}
