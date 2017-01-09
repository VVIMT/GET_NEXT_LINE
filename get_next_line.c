/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinvimo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 07:06:31 by vinvimo           #+#    #+#             */
/*   Updated: 2017/01/09 22:22:58 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl			*ft_newfile(void const *content, size_t fd)
{
	t_gnl	*file;

	if (!(file = (t_gnl*)malloc(sizeof(t_gnl))))
		return (NULL);
	if (content)
	{
		file->fd = fd;
		file->content = ft_memalloc(1);
		ft_memcpy(file->content, content, 1);
	}
	else
	{
		file->content = NULL;
		file->fd = 0;
	}
	file->next = NULL;
	return (file);
}

static	t_gnl	*find_file(t_gnl **file, int fd)
{
	t_gnl	*tmp;

	tmp = *file;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_newfile("\0", fd);
	tmp->next = *file;
	*file = tmp;
	tmp = *file;
	return (tmp);
}

int				fill_line(int sig, int *i, char **line, t_gnl *lst)
{
//	int		x;

	if (sig == 1)
	{
		*i = 0;
		while (lst->content && lst->content[*i] && lst->content[*i] != '\n')
			(*i)++;
		ERRORCHECK((*line = ft_strnew(*i + 1)));
		*i = -1;
		while (lst->content && lst->content[++(*i)] && lst->content[*i] != '\n')
			*(*line + *i) = lst->content[*i];
		*(*line + *i) = 0;
	}
/*	else if (sig == 0)
	{
		x = 0;
		while (lst->content && lst->content[x])
		{
			if (lst->content[x] == '\n' && lst->content[x + 1])
				sig = x;
			x++;
		}
ft_putnbr(x);
ft_putchar(':');
ft_putnbr(sig);
ft_putchar('\n');
		lst->content[sig] = 0;
		ERRORCHECK((*line = ft_strnew(x - sig + 1)));
		ft_strcpy(*line, lst->content + sig);
//ft_putendl(*line);
	}*/
	return (1);
}

int				read_loop(char *buff, char **line, t_gnl *lst)
{
	char	*tmp;

	ERRORCHECK((buff = ft_strnew(BUFF_SIZE + 1)));
	ft_bzero(buff, BUFF_SIZE + 1);
	if (read(lst->fd, buff, 0) < 0)
		return (-1);
	while (read(lst->fd, buff, BUFF_SIZE) > 0)
	{
		tmp = lst->content;
		ERRORCHECK((lst->content = ft_strjoin(lst->content, buff)));
		ft_strdel(&tmp);
		ft_bzero(buff, BUFF_SIZE + 1);
		if (lst->fd == 0)
			ERRORCHECK(fill_line(0, NULL, line, lst));
	}
	ft_strdel(&buff);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int				i;
	char			*tmp;
	static	t_gnl	*file = NULL;
	t_gnl			*lst;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	ERRORCHECK((lst = find_file(&file, fd)));
	if (read_loop(NULL, line, lst) == -1)
		return (-1);
	ERRORCHECK(fill_line(1, &i, line, lst));
	if (!(lst->content) || *(lst->content) == 0)
		return (0);
	if (lst->content[i] == '\n')
		i++;
	ERRORCHECK((tmp = ft_strdup(lst->content + i)));
	ft_strclr(lst->content);
	ft_strcpy(lst->content, tmp);
	ft_strdel(&tmp);
	return (1);
}
