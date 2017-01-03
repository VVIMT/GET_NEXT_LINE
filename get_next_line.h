/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinvimo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 07:06:45 by vinvimo           #+#    #+#             */
/*   Updated: 2017/01/03 13:20:12 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 999

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

int	get_next_line(const int fd, char **line);

#endif
