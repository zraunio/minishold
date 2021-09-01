/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief
 *
 *****************************************************************************/

#ifndef PRINT_H
# define PRINT_H

# include <stdarg.h>
# include <stddef.h>
# include <inttypes.h>
# include <stdint.h>
# include <sys/types.h>

int		ft_printf(const char *format, ...);
int		print_fd(int fd, const char *format, ...);
int		print_file(const char *file, const char *format, ...);
char	*format(const char *format, ...);

#endif
