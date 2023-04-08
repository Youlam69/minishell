/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:44:59 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 22:30:57 by ylamraou         ###   ########.fr       */
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

int is_good(char c)
{
	if (is_digit(c) || is_alpha(c))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	valid_var(char c)
{
	if(is_good(c))
		return(1);
	return (0);
}

char *cmp_env(char * str, t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if(!env->var)
			return (NULL);
		if(ft_strcmp(str, env->var) == 0)
			return(env->val);
		env = env->next;
	}
	return (NULL);		
}

char *ft_itoa(int nbr)
{
	char *tab;
	int len, tmp = 0;

	len = (nbr <= 0);
	tmp = nbr;
	while(tmp)
	{
		len++;
		tmp /= 10;
	}
	tab = malloc(sizeof(char) * (len + 1));
	tab[len] = '\0';
	if(nbr < 0)
		tab[0] = '-';
	else if(nbr == 0)
		tab[0] = '0';
	tmp = nbr;
	while(tmp)
	{
		len--;
		tab[len] = tmp % 10 * (nbr < 0 ? -1 : 1) + '0';
		tmp /= 10;
	}
	return (tab);
}

void	dollar_start(char **str, t_data *data, t_rdr *tmp)
{
	tmp->t1 = ft_substr(*str, tmp->i + 1, tmp->j - tmp->i - 1);
	tmp->t2 = cmp_env(tmp->t1, data->env);
	free(tmp->t1);
	tmp->t1 = ft_substr(*str, 0, tmp->i);
	tmp->t3 = ft_substr(*str, tmp->j, ft_strlen(*str) - tmp->j);
	if((*str)[tmp->i + 1] == '\?')
		tmp->t2 = strjoin(tmp->t1, ft_itoa(data->exit_status));
	else
		tmp->t2 = strjoin(tmp->t1, tmp->t2);
	free(*str);
	tmp->j = ft_strlen(tmp->t2);
	free(tmp->t1);
	tmp->t1 = NULL;
	*str = strjoin(tmp->t2, tmp->t3);
	free(tmp->t2);
	tmp->t2 = NULL;
	free(tmp->t3);
	tmp->t3 = NULL;
}

char	*check_dollars(char *str, t_data *data)
{
	t_rdr	tmp;

	reset_rdr(&tmp);
	while (str[tmp.i])
	{
		tmp.j = tmp.i + 1;
		if (str[tmp.i] == '$')
		{
			if (str[tmp.j] == DQ || str[tmp.j] == SQ || str[tmp.j] == '\?')
				tmp.j++;
			else
				while (str[tmp.j] && valid_var(str[tmp.j]))
					tmp.j++;
			if (tmp.i < tmp.j - 1)
				dollar_start(&str, data, &tmp);
		}
		tmp.i = tmp.j;
	}
	return (str);
}


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

