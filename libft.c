
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
	while ( c1 && c2 && (*c1 || *c2))
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
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)b;
	i = 0;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (ptr);
}
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
int	ft_strlcat(char *dst, char *src, int size)
{
	int	i;
	int	lendst;
	int	lensrc;

	i = 0;
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size < lendst)
		return (size + lensrc);
	while (*src && (lendst + i + 1) < size)
		dst[lendst + i++] = *src++;
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}

void	*ft_calloc(int count, int size)
{
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (0);
	ft_bzero(s, count * size);
	return (s);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	size_t	l1;
// 	size_t	l2;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	l1 = ft_strlen(s1);
// 	l2 = ft_strlen(s2);
// 	str = (char *)ft_calloc(l1 + l2 + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	ft_strlcat(str, s1, l1 + 1);
// 	l2 = l2 + l1;
// 	ft_strlcat(str, s2, l2 + 1);
// 	return (str);
// }

void	strjoin_help(char *src, int *i, char *tmp)
{
	int	len;

	len = 0;
	while(src && src[len])
	{
		tmp[*i] = src[len];
		len++;
		(*i)++;
	}
	tmp[*i] = '\0';
}

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
	strjoin_help(src, &i, tmp);
	return (tmp);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int        len;
    int        l;
    int        i;
    char    *str;

    if (!s1)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2);
    str = (char *)malloc(sizeof(char) * len);
    l = ft_strlen(s1);
    if (!str)
        return (NULL);
    i = -1;
    while (i++ <= l)
        str[i] = s1[i];
    i = 0;
    while (l < len)
        str[l++] = s2[i++];
    str[len] = '\0';
    return (str);
}

// char	*strjoin(char *str1, char *str2) 
// {
//     if (str1 == NULL || str2 == NULL) {
//         return NULL;
//     }

//     int len1 = 0;
//     while (str1[len1] != '\0') {
//         len1++;
//     }

//     int len2 = 0;
//     while (str2[len2] != '\0') {
//         len2++;
//     }

//     char *result = (char*) malloc(len1 + len2 + 1);
	
//     if (result != NULL) {
//         int i = 0;
//         while (i < len1) {
//             result[i] = str1[i];
//             i++;
//         }
		
//         int j = 0;
//         while (j < len2) {
//             result[i + j] = str2[j];
//             j++;
//         }
		
//         result[i + j] = '\0';
//     }
	
//     return result;
// }

// char *strjoin(char *str1, char *str2)
//  {
// 	int len1;
// 	char *result;

// 	len1 = 0;
// 	if (str1 == NULL || str2 == NULL) 
// 		return (NULL);
// 	while (str1[len1] != '\0')
// 		len1++;


// 	len2 = 0;
// 	while (str2[len2] != '\0') {
// 		len2++;
// 	}

// 	result = (char*) malloc(len1 + len2 + 1);
// 	if (result == NULL) {
// 		return NULL;
// 	}
	
// 	char *p = result;
// 	char *q = str1;
// 	while (*q != '\0') {
// 		*p++ = *q++;
// 	}
	
// 	q = str2;
// 	while (*q != '\0') {
// 		*p++ = *q++;
// 	}
	
// 	*p = '\0';
	
// 	return result;
// }








// // char *strjoin(char *str1, char *str2) {
// //     if (str1 == NULL || str2 == NULL) {
// //         return NULL;
// //     }

// //     size_t len1 = 0;
// //     while (str1[len1] != '\0') {
// //         len1++;
// //     }
	
// //     size_t len2 = 0;
// //     while (str2[len2] != '\0') {
// //         len2++;
// //     }

// //     char *result = (char*) malloc(len1 + len2 + 1);
	
// //     if (result != NULL) {
// //         for (size_t i = 0; i < len1; i++) {
// //             result[i] = str1[i];
// //         }
// //         for (size_t i = 0; i < len2; i++) {
// //             result[len1 + i] = str2[i];
// //         }
// //         result[len1 + len2] = '\0';
// //     }
	
// //     return result;
// // }