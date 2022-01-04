#include "minishell.h"

// static	int	ft_nbrword(char *str, char c)
// {
// 	int	i;
// 	int	nb_word;

// 	i = 0;
// 	nb_word = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
// 			nb_word++;
// 		i++;
// 	}
// 	return (nb_word);
// }

// static	int	ft_strlenpart(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != c)
// 		i++;
// 	return (i);
// }

// static	char	*ft_strduppart(char **src, char c)
// {
// 	int		i;
// 	char	*cpy;

// 	i = 0;
// 	cpy = malloc(sizeof(char) * (ft_strlenpart(*src, c) + 1));
// 	if (!cpy)
// 		return (0);
// 	while (**src && **src != c)
// 	{
// 		cpy[i] = **src;
// 		*src += 1;
// 		i++;
// 	}
// 	cpy[i] = 0;
// 	return (cpy);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	char	**tab;
// 	char	*save;

// 	i = 0;
// 	save = (char *)s;
// 	if (!save)
// 		return (NULL);
// 	tab = ft_calloc(ft_nbrword(save, c) + 1, sizeof(char *));
// 	if (!tab)
// 		return (NULL);
// 	if (save && *save && *save != c)
// 		tab[i] = ft_strduppart(&save, c);
// 	if (tab[i] != 0)
// 		i++;
// 	while (save && *save && *save == c)
// 	{
// 		save++;
// 		if (*save && *save != c)
// 		{
// 			tab[i] = ft_strduppart(&save, c);
// 			i++;
// 		}
// 	}
// 	return (tab);
// }

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
	//printf("|||||||||||||count = %d||||||||||\n", count);
	return (count);
}

char	**ft_custom_split(char *str)
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
		index++;
		j++;
	}
//	result[j] = NULL;
	return (result);
}

char	**parse_command(char *str)
{
	char	**tab;

	tab = ft_custom_split(str);
	ft_puttab(tab);
	return (tab);
}
