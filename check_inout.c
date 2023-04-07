# include "minishell.h"

// void	frfr(char *str, char *ptr)
// {
// 	if (str)
// 		free(str);
// 	if (ptr)
// 		free(ptr);
// }
char	*joinheredoc(char *av)
{
	char	*hd_content;
	char	*limiter;
	char	*tmp;

		tmp = av;
	hd_content = NULL;
	while (1)
	{
		limiter = readline(" > ");
//		tmp = strjoin(av, "\n");
        // printf("[%s][%s]\n", limiter, tmp);
		if (ft_strcmp(tmp, limiter) != 0) // yaha
		{
			free(tmp);
			tmp = hd_content;
			hd_content = strjoin(hd_content, limiter);
			hd_content = strjoin(hd_content, limiter);
			frfr(tmp, limiter);
            rmp
		}
		else
		{
			frfr(tmp, limiter);
			break ;
		}
	}
	return (hd_content);
}


char *get_next_word(char **str_ptr)
{
    char *word = NULL;
    char *str = *str_ptr;
    int len = 0;
    
    // skip leading whitespace
    while (*str && isspace(*str)) {
        str++;
    }
    
    // find length of next word
    while (*str && !isspace(*str)) {
        len++;
        str++;
    }
    
    // allocate memory for word
    word = (char*) malloc(sizeof(char) * (len + 1));
    if (!word) {
        return NULL;
    }
    
    // copy word into buffer
    strncpy(word, str - len, len); ///ft_strncpy
    word[len] = '\0';
    
    // update str_ptr to point to next word
    *str_ptr = str;
    
    return word;
}

void search_herdoc_and_redirection(t_list *cmd, char *str)
{
    int i = 0;
    char *word;
    while (str[i]) {
        // get next word
        word = get_next_word(&str);
        if (!word) {
            break;
        }
        // check for heredoc operators
        if (ft_strcmp(word, "<<") == 0) {
            free(word);
            // get heredoc delimiter
            word = get_next_word(&str);
            if (!word) {
                printf("syntax error\n");
                return;
            }
            // read heredoc content
            char *heredoc_content = joinheredoc(word);
            if (!heredoc_content) {
                printf("error reading heredoc content\n");
                return;
            }
            // set heredoc string
            cmd->heredocstr = heredoc_content;
            // update word and str
            free(word);
            i = 0;
            str = cmd->content;
            continue;
        }
        else if (ft_strcmp(word, ">>") == 0) {
            // get filename
            word = get_next_word(&str);
            if (!word) {
                printf("syntax error\n");
                return;
            }
            // open file in append mode
            int fd = open(word, O_WRONLY | O_APPEND | O_CREAT, 0666);
            if (fd == -1) {
                printf("error opening file\n");
                return;
            }
            // set file descriptor
            cmd->fdinout[1] = fd;
            free(word);
        }
        else if (ft_strcmp(word, ">") == 0) {
            // get filename
            word = get_next_word(&str);
            if (!word) {
                printf("syntax error\n");
                return;
            }
            // open file in write mode
            int fd = open(word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
            if (fd == -1) {
                printf("error opening file\n");
                return;
            }
            // set file descriptor
            cmd->fdinout[1] = fd;
            free(word);
        }
        else if (ft_strcmp(word, "<") == 0) {
            // get filename
            word = get_next_word(&str);
            if (!word) {
                printf("syntax error\n");
                return;
            }
            // open file in read mode
            int fd = open(word, O_RDONLY);
            if (fd == -1) {
                printf("error opening file\n");
                return;
            }
            // set file descriptor
            cmd->fdinout[0] = fd;
            free(word);
        }
        else {
            free(word);
        }
    }
}
