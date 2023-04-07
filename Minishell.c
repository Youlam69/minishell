# include "minishell.h"

void  hendl_ctr_c(int sig)
{
    (void)sig;
    // printf("\n");
	write(	1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
	rl_redisplay();
}

void	frfr(char *str, char *ptr)
{
	if (str)
		free(str);
	if (ptr)
		free(ptr);
}


// char	*joinheredoc(char *av)
// {
// 	char	*hd_content;
// 	char	*limiter;
// 	char	*tmp;

// 		tmp = av;
// 	hd_content = NULL;
// 	while (1)
// 	{
// 		limiter = readline(" > ");
// //		tmp = strjoin(av, "\n");
//         printf("[%s][%s]\n", limiter, tmp);
// 		if (strcmp(tmp, limiter) != 0) // yaha
// 		{
// 			free(tmp);
// 			tmp = hd_content;
// 			hd_content = strjoin(hd_content, limiter);
// 			frfr(tmp, limiter);
// 		}
// 		else
// 		{
// 			frfr(tmp, limiter);
// 			break ;
// 		}
// 	}
// 	return (hd_content);
// }
// int ft_lstsize_env(t_env *env)
// {
// 	int i;

// 	i = 0;
// 	while (env)
// 	{
// 		i++;
// 		env = env->next;
// 	}
// 	return (i);
// }

// char **take_envc(t_env *env)
// {
// 	char **envc;
// 	int i;
// 	int len;
// 	char *tmp;

// 	i = 0;
// 	len = ft_lstsize_env(env);
// 	envc = malloc(sizeof(char *) * (ft_lstsize_env(env) + 1));
// 	envc[len] = NULL;
// 	i = 0;
// 	while (env->var)
// 	{
// 		if(!env->print_env)
// 		{
// 			tmp = strjoin(env->var, "=");
// 			envc[i] = strjoin(tmp, env->val);
// 			free(tmp);
// 			i++;
// 		}
// 		env = env->next;
// 	}
// 	envc[i] = NULL;
// 	return (envc);
// }

// char	**splitpath(t_env *env)
// {
// 	char	*path;
// 	// t_env	*env;
// 	char	**splited;
// 	int		i;

// 	i = 0;
// 	if (!env)
// 		return NULL;
// 	else if (!env->var)
// 		return NULL;
// 	while (env->var)
// 	{
// 		// path = ft_strnstr(env[i], "PATH=", 5);
// 		if (!strcmp(env->var, "PATH")) //should use ft_strcmp
// 		{
// 			path = env->val; // should just break
// 			break ;
// 		}
// 		env = env->next;
// 	}
// 	if (!env->var)
// 		return NULL;
// 	splited = ft_split(env->val, ':'); //shouled take env->val
// 	// free(path);
// 	i = 0;
// 	while(splited[i])
// 	{
// 		path = splited[i];
// 		splited[i] = strjoin(path, "/");
// 		free(path);
// 		path = NULL;
// 		i++;
// 	}
// 	return (splited);
// }


char	**splitpath(t_env *env)
{
	char	*path;
	// t_env	*env;
	char	**splited;
	int		i;
	i = 0;
	if (!env )
		return NULL;
	if(!env->var)
		return NULL;
	while (env)
	{
		if(env->var)
		{

		// path = ft_strnstr(env[i], "PATH=", 5);
		if (!strcmp(env->var, "PATH")) //should use ft_strcmp
		{
			path = env->val; // should just break
			break ;
		}
		}
		env = env->next;
	}
// exit(1);
	if (!env)
		return NULL;
	splited = ft_split(env->val, ':'); //shouled take env->val
	// free(path);
	i = 0;
	while(splited[i])
	{
		path = splited[i];
		splited[i] = strjoin(path, "/");
		free(path);
		path = NULL;
		i++;
	}
	return (splited);
}


int	accs(char *path)
{
	if (access(path, F_OK))
		return (1);
	if (open(path, O_DIRECTORY) < 0)
	{
		if (!(access(path, X_OK)))
			return (0);
		else
			return (2);
	}
	return (3);
}

void	joinpath(t_data *data)
{
	int		i;

	t_list *cmd = data->cmd;
	if (!data->splitedp)
	{
		cmd->cmdp = ft_strdup(cmd->cmd[0]);
		return ;
	}

	while (cmd)
	{
		if(cmd->cmd && cmd->cmd[0])
		{
			i = -1;
			while (data->splitedp[++i])
			{
				cmd->cmdp = strjoin(data->splitedp[i], cmd->cmd[0]);
				if (accs(cmd->cmdp) == 0)
					break ;
				free(cmd->cmdp);
			}
			if (!data->splitedp[i])
				cmd->cmdp = ft_strdup(cmd->cmd[0]);
		}
		cmd = cmd->next;
	}
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// void free_after_split(char **tab)
// {
// 	int i = 0;
// 	if(!tab)
// 		return;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

// void free_list(t_list *lst)
// {
// 	t_list *tmp;
// 	while (lst)
// 	{
// 		tmp = lst;
// 		lst = lst->next;
// 		free_after_split(tmp->cmd);
// 		free(tmp->cmdp);
// 		free(tmp->content);
// 		free(tmp);
// 	}
// }

// void free_env(t_env *lst)
// {
// 	t_env *tmp;
// 	while (lst)
// 	{
// 		tmp = lst;
// 		lst = lst->next;
// 		free(tmp->var);
// 		free(tmp->val);
// 		free(tmp);
// 	}
// }

void init_data(t_data *data)
{
	data->nbrcmd = 0;
	data->cmd = NULL;
	data->env = NULL;
	data->envc = NULL;
	data->splitedp = NULL;
	data->exit_status = 0;
	data->homep= NULL;
	data->pwd = NULL;
}

int  ft_size_env(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char **take_envc(t_env *env)
{
	char **envc;
	int i;
	int len = 0	;
	char *tmp= NULL;
	i = 0;
	len = ft_size_env(env);

	envc = malloc(sizeof(char *) * len + 1);
	if(!envc)
	{
			// printf("failure env->var = %s env->val = %s len is %ld\n", env->var, env->val, l);
				// fflush(stdout);
				// exit (error);	
		return (NULL);
	}
	envc[len] = NULL;
	i = 0;
	while (env)
	{
		if(!env->print_env)
		{
			tmp = strjoin(env->var, "=");
			envc[i] = strjoin(tmp, env->val);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	envc[i] = NULL;
	return (envc);
}


int main (int ac, char **av, char **env)
{
    (void)av;

    char *str;
    char *tmp;

    t_data data; 

		// printf("|%p|\n", env);
		// printf("|%p|\n", *env);
		// exit(2);
    if(ac != 1)
        return(printf("Minishell not take args \n "));
        
    // enva = malloc(sizeof(t_env)); // protect malloc
	init_data(&data);
    data.env = ft_envar(env);
	
    // int i = -1;
    // data.splitedp = splitpath(enva);
    //     while(data.splitedp[++i])
    //     {
    //  printf("%s\n",data.splitedp[i]); // poure les flage ne lpeure pas 
            // j = 0;
            // while(tab[i][j])
            // {
            //     if(tab[i][j] == '<' && tab[i][j + 1] == '<')
            //     joinheredoc(tab[i + 1]);
            //     j++;
            // }
            // i++;
        // }
        //     exit(0);
        data.pwd = getcwd(NULL, 0);
    while(2)
    {
        signal(SIGINT, hendl_ctr_c);
        signal(SIGQUIT, SIG_IGN);
		data.envc = take_envc(data.env); //shoul take it in boucle when i ussing my_t_env;
		data.splitedp = splitpath(data.env);

        tmp = strjoin(data.pwd, " ~> ");
        str = readline(tmp);
        free(tmp);
        if(!str)
        {
			free_all_exit(&data, 1);
            // exit(0);
        }
        add_history(str);
        data.cmd =  parsing(str, &data);
        
		if(!data.cmd)
                continue;

        joinpath(&data);
// exit(1);
		data.nbrcmd = ft_lstsize(data.cmd);
        tofork(&data, 0);
		// free(data.pwd);
		free_all_exit(&data, 0);
		// free(data.pwd);
	// 	free_list(data.cmd);
	// // exit(1);
	// 	free(str);
	// 	free_after_split(data.splitedp);
	// 	free_after_split(data.envc);
		

		// continue;
		
    // t_list *ptr =  data.cmd;
	// int i = 0;
    // while (ptr->next)
	// {
	// 	// while(*ptr->cmd)
	// 	// {
	// 	    printf("cmdp{%s} ou i = %d \n", ptr->cmdp, i);
	// 	    printf("cmd{%s} ou i = %d \n", ptr->cmd[0], i++);
			
	// 	//     ptr->cmd++;
	// 	// }
	// 	ptr = ptr->next;
	// }
        // int j = 0;
        // while(tab[i])
        // {
        //     j = 0;
        //     while(tab[i][j])
        //     {
        //         if(tab[i][j] == '<' && tab[i][j + 1] == '<')
        //         joinheredoc(tab[i + 1]);
        //         j++;
        //     }
        //     i++;
        // }
        // printf("loooooooooooooooooooooooooooooooooooooool\n");
    }
}