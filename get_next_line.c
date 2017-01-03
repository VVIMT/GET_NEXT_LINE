/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinvimo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 07:06:31 by vinvimo           #+#    #+#             */
/*   Updated: 2017/01/03 13:18:05 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_list	*find_file(t_list **file, int fd)
{
	t_list *tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

void			fill_line(int *i, char *tmp, char **line)
{
	*i = -1;
	while (tmp[++*i] && tmp[*i] != '\n')
		*(*line + *i) = tmp[*i];
	*(*line + *i) = 0;
}

int				get_next_line_bis(int fd, int *i, char **line, t_list *lst)
{
	char	*tmp;
	char	*buff;

	buff = ft_strnew(BUFF_SIZE + 1);
	if (BUFF_SIZE <= 0 || read(fd, buff, 0) < 0)
		return (-1);
	ft_bzero(buff, BUFF_SIZE);
	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		tmp = ft_strdup(lst->content);
		free(lst->content);
		if (!(lst->content = ft_strjoin(tmp, buff)))
			return (-1);
		ft_bzero(buff, BUFF_SIZE);
		free(tmp);
	}
	free(buff);
	tmp = (char*)lst->content;
	while (tmp[*i] && tmp[*i] != '\n')
		(*i)++;
	if (!(*line = ft_strnew(*i + 1)))
		return (-1);
	fill_line(i, tmp, line);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int				i;
	char			*tmp;
	static	t_list	*file;
	t_list			*lst;

	i = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	lst = find_file(&file, fd);
	if (get_next_line_bis(fd, &i, line, lst) == -1)
		return (-1);
	if (*((char*)lst->content) == 0)
		return (0);
	tmp = ft_strdup(lst->content);
	ft_strclr(lst->content);
	if (tmp[i] == 0)
		ft_strcpy(lst->content, tmp + i);
	else if (tmp[i] == '\n')
		ft_strcpy(lst->content, tmp + i + 1);
	free(tmp);
	return (1);
}
