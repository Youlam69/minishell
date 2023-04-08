// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   backup_redirection.c                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/04/08 11:08:09 by ylamraou          #+#    #+#             */
// /*   Updated: 2023/04/08 22:32:26 by ylamraou         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

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
// 		if (ft_strcmp(av, limiter) != 0)
// 		{
// 			tmp = hd_content;
// 			hd_content = strjoin(hd_content, limiter);
// 			free(limiter);
// 			limiter = hd_content;
// 			hd_content = strjoin(hd_content, "\n");
// 			frfr(tmp, limiter);
// 			limiter = NULL;
// 			tmp = NULL;
// 		}
// 		else
// 		{
// 			frfr(tmp, limiter);
// 			break ;
// 		}
// 	}
// 	return (hd_content);
// }

// char	*anex_hedoc(int *tab, char *str, t_list *cmd)
// {
// 	char	*tmp;
// 	char	*tmp_2;
// 	char	*tmp_3;

// 	tmp_3 = ft_substr(str, tab[2], tab[1] - tab[2]);
// 	cmd->heredocstr = joinheredoc(tmp_3);
// 	cmd->fdinout[0] = open("/tmp/justheredoc", O_CREAT | O_WRONLY | O_TRUNC, 777);
// 	ft_putstr_fd(cmd->heredocstr, cmd->fdinout[0]);
// 	close(cmd->fdinout[0]);
// 	cmd->fdinout[0] = open("/tmp/justheredoc", O_RDONLY);
// 	cmd->her_exist = 1;
// 	tmp = ft_substr(str, 0, tab[0]);
// 	tmp_2 = ft_substr(str, tab[1], ft_strlen(str) - tab[1]);
// 	free(str);
// 	str = strjoin(tmp, tmp_2);
// 	free(tmp_2);
// 	free(tmp_3);
// 	free(tmp);
// 	return (str);
// }

// char	*check_heredoc(t_list *cmd, char *str)
// {
// 	int		*all;

// 	all = malloc(sizeof(int) * 3);
// 	all[0] = 0;
// 	while (str[all[0]])
// 	{
// 		all[1] = all[0] + 2;
// 		if (str[all[0]] == '>' && str[all[0] + 1] == '>')
// 		{
// 			all[2] = all[1];
// 			all[2] = check_error_and_space_reinout(str, all[2]);
// 			if (all[1] == -1)
// 			{
// 				free(str);
// 				return (NULL);
// 			}
// 			all[1] = all[2];
// 			all[1] = check_name_reinout(str, all[1]);
// 			if (all[2] < all[1])
// 			str = anex_hedoc(all, str, cmd);
// 		}
// 		all[0]++;
// 	}
// 	free(all);
// 	return (str);
// }

// char *anex_inf(int *tab, char *str, t_list *cmd)
// {
// 	char	*tmp;
// 	char	*tmp_2;
// 	char	*tmp_3;

// 	tmp_3 = ft_substr(str, tab[2], tab[1] - tab[2]);
// 	cmd->fdinout[0] = open(convet_value(tmp_3), O_RDONLY);
// 	cmd->her_exist = 0;
// 	tmp = ft_substr(str, 0, tab[0]);
// 	tmp_2 = ft_substr(str, tab[1], ft_strlen(str) - tab[1]);
// 	free(str);
// 	if (cmd->fdinout[1] < 0)
// 	{
// 		printf("minishell: %s: Permission denied\n", tmp);
// 		free(str);
// 		str = ft_strdup("");
// 		tab[0]--;
// 	}
// 	else
// 		str = strjoin(tmp, tmp_2);
// 	free(tmp_2);
// 	free(tmp_3);
// 	free(tmp);
// 	return (str);
// }


// char	*check_redirection_in(t_list *cmd, char *str)
// {
// 	int		*all;

// 	all = malloc(sizeof(int) * 3);
// 	all[0] = 0;
// 	while (str[all[0]])
// 	{
// 		all[1] = all[0] + 1;
// 		if (str[all[0]] == '<' && str[all[1]] != '<')
// 		{
// 			all[2] = all[1];
// 			all[2] = check_error_and_space_reinout(str, all[2]);
// 			if (all[1] == -1)
// 			{
// 				free(str);
// 				return (NULL);
// 			}
// 			all[1] = all[2];
// 			all[1] = check_name_reinout(str, all[1]);
// 			if (all[2] < all[1])
// 				str = anex_inf(all, str, cmd);
// 		}
// 		all[0]++;
// 	}
// 	free(all);
// 	return (str);
// }

