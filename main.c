/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/15 18:55:19 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(int *pip, t_node *head, t_datas *datas)
{
	printf("%i\n", head->right->redir->fd_in);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	if (head->left)
	execute_tree(head->left, datas);

}

void	parent(int *pip, t_node *head, t_datas *datas)
{
	int		status;

	if (head->redir->fd_in >= 0)
		dup2(head->redir->fd_in, STDIN_FILENO);
	if (head->redir->fd_out >= 0)
		dup2(head->redir->fd_out, STDOUT_FILENO);
	dup2(pip[0], STDIN_FILENO);
	close(pip[1]);
	waitpid(-1, &status, 0);
	execve(check_exe(head->cmd->name, datas->env), head->cmd->args, datas->env);
}

void	execute_tree(t_node *head, t_datas *datas)
{
	int		pip[2];
	int		pid;

	pipe(pip);
	if (!(head->cmd->name)) //PIPE
	{
		pid = fork();
		if (pid == 0)
			child(pip, head, datas);
		else
			parent(pip, head->right, datas);
	}
	else{ //On est arrive a la commande en bas a gauche
		parent(pip, head, datas);
//		execve(check_exe(head->cmd->name, datas->env), head->cmd->args, datas->env);
	}
	close(pip[0]);
	close(pip[1]);
}

void	interpret_command(char *command, t_datas *datas)
{
	char	**parsed_command;
	int		pid;

	parsed_command = lexer(command);
	if (*parsed_command == NULL)
		return ;
	if (parsed_command[1])
		datas->head = create_tree(parsed_command);
	else
		datas->head = create_node_command(&command[0]);
	pid = fork();
	if (pid == 0)
	{
		execute_tree(datas->head, datas);
		exit(0);
	}
	else{
		waitpid(0, &pid, 0);
	}
	// while (datas->head)
	// {
	// 	printf("[ici : %s]\n", datas->head->cmd->name);
	// 	if (datas->head->left)
	// 		printf("[left : %s] [right : %s]\n", datas->head->left->cmd->name, datas->head->right->cmd->name);
	// 	datas->head = datas->head->left;
	// }
}

int	main(int ac, char **av, char **envp)
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
	while (!quit)
	{
		command = readline("Minishell $> ");
		quit = ((command && command[0] == 'q' && !command[1]) || !command);
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
