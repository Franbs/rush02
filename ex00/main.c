/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:29:46 by fbanzo-s          #+#    #+#             */
/*   Updated: 2024/11/03 15:35:18 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024

int		ft_strlen(char *str);

char	*ft_strstr(char *str, char *to_find);

int		ft_isdigit(char c);

int		ft_atoi(char *str);

char	*ft_strcu(char *str, char to_find);

char	*ft_strc(char *str, char to_find)
{
	char	*linestart;
	int		i;

	linestart = str;
	while (*linestart)
	{
		if (ft_isdigit(*linestart) && ft_isdigit(*(linestart + 1)))
		{
			i = 0;
			while (linestart[i] == to_find)
			{
				i++;
			}
			if (i > 0)
				return (linestart);
		}
		linestart++;
	}
	return (NULL);
}

char	*getdesc(char *match, int numlen)
{
	char	*desc;
	int		i;
	char	*str;

	desc = match + numlen;
	while (*desc && *desc == ' ')
	{
		desc++;
	}
	while (*desc && *desc == ':')
	{
		desc++;
	}
	while (*desc && (*desc == ' '))
	{
		desc++;
	}
	i = 0;
	while (desc[i] != '\n')
	{
		i++;
	}
	desc[i] = '\0';
	return (desc);
}

void	readfile(char *num, int numlen)
{
	int		fd;
	ssize_t	bytesread;
	char	*buffer;
	char	*match;
	char	*desc;

	fd = open("numbers.dict", O_RDONLY);
	buffer = (char *)malloc(BUFFER_SIZE);
	bytesread = read(fd, buffer, BUFFER_SIZE - 1);
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		match = ft_strstr(buffer, num);
		if (match != NULL)
		{
			desc = getdesc(match, numlen);
			write(1, desc, ft_strlen(desc));
		}
		bytesread = read(fd, buffer, BUFFER_SIZE - 1);
	}
	free(buffer);
	close(fd);
}

void	readfiledec(char *num, int numlen)
{
	int		fd;
	ssize_t	bytesread;
	char	*buffer;
	char	*match;
	char	*desc;

	fd = open("numbers.dict", O_RDONLY);
	buffer = (char *)malloc(BUFFER_SIZE);
	bytesread = read(fd, buffer, BUFFER_SIZE - 1);
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		match = ft_strc(buffer, num[0]);
		if (match != NULL)
		{
			desc = getdesc(match, numlen);
			write(1, desc, ft_strlen(desc));
		}
		if (num[1] != '0')
		{
			match = ft_strcu(buffer, num[1]);
			write(1, " ", 1);
			if (match != NULL)
			{
				desc = getdesc(match, numlen);
				write(1, desc, ft_strlen(desc));
			}
		}
		bytesread = read(fd, buffer, BUFFER_SIZE - 1);
	}
	free(buffer);
	close(fd);
}

int	main(int ac, char **av)
{
	char	*numstr;
	int		numlen;
	int		numint;

	if (ac == 2)
	{
		numstr = av[1];
		numint = ft_atoi(numstr);
		numlen = ft_strlen(numstr);
		if (numlen < 3)
		{
			if (numint <= 20 && numint >= 0)
			{
				readfile(numstr, numlen);
			}
			else
			{
				readfiledec(numstr, numlen);
			}
		}
	}
	else if (ac == 3)
	{
		return (0);
	}
	else
		return (0);
}