// char	*anex_o_trunc(int *tab, char *str, t_list *cmd)
// {
// 	char	*tmp;
// 	char	*tmp_2;
// 	char	*tmp_3;

// 	tmp_3 = ft_substr(str, tab[2], tab[1] - tab[2]);
// 	cmd->fdinout[1] = open(convet_value(tmp_3), O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	tmp = ft_substr(str, 0, tab[0]);
// 	tmp_2 = ft_substr(str, tab[1], ft_strlen(str) - tab[1]);
// 	free(str);
// 	if (cmd->fdinout[1] < 0)
// 	{
// 		printf("minishell: %s: Permission denied\n", tmp);
// 		free(str);
// 		str = ft_strdup("");
// 		tab[0]--;
// 	}
// 	else
// 		str = strjoin(tmp, tmp_2);
// 	free(tmp_2);
// 	free(tmp_3);
// 	free(tmp);
// 	return (str);
// }

// char	*check_redirection_out(t_list *cmd, char *str)
// {
// 	int		*all;

// 	all = malloc(sizeof(int) * 3);
// 	all[0] = 0;
// 	while (str[all[0]])
// 	{
// 		all[1] = all[0] + 1;
// 		if (str[all[0]] == '>' && str[all[1]] != '>')
// 		{
// 			all[2] = all[1];
// 			all[2] = check_error_and_space_reinout(str, all[2]);
// 			if (all[1] == -1)
// 			{
// 				free(all);
// 				return (NULL);
// 			}
// 			all[1] = all[2];
// 			all[1] = check_name_reinout(str, all[1]);
// 			if (all[2] < all[1])
// 				str = anex_o_trunc(all, str, cmd);
// 		}
// 		all[0]++;
// 	}
// 	free(all);
// 	return (str);
// }

// char	*anex_apend(int *tab, char *str, t_list *cmd)
// {
// 	char	*tmp;
// 	char	*tmp_2;
// 	char	*tmp_3;

// 	tmp_3 = ft_substr(str, tab[2], tab[1] - tab[2]);
// 	cmd->fdinout[1] = open(convet_value(tmp_3), \
// 		O_CREAT | O_RDWR | O_APPEND, 0777);
// 	tmp = ft_substr(str, 0, tab[0]);
// 	tmp_2 = ft_substr(str, tab[1], ft_strlen(str) - tab[1]);
// 	free(str);
// 	if (cmd->fdinout[1] < 0)
// 	{
// 		printf("minishell: %s: Permission denied\n", tmp);
// 		free(str);
// 		str = ft_strdup("");
// 		tab[0]--;
// 	}
// 	else
// 		str = strjoin(tmp, tmp_2);
// 	free(tmp_2);
// 	free(tmp_3);
// 	free(tmp);
// 	return (str);
// }

// int	check_error_and_space_reinout(char *str, int s)
// {
// 	while (str[s] && str[s] == ' ')
// 		s++;
// 	if (str[s] == '\0' || str[s] == '<' || str[s] == '>')
// 	{
// 		printf("syntax error\n");
// 		free(str);
// 		return (-1);
// 	}
// 	return (s);
// }

// int	check_name_reinout(char *str, int j)
// {
// 	while (str[j] && str[j] != ' ' && str[j] != '<' && str[j] != '>')
// 				j++;
// 	return (j);
// }

// char	*check_outapend(t_list *cmd, char *str)
// {
// 	int		*all;

// 	all = malloc(sizeof(int) * 3);
// 	all[0] = 0;
// 	while (str[all[0]])
// 	{
// 		all[1] = all[0] + 2;
// 		if (str[all[0]] == '>' && str[all[0] + 1] == '>')
// 		{
// 			all[2] = all[1];
// 			all[2] = check_error_and_space_reinout(str, all[2]);
// 			if (all[1] == -1)
// 			{
// 				free(str);
// 				return (NULL);
// 			}
// 			all[1] = all[2];
// 			all[1] = check_name_reinout(str, all[1]);
// 			if (all[2] < all[1])
// 				str = anex_apend(all, str, cmd);
// 		}
// 		all[0]++;
// 	}
// 	free(all);
// 	return (str);
// }

