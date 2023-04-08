#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((i < n )&& s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
}

void	free_unset(t_env **env, t_env *tmp_env)
{
	if (tmp_env->next)
	{
		*env = tmp_env->next;
		frfr(tmp_env->var, tmp_env->val);
		free(tmp_env);
	}
	else
	{
		frfr(tmp_env->var, tmp_env->val);
		free(tmp_env);
		*env = NULL;
	}
}

void	unset_var(t_env **env, char *var)
{
	t_env	*tmp_env;
	t_env	*prev;

	tmp_env = *env;
	prev = NULL;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->var, var) == 0)
		{
			if (prev)
			{
				prev->next = tmp_env->next;
				frfr(tmp_env->var, tmp_env->val);
				free(tmp_env);
			}
			else
				free_unset(env, tmp_env);
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
}

void	ft_putstr_3d(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str1)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	if (str4)
		ft_putstr_fd(str4, 2);
	ft_putstr_fd("\n", 2);
}

void	unset(t_data *data, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j] && is_good(cmd[i][j]))
			j++;
		if (cmd[i][j])
		{
			ft_putstr_3d("minishell: unset: `",cmd[i], "': not a valid identifier", NULL);
			data->exit_status = 1;
			continue ;
		}
		unset_var(&data->env, cmd[i]);
	}
	data->exit_status = 0;
}


int	check_implmnt(t_data *data)
{
	t_list *cmd = data->cmd;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return(1);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return(2);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return(3);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return(4);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return(5);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return(6);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return(7);
	return (0);
}

void env(t_env *env)
{
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
	exit(0);
}

void	pwd(char *pwd)
{
	printf("%s\n", pwd);
}

// int	chdir_anex(t_data *data, char ** cmd)
// {
// 	if (!cmd[1])
// 		chdir("/home");
// 	else if (cmd[2])
// 	{
// 		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
// 		data->exit_status = 1;
// 		return (1);
// 	}
// 	else if (chdir(cmd[1]) < 0)
// 	{
// 		ft_putstr_fd("Minishell : ", 2);
// 		perror(cmd[1]);
// 		data->exit_status = 1;
// 		return (1);
// 	}
// 	return (0);
// }

// void cd(t_data *data)
// {
// 	char	*tmp;
// 	char	**cmd;

// 	cmd = data->cmd->cmd;
// 	if (chdir_anex(data, cmd))
// 		return ;
// 	tmp = getcwd(NULL, 0);
// 	if (!tmp)
// 	{
// 		ft_putstr_fd("cd: error retrieving current directory: \
// 			getcwd: cannot access parent directories: No such file \
// 			or directory\n", 2);
// 		return ;
// 	}
// 	else
// 	{
// 		free(data->pwd);
// 		data->pwd = tmp;
// 	}
// 	data->exit_status = 0;
// }

void	echo(char **cmd)
{
	int	i;
	int	j;
	int	del_nl;

	i = 1;
	del_nl = 0;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j])
			break ;
		del_nl = 1;
		i++;
	}
	while (cmd[i] && cmd[i + 1])
		printf("%s ", cmd[i++]);
	if (cmd[i])
		printf("%s", cmd[i]);
	if (!del_nl)
		printf("\n");
}
