/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief
 *
 *****************************************************************************/

#include "../../../incl/libft.h"
#include "../inc/print_internal.h"

void	*_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	copy_size;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		new = NULL;
	}
	else
		new = (void *)malloc(new_size);
	if (new != NULL && ptr != NULL)
	{
		if (new_size < old_size)
			copy_size = new_size;
		else
			copy_size = old_size;
		ft_memcpy(new, ptr, copy_size);
		if (new_size > old_size)
			ft_memset((void *)(&((char *)new)[old_size]),
				0, new_size - old_size);
		free(ptr);
	}
	return (new);
}
