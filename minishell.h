/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:18:55 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 16:52:05 by adylewsk         ###   ########.fr       */
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
# include <dirent.h>
# include "libft/libft.h"

/*
**	Ici notre variable globale qui nous permet de stocker la valeur du retour de la derniere commande
*/

extern int _variable;

/*
 * struct ENV
 */

typedef struct s_datas
{
	char			*command;
	char			**env;
	int				len_env;
	struct s_node	*head;
	int				here_doc_limit;
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

typedef struct s_in_list
{
	int					fd;
	char				*filename;
	struct s_in_list	*next;
}				t_in_list;

typedef struct s_redirection
{
	t_in_list	*in_list;
	char		*file_out;
	int			append;
	int			fd_in;
	int			fd_out;
}				t_redirection;

/*
 * manage_env.c
 */

t_datas			*manage_env(t_datas *datas);
char			**envp_to_alloc_tab(char **envp, int *len_env);
int				get_envindex(char **env, char *var);
char			*get_value(char *env);
int				change_env_value(char **env, char *var);

/*
 * create_tree.c
 */

t_redirection	*create_redir(char *command);
t_command		*create_cmd(char *command);
t_node			*create_node(char *command);
t_node			*create_tree(char **command);
t_node			*init_node(t_node *node, int is_builtins);

/*
 * utils_tree.c
 */

char			*get_value2(char *str, int i);
int				is_special(char c, char *str);

/*
 * lexer.c
 */

int				check_pipe_error(char *command);
char			**lexer(char *command, t_datas *datas);

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

int				ft_echo(char **strs, t_node *head);
int				ft_pwd(t_node *head);
int				ft_export(char ***env, int *len_env, char *var);
int				ft_unset(char **env, char *var);

/*
 * builtins2.c
 */

int				ft_cd(char **args, t_datas *datas);
int				ft_env(char **env, t_node *head);
int				ft_exit(t_datas *datas, t_node *head);
int				redir_builtins(t_node *head);

/*
 * interpret.c
 */

int				interpret_command(t_datas *datas);
int				ft_wait(int pid);

/*
 * signal.c
 */

void			ft_sigreset(int signal);
void			ft_sighere(int signal);
void			ft_sigchild(int signal);
void			ft_sigherechild(int signal);
int				catch_sig(void);

/*
 * exit.c
 */

void			free_tree(t_node *head);
t_in_list		*free_in_list(t_in_list *list);
t_redirection	*free_redir(t_redirection *redir);

/*
 * is_execve.c
 */

int				is_execve(char *name);
int				exec_builtin(t_node *head, t_datas *datas);

/*
 * utils.c
 */

char			*search_for_home(t_datas *datas);
void			modify_env(char *to_replace, char *to_insert, t_datas *datas);
char			*interpret_dollar(char *str, t_datas *datas);
int				go_home(t_datas *datas);
int				ft_check_dir(char **args);

/*
 * parsing.c
 */

char			**ft_custom_split(char *str, t_datas *datas);
char			**parse_command(char *str, t_datas *datas);
int				ft_look(char *str, int i, char type);
int				ft_look2(char *str, int i, char type);
int				ft_closed_quote(char *str);
char			*erase_quotes(char *str);

/*
 * dollars.c
 */

char			*dollar_interpretation(char *str, t_datas *datas);

/*
 * redir.c
 */

t_redirection	*init_redir(char *command, t_datas *datas);
t_node			*get_redir_tree(t_node *head, t_datas *datas);

#endif
