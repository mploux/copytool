#include "libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>

void		error(int nb, ...)
{
	int		i;
	va_list	list;
	char 	*str;

	i = -1;
	if (nb <= 0)
		return ;
	ft_putstr_fd(T_RED, 2);
	ft_putstr_fd(" Error: ", 2);
	ft_putstr_fd(T_NRM, 2);
	va_start(list, nb);
	while (++i < nb)
	{
		str = va_arg(list, char *);
		ft_putstr_fd(str, 2);
	}
	ft_putchar_fd('\n', 2);
	exit(1);
}

char		warning(int nb, ...)
{
	int		i;
	va_list	list;
	char 	*str;

	i = -1;
	if (nb <= 0)
		return (1);
	ft_putstr_fd(T_MAG, 1);
	ft_putstr_fd(" Warning: ", 1);
	ft_putstr_fd(T_NRM, 1);
	va_start(list, nb);
	while (++i < nb)
	{
		str = va_arg(list, char *);
		ft_putstr_fd(str, 1);
	}
	ft_putchar_fd('\n', 1);
	return (1);
}

char		copy_file(char *src, char *dst, int type)
{
	int		fd_src;
	int		fd_dst;
	char	buff[BUFF_SIZE + 1];
	int		rd;

	if (type == DT_DIR)
		return (2 * mkdir(dst, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH));
	if ((fd_src = open(src, O_RDONLY)) < 0)
		return (1 - warning(2, "failed to open ", src));
	if ((fd_dst = open(dst, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) < 0)
		return (1 - warning(2, "failed to open ", dst) + close(fd_src));
	while ((rd = read(fd_src, buff, BUFF_SIZE)) > 0)
		write(fd_dst, buff, rd);
	if (close(fd_dst) < 0)
		return (-1);
	return (close(fd_src));
}

char		copy(char *src, char *dst, int type)
{
	ft_putstr_fd(T_GRN, 1);
	ft_putstr("Copying ");
	ft_putstr_fd(T_NRM, 1);
	ft_putstr(src);
	ft_putstr_fd(T_GRN, 1);
	ft_putstr(" in ");
	ft_putstr_fd(T_NRM, 1);
	ft_putstr(dst);
	ft_putstr_fd(T_GRN, 1);
	ft_putstr("...\n");
	ft_putstr_fd(T_NRM, 1);
	return (copy_file(src, dst, type));
}

char		*concat_dirs(char *src, char *dst, int type)
{
	char	*result;
	int		len;
	int		is_dir;
	char	*tmp;

	result = ft_strdup(src);
	len = ft_strlen(src);
	is_dir = type == DT_DIR;
	tmp = ft_coffee(src, (result[len - 1] != '/' ? "/" : NULL), 0);
	ft_strdel(&result);
	result = ft_coffee(tmp, dst, 0);
	ft_strdel(&tmp);
	return (result);
}

int			copy_dirs_one_bye_one(char *src, char *dst)
{
	DIR				*dir;
	struct dirent	*entry;
	char 			*src_dir;
	char 			*dst_dir;
	int				ret;

	if (!(dir = opendir(src)))
		error(1, "invalid source directory !");
	src_dir = NULL;
	while (entry = readdir(dir))
	{
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
			continue;
		if (!(src_dir = concat_dirs(src, entry->d_name, entry->d_type)))
			error(1, "failed concating sub directory !");
		if (!(dst_dir = concat_dirs(dst, entry->d_name, entry->d_type)))
			error(1, "failed concating sub directory !");
		ret = copy(src_dir, dst_dir, entry->d_type);
		if (ret == -2)
			warning(1, "failed to create directory !");
		if (ret == -1)
			error(1, "failed to close file !");
		if (entry->d_type == DT_DIR)
			if (copy_dirs_one_bye_one(src_dir, dst_dir) != 0)
				return (-1);
		ft_strdel(&src_dir);
	}
	closedir(dir);
	return (0);
}

int			run_copy(char *flags, char *src, char *dst)
{
	int		ret;
	(void) flags;

	if (ft_strcmp(src, dst) == 0)
		error(1, "source directory can't be copied in himself !");
	if (ret = open(dst, O_RDONLY | O_DIRECTORY) < 0)
		error(1, "invalid destination directory !");
	if (close(ret) < 0)
		error(1, "failed to clode destination directory !");
	copy_dirs_one_bye_one(src, dst);
	ft_putendl("Done !");
	return (0);
}

int			main(int ac, char **av)
{
	if (ac == 3)
		return (run_copy(NULL, av[1], av[2]));
	else if (ac == 4)
		return (run_copy(av[1], av[2], av[3]));
	else
	{
		ft_putstr_fd(T_GRN, 2);
		ft_putstr_fd("Usage:\n\t", 2);
		ft_putstr_fd(T_NRM, 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" src_path dest_path\n", 2);
		return (1);
	}
	return (0);
}
