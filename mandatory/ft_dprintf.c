/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:30:22 by fli               #+#    #+#             */
/*   Updated: 2024/07/02 10:11:14 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_dprintf_s(va_list arg_ptr, int *count, int fd)
{
	char	*s;

	s = va_arg(arg_ptr, char *);
	if (s == NULL)
	{
		ft_putstr_fd("(null)", fd);
		*count = *count + 6;
		return ;
	}
	ft_putstr_fd(s, fd);
	*count = *count + ft_strlen(s);
}

int	ft_dprintf(int fd, const char *entry, ...)
{
	int		i;
	int		count;
	va_list	arg_ptr;

	if (entry == NULL)
		return (-1);
	va_start(arg_ptr, entry);
	i = 0;
	count = 0;
	while (entry[i] != '\0')
	{
		if (entry[i] == '%' && entry[++i] == 's')
		{
			i++;
			ft_dprintf_s(arg_ptr, &count, fd);
			i++;
		}
		else
		{
			ft_putchar_fd(entry[i], fd);
			count = count + 1;
			i++;
		}
	}
	return (count);
}
