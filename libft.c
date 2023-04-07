
#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*sr;
	int		i;

	i = 0;
	sr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!sr)
		return (NULL);
	if(s1 == NULL)
		return (NULL);
	while (s1[i])
	{
		sr[i] = s1[i];
		i++;
	}
	sr[i] = '\0';
	return (sr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*d;
	size_t	i;
	size_t	len;

	d = (char *)s;
	len = ft_strlen(d);
	if ((char)c == '\0')
		return (d + len);
	i = 0;
	while (i < len)
	{
		if (d[i] == (char)c)
			return (&d[i]);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set || *set == '\0')
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[j]) && j != 0 && j >= i)
		j--;
	len = j - i + 1;
	return (ft_substr(s1, i, len));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while ((*c1 || *c2))
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	return (0);
}

// int len(char *str) // replace by ft_strlen
// {
//     int i;

//     i = 0;
//     if(str)
//     {
//         while(str[i])
//             i++;
//     }
//     return(i);
// }

char    *strjoin(char *dst, char *src)
{
    int i;
    int ln;
    char *tmp = NULL;

    i = 0;
    ln = ft_strlen(dst) + ft_strlen(src);
    tmp = malloc(sizeof(char) * (ln + 1));
	if(!tmp)
	{
		printf("Error: malloc failed in strjoin\n");
		return NULL;
	}
	tmp[ln] = '\0';
    if(dst)
    {
        while(dst[i])
		{
            tmp[i] = dst[i];
			i++;
		}
    }
	if(!src)
		return tmp;
    ln = 0 ;
    while(src[ln])
    {
        tmp[i] = src[ln];
        ln++;
        i++;
    }
    tmp[i] = '\0';
    return tmp;
}