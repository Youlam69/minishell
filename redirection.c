/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:34:18 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 22:04:43 by ylamraou         ###   ########.fr       */
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

char *check_heredoc(t_list *cmd, char *str)
{
	t_rdr tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 2;
		if (str[tmp.i] == '<' && str[tmp.i + 1] == '<')
		{
            tmp.s = tmp.j;
            while(str[tmp.s] && str[tmp.s] == ' ')
                tmp.s++;
            if (str[tmp.s] == '\0' || str[tmp.s] == '<' || str[tmp.j] == '>')
				if (!tt(str))
					return (NULL);
            tmp.j = tmp.s;
			while (str[tmp.j] && str[tmp.j] != ' ' && str[tmp.j] != '<' && str[tmp.j] != '>')
				tmp.j++;
			if (tmp.s < tmp.j)
				nnn(&tmp, &str, cmd);
		}
		tmp.i++;
	}
	return(str);
}

int tt(char *str) {
	printf("syntax error\n");
	free(str);
	return (0);
}

int ss(char *str, int *s, int *j) {
	while(str[*s] && str[*s] == ' ')
                (*s)++;
	if (str[*s] == '\0' || str[*s] == '<' || str[*j] == '>')
				return tt(str);
	*j = *s;
	while (str[*j] != '\0')
	{
		if (str[*j] == ' ' || str[*j] == '<' || str[*j] == '>')
			break;
		(*j)++;
	}
	return (*s);
}

int nn(t_rdr *tmp, t_list *cmd, char **str) {
	tmp->t3 = ft_substr(*str, tmp->s, tmp->j - tmp->s);		
	if(cmd->fdinout[0] > 0)
		close(cmd->fdinout[0]);
	cmd->fdinout[0] = open(convet_value(tmp->t3), O_RDONLY);
	cmd->her_exist = 0;
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t2 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
	free(*str);
	if(cmd->fdinout[0] < 0)
	{
		ft_putstr_3d("minishell: ", tmp->t1, ": No such file or directory\n", NULL);  // khst tkun put str 2 fd
		*str = ft_strdup("");
		--tmp->i;
		return 0;
	}
	else
		*str = ft_strjoin(tmp->t1, tmp->t2);
	free(tmp->t1);
	free(tmp->t3);
	free(tmp->t2);
	return 1;
} 


char *check_redirection_in(t_list *cmd, char *str)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
    
		tmp.j = tmp.i + 1;
		if (str[tmp.i] == '<' && str[tmp.j] != '<')
		{
            tmp.s = tmp.j;
            tmp.s = ss(str, &tmp.s, &tmp.j);
			if (!tmp.s)
				return NULL;
    
			if (tmp.s < tmp.j)
				if (!nn(&tmp, cmd, &str))
					break;
		}
		tmp.i++;
	}
	return(str);
}

int	redir_assist(t_rdr *tmp, t_list *cmd, char **str)
{
	tmp->t3 = ft_substr(*str, tmp->s, tmp->j - tmp->s);
    cmd->fdinout[1] = open(convet_value(tmp->t3), O_CREAT | O_RDWR | O_TRUNC, 0644);
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t2 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
    free(*str);
    if(cmd->fdinout[1] < 0)
    {
        printf("minishell: %s: Permission denied\n", tmp->t1);  // khst tkun put str 2 fd
        *str = ft_strdup("");
        --tmp->i;
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

void	loop_over_j(char *str, t_rdr *tmp)
{
	while (str[tmp->j] != '\0')
    {
		if (str[tmp->j] == ' ' || str[tmp->j] == '<' || str[tmp->j] == '>')
            break;
        tmp->j++;
    }
}

char *check_redirection_out(t_list *cmd, char *str)
{
	t_rdr tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 1;
		if (str[tmp.i] == '>' && str[tmp.j] != '>')
		{
            tmp.s = tmp.j;
            while(str[tmp.s] && str[tmp.s] == ' ')
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
	return(str);
}


int	outapent_plus(t_rdr *tmp, char **str, t_list *cmd)
{
	tmp->t3 = ft_substr(*str, tmp->s, tmp->j - tmp->s);
    cmd->fdinout[1] = open(convet_value(tmp->t3), O_CREAT | O_RDWR | O_APPEND, 0644);
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t2 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
    free(*str);
    if(cmd->fdinout[1] < 0)
    {
        printf("minishell: %s: Permission denied\n", tmp->t1);  // khst tkun put str 2 fd
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

char *check_outapend(t_list *cmd, char *str)
{
	t_rdr tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 2;
		if (str[tmp.i] == '>' && str[tmp.i + 1] == '>')
		{
            tmp.s = tmp.j;
            while(str[tmp.s] && str[tmp.s] == ' ')
                tmp.s++;
            if (str[tmp.s] == '\0' || str[tmp.s] == '<' || str[tmp.j] == '>')
				if (!tt(str))
					return (NULL);
            tmp.j = tmp.s;
			while (str[tmp.j] && str[tmp.j] != ' ' && str[tmp.j] != '<' && str[tmp.j] != '>')
				tmp.j++;
			if (tmp.s < tmp.j)
				if (!outapent_plus(&tmp, &str, cmd))
					break ;
		}
		tmp.i++;
	}
	return(str);
}
