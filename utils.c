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
	while((datas->env[i] && strncmp(to_replace, datas->env[i], ft_strlen(to_replace)) != 0)) //REMPLACER AVEC NOTRE STRNCMP
		i++;
	if (datas->env[i])
		datas->env[i] = to_insert;
}

char	*interpret_dollar(char *str, t_datas *datas)//envoyer la variable sans le dollar à cette fonction, elle retourne la valeur
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(datas->env[i] && strncmp(datas->env[i], str, ft_strlen(str)) != 0) //REMPLACER AVEC NOTRE STRNCMP
		i++;
	while(datas->env[i][j] && datas->env[i][j] != '=')
		j++;
	j++;
	return (&datas->env[i][j]);
}
