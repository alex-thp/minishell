/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:46:10 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/28 19:10:50 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "macro.h"

/* Len */
size_t	ft_intlen(int nbr);
size_t	ft_strlen(const char *str);
size_t	ft_tablen(char **tab);

/* Compare */
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_strisdigit(char *str);
int		ft_tabisdigit(char **tab);

/* Str */
char	**ft_split(char const *s, char c);
char	**ft_splits(char const *str, char *cutter);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* Memory */
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *s, int c, size_t n);

/* Char */
int		ft_tolower(int c);
int		ft_toupper(int c);

/* Calculate */
long	ft_pow(long nbr, long exp);

/* Convert */
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

/* Put */
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_printf(const char *format, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_puttab(char **tab);

/* Files */
int		get_next_line(int fd, char **line);

/* Alloc */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* Free */
int		ft_freetab(char **tab);

#endif
