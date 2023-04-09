/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:34:18 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 01:15:59 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	joinheredoc(char *av)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	while (1)
	{
		line = readline("herdoc >");
		if (!line)
			break ;
		if (!ft_strcmp(av, line))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}

void	nnn(t_rdr *tmp, char **str, t_list *cmd)
{
	tmp->t3 = ft_substr(*str, tmp->s, tmp->j - tmp->s);
	cmd->fdinout[0] = joinheredoc(tmp->t3);
	cmd->her_exist = 1;
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t2 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
	free(*str);
	*str = strjoin(tmp->t1, tmp->t2);
	free(tmp->t2);
	free(tmp->t3);
	free(tmp->t1);
}

void	reset_rdr(t_rdr *tmp)
{
	tmp->i = 0;
	tmp->j = 0;
	tmp->s = 0;
	tmp->t1 = NULL;
	tmp->t2 = NULL;
	tmp->t3 = NULL;
}

char	*check_heredoc(t_list *cmd, char *str)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 2;
		if (str[tmp.i] == '<' && str[tmp.i + 1] == '<')
		{
			tmp.s = tmp.j;
			while (str[tmp.s] && str[tmp.s] == ' ')
				tmp.s++;
			if (str[tmp.s] == '\0' || str[tmp.s] == '<' || str[tmp.j] == '>')
				if (!tt(str))
					return (NULL);
			tmp.j = tmp.s;
			while (str[tmp.j] && str[tmp.j] != ' ' && str[tmp.j]
				!= '<' && str[tmp.j] != '>')
				tmp.j++;
			if (tmp.s < tmp.j)
				nnn(&tmp, &str, cmd);
		}
		tmp.i++;
	}
	return (str);
}

int	tt(char *str)
{
	printf("syntax error\n");
	free(str);
	return (0);
}
