/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:44:59 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 09:25:58 by ylamraou         ###   ########.fr       */
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

// int	ft_strcmp(char *s1, char *s2)
// {
// 	unsigned char	*c1;
// 	unsigned char	*c2;

// 	c1 = (unsigned char *)s1;
// 	c2 = (unsigned char *)s2;
// 	while ((*c1 || *c2))
// 	{
// 		if (*c1 != *c2)
// 			return (*c1 - *c2);
// 		c1++;
// 		c2++;
// 	}
// 	return (0);
// }

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

char	*check_dollars(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;

	tmp = NULL;
	tmp_2 = NULL;
	tmp_3 = NULL;
	i = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '$')
		{
			if (str[j] == DQ || str[j] == SQ || str[j] == '\?')
				j++;
			else
				while (str[j] && valid_var(str[j]))
					j++;
			if (i < j - 1)
			{
				tmp = ft_substr(str, i + 1, j - i - 1);
				tmp_2 = cmp_env(tmp, data->env);
				free(tmp);
				tmp = ft_substr(str, 0, i);
				tmp_3 = ft_substr(str, j, ft_strlen(str) - j);
				if(str[i + 1] == '\?')
					tmp_2 = strjoin(tmp, ft_itoa(data->exit_status));
				else
					tmp_2 = strjoin(tmp, tmp_2);
				free(str);
				j = ft_strlen(tmp_2);
				free(tmp);
				tmp = NULL;
				str = strjoin(tmp_2, tmp_3);
				free(tmp_2);
				tmp_2 = NULL;
				free(tmp_3);
				tmp_3 = NULL;
			}
		}
		// fflush(stdout);
		i = j;
	}
	
	return (str);
}


char	*convet_value(char *str)
{
	int	j;

	j = -1;
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

t_list	*parsing(char *str, t_data *data)
{
	t_list	*ptr;

	str = check_q(str, data);
	if (!str)
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
	return (ptr);
}

