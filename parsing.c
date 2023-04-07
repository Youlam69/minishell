
#include "minishell.h"


char    *check_dq(char *str, t_data *data)
{
	int i;
	int q;
	int dq;

	dq = 0;
	q = 0;
	i = -1;
	while (str[++i])
	{
		if(is_q(str[i]) && (dq % 2) == 0)
			q++;
		else if (is_dq(str[i]) && (q % 2) == 0)
			dq++;
		if(((dq % 2) != 0) && (is_special(str[i]) || is_q(str[i])))
			str[i] *= -1;
	}
	if((dq % 2) != 0)
	{
		ft_syntax_err(data); // free str should be free free
		free(str);
		return NULL;
	}
	return(str);
}


char    *check_q(char *str, t_data *data)
{
	int i;
	int q;
	int dq;

	dq = 0;
	i = -1;
	q = 0;
	while (str[++i])
	{
		if(is_dq(str[i]) && (q % 2) == 0)
			dq++;
		else if (is_q(str[i]) && (dq % 2) == 0)
			q++;
		if(((q % 2) != 0) && (is_special(str[i]) || is_dq(str[i]) || is_dlr(str[i])))
			str[i] *= -1;
	}
	if((q % 2) != 0)
	{
		ft_syntax_err(data); // free str should be free free
		free(str);
		return NULL;
	}
	
	return(str);
}

char *check_d_pip(char *str, t_data *data)
{
	int i;
	int j;
	i = 0;
	while (str[i])
	{
		j = i + 1;
		if(str[i] == '|') // not working
		{
			while(str[j] && str[j] == ' ')
				j++;
			if(str[j] == '|')
			{
				ft_syntax_err(data); // free str should be free free
				free(str);
				return NULL;
			}
		}
		i = j;
	}
	if(str[0] == '|' || str[i - 1] == '|')
	{
		ft_syntax_err(data); // free str should be free free
		free(str);
		return NULL;
	}
	
	return(str);
}


int	ft_cmd(t_list *tmp)
{
	// t_list *tmp;
	
	// tmp = ptr;
	// int i = 1;
	while (tmp)
	{
		tmp->fdinout[0] = 0;
		tmp->fdinout[1] = 1;
		tmp->her_exist = 0;
		tmp->content = check_heredoc(tmp, tmp->content);
		if(!tmp->content)
			return -1;
		tmp->content = check_outapend(tmp, tmp->content);
		if(!tmp->content)
			return -1; 
		tmp->content = check_redirection_in(tmp, tmp->content);
		if(!tmp->content)
			return -1;
		tmp->content =check_redirection_out(tmp, tmp->content);
		if(!tmp->content)
			return -1;
		// printf("-----------------------------------------------------\n");
		// printf("lmra %d fd man mora : -%d-\n", i++, tmp->fdinout[0]);
		// printf("content man mora : -%s-\n", tmp->content);
		// printf("-----------------------------------------------------\n");

		// fflush(stdout);
		if(!tmp->content)
			return -1;
		tmp->cmd = ft_split(tmp->content, ' ');
		// printf(" mora split awal cmnd : -%s-\n", tmp->cmd[0]);

		// free(tmp->content);
		// tmp->content = NULL;
		tmp = tmp->next;
	}
	return 0;
}

// void	joinpath(t_list *cmd)
// {
// 	int		i;
// 	int		j;
// 	// char	*tmp;
// 	t_list *cmd = data->cmd;

// 	j = -1;
// 	while (++j < data->nbrcmd && cmd[j].cmd[0])
// 	{
// 		i = -1;
// 		while (cmd->splitedp[++i])
// 		{
// 			// tmp = ft_strjoin(cmd->splitedp[i], "/"); // doese not meter shoud
// 			cmd[j].cmdp = ft_strjoin(cmd->splitedp[i], (cmd[j].cmd[0]));
// 			// free(tmp);
// 			if (accs(cmd[j].cmdp) == 0)
// 				break ;
// 			free(cmd[j].cmdp);
// 		}
// 		if (!cmd->splitedp[i])
// 			cmd[j].cmdp = strdup(cmd[j].cmd[0]);

// 		data->cmnd;
// 	}
// }

// void init_data(t_list *cmd)
// {
// 	while(cmd)
// 	{
// 		cmd->cmdp = 
// 		cmd = cmd->next;
// 	}
// }


