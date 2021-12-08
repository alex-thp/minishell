/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/08 17:31:21 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_pipe_error(char *command) //return 1 = error || return 0 = ok
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (command[i] == 32)
		i++;
	if (command[i] == '|')
		return(1);
	while (command[i])
	{
		j = 0;
		k = 1;
		while(command[i + k] && command[i + k] != '|')
		{
			if (command[i + k] != 32)
				j++;
			k++;
		}
		if (j == 0 && command[i + k])
			return (1);
		i += k;
	}
	return (0);
}

char	**lexer(char *command)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	if (check_pipe_error(command) == 1)
	{
		printf("error with pipe\n");
		return (NULL);
	}
	result = ft_split(command, '|');
	return (result);
}
int		is_special(char c, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
char	*get_value2(char *str, int i)
{
	int	j;
	char	*result;

	str[i] = ' ';
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i + j] && is_special(str[i + j], " <>") == 0)
		j++;
	result = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (str[i + j] && is_special(str[i + j], " <>") == 0)
	{
		result[j] = str[i + j];
		str[i + j] = ' ';
		j++;
	}
	result[j] = 0;
	return (result);
}

t_redirection	*create_redir(char *command)
{
	int				i;
	int				j;
	int				fd;
	t_redirection	*redir;
	char			*to_open;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	redir->stdin = -2;
	redir->stdout = -2;
	redir->stdin_file = NULL;
	i = 0;
	while (command[i] != 0)
	{
		if (command[i] == '<' || command[i] == '>' )
		{
			j = 0;
			if (command[i] == '<')
			{
				if (redir->stdin_file)
					free(redir->stdin_file);
				redir->stdin_file = get_value2(command, i);
			}
			else if (command[i] == '>')
			{
				to_open = get_value2(command, i);
				fd = open(to_open, O_CREAT | O_RDWR | O_TRUNC, 00664);
				free(to_open);
				redir->stdout = fd;
			}
		}
		i++;
	}
	return (redir);
}

t_command	*create_cmd(char *command)
{
	t_command	*cmd;
	char		**args;

	cmd = (t_command *)malloc(sizeof(t_command));
	args = ft_split(command, ' ');
	if (args)
	{
		cmd->name = args[0];
		cmd->args = args;
	}
	return (cmd);

}

t_node	*create_node(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->redir = create_redir(command);
	node->cmd = create_cmd(command);
	// printf("cmd->name %s\nstdin: %s\ncmd->args :\n", node->cmd->name, node->redir->stdin_file);
	// ft_puttab(node->cmd->args);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*create_tree(char **command)
{
	int		i;
	t_node	*head;

	i = 0;
	while(command[i])
		i++;
	while (i > 0)
	{
		i--;
		head = create_node(command[i]);
	}
	return (head);
}

void	interpret_command(char *command, t_datas *datas)
{
	char	**parsed_command;

	parsed_command = lexer(command);
	if (parsed_command == NULL)
		return ;
	datas->head = create_tree(parsed_command);
	// while (*parsed_command)
	// {
	// 	printf("%s\n", *parsed_command);
	// 	parsed_command++;
	// }
	//printf("la commande : %s\n", command);
}
 //print l'env : printf("%s\n", *(env->g_env));

int		main(int ac, char **av, char **envp)
{
	char	*command;
	int		quit;
	t_datas	*datas;

	(void)ac;
	(void)av;
	command = NULL;
	quit = 0;
	using_history();
	datas = (t_datas *)malloc(sizeof(t_datas));
	datas->env = envp_to_alloc_tab(envp, &datas->len_env);
	//datas = manage_env(datas);
	/* Builtin ENV
	while(tmp->next)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	*/
	while (!quit)
	{
		command = readline("Minishell $> ");
		quit = (command && command[0] == 'q' && !command[1]) || !command;
		if (!quit)
		{
			add_history(command);
			interpret_command(command, datas);
		}
		free(command);
	}
	//rl_clear_history();
	ft_freetab(datas->env);
	free(datas);
}
