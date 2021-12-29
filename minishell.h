/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:18:55 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/29 18:28:14 by ade-temm         ###   ########.fr       */
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
# include <signal.h>
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
	char					*line;
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
	int		fd_in;
	int		fd_out;
}				t_redirection;

/*
 * manage_env.c
 */

t_datas			*manage_env(t_datas *datas);
char			**envp_to_alloc_tab(char **envp, int *len_env);
int				get_envindex(char **env, char *var);
char			*get_value(char *env);

/*
 * create_tree.c
 */

t_redirection	*create_redir(char *command);
t_command		*create_cmd(char *command);
t_node			*create_node(char *command);
t_node			*create_tree(char **command);
t_node			*init_node(t_node *node);

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

/*
 * files.c
 */

char			*file_to_path(char *file, char *path);
char			**env_to_paths(char **envp);
char			*relative_path(char *file, char **envp);
char			*absolute_path(char *file, char **envp);
char			*check_exe(char *file, char **envp);

/*
 * main.c
 */

void			execute_tree(t_node *head, t_datas *datas);

/*
 * builtins.c
 */

void			ft_echo(char **strs);
void			ft_pwd(void);
int				ft_cd(char **args, t_datas *datas);
int				ft_export(char ***env, int *len_env, char *var);
int				ft_unset(char **env, char *var);
void			ft_env(char **env);

/*
 * interpret.c
 */

int				interpret_command(char *command, t_datas *datas);

/*
 * signal.c
 */

int				catch_sig();

/*
 * exit.c
 */

void			free_tree(t_node *head);

/*
 * is_execve.c
 */

int is_execve(char *name);
int exec_builtin(t_node *head, t_datas *datas);

/*
 * utils.c
 */

char	*search_for_home(t_datas *datas);
void	modify_env(char *to_replace, char *to_insert, t_datas *datas);

#endif
