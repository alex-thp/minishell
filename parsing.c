#include "minishell.h"

int		ft_look(char *str, int i, char type)
{
	i++; //se positionner après type
	while (str[i] && str[i] != type)
		i++;
	if (str[i] != 0)
		return (i);
	return (-1);
}

char	*get_word(char *str, int *j)
{
	char	*result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[*j + i] && str[*j + i] != '|')
	{
		if (str[*j + i] == '\'' || str[*j + i] == '"')
		{
			if (ft_look(str, *j + i, str[*j + i]) != -1)
				i = ft_look(str, *j + i, str[*j + i]);
		}
		i++;
	}
	result = malloc(sizeof(char) * i + 1);
	result[i] = 0;
	i += *j;
	while(*j < i)
	{
		result[k] = str[*j];
		*j += 1;
		k++;
	}
	return (result);
}
int		ft_init_split(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (ft_look(str, i, str[i]) != -1)
				i = ft_look(str, i, str[i]);
		}
		else if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**ft_custom_split(char *str, t_datas *datas)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	i = ft_init_split(str);
	j = 0;
	index = 0;
	result = ft_calloc(i + 1, sizeof(char*));
	while(j < i)
	{
		result[j] = get_word(str, &index);
		result[j] = dollar_interpretation(result[j], datas);
		index++;
		j++;
	}
//	result[j] = NULL;
	return (result);
}

char	**parse_command(char *str, t_datas *datas)
{
	char	**tab;

	tab = ft_custom_split(str, datas);
	//ft_puttab(tab);
	return (tab);
}
