#include "minishell.h"

t_env	*ft_lstnew_export(char *var, char *val)  
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->var = var;
		new->val = val;
		new->print_env = 0;
		new->next = NULL;
	}
	return (new);
}

int	check_var(char *var, char *arg)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (!is_good(var[i]) || var[0] == '=' || is_digit(var[0]))
		{
			ft_putstr_fd("bash: export: `", 2); // putstr fd 2
			ft_putstr_fd(arg, 2); // putstr fd 2
			ft_putstr_fd("': not a valid identifier\n", 2); // putstr fd 2
			return (-1);
		}
	}
	return (0);
}

t_env	*add_to_env(char *var, char *val, t_env *env, int j)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*vl;

	vl = strjoin(var, val);
	if (check_var(var, vl))
		return env;
	free(vl);
		vl = NULL;
	if (!env)
	{
		env = ft_lstnew_export(var, val);
		return (env);
	}
	tmp = env;
	while (tmp)
	{
		if (!strcmp(var, tmp->var))
		{
			if (!val)
				return (env);
			vl = tmp->val;
			if (j)
				tmp->val = strjoin(tmp->val, val);
			else
				tmp->val = val;
			free(vl);
			vl = NULL;
			return (env);
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		tmp2->next = ft_lstnew_export(var, val);
	return (env);
}


t_env *split_export(char *arg, 	t_env *env)
{
	int		i;
	int		j;
	char	*var;
	char	*val;

	i = 0;
	j = 0;
	i = sheegal(arg);
	if (i == 0)
	{
		check_var(arg, arg);
		return (env);
	}
	if (i > 1 && arg[i - 1] == '+')
		j = 1;
	var = ft_substr(arg, 0, i - j);
	val = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	if (!val)
	{
		val = malloc(sizeof(char)); // ft_mallo
		val[0] = '\0';
	}
	if (check_var(var, arg))
	{
		frfr(var, val);
		return (NULL);
	}
	else
		env = add_to_env(var, val, env, j);
	return (env);
}

void	sort_and_prnit(char **arg)
{
	int		count;
	int		i;
	int		j;
	char	*temp;

	count = 0;
	i = -1;
	while (arg[count])
		count++;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (strcmp(arg[j], arg[j + 1]) > 0) //should i used ft_strcmp
			{
				temp = arg[j];
				arg[j] = arg[j + 1];
				arg[j + 1] = temp;
			}
		}
	}
	i = 0;
	while (arg[i])
		printf("declare -x %s\n", arg[i++]);
	free_after_split(arg);
}

int	ft_lstsize_env(t_env *lst)
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

void	print_env(t_env *env)
{
	t_env	*tmp;
	char	*tp;
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * ft_lstsize_env(env) + 1);
	tmp = env;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->var)
		{
			if (!tmp->val)
				tab[i] = strjoin(NULL, tmp->var);
			else
			{
				tab[i] = strjoin(tmp->var, "=");
				tp = tab[i];
				tab[i] = strjoin(tp, "\'");
				tp = tab[i];
				tab[i] = strjoin(tp, tmp->val);
				tp = tab[i];
				tab[i] = strjoin(tab[i], "\'");
			}
			i++;
			tab[i] = NULL;
		}
		tmp = tmp->next;
	}
	sort_and_prnit(tab);
}

void	export(t_data* data, char** val)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->env;
	while (val[++i])
	{
		if (sheegal(val[i]) == ft_strlen(val[i]))
			data->env = add_to_env(val[i], NULL, data->env, 0);
		else
			data->env = split_export(val[i], data->env);
	}
	if (i == 1)
		print_env(env);
}

// int is_digit(char c)
// {
// 	return (c <= '9' && c >= '0');
// }

// int is_alpha(char c)
// {
// 	if (c <= 'z' && c >= 'a')
// 		return(1);
// 	else if (c <= 'Z' && c >= 'A')
// 		return(1);
// 	return(0);
// }

// int is_good(char c)
// {
// 	if (is_digit(c) || is_alpha(c))
// 		return (1);
// 	else if (c == '_')
// 		return(1);
// 	return (0);
// }
// 
// int	check_var(char *var, char *arg)
// {
	// int i;
