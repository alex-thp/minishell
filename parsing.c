#include "minishell.h"

int		ft_look2(char *str, int i, char type)
{
	int		j;

	j = 1; //se positionner après type
	while (str[i + j] && str[i + j] != type)
		j++;
	if (str[i + j] != 0)
		return (j);
	return (-1);
}

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
			if (ft_look2(str, *j + i, str[*j + i]) != -1)
				i += ft_look2(str, *j + i, str[*j + i]);
		}
		i++;
	}
	result = malloc(sizeof(char) * (i + 1));
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

int	ft_closed_quote(char *str)
{
	int		i;
	char	quote;

	i = 1;
	if (!str || !*str)
		return (0);
	if (*str != '"' && *str != '\'')
		return(0);
	quote = *str;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

char	*erase_quotes(char *str)
{
	int		i;
	int		j;
	int		closed_quote;
	char	*result;

	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	j = 0;
	closed_quote = 0;
	while (str[i])
	{
		closed_quote = ft_closed_quote(str + i);
		if (closed_quote)
		{
			i++;
			while (closed_quote > 1)
			{
				result[j] = str[i];
				i++;
				j++;
				closed_quote--;
			}
			i++;
		}
		else
		{
			result[j] = str[i];
			j++;
			i++;
		}
	}
	result[j] = 0;
	free(str);
	return (result);
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
//		result[j] = erase_quotes(result[j]);
		index++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**parse_command(char *str, t_datas *datas)
{
	char	**tab;

	tab = ft_custom_split(str, datas);
	return (tab);
}
