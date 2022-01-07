#include "minishell.h"

char	*dollar_interpretation(char *str, t_datas *datas)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'')
		{
			if (str[i] == '$')
			{
				interpret_dollar(&str[i], datas); //inserer ce char* à la place du dollar
			}
			i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		c = str[i];
		if (c == 0)
			return (str);
		i++;
	}
	i++; //on passe le guillemet ouvrant
	while (str[i] && str[i] != c)
		i++;
}