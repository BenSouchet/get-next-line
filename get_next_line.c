/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:36:34 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/02 19:51:41 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_read(char *all, int const fd, int *ret)
{
	char	*tmp;
	char	*buf;

	if (!(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (NULL);
	if ((*ret = read(fd, buf, BUFF_SIZE)) != -1 && *ret > 0)
	{
		buf[*ret] = '\0';
		tmp = ft_strjoin(all, buf);
		free(all);
		free(buf);
		all = tmp;
	}
	return (all);
}

static int		ft_check(char **all, int ret)
{
	if (ret == 0 && ft_strlen(*all) != 0)
	{
		*all = ft_strnew(1);
		return (1);
	}
	else if (ret == 0 && !(ft_strlen(*all)))
		return (0);
	return (-1);
}

int				get_next_line(int const fd, char **line)
{
	int				ret;
	char			*str;
	static char		*all = NULL;

	ret = 1;
	if ((fd < 0 || !line || BUFF_SIZE < 1) ||
			(!all && !(all = (char *)malloc(sizeof(char) * 1))))
		return (-1);
	while (ret > 0)
	{
		if (!(all = ft_read(all, fd, &ret)))
			return (-1);
		if ((str = ft_strchr(all, '\n')) != NULL)
		{
			*str = '\0';
			if (!(*line = ft_strdup(all)))
				return (-1);
			ft_memmove(all, str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
	}
	if (!(*line = ft_strdup(all)))
		return (-1);
	return (ft_check(&all, ret));
}
