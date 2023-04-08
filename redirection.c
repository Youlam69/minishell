#include "minishell.h"

char	*joinheredoc(char *av)
{
	char	*hd_content;
	char	*limiter;
	char	*tmp;

	tmp = NULL;
	hd_content = NULL;
	while (1)
	{
		limiter = readline(" > ");
//		tmp = strjoin(av, "\n");
        // printf("[%s][%s]\n", limiter, tmp);
		if (ft_strcmp(av, limiter) != 0) // yaha
		{
			// free(tmp);
			tmp = hd_content;
			hd_content = strjoin(hd_content, limiter);
            free(limiter);
            limiter = hd_content;
            hd_content = strjoin(hd_content, "\n");
			frfr(tmp, limiter);
            limiter = NULL;
            tmp = NULL;
		}
		else
		{
			frfr(tmp, limiter);
			break ;
		}
	}
	return (hd_content);
}

char *check_heredoc(t_list *cmd, char *str)
{
	int		i;
	int		j;
	int		s;
	char *tmp =	NULL;
	char *tmp_2 = NULL;
	char *tmp_3 = NULL;

	i = 0;
	while (str[i])
	{
		j = i + 2;
		if (str[i] == '<' && str[i + 1] == '<')
		{
            //check_<< nno should be error
            s = j;
            while(str[s] && str[s] == ' ')
                s++;
            if (str[s] == '\0' || str[s] == '<' || str[j] == '>')
            {
                // ft_syntax_err();
                printf("syntax error\n");
                free(str);
                return (NULL); ////
            }
            j = s;
			while (str[j] && str[j] != ' ' && str[j] != '<' && str[j] != '>')
				j++;
			if (s < j)
			{

				tmp_3 = ft_substr(str, s, j - s);
                cmd->heredocstr = joinheredoc(tmp_3);
                cmd->fdinout[0] = open("/tmp/justheredoc", O_CREAT | O_WRONLY | O_TRUNC, 777);
                ft_putstr_fd(cmd->heredocstr, cmd->fdinout[0]);
				close(cmd->fdinout[0]);
                cmd->fdinout[0] = open("/tmp/justheredoc", O_RDONLY);

				ft_putstr_fd("here",1);
				printf("|%d|\n", cmd->fdinout[0]);
				
                // close(cmd->fdinout[0]);
                cmd->her_exist = 1;
				tmp = ft_substr(str, 0, i);
				tmp_2 = ft_substr(str, j, ft_strlen(str) - j);
                free(str);
                str = strjoin(tmp, tmp_2);
                free(tmp_2);
				free(tmp_3);
				free(tmp);
                fflush(stdout);
			}
		}
		if(!str[i])
			break;
		i++;
	}
    // exit(0);
	return(str);
}


char *check_redirection_in(t_list *cmd, char *str)
{
	int		i;
	int		j;
	int		s;
	char *tmp =	NULL;
	char *tmp_2 = NULL;
	char *tmp_3 = NULL;


	i = 0;
	while (str[i])
	{
    
		j = i + 1;
		if (str[i] == '<' && str[j] != '<')
		{
            // if (str[j] == '\0')

            //check_<< nno should be error
            s = j;
            while(str[s] && str[s] == ' ')
                s++;
            if (str[s] == '\0' || str[s] == '<' || str[j] == '>')
            {
                // ft_syntax_err();
                printf("syntax error\n");
                free(str);
                return (NULL); ////
                // return (NULL); ////
            }
            j = s;
			while (str[j] != '\0')
            {
				if (str[j] == ' ' || str[j] == '<' || str[j] == '>')
                    break;
                j++;
            }
    
			if (s < j)
			{
				tmp_3 = ft_substr(str, s, j - s);
                cmd->fdinout[0] = open(convet_value(tmp_3), O_RDONLY);
                cmd->her_exist = 0;
				tmp = ft_substr(str, 0, i);
				tmp_2 = ft_substr(str, j, ft_strlen(str) - j);
                free(str);
                if(cmd->fdinout[0] < 0)
                {
                    printf("minishell: %s: No such file or directory\n", tmp);  // khst tkun put str 2 fd
                    str = ft_strdup("");
                    --i; 
                }
                else
                    str = strjoin(tmp, tmp_2);
                free(tmp_2);
				free(tmp_3);
				free(tmp);
				tmp = NULL;
				tmp_2 = NULL;

			}
		}
		i++;
	}
    // exit(0);
	return(str);
}


char *check_redirection_out(t_list *cmd, char *str)
{
	int		i;
	int		j;
	int		s;
	char *tmp =	NULL;
	char *tmp_2 = NULL;
	char *tmp_3 = NULL;


	i = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '>' && str[j] != '>')
		{
            s = j;
            while(str[s] && str[s] == ' ')
                s++;
            if (str[s] == '\0' || str[s] == '<' || str[j] == '>')
            {
                // ft_syntax_err();
                printf("syntax error\n"); //// putsr
                free(str);
                return (NULL); ////
                // return (NULL); ////
            }
            j = s;
			while (str[j] != '\0')
            {
				if (str[j] == ' ' || str[j] == '<' || str[j] == '>')
                    break;
                j++;
            }
    		if (s < j)
			{
				tmp_3 = ft_substr(str, s, j - s);
                cmd->fdinout[1] = open(convet_value(tmp_3), O_CREAT | O_RDWR | O_TRUNC, 0777);
				// close(cmd->fdinout[1]);
				tmp = ft_substr(str, 0, i);
				tmp_2 = ft_substr(str, j, ft_strlen(str) - j);

                free(str);
                if(cmd->fdinout[1] < 0)
                {
                    printf("minishell: %s: Permission denied\n", tmp);  // khst tkun put str 2 fd
                    str = ft_strdup("");
                    --i; 
                }
                else
				{
					
                    str = strjoin(tmp, tmp_2);

				}
                free(tmp_2);
				free(tmp_3);
				free(tmp);
				tmp = NULL;
				tmp_2 = NULL;
			}
		}
		i++;
	}
    // exit(0);
	return(str);
}


char *check_outapend(t_list *cmd, char *str)
{
	int		i;
	int		j;
	int		s;
	char *tmp =	NULL;
	char *tmp_2 = NULL;
	char *tmp_3 = NULL;

	i = 0;
	while (str[i])
	{
		j = i + 2;
		if (str[i] == '>' && str[i + 1] == '>')
		{
            //check_<< nno should be error
            s = j;
            while(str[s] && str[s] == ' ')
                s++;
            if (str[s] == '\0' || str[s] == '<' || str[j] == '>')
            {
                // ft_syntax_err();
                printf("syntax error\n");
                free(str);
                return (NULL); ////
            }
            j = s;
			while (str[j] && str[j] != ' ' && str[j] != '<' && str[j] != '>')
				j++;
			if (s < j)
			{
				tmp_3 = ft_substr(str, s, j - s);
                cmd->fdinout[1] = open(convet_value(tmp_3), O_CREAT | O_RDWR | O_APPEND, 0777);
				tmp = ft_substr(str, 0, i);
				tmp_2 = ft_substr(str, j, ft_strlen(str) - j);

                free(str);
                if(cmd->fdinout[1] < 0)
                {
                    printf("minishell: %s: Permission denied\n", tmp);  // khst tkun put str 2 fd
                    str = ft_strdup("");
                    --i; 
                }
                else
				{
                    str = strjoin(tmp, tmp_2);
				}
                free(tmp_2);
				free(tmp_3);
				free(tmp);
				tmp = NULL;
				tmp_2 = NULL;
			}
		}
		i++;
	}
    // exit(0);
	return(str);
}

