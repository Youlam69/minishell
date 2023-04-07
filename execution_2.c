#include "minishell.h"

int	dup_close(int in, int out)
{
	if (dup2(in, 0))
		return (-1);
	if (in != 0)
		close(in);
	if (dup2(out, 1))
		return (-1);
	if (out != 1)
		close(out);
	if (out != 1)
		close(out);
	return (0);
}

// void	child(t_data *data, int *fdp, int fd2, int i)  // int *fdp == fdp[2]
// {
// 	t_list *cmd;

// 	cmd = data->cmd;
// 	close(fdp[0]);
// 	if (i + 1 < data->nbrcmd)
// 	{
// 		if (i == 0)
// 		{
// 			if (cmd->fdinout[0] < 0)
// 				exit(1); // should manage the errors
// 			dup_close(cmd->fdinout[0], fdp[1]);
// 		}
// 		else
// 			dup_close(fd2, fdp[1]);
// 	}
// 	else
// 		dup_close(fd2, cmd->fdinout[1]);
// }
void	exec_imp(t_data *data, int imp, int ref)
{
	data->exit_status = 0;
	if(imp == 1)
		echo(data->cmd->cmd);
	else if(imp == 2)
		pwd(data->pwd);
	else if(imp == 3)
		env(data->env);
	else if(imp == 4)
		ft_exit(data, &data->cmd->cmd[1]);
	else if(imp == 5)
		cd(data);
	else if(imp == 6)
		export(data, data->cmd->cmd);
	else if(imp == 7)
		unset(data, data->cmd->cmd);
	if(ref)
		exit (data->exit_status);
}

void hadler_quit(int sig)
{
	(void)sig;
	// if(sig == SIGQUIT)
	// {
		write(1, "Quit\n", 5);
		ft_putstr_fd("Quit\n", 2);
		// exit(131);
	// }
}
void handler_c(int sig)
{
	if(sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		exit(130);
	}
}
void	child(t_data *data, int *fdp, int fd2)  // int *fdp == fdp[2]
{
	t_list *cmd;
	int		imp;
	// t_data *data = *beta;

	// data = *beta;
	cmd = data->cmd;
	if(cmd->fdinout[1] < 0 || cmd->fdinout[0] < 0)
		exit(1);
	close(fdp[0]);
	if (cmd->next)
	{
		if (ft_lstsize(cmd) == data->nbrcmd)
		{
			if(cmd->fdinout[1] > 1)
				dup_close(cmd->fdinout[0], cmd->fdinout[1]);
			else
			dup_close(cmd->fdinout[0], fdp[1]);
		}
		else
		{	

			if (cmd->fdinout[0] > 1)
				dup2(cmd->fdinout[0], 0);
			else
				dup2(fd2, 0);
			if (cmd->fdinout[1] > 1)
				dup2(cmd->fdinout[1], 1);
			else
				dup2(fdp[1], 1);
		}
	}
	else
	{
		if (ft_lstsize(cmd) == data->nbrcmd)
			dup_close(cmd->fdinout[0], cmd->fdinout[1]);
		else
			dup_close(fd2, cmd->fdinout[1]);
	}
	imp = check_implmnt(data);
	if(imp)
		exec_imp(data, imp, 1);

	if (!cmd->cmdp)
		exit(0);
	execve(cmd->cmdp, cmd->cmd, data->envc);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd("\n", 2);
	exit(127);

}
void	parent(t_data *data, int *fdp)
{
	// int	i;
	t_list *cmd = data->cmd;


	close(fdp[1]);
	// if(cmd->cmd[0])
	// 	if ((accs(cmd->cmdp)))
	// 		if (cmd->fdinout[0] >= 0)
	// 			printf("command not found: %s\n", cmd->cmd[0]);
	data->cmd = cmd->next;
	if (data->cmd) // should change if(data->cmd)
		tofork(data, fdp[0]);
	if (fdp[0] != 0)
		close(fdp[0]);
}

// int	ft_lstsize(t_list *lst)
// {
// 	int	i;

// 	i = 0;
// 	if (!lst)
// 		return (0);
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (i);
// }

void	tofork(t_data *data, int fd2)
{
	pid_t	pid;
	int		ext_s;
	// int		implmnd;
	int		fdp[2];
	// t_list	*cmd = data->cmd;
	// cmd = data->cmd;
	ext_s = 0;
	pid = -3;
	if (pipe(fdp) < 0)
	{
		perror("Error");
		return ;
	}
	if(!data->cmd->next && data->nbrcmd == ft_lstsize(data->cmd) && check_implmnt(data) >= 4)
	{
		exec_imp(data, check_implmnt(data), 0);
		// return; katkhasar lia export khasny n7at variable exit f global variable
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);

		pid = fork();
	}
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, handler_c);
		signal(SIGQUIT, hadler_quit);

		child(data, fdp, fd2);  // int *fdp == fdp[2]

	}
	else
	{
		parent(data, fdp);

		// close(fdp[1]);
		// if ((accs(cmd->cmdp)))
		// 	if (cmd->fdinout[0] >= 0)
		// 		printf("command not found: %s\n", cmd->cmd[0]);
	  	// data->cmd = cmd->next;
		// if (data->cmd) // should change if(data->cmd)
		// 	tofork(data, fdp[0]);
		// if (fdp[0] != 0) close(fdp[0]);
		// parent(data, fdp, &i);
	}
	waitpid(-1,&ext_s,0);
	if (!data->cmd)
		if (WIFEXITED(ext_s))
			data->exit_status = WEXITSTATUS(ext_s);

}