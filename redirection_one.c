/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:15:01 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 01:21:16 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_redirection_out(t_list *cmd, char *str)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 1;
		if (str[tmp.i] == '>' && str[tmp.j] != '>')
		{
			tmp.s = tmp.j;
			while (str[tmp.s] && str[tmp.s] == ' ')
				tmp.s++;
			if (str[tmp.s] == '\0' || str[tmp.s] == '<' || str[tmp.j] == '>')
				if (!tt(str))
					return (NULL);
			tmp.j = tmp.s;
			loop_over_j(str, &tmp);
			if (tmp.s < tmp.j)
				if (!redir_assist(&tmp, cmd, &str))
					break ;
		}
		tmp.i++;
	}
	return (str);
}

int	outapent_plus(t_rdr *tmp, char **str, t_list *cmd)
{
	tmp->t3 = ft_substr(*str, tmp->s, tmp->j - tmp->s);
	cmd->fdinout[1] = open(convet_value(tmp->t3),
			O_CREAT | O_RDWR | O_APPEND, 0644);
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t2 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
	free(*str);
	if (cmd->fdinout[1] < 0)
	{
		ft_putstr_3d("minishell: ", tmp->t1, " : Permission denied\n", NULL);
		*str = ft_strdup("");
		return (0);
	}
	else
		*str = ft_strjoin(tmp->t1, tmp->t2);
	free(tmp->t2);
	free(tmp->t3);
	free(tmp->t1);
	tmp->t1 = NULL;
	tmp->t2 = NULL;
	tmp->t3 = NULL;
	return (1);
}

char	*check_outapend(t_list *cmd, char *str)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 2;
		if (str[tmp.i] == '>' && str[tmp.i + 1] == '>')
		{
			tmp.s = tmp.j;
			while (str[tmp.s] && str[tmp.s] == ' ')
				tmp.s++;
			if (str[tmp.s] == '\0' || str[tmp.s] == '<' || str[tmp.j] == '>')
				if (!tt(str))
					return (NULL);
			tmp.j = tmp.s;
			while (str[tmp.j] && str[tmp.j] != ' '
				&& str[tmp.j] != '<' && str[tmp.j] != '>')
				tmp.j++;
			if (tmp.s < tmp.j)
				if (!outapent_plus(&tmp, &str, cmd))
					break ;
		}
		tmp.i++;
	}
	return (str);
}