// int	accs(char *path)
// {
// 	if (access(path, F_OK))
// 		return (1);
// 	if (open(path, O_DIRECTORY) < 0)
// 	{
// 		if (!(access(path, X_OK)))
// 			return (0);
// 		else
// 			return (2);
// 	}
// 	return (3);
// }


// void	joinpath(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	// char	*tmp;
// 	t_list *cmd = data->cmd;

// 	j = -1;
// 	while (cmd && cmd->cmd && cmd->cmd[0])
// 	{
// 		i = -1;
// 		while (data->splitedp[++i])
// 		{
// 			// tmp = ft_strjoin(cmd->splitedp[i], "/"); // doese not meter shoud
// 			cmd->cmdp = strjoin(data->splitedp[i], cmd->cmd[0]);
// 			// free(tmp);
// 			if (accs(cmd->cmdp) == 0)
// 				break ;
// 			free(cmd->cmdp);
// 		}
// 		if (!data->splitedp[i])
// 			cmd->cmdp = strdup(cmd->cmd[0]);
// 		cmd =  cmd->next;
// 	}
// }


void	change_nl_tabs_to_space(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if(str[i] == '\n' || str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}


int is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

int is_alpha(char c)
{
	if (c <= 'z' && c >= 'a')
		return(1);
	else if (c <= 'Z' && c >= 'A')
		return(1);
	return(0);
}

int is_good(char c)
{
	if (is_digit(c) || is_alpha(c))
		return (1);
	else if (c == '_')
		return(1);
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

char *check_dollars(char *str, t_data *data)
{
	int		i;
	int		j;
	char *tmp =	NULL;
	char *tmp_2 = NULL;
	char *tmp_3 = NULL;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '$')
		{
			if (str[j] == DQ || str[j] == SQ || str[j] == '\?')
				j++;
			else
				while (str[j] && valid_var(str[j]) )
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
				// printf("str hia = %s\n", str);
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
	
	return(str);
}

// int check_heredoc_from

// t_list *check_redirection_heredoc(t_data *data)
// {
// 	t_list *cmd;
// 	t_list *tmp;
// 	int i;

// 	cmd = data->cmd;
// 	tmp = NULL;
// 	int i;
// 	int j;

// 	while(cmd)
// 	{
// 		i = -1;
// 		while(cmd->cmd[++i])
// 		{
			

// 		}
// 		cmd = cmd->next;
// 	}

// }

char *convet_value(char *str)
{
	int j;

	j = -1;
	while (str[++j])
	{
		if (str[j] < 0)
		{
			if( str[j] == -127)
				str[j] = '\0';
			else
				str[j] *= -1;
		}
	}
	return str;
}

void value_positif(t_list *cmd)
{
	int i;

	while(cmd)
	{
		i = -1;
		while(cmd->cmd[++i])
			convet_value(cmd->cmd[i]);
		cmd = cmd->next;
	}
}

t_list *parsing(char *str, t_data *data)
{
	t_list *ptr;

	str = check_q(str,data);
	if(!str)
		return NULL;
	str = check_dq(str, data);
	if(!str)
		return NULL;

	change_nl_tabs_to_space(str);
	str = ft_strtrim(str, " ");
	if(!str)
		return NULL;
	// printf("str = {%s}\n", str);
	str = check_d_pip(str, data);
	if(!str)
		return NULL;
	// (void)data;
	str = check_dollars(str, data);
	if (!str)
		return NULL;
	// exit(5);
	str = check_attched_quoets(str);

    str = ft_del_qs(str);
	if(!str)
		return NULL;

	ptr = my_token(str);
	// t_list *tmp = ptr;
	// while(tmp)
	// {
	// 		search_herdoc_and_redirection(tmp, tmp->content);

	// 	tmp = tmp->next;
	// }
	
	////
	// ptr = management_dollar(ptr, env);

	// while (ptr)
	// {
	// 	// while(*ptr->cmd)
	// 	// {
	// 	    printf("in{%d}\n", ptr->fdinout[0]);
	// 	    printf("out{%d}\n", ptr->fdinout[1]);
	// 	//     ptr->cmd++;
	// 	// }
	// 	ptr = ptr->next;
	// }
	// exit(5)	;
	if(ft_cmd(ptr))
		return NULL;

		// ptr = convert(ptr);
	
	
	
	return (ptr);
}