/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:12:56 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 22:31:44 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_variable = 0;

int	start(char **envp)
{
	int		quit;
	t_datas	*datas;

	quit = 0;
	using_history();
	datas = (t_datas *)malloc(sizeof(t_datas));
	datas->command = NULL;
	datas->env = envp_to_alloc_tab(envp, &datas->len_env);
	while (!quit)
	{
		catch_sig();
		datas->command = readline("Minishell $> ");
		quit = (!datas->command);
		if (!quit && datas->command && *datas->command)
		{
			add_history(datas->command);
			if (interpret_command(datas))
				free_tree(datas->head);
		}
		free(datas->command);
	}
	ft_freetab(datas->env);
	free(datas);
	printf("exit\n");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Minishell: too many arguments\n", 2);
		return (0);
	}
	return (start(envp));
}
