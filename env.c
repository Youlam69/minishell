
#include "minishell.h"

int	ft_strrrcmp(char *str1, char *str2)
{
	int	j;

	j = 0;
	while (str1[j] || str2[j])
	{
		if (str1[j] != str2[j])
			return (1);
		j++;
	}
	return (0);
}

int	sheegal(char *conten)
{
	int	i;

	i = 0;
	while (conten[i])
	{
		if (conten[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	*ft_variab(char *content)
{
	char	*str;
	int		i;

	i = sheegal(content);
	str = ft_substr(content, 0, i);
	return (str);
}

char	*ft_valu(char *content)
{
	char	*str;
	int		i;

	i = sheegal(content);
	str = ft_substr(content, i + 1, ft_strlen(content) - i);
	return (str);
}

t_env	*ft_lstnew(char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->var = ft_variab(content);
		new->val = ft_valu(content);
		new->print_env = 0;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*ptr;

	if (alst)
	{
		if (*alst == NULL)
		{
			*alst = new;
			new = NULL;
		}
		else
		{
			ptr = *alst;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}

int	ft_isdigit(char c)
{
	return (c <= '0' || c >= '9');
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*str == ' ') || (*str >= 7 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res * sign);
}

void	shlvl_anex(t_env *ev)
{	
	int		i;
	char	*tmp;

	i = ft_atoi(ev->val);
	if (i >= 999)
	{
		printf("warning: shell level (1000) too high\
			, resetting to 1\n");
	}
	else if (i < 0)
	i = 0;
	else
		i++;
	tmp = ev->val;
	ev->val = ft_itoa(i);
	free(tmp);
}

void	shlvl(t_env *ev)
{
	if (!ev || !ev->var)
		return ;
	while (ev)
	{
		if (!ft_strcmp(ev->var, "SHLVL" ))
		{
			shlvl_anex(ev);
			break ;
		}
		ev = ev->next;
	}
}

t_env	*ft_envar(char **env)
{
	int		i;
	t_env	*ptr;

	i = -1;
	ptr = NULL;
	if (!env || env[0] == NULL)
		return (NULL);
	while (env[++i])
		ft_lstadd_back(&ptr, ft_lstnew(env[i]));
	shlvl(ptr);
	return (ptr);
}

