/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinvimo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 07:06:31 by vinvimo           #+#    #+#             */
/*   Updated: 2017/01/05 23:46:26 by vinvimo          ###   ########.fr       */
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

int				read_loop(int *i, char *buff, t_gnl *lst)
{
	char	*tmp;

	if (read(lst->fd, buff, 0) < 0)
		return (-1);
	while (read(lst->fd, buff, BUFF_SIZE) > 0)
	{
		ERRORCHECK((tmp = ft_strdup(lst->content)));
		free(lst->content);
		ERRORCHECK((lst->content = ft_strjoin(tmp, buff)));
		ft_bzero(buff, BUFF_SIZE + 1);
		free(tmp);
	}
	*i = 0;
	while (lst->content && lst->content[*i] && lst->content[*i] != '\n')
		(*i)++;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int				i;
	char			*buff;
	static	t_gnl	*file = NULL;
	t_gnl			*lst;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	lst = find_file(&file, fd);
	ERRORCHECK((buff = ft_strnew(BUFF_SIZE + 1)));
	ft_bzero(buff, BUFF_SIZE + 1);
	if (read_loop(&i, buff, lst) == -1)
		return (-1);
	free(buff);
	ERRORCHECK((*line = ft_strnew(i + 1)))
	i = -1;
	while (lst->content && lst->content[++i] && lst->content[i] != '\n')
		*(*line + i) = lst->content[i];
	*(*line + i) = 0;
	if (!(lst->content) || *(lst->content) == 0)
		return (0);
	if ((lst->content = ft_strchr(lst->content, '\n')))
		(lst->content)++;
	return (1);
}
