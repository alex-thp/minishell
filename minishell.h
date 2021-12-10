/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:18:55 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/10 16:17:44 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/*
* struct ENV
*/

typedef struct s_datas
{
	char			**env;
	int				len_env;
	struct s_node	*head;
}				t_datas;

/*
* struct ARBRE
*/

typedef struct s_node
{
	struct s_command		*cmd;
	struct s_redirection	*redir;
	struct s_node			*left;
	struct s_node			*right;
}				t_node;

typedef struct s_command
{
	char	*name;
	char	**args;
}				t_command;

typedef struct s_redirection
{
	char	*stdin_file;
	int		stdin;
	int		stdout;
}				t_redirection;

/*
* manage_env.c
*/

t_datas			*manage_env(t_datas *datas);
int				ft_unset(char **env, char *var);
int				ft_export(char ***env, int *len_env, char *var);
char			**envp_to_alloc_tab(char **envp, int *len_env);
int				get_envindex(char **env, char *var);

/*
* utils.c
*/

char			**ft_split(char const *s, char c);

/*
* create_tree.c
*/

t_redirection	*create_redir(char *command);
t_command		*create_cmd(char *command);
t_node			*create_node_command(char *command);
t_node			*create_node_pipe(void);
t_node			*create_tree(char **command);

/*
* utils_tree.c
*/

char			*get_value2(char *str, int i);
int				is_special(char c, char *str);

/*
* lexer.c
*/

int				check_pipe_error(char *command);
char			**lexer(char *command);

#endif
