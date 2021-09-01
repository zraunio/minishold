/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief
 *
 *****************************************************************************/

#include "../../incl/libft.h"
#include "../inc/print_internal.h"

int	print_file(const char *file, const char *format, ...)
{
	va_list	ap;
	char	*result;
	int		ret;
	int		fd;

	result = NULL;
	fd = open(file, O_RDONLY);
	if (!fd)
		return (0);
	va_start(ap, format);
	ret = _vasprint(&result, format, ap);
	va_end(ap);
	if (ret != -1)
		ret = write(fd, result, (size_t)ret);
	close(fd);
	free(result);
	return (ret);
}
