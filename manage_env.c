/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:39:30 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/10 16:18:30 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_name(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*get_name(char *env)
{
	int		i;
	int		j;
	char	*name;

	i = get_size_name(env);
	j = 0;
	name = malloc(sizeof(char) * i);
	name[i - 1] = 0;
	while (j < i)
	{
		name[j] = env[j];
		j++;
	}
	return (name);
}

char	*get_value(char *env)
{
	int		i;
	int		j;
	char	*value;

	j = 0;
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	while (env[i + j])
		j++;
	value = malloc(sizeof(char) * j);
	value[j - 1] = 0;
	j = 0;
	while (env[i + j])
	{
		value[j] = env[i + j];
		j++;
	}
	return (value);
}

int	get_envindex(char **env, char *var)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = ft_strlen(var);
	while (env[i])
	{
		if (!ft_memcmp(env[i], var, len_var) && (env[i][len_var] == '='))
			return (i);
		i++;
	}
	return (-1);
}

char	**envp_to_alloc_tab(char **envp, int *len_env)
{
	char	**new;
	int		i;

	*len_env = ft_tablen(envp);
	new = ft_calloc(*len_env + 1, sizeof(char *));
	i = 0;
	while (i < *len_env)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new);
}

//t_env	*create_new(char *name, char *value)
//{
//	t_env	*new;
//
//	new = malloc(sizeof(t_env));
//	new->name = name;
//	new->value = value;
//	new->previous = NULL;
//	new->next = NULL;
//	return (new);
//}
//
//void	push_last(t_ptr_env *list, t_env *new)
//{
//	if (!new)
//		return;
//	new->next = NULL;
//	new->previous = list->last;
//	if (list->last)
//		list->last->next = new;
//	else
//		list->first = new;
//	list->last = new;
//}
//
//void	init_list(t_ptr_env *list)
//{
//	list->first = NULL;
//	list->last = NULL;
//}
//
//t_datas	*manage_env(t_datas *datas)
//{
//	char		**copy;
//	t_env		*new;
//	
//	t_env		*tmp;
//	init_list(&datas->env);
//	copy = datas->base_env;
//	while(*copy)
//	{
//		new = create_new(get_name(*copy), get_value(*copy));
//		push_last(&datas->env, new);
//		copy++;
//	}
//	tmp = datas->env.first;
//	while (tmp)
//	{
//		//printf("name : %s=%s\n", tmp->name, tmp->value);
//		tmp = tmp->next;
//	}
//
//
//	// list = (t_env *)malloc(sizeof(t_env));
//	// copy = datas->base_env;
//	// tmp = NULL;
//    // while (*copy)
//    // {
//	// 	if ()
//	// 	//printf("list->previous [%p], list->next [%p]\n", list->previous, list->next);
//    //     copy++;
//    // }
//	// while (list->previous != NULL)
//	// {
//	// 	list = list->previous;
//	// 	//printf("%p\n", list->previous);
//	// }
//	return (datas);
//}
