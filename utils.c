#include "minishell.h"

char	*search_for_home(t_datas *datas)
{
	int		i;

	i = 0;
	while(strncmp(datas->env[i], "HOME", 4) != 0) //REMPLACER AVEC NOTRE STRNCMP
		i++;
	return (datas->env[i]);
}

void	modify_env(char *to_replace, char *to_insert, t_datas *datas)
{
	int		i;

	i = 0;
	while(strncmp(to_replace, datas->env[i], ft_strlen(to_replace)) != 0) //REMPLACER AVEC NOTRE STRNCMP
		i++;
	datas->env[i] = to_insert;
}
