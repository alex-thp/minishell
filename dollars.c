#include "minishell.h"

int		is_finished(char *str)
{
	int		i;

	i = 1; //on passe le premier '
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == 0)
		return (-1);
	return (i);
}
char	*add_variable_to_str(char *result, int i, t_datas *datas)
{
	char 	*str;
	char	*tmp;
	int		j;
	
	tmp = interpret_dollar(&result[i + 1], datas);
	if (!tmp)
		return(result);
	str = malloc(sizeof(char) * (ft_strlen(result) + ft_strlen(tmp)) + 1);
	j = 0;
	while (j < i)
	{
		str[j] = result[j];
		j++;
	}
	i = 0;
	while(tmp[i])
	{
		str[j + i] = tmp[i];
		i++;
	}
	i += j;
	while(result[j] && result[j] != ' ')
		j++;
	while (result[j])
	{
		str[i] = result[j];
		j++;
		i++;
	}
	str[i] = 0;
	free(result);
	return (str);
}
char	*dollar_interpretation(char *str, t_datas *datas)
{
	int		i;
	char	*result;

	i = 0;
	result = str;
	while (result[i])
	{
		while (result[i] && result[i] != '\'')
		{
			if (result[i] == '$')
				result = add_variable_to_str(result, i, datas);
			i++;
		}
		if (result[i] == '\'')
		{
			if (is_finished(&result[i]) != -1)
				i = is_finished(&result[i]);
			else
				return (result);
			i++;
		}
	}
	return (result);
}