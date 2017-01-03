/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinvimo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:21:56 by vinvimo           #+#    #+#             */
/*   Updated: 2016/11/07 19:21:58 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	if ((str = (char *)malloc(sizeof(char) * (size + 1))))
	{
		i = 0;
		while (i < size + 1)
		{
			str[i] = '\0';
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
