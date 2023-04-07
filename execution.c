#include "minishell.h"

char	**splitpath(t_env *ev)
{
	char	*path;
	t_env	*env;
	char	**splited;
	int		i;

	i = 0;
	while (env)
	{
		// path = ft_strnstr(env[i], "PATH=", 5);
		if (!strcmp(env->var, "PATH"))
		{
			path = env->val; // should just break
			break ;
		}
		env = env->next;
	}
	if (!env)
		return NULL;
	splited = ft_split(path, ':'); //shouled take env->val
	free(path);
	i = 0;
	while(splited[i])
	{
		path = splited[i];
		splited[i] = strjoin(path, splited[i]);
		free(path);
		path = NULL;
		i++;
	}
	return (splited);
}

void	joinpath(t_cp *cmd)
{
	int		i;
	int		j;
	// char	*tmp;
	t_list *cmd = data->cmd;

	j = -1;
	while (++j < data->nbrcmd && cmd[j].cmd[0])
	{
		i = -1;
		while (cmd->splitedp[++i])
		{
			// tmp = ft_strjoin(cmd->splitedp[i], "/"); // doese not meter shoud
			cmd[j].cmdp = ft_strjoin(cmd->splitedp[i], (cmd[j].cmd[0]));
			// free(tmp);
			if (accs(cmd[j].cmdp) == 0)
				break ;
			free(cmd[j].cmdp);
		}
		if (!cmd->splitedp[i])
			cmd[j].cmdp = strdup(cmd[j].cmd[0]);

		data->cmnd;
	}
}

int	dup_close(int in, int out)
{
	int	dup_;

	dup_ = dup2(in, 0);
	if (dup_ < 0)
		return (dup_);
	dup_ = dup2(out, 1);
	if (dup_ < 0)
		return (dup_);
	return (0);
}

void	child(t_list *cmd, int *fdp, int fd2, int i)
{
	close(fdp[0]);
	
	if (i + 1 < cmd->nbrcmd)
	{
		if (i == 0)
		{
			if (cmd->files[0] < 0)
				exit(1);
			dup_close(cmd->files[0], fdp[1]);
		}
		else
			dup_close(fd2, fdp[1]);
	}
	else
		dup_close(fd2, cmd->files[1]);
}

void	child(t_list *cmd, int *fdp, int fd2, int i)
{
	close(fdp[0]);
	
	if (i  < cmd->nbrcmd)
	{
		if (i == 0)
		{
			if (cmd->files[0] < 0)
				exit(1);
			dup_close(cmd->files[0], fdp[1]);
		}
		else
			dup_close(fd2, fdp[1]);
	}
	else
		dup_close(fd2, cmd->files[1]);
}

void	parent(t_list *cmd, int *fdp, int *r, char **env)
{
	int	i;

	i = *r;
	if ((accs(cmd[i].cmdp)))
		if (cmd->files[0] >= 0 || i != 0)
			ft_printf("command not found: %s\n", cmd[i].cmd[0]);
	i = ++*r;
	if (cmd->nbrcmd > i)
	{
		close(fdp[1]);
		tofork(cmd, env, i, fdp[0]);
	}
}
char	**get_env(t_env *env)
{
	t_env	*tmp; 
	char	*tp;
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * ft_lstsize(env) + 1);
	tmp = env;

	while(tmp)
	{
		if(tmp->val)
		{
			tab[i] = strjoin(tmp->var, "=");
			tp = tab[i];
			tab[i] = strjoin(tp, "\'");
			free(tp);
			tp = tab[i];
			tab[i] = strjoin(tp,tmp->val);
			free(tp);
			tp = tab[i];
			tab[i] = strjoin(tab[i], "\'");
			free(tp);
			tp = NULL;
		}
		i++;
		tab[i] = NULL;
		tmp = tmp->next;
	}
	return (tab);
}

void	tofork(t_list *cmd, char **env, int i, int fd2)
{
	pid_t	pid;
	int		fdp[2];

	if (pipe(fdp) < 0)
	{
		perror("Error");
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		child(cmd, fdp, fd2, i);
		execve(cmd->cmdp, cmd->cmd, env);
		exit(1);
	}
	else
	{
		if (pid == -1)
			return ;
		parent(cmd, fdp, &i, env);
	}
}
