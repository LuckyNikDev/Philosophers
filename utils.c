/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsailor <bsailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:27:11 by bsailor           #+#    #+#             */
/*   Updated: 2021/08/12 18:27:25 by bsailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_numlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= (long) 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long n)
{
	char	*s;
	long	nn;
	int		i;

	i = 0;
	nn = n;
	i = ft_numlen(n);
	s = (char *)malloc(i + 1);
	if (s == NULL)
		return (NULL);
	if (nn == 0)
	{
		s[i] = '\0';
		s[0] = 0 + 48;
		return (s);
	}
	s[i--] = '\0';
	while (nn != 0)
	{
		s[i--] = (nn % 10) + 48;
		nn /= (long)10;
	}
	return (s);
}

char	*ft_strjoin(char *s1, char *s2, char *s3, char *s4)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, (ft_strlen(s1) + 1));
	ft_strlcpy(&str[ft_strlen(s1)], s2, (ft_strlen(s2) + 1));
	ft_strlcpy(&str[ft_strlen(s1) + ft_strlen(s2)], s3, (ft_strlen(s3) + 1));
	ft_strlcpy(&str[ft_strlen(s1) + \
	ft_strlen(s2) + ft_strlen(s3)], s4, (ft_strlen(s4) + 1));
	free(s1);
	free(s3);
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			count;
	int				i;

	if (dst == NULL && src == NULL)
		return (0);
	count = 0;
	i = 0;
	while (src[i] != '\0')
	{
		count++;
		i++;
	}
	i = 0;
	if (size != 0)
	{
		size--;
		while (size && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
			size--;
		}
		dst[i] = '\0';
	}
	return (count);
}
