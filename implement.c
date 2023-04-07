#include "minishell.h"

int ft_strncmp(char *s1, char *s2, int n)
{
	int i;

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
void ft_putstr_fd(char *str, int fd)
{
	int i = -1;
	if(!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
}

// void	check_implmnt(t_data *data)
// {
// 	t_list *cmd = data->cmd;
// 	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
// 		echo(cmd->cmd);
// 	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
// 		cd(data);
// 	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
// 		pwd(data->pwd);
// 	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
// 		export(data->env, cmd->cmd);
// 	// else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
// 	// 	unset(data, &cmd->cmd[1], child);
// 	// else if (ft_strcmp(cmd->cmd[0], "env") == 0)
// 	// 	env(data->env);
// 	// else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
// 	// 	ft_exit(data, &cmd->cmd[1], &data->exit_status);
// }


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
				free(tmp_env->var);
				free(tmp_env->val);
				free(tmp_env);
			}
			else
			{
				if (tmp_env->next)
				{

					*env = tmp_env->next;
					free(tmp_env->var);
					free(tmp_env->val);
					free(tmp_env);
					// *env = NULL;

				}
				else
				{
					free(tmp_env->var);
					free(tmp_env->val);
					free(tmp_env);
					*env = NULL;
				}
			}
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
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
			ft_putstr_fd("minishell: unset: `",2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier",2);
			ft_putstr_fd("\n",2);
			data->exit_status = 1;
			continue ;
		}
		unset_var(&data->env, cmd[i]);
	}
	data->exit_status = 0;
	// if (child)
	// 	exit(0);
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

void pwd(char *pwd)
{
	printf("%s\n", pwd);
}

void cd(t_data *data)
{
	char *tmp;
	char **cmd;

	cmd = data->cmd->cmd;
	if (!cmd[1])
		chdir("/home");
		// chdir(data->home);
	else if (cmd[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		data->exit_status = 1;
		// exit(1);
		return;
	}
	else if (chdir(cmd[1]) < 0)
	{
		ft_putstr_fd("Minishell : ", 2);
		perror(cmd[1]);	
		data->exit_status = 1;
		return;
	}
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_putstr_fd("cd: error retrieving current directory: \
			getcwd: cannot access parent directories: No such file \
			or directory\n", 2);
		return;
	}
	else
	{
		free(data->pwd);
		data->pwd = tmp;
	}
	data->exit_status = 0;
}

void echo(char **cmd)
{
	int i;
	int j;
	int del_nl;

	i = 1;
	del_nl = 0;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j])
			break;
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