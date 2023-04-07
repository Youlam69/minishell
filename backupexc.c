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
void	child(t_data *data, int *fdp, int fd2)  // int *fdp == fdp[2]
{
	t_list *cmd;
	// t_data *data = *beta;

	// data = *beta;
	cmd = data->cmd;
	close(fdp[0]);
	if (cmd->next)
	{
		if (ft_lstsize(cmd) == data->nbrcmd)
		{
			if (cmd->fdinout[0] < 0)
				exit(1); // should manage the errors
			dup_close(cmd->fdinout[0], fdp[1]);
		}
		else
			dup_close(fd2, fdp[1]);
	}
	else
		dup_close(fd2, cmd->fdinout[1]);

	execve(cmd->cmdp, cmd->cmd, data->envc);
	exit(127);
}

void	parent(t_data *data, int *fdp)
{
	// int	i;
	t_list *cmd = data->cmd;


	close(fdp[1]);
	if ((accs(cmd->cmdp)))
		if (cmd->fdinout[0] >= 0)
			printf("command not found: %s\n", cmd->cmd[0]);
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
	int		fdp[2];
	// t_list	*cmd = data->cmd;
	// cmd = data->cmd;
	ext_s = 0;
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