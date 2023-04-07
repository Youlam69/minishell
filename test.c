#include "minishell.h"

int main(int ac, char **av, char **ev)

{

    char **cmd = NULL;
    char *cmdp = NULL;
	execve(cmdp, cmd, ev);

    printf("Hello World!\n");

}
// // typedef struct s_list
// // {
// // 	// char			**cmd;
// // 	// int				files[2];
// // 	// int				fd[2];
// // 	// int				fd2;
// // 	char			*herdoc;
// // 	// int				nbrcmd;
// // 	int				her_exist;
// // 	int				index;
// // 	char			*cmdp;
// // 	char 			*heredocstr;

// // 	int				fdinout[2];

// // 	// int 			input;
// // 	// int 			output;
// // 	char			*content;
// // 	char			**cmd;
// // 	struct s_list	*next;
// // }	t_list; // t_cmd

// char *get_next_word(char **str_ptr)
// {
//     char *word = NULL;
//     char *str = *str_ptr;
//     int len = 0;
    
//     // skip leading whitespace
//     while (*str && isspace(*str)) {
//         str++;
//     }
    
//     // find length of next word
//     while (*str && !isspace(*str)) {
//         len++;
//         str++;
//     }
    
//     // allocate memory for word
//     word = (char*) malloc(sizeof(char) * (len + 1));
//     if (!word) {
//         return NULL;
//     }
    
//     // copy word into buffer
//     strncpy(word, str - len, len);
//     word[len] = '\0';
    
//     // update str_ptr to point to next word
//     *str_ptr = str;
    
//     return word;
// }

// void search_herdoc_and_redirection(t_list *cmd, char *str)
// {
//     int i = 0;
//     char *word;
//     while (str[i]) {
//         // get next word
//         word = get_next_word(&str);
//         if (!word) {
//             break;
//         }

//         // check for heredoc operators
//         if (strcmp(word, "<<") == 0) {
//             free(word);
//             // get heredoc delimiter
//             word = get_next_word(&str);
//             if (!word) {
//                 printf("syntax error\n");
//                 return;
//             }
//             // read heredoc content
//         //     char *heredoc_content = joinheredoc(word);
//         //     if (!heredoc_content) {
//         //         printf("error reading heredoc content\n");
//         //         return;
//         //     }
//         //     // set heredoc string
//         //     cmd->heredocstr = heredoc_content;
//         //     // update word and str
//         //     free(word);
//         //     i = 0;
//         //     str = cmd->content;
//         //     continue;
//         // }
//         // else if (strcmp(word, ">>") == 0) {
//             // get filename
//             word = get_next_word(&str);
//             if (!word) {
//                 printf("syntax error\n");
//                 return;
//             }
//             // open file in append mode
//             int fd = open(word, O_WRONLY | O_APPEND | O_CREAT, 0666);
//             if (fd == -1) {
//                 printf("error opening file\n");
//                 return;
//             }
//             // set file descriptor
//             cmd->fdinout[1] = fd;
//             free(word);
//         }
//         else if (strcmp(word, ">") == 0) {
//             // get filename
//             word = get_next_word(&str);
//             if (!word) {
//                 printf("syntax error\n");
//                 return;
//             }
//             // open file in write mode
//             int fd = open(word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
//             if (fd == -1) {
//                 printf("error opening file\n");
//                 return;
//             }
//             // set file descriptor
//             cmd->fdinout[1] = fd;
//             free(word);
//         }
//         else if (strcmp(word, "<") == 0) {
//             // get filename
//             word = get_next_word(&str);
//             if (!word) {
//                 printf("syntax error\n");
//                 return;
//             }
//             // open file in read mode
//             int fd = open(word, O_RDONLY);
//             if (fd == -1) {
//                 printf("error opening file\n");
//                 return;
//             }
//             // set file descriptor
//             cmd->fdinout[0] = fd;
//             free(word);
//         }
//         else {
//             free(word);
//         }
//     }
// }


// int main()
// {
// 	t_list *hi;
// 	hi = malloc(sizeof(t_list));
// 	char str[15] = "< env2.c dsfkhd";
// 	search_herdoc_and_redirection(hi,str);
// 	printf("had |%s|\n", str);
// }


// // char	*ft_get_copy(char *str, char *line, int i)
// // {
// // 	int	j;

// // 	j = 0;
// // 	while (str[j])
// // 	{
// // 		line[i] = str[j];
// // 		i++;
// // 		j++;
// // 	}
// // 	return (line);
// // }


// // char	*ft_get_value_of_env(char *line, int i, t_env *env)
// // {
// // 	char	*str;
// // 	int		j;

// // 	j = 0;
// // 	(void)line;
// // 	(void)i;
// // 	str = (char *)malloc(sizeof(char *));
// // 	if (!str)
// // 		return (NULL);
// // 	while (env->val[j])
// // 	{
// // 		str[j] = env->val[j];
// // 		j++;
// // 	}
// // 	return (str);
// // }

// // char	*check_cmp(char *line, int i, t_env *env)
// // {
// // 	int		k;
// // 	char	*str;

// // 	str = malloc(sizeof(char *));
// // 	if (!str)
// // 		return (NULL);
// // 	str = "";
// // 	while (env)
// // 	{
// // 		k = i;
// // 		if (!ft_strncmp(line, k + 1, env->var))
// // 		{
// // 			str = ft_get_value_of_env(line, k + 1, env);
// // 			return (str);
// // 		}
// // 		else
// // 			env = env->next;
// // 	}
// // 	return (str);
// // }


// // t_tok	*replace_env(t_tok *lst, t_env *env)
// // {
// // 	int		i;
// // 	t_tok	*tmp;
// // 	char	*str;

// // 	tmp = lst;
// // 	str = malloc(sizeof(char *));
// // 	if (!str)
// // 		return (NULL);
// // 	while (tmp)
// // 	{
// // 		i = 0;
// // 		//tmp->value = ft_check_qout(tmp->value);
// // 		while (tmp->value[i])
// // 		{
// // 			if (tmp->value[i] == '$')
// // 			{
// // 				str = check_cmp(tmp->value, i, env);
// // 				if (!ft_strcmp(str, ""))
// // 					tmp->value = "";
// // 				else
// // 					tmp->value = ft_get_copy(str, tmp->value, i);
// // 			}
// // 			i++;
// // 		}
// // 		tmp = tmp->next;
// // 	}
// // 	return (lst);
// // }
