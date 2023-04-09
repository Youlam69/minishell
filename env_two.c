/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:36:48 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 23:37:52 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
