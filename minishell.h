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
	char			*herdoc;
	int				her_exist;
	int				index;
	char			*cmdp;
	char			*heredocstr;
	int				fdinout[2];
	char			*content;
	char			**cmd;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*var;
	char			*val;
	int				print_env;
	struct s_env	*next;
}	t_env;

typedef struct s_rdr
{
	int		i;
	int		j;
	int		s;
	char	*t1;
	char	*t2;
	char	*t3;
}	t_rdr;

typedef struct s_envv {
	t_env	*tmp;
	t_env	*tmp2;
	char	*vl;
}	t_envv;

typedef struct s_data
{
	int			nbrcmd;
	int			exit_status;
	char		**splitedp;
	char		*pwd;
	char		*homep;
	char		**envc;
	t_env		*env;
	t_list		*cmd;
}	t_data;

void	free_unset(t_env **env, t_env *tmp_env);
void	ft_putstr_3d(char *str1, char *str2, char *str3, char *str4);
void	ft_putstr_fd(char *str, int fd);
int		check_implmnt(t_data *data);
char	*ft_strdup(char *s1);
char	*ft_itoa(int nbr);
int		ft_lstsize(t_list *lst);
int		is_alpha(char c);
int		is_good(char c);
int		is_digit(char c);
int		is_dq(char c);
int		is_q(char c);
int		is_pipe(char c);
int		is_rinp(char c);
int		is_routp(char c);
int		ft_strlen(char *s);
t_list	*parsing(char *str, t_data *data);
int		is_special(char c);
char	*ft_substr(char *s,int start, int len);
char	**ft_split(char *st, char c);
char    *strjoin(char *dst, char *src);
int		ft_atoi(char *str);
char	*ft_strtrim(char *s1, char *set);
t_env	*ft_envar(char **env);
void	ft_syntax_err(t_data *data);
t_list	*my_token(char *str);
/////////////////////////////////////
char	*ft_del_qs(char *);
int		is_dlr(char c);
char	*check_attched_quoets(char *str);
void	frfr(char *str, char *ptr);
int		accs(char *path);
void	tofork(t_data *data, int fd2);
int		ft_strcmp(const char *s1, const char *s2);
void	export(t_data *data, char** val);
char	*check_q(char *str, t_data *data);
char	*check_dq(char *str, t_data *data);
char	*check_d_pip(char *str, t_data *data);
void	change_nl_tabs_to_space(char *str);
int		sheegal(char *conten);
////////////////////////////////
void	joinpath(t_data *data);
char	**splitpath(t_env *env);

///////////////////////////////
void	cd(t_data *data);
void	export(t_data *data, char **val);
void	echo(char **cmd);
void	cd(t_data *data);
void	pwd(char *pwd);
void	unset(t_data *data, char **cmd);
void	env(t_env *env);
void	ft_exit(t_data *data, char **cmd);

///////////////////////////
void	free_list(t_list *lst);
void	free_env(t_env *lst);
void	free_all_exit(t_data *data, int ref);
void	free_after_split(char **tab);
// void search_herdoc_and_redirection(t_list *cmd, char *str);
char	*check_redirection_in(t_list *cmd, char *str);
char	*check_redirection_out(t_list *cmd, char *str);
char	*check_heredoc(t_list *cmd, char *str);
char	*check_outapend(t_list *cmd, char *str);
char	*convet_value(char *str);
int		check_name_reinout(char *str, int j);
int		check_error_and_space_reinout(char *str, int s);
void	ft_putndl_fd(char *str, int fd);
char *ft_strjoin(char *s1, char *s2);
int tt(char *str);
void	reset_rdr(t_rdr *tmp);
void	ft_lstadd_back(t_env **alst, t_env *new);
int	ft_isdigit(char c);
int	ft_atoi(char *str);
void	shlvl_anex(t_env *ev);
void	shlvl(t_env *ev);
t_env	*ft_envar(char **env);
t_env	*ft_lstnew(char *content);
char	*ft_valu(char *content);
char	*ft_variab(char *content);
int	sheegal(char *conten);
int	ft_strrrcmp(char *str1, char *str2);
void	tofork(t_data *data, int fd2);
void	tofork_plus(int *pid, t_data *data, int *fdp);
void	parent(t_data *data, int *fdp);
void	child(t_data *data, int *fdp, int fd2);
void	dup_close(int in, int out );
void	exec_imp(t_data *data, int imp, int ref);
void	hadler_quit(int sig);
void	handler_c(int sig);
void	child_help(t_list *cmd, t_data *data, int *fdp, int fd2);
t_env	*ft_lstnew_export(char *var, char *val);
int	check_var(char *var, char *arg);
int	add_to_env_plus(t_envv *tmp, char *var, char *val, t_env **env);
t_env	*add_to_env(char *var, char *val, t_env *env, int j);
t_env	*split_export(char *arg, t_env *env);
void	annex_exit(t_data *data, char *cmd, int i);
int	ft_strlen(char *s);
void	unset_var(t_env **env, char *var);
int	ft_strncmp(char *s1, char *s2, int n);
void	init_data(t_data *data);
int	valid_var(char c);
char	*check_dollars(char *str, t_data *data);
void	dollar_start(char **str, t_data *data, t_rdr *tmp);
int	ft_cmd(t_list *tmp);
char	*ft_del_qs(char *str);
int	ft_autre_carac(char *str, int n, t_list **ptr);
t_list  *my_token(char *str);
int	skeap_space(char *str, int i);
char	*check_attched_quoets(char *str);
char	*anex_del_qs(char *str, int len);
t_list	*new_node(int debu, int siz, char *str, int index);
void	add_back_node(t_list **head, t_list *new);
char    *strjoin(char *dst, char *src);
void	strjoin_help(char *src, int *i, char *tmp);
void	*ft_calloc(int count, int size);
int	ft_strlcat(char *dst, char *src, int size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	loop_over_j(char *str, t_rdr *tmp);
int	redir_assist(t_rdr *tmp, t_list *cmd, char **str);
// char	*check_redirection_in(int *tab, char *str, t_list *cmd);

#endif
