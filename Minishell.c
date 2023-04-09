/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:58:40 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 00:00:31 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hendl_ctr_c(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**take_envc(t_env *env)
{
	char	**envc;
	int		i;
	int		len;
	char	*tmp;

	tmp = NULL;
	i = 0;
	len = ft_size_env(env);
	envc = malloc(sizeof(char *) * len + 1);
	if (!envc)
		return (NULL);
	envc[len] = NULL;
	i = 0;
	while (env)
	{
		if (!env->print_env)
		{
			tmp = strjoin(env->var, "=");
			envc[i] = strjoin(tmp, env->val);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	return (envc[i] = NULL, envc);
}

void	start_mini(t_data *data, char *str, char *tmp, char **env)
{
	init_data(data);
	data->env = ft_envar(env);
	data->pwd = getcwd(NULL, 0);
	while (2)
	{
		signal(SIGINT, hendl_ctr_c);
		signal(SIGQUIT, SIG_IGN);
		data->envc = take_envc(data->env);
		data->splitedp = splitpath(data->env);
		tmp = strjoin(data->pwd, " ~> ");
		str = readline(tmp);
		free(tmp);
		if (!str)
			free_all_exit(data, 1);
		add_history(str);
		data->cmd = parsing(str, data);
		if (!data->cmd)
			continue ;
		joinpath(data);
		data->nbrcmd = ft_lstsize(data->cmd);
		tofork(data, 0);
		free_all_exit(data, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void) av;
	if (ac != 1)
		return (printf("Minishell not take args \n "));
	start_mini(&data, NULL, NULL, env);
	return (0);
}
