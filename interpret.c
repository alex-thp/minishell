/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:10:27 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 21:42:07 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_command(t_datas *datas, t_node *tmp, char **parsed_command)
{
	int	pid;

	pid = 0;
	datas->head = create_node(parsed_command[0]);
	tmp = datas->head;
	tmp->redir = init_redir(parsed_command[0], datas);
	if (tmp->redir != NULL)
	{
		datas->head = tmp;
		datas->head->cmd = create_cmd(datas->head->line);
		if (is_execve(datas->head->cmd->name) == -1)
		{
			pid = fork();
			if (pid == 0)
				first(datas->head, datas);
			g_variable = ft_wait(pid);
		}
		else
		{
			datas->head = init_node(datas->head, 1);
			g_variable = exec_builtin(datas->head, datas);
		}
	}
}

int	interpret_command(t_datas *datas)
{
	char	**parsed_command;
	t_node	*tmp;

	datas->here_doc_limit = 0;
	tmp = NULL;
	signal(SIGINT, &ft_sigreset);
	parsed_command = lexer(datas->command, datas);
	if (parsed_command == NULL)
		return (0);
	if (parsed_command[1])
	{
		datas->head = create_tree(parsed_command);
		tmp = get_redir_tree(datas->head, datas);
		if (tmp != NULL)
		{
			datas->head = tmp;
			execute_tree(datas->head, datas);
		//	g_variable = ft_wait(0);
		}
	}
	else
		single_command(datas, tmp, parsed_command);
	ft_freetab(parsed_command);
	return (1);
}
