/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:34:18 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 19:53:46 by ylamraou         ###   ########.fr       */
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
// char	*joinheredoc(char *av)
// {
// 	char	*hd_content;
// 	char	*limiter;
// 	char	*tmp;

// 	tmp = NULL;
// 	hd_content = NULL;
// 	while (1)
// 	{
// 		limiter = readline(" > ");
// //		tmp = strjoin(av, "\n");
//         // printf("[%s][%s]\n", limiter, tmp);
// 		if (ft_strcmp(av, limiter) != 0) // yaha
// 		{
// 			// free(tmp);
// 			tmp = hd_content;
// 			hd_content = strjoin(hd_content, limiter);
//             free(limiter);
//             limiter = hd_content;
//             hd_content = strjoin(hd_content, "\n");
// 			frfr(tmp, limiter);
//             limiter = NULL;
//             tmp = NULL;
// 		}
// 		else
// 		{
// 			frfr(tmp, limiter);
// 			break ;
// 		}
// 	}
// 	return (hd_content);
// }

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
                // cmd->heredocstr = joinheredoc(tmp_3);
				cmd->fdinout[0] = joinheredoc(tmp_3);
                // cmd->fdinout[0] = open("/tmp/justheredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
                // ft_putstr_fd(cmd->heredocstr, cmd->fdinout[1]);
                // close(cmd->fdinout);
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
		i++;
	}
    // exit(0);
	return(str);
}

void *tt(char *str) {
	printf("syntax error\n");
                free(str);
                return (NULL);
}

int ss(char *str, int s) {
	while(str[s] && str[s] == ' ')
                s++;
	return s;
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
            s = j;
            s = ss(str, s);
            if (str[s] == '\0' || str[s] == '<' || str[j] == '>')
				return tt(str);
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
				if(cmd->fdinout[0] > 0)
					close(cmd->fdinout[0]);
				
                
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
                cmd->fdinout[1] = open(convet_value(tmp_3), O_CREAT | O_RDWR | O_TRUNC, 0644);
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
                cmd->fdinout[1] = open(convet_value(tmp_3), O_CREAT | O_RDWR | O_APPEND, 0644);
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

// void check_redirection_heredoc(t_list *cmd, char *tab)
// {

//     int i;
//     int j;

//     i = 0;
//     j = 0;
    
//     char *fdname;
//     char *str;

//     while (str[i])
//     {
//         if (str[i] == '<' && str[i + 1] != '<')
//         {
//             j = i + 1;
//             if(!str[i + 1])
//             {
//                 if(cmd->next)
//                 ft_syntax_err();
//                 return;

//             }
//             if(str[i + 2] == '<')
//             {
//                 ft_syntax_err();
//                 exit_status = 2;
//                 // ft_syntax_err(data);
//                 // ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
//                 return;
//             }
//             while (str[j] == ' ')
//                 j++;
//             i = j;
//             while (str[j] &&  str[j] != ' ' && str[j] != '<')
//                 j++;
//             t
//             if (str[j] == '\0')
//             {
//                 ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
//                 return (NULL);
//             }
//             while (str[j] == ' ')
//                 j++;
//             if (str[j] == '\0')
//             {
//                 ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
//                 return (NULL);
//             }
//             while (str[j] != ' ' && str[j] != '\0')
//                 j++;
//             if (str[j] != '\0')
//             {
//                 ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
//                 return (NULL);
//             }
//         }
//         i++;
//     }
    

// }