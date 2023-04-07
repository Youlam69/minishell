#include "./minishell.h"

typedef struct s_list
{
    void    *content;
    struct s_list *next;
}   t_list;

void	ft_lstdelone(t_list *lst)
{
	if (!lst || !lst->content)
		return ;
    free(lst->content);
    lst->content = NULL;
	free(lst);
    lst = NULL;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		ft_lstdelone(curr);
		curr = next;
	}
	*lst = NULL;
}

void    ft_exit(t_list *holder, int status)
{

    ft_lstclear(holder);
    exit(status);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void *ft_malloc(void *ptr)
{
    static t_list   *holder;
    t_list          *new;
    if(!ptr)
        ft_exit(holder, 1);
    new = ft_lstnew(ptr);
    if (!new)
    {
        free(ptr);
        ft_exit(holder, 1);
    }
    ft_lstadd_front(&holder, new);
    return (ptr);
}

