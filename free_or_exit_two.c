/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_or_exit_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:47:19 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:48:47 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[0] && is_digit(cmd[0][i]))
		i++;
	if (cmd[0] && cmd[0][i])
	{
		ft_putstr_3d("minishell: exit: ", cmd[0],
			": numeric argument required", NULL);
		data->exit_status = 255;
		free_all_exit(data, 1);
	}
	i = 0;
	while (cmd[i])
		i++;
	annex_exit(data, cmd[0], i);
}
