/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_to_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:46:50 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/08 09:44:48 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	i = 0;
	if (len + start > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (start >= ft_strlen((char *)s))
		return (str);
	if (str == NULL)
		return (NULL);
	while (i <= len && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_count_word(char const *s, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i] != '\n' && s[i] != ',')
	{
		if (!ft_isdigit(s[i]) && s[i] != '-')
			return (0);
		size++;
		i++;
	}
	return (size);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*k;

	k = s;
	while (n != 0)
	{
		*k = 0;
		k++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;
	size_t			i;

	if (size != 0 && SIZE_MAX / size < count)
		return (NULL);
	i = 0;
	tab = malloc(size * count);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}

char *get_word(const char *s, int i)
{
	char *str;
	int j;

	str = calloc(8, sizeof(char));
	if (!str)
		return (NULL);
		j = 0;
	while (s[i] != ' ' && s[i] != '\n')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	return (str);
}

int	base_pos(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ahextoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r' )
		i++;
	nb = 0;
	while (str[i])
	{
		nb = nb * 16 + base_pos(str[i], "0123456789ABCDEF");
		i++;
	}
	return (nb);
}

int	ft_split_hex_color(const char *s, int i)
{
	char	*str;
	int		j;
	int		count;

	j = i;
	count = 0;
	while (s[j] && s[j - 1] != ',')
	{
		if (s[j] == ' ' || s[j] == '\n')
			return (0xFFFFFF);
		j++;
	}
	if (s[j] == 0)
		return (0);
	while (s[j] && s[j++] != ' ')
		count++;
	str = malloc(count * sizeof(char));
	if (!str)
		return (0);
	i+=4;
	j = 0;
	while (s[i] != ' ')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (ahextoi(str));
}

t_array	ft_split_to_int(char const *s, char c)
{
	int		i;
	int		word;
	t_array	line;
	int		j;
	int		size;

	i = 0;
	j = -1;
	word = ft_count_word(s, c);
	line.arr = malloc(word * sizeof(int));
	if (!line.arr)
		exit(1);
	line.color = malloc(word * sizeof(int));
	if (!line.color)
		exit(1);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		size = ft_size_word(s, c, i);
		line.arr[j] = ft_atoi(ft_substr(s, i, size));
		// line.color[j] = ft_split_hex_color(s, i);
		// ft_err_printf("%d", line.arr[j]);
		// ft_err_printf(",%d:%d|", line.color[j], j);
		i += size;
		while (s[i] != c && s[i])
			i++;
	}
	// printf("\n");
	return (line.size = word, line);
}
