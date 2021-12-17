/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/17 21:28:23 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!quit && command && *command)
		{
			add_history(command);
			if (interpret_command(command, datas))
				free_tree(datas->head);
		}
		free(command);
	}
	ft_freetab(datas->env);
	free(datas);
}
/*	rl_clear_history(); */