// 
	// i = -1;
	// while(var[++i])
	// {
		// if(!is_good(var[i]) || var[0] == '=' || is_digit(var[0]))
		// {
			// printf("bash: export: `%s': not a valid identifier\n", arg);
			// return(-1);
		// }
	// }
	// return (0);
// }
// 
// void add_to_env(char *var, char *val, t_env *env, int j)
// {
	// t_env *tmp;
	// char* vr;
	// char* vl;
// 
	// tmp = env;
	// while(tmp)
	// {
		// if(ft_strcmp(var) == ft_strcmp(tmp->var))
		// {
			// if (!val)
				// return;
			// vl = tmp->val;
			// if(j)
				// tmp->val = strjoin(tmp->val,val);
			// else
				// tmp->val = val;
			// free(vl);
			// vl = NULL;
			// return;
		// }
		// tmp = tmp->next;
	// }
// 
	// if(!tmp)
		// tmp = ft_lstnew_export(var,val);
// }
// 
// int split_export(char *arg, t_env *env)
// {	
	// int i;
	// int j;
	// char *var;
	// char *val;
// 
	// i = 0;
	// j = 1;
	// i = sheegal(arg);
	// if(i > 1 && arg[i - 1] == '+')
		// j = 1;
	// var = ft_substr(arg, 0 , i - j);
	// val = ft_substr(arg, i + 1, ft_strlen(arg) - i );
	// if(!val)
	// {
		// val = malloc(sizeof(char)); // ft_malloc
		// val[0] = '\0';
	// }
	// 
	// if(check_var(var ,arg))
	// {
		// frfr(var,val);
		// return (-1);
	// }
	// else
		// add_to_env(var, val, env, j);
	// return (0);
// }
// int	ft_strcmp(char *s1, char *s2)
// {
	// unsigned char	*c1;
	// unsigned char	*c2;
// 
	// c1 = (unsigned char *)s1;
	// c2 = (unsigned char *)s2;
	// while ((*c1 || *c2))
	// {
		// if (*c1 != *c2)
			// return (*c1 - *c2);
		// c1++;
		// c2++;
	// }
	// return (0);
// }
// 
// int sort_and_prnit(char **arg)
// {
  //  Count the number of elements in the array
	// int		count;
	// int		i;
	// int		j;
	// char	*temp;
// 
	// count = 0;
	// i = -1;
	// while (arg[count])
		// count++;
// 
  //  Sort the array using a simple bubble sort
	// while (++i < count - 1)
	// {
		// j = -1;
		// while (++j < count - i - 1) 
		// {
			// if (ft_strcmp(arg[j], arg[j+1]) > 0)
			// {
				// temp = arg[j];
				// arg[j] = arg[j+1];
				// arg[j+1] = temp;
			// }
		// }
	// }
	// i = -1;
	// while(arg[++i])
		// printf("declare -x %s", arg[i]);
	// i = -1;
	// while(arg[++i])
	// {
		// free(arg[i]);
		// arg[i] = NULL;
	// }
	// free(arg);
	// arg = NULL;
// }
// 
// void	print_env(t_env *env)
// {
	// t_env	*tmp; 
	// char	*tp;
	// char	**tab;
	// int		i;
// 
	// i = 0;
	// tab = ft_malloc(malloc(sizeof(char *) * ft_lstsize(env)));
	// tmp = env;
// 
	// while(tmp)
	// {
		// if(!tmp->val)
			// tab[i] = strjoin(NULL,tmp->var);
		// else
		// {
			// tab[i] = strjoin(tmp->var,SQ);
			// tp = tab[i];
			// tab[i] = strjoin(tp,tmp->val);
			// free(tp);
			// tp = tab[i];
			// tab[i] = strjoin(tab[i], SQ);
			// frfr(tp, NULL);
		// }
		// i++;
		// tab[i] == NULL;
		// tmp = tmp->next;
	// }
	// sort_and_prnit(tab);
// }
// 
// void export(t_env *env, char** val)
// {
	// t_env *tmp = env;
	// char **tp;
	// int i = 0;
// 
	// while(val[++i])
	// {
		// if(sheegal(val[i]) == ft_strlen(val[i]))
			// add_to_env(val[i],NULL, env, 0);
		// else
			// split_export(val[i]);
	// }
	// if(i == 1)
		// print_env(env);
// }
// 