
#ifndef MINISHELL_H
# define MINISHELL_H


# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>



# define SQ 39
# define DQ 34
# define PIPE 124
# define DLR 36
# define RINPUT 60
# define ROUTPUT 62




typedef struct s_list
{
	// char			**cmd;
	// int				files[2];
	// int				fd[2];
	// int				fd2;
	char			*herdoc;
	// int				nbrcmd;
	int				her_exist;
	int				index;
	char			*cmdp;
	char 			*heredocstr;


	int				fdinout[2];
	// int 			input;
	// int 			output;
	char			*content;
	char			**cmd;
	struct s_list	*next;
}	t_list; // t_cmd

typedef struct s_env
{
	char			*var;
	char			*val;
	int			print_env;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	// char		*pathj;
	int 		nbrcmd;
	int 		exit_status;
	char		**splitedp;
    char 		*pwd;
    char 		*homep;
	char 		**envc;
    t_env 		*env;
	t_list 		*cmd;
}   t_data;



void ft_putstr_fd(char *str, int fd);
int	check_implmnt(t_data *data);
char	*ft_strdup(char *s1);
char *ft_itoa(int nbr);
int	ft_lstsize(t_list *lst);
int is_alpha(char c);
int is_good(char c);
int is_digit(char c);
int is_dq(char c);
int is_q(char c);
int is_pipe(char c);
int is_rinp(char c);
int is_routp(char c);
int ft_strlen(char *s);
t_list *parsing(char *str, t_data *data);
int is_special(char c);
char	*ft_substr(char *s,int start, int len);
char	**ft_split(char *st, char c);
// int len(char *str);
// char    *strjoin(char *dst, char *src);
char    *strjoin(char *dst, char *src);
int	ft_atoi(char *str);
char	*ft_strtrim(char *s1, char *set);
t_env *ft_envar(char **env);
void ft_syntax_err(t_data *data);
t_list *my_token(char *str);
// void	ft_free_(char **tab);
/////////////////////////////////////
char *ft_del_qs(char *);
int is_dlr(char c);
char *check_attched_quoets(char *str);
void	frfr(char *str, char *ptr);
int	accs(char *path);
void	tofork(t_data *data, int fd2);
int	ft_strcmp(const char *s1, const char *s2);
void export(t_data *data, char** val);
int sheegal(char *conten);

////////////////////////////////
void cd(t_data *data);
void export(t_data *data, char** val);
void echo(char **cmd);
void cd(t_data *data);
void pwd(char *pwd);
void	unset(t_data *data, char **cmd);
void env(t_env *env);
void	ft_exit(t_data *data, char **cmd);

///////////////////////////
void free_list(t_list *lst);
void free_env(t_env *lst);
void free_all_exit(t_data *data, int ref);
void free_after_split(char **tab);
void search_herdoc_and_redirection(t_list *cmd, char *str);


// void ft_putstr_fd(char *str, int fd);




// t_list *convert(t_list *cmnd);


#endif