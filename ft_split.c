
#include "minishell.h"

int ft_strlen(char *s)
{
    int i;

    i = 0;
	if(!s)
		return (0);
    while(s[i])
        i++;
    return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start + 1)
		len = ft_strlen(s) - start + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	return (str[j] = '\0', str);
}

static	int	ft_calcul(char *s, char d)
{
	int	i;
	int	cont;

	if (s[0] != d)
		cont = 1;
	else
		cont = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == d && s[i + 1] != d && s[i + 1] != '\0')
			cont++;
		i++;
	}
	return (cont);
}

// void	ft_free_(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 		free(tab[i++]);
// 	free(tab);
// }

static	char	**ft_my_split(char *str, char d, int i, int j)
{
	char	**tab;
	int		debut;
	int		fin;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_calcul(str, d) + 1));
	if (!tab)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] && str[i] == d)
			i++;
		debut = i;
		while (str[i] && str[i] != d)
			i++;
		fin = i;
		if (j < ft_calcul(str, d))
		{
			tab[j++] = ft_substr(str, debut, fin - debut);
			if (!tab[j - 1])
				return (free_after_split(tab), NULL);
		}
	}
	return (tab[j] = NULL, tab);
}

char	**ft_split(char *st, char c)
{	
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = ft_my_split(st, c, i, j);
	return (tab);
}