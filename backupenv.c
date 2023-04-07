***************************************************** */

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


int sheegal(char *conten)
{
	int i;
	i = 0;
	while(conten[i])
	{
		if(conten[i] == '=')
			break;
		i++;
	}
	return(i);
}

char *ft_variab(char *content)
{
	char *str;
	int i;

	i = sheegal(content);
	str = ft_substr(content, 0 , i);
	return(str);
}

char *ft_valu(char *content)
{
	char *str;
	int i;

	i = sheegal(content);
	str = ft_substr(content, i + 1 , ft_strlen(content) - i);
	return(str);
}



t_env	*ft_lstnew(char *content)  
{
	t_env	*new;
	(void)content;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		// new->var = ft_variab(content);
		// new->val = ft_valu(content);
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


// int ft_isdigit(char c)
// {
// 	return (c <= '0' || c >= '9');
// }

int	ft_atoi(char *str)
{
	int		s;
	long	d;

	s = 1;
	d = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (d > d * 10 + *str - '0' && s == -1)
			return (0);
		if (d > d * 10 + *str - '0' && s == 1)
			return (-1);
		d = d * 10 + *str - '0';
			str++;
	}
	return ((int)(d * s));
}

// static int	ft_get_size(int n)
// {
// 	int	c;

// 	c = 0;
// 	if (n < 0)
// 	{
// 		c++;
// 		n *= -1;
// 	}
// 	if (n == 0)
// 		c++;
// 	while (n != 0)
// 	{
// 		n = n / 10;
// 		c++;
// 	}
// 	return (c);
// }

// char	*ft_itoa(int n)
// {
// 	char	*tab;
// 	int		size;
// 	long	nbr;

// 	nbr = n;
// 	size = ft_get_size(nbr);
// 	tab = (char *)malloc(sizeof(char) * (size + 1));
// 	if (!tab)
// 		return (NULL);
// 	tab[size--] = '\0';
// 	if (nbr < 0)
// 	{
// 		nbr *= -1;
// 		tab[0] = '-';
// 	}
// 	if (nbr == 0)
// 		tab[size] = '0';
// 	while (nbr != 0)
// 	{
// 		tab[size--] = nbr % 10 + '0';
// 		nbr = nbr / 10;
// 	}
// 	return (tab);
// }


void shlvl(t_env *ev)
{
	int i;
	char *tmp;
	i = 0;
	if(!ev || !ev->var)
		return;
	while (ev)
	{
		if(!ft_strcmp(ev->var, "SHLVL" ))
		{
			i = ft_atoi(ev->val);
			if(i >= 999)
			{
				printf("our minisheel rah fu9 100000rja3 1"); //to change
				i = 1;
			}
			else if (i < 0)
				i = 0;
			else
				i++;
			tmp = ev->val;
			ev->val = ft_itoa(i);
			free(tmp);
		}
		ev = ev->next;
	}
}

t_env *ft_envar(char **env)
{
    int i = 0;
    
    t_env *ptr;
    
    ptr = NULL;
	if (!env || !env[0])
		return (NULL);
    while(env[i])
	{
		ft_lstadd_back(&ptr, ft_lstnew(env[i]));
		i++;
	}
	// exit(1);

	shlvl(ptr);
    return (ptr);
}

int	ft_strtest(char *str1, int i, char *str2)
{
	int	j;

	j = 0;
	while ((str1[i] && str1[i] != '$') || str2[j])
	{
		if (str1[i] != str2[j])
			return (1);
		i++;
		j++;
	}
	return (0);
}

char *cpy_str_to_lst(char *s1, char *s2, int i)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	return (s1);
}

char *ft_copy_valu(t_env *en)
{
	char *str = NULL;
	int i = 0;
	str = malloc(sizeof(char)); // protect 
	while(en->val[i])
	{
		str[i] = en->val[i];
		i++;
	}
	return(str);
}



char	*take_env(char *str, int i, t_env *ev)
{
	char *tmp = NULL;
	// tmp = malloc(sizeof(char));
	// t_env *env;
	while(ev)
	{
		if((ft_strtest(str, i + 1, ev->var)) == 0)
		{
			// tmp = ft_copy_valu(ev);
			tmp = strjoin(NULL, ev->val);
			return(tmp);
		}
		else 
			ev = ev->next;
	}
	return (tmp);
}



t_list *management_dollar(t_list *head, t_env *en)
{
    int i;
    char *str;
    t_list  *ptr;

	

    i = 0;
    str = malloc(sizeof(char ) + 1); // protect malloc
    ptr = head;
	
	
    while(head)
    {
        i = 0;
        while(head->content[i])
		{
			if(head->content[i] == '$')
			{
				str = take_env(head->content,i, en);
				if(!ft_strrrcmp(str, ""))
				{
					head->content = "";
				}
				else
				{
					head->content = cpy_str_to_lst(head->content, str, i);
				}
			}
			i++;
		}
		head = head->next;
    }
	return (ptr);
}