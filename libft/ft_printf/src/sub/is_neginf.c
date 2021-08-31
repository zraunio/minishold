/******************************************************************************
 *
 * \authors Satu Koskinen
 *
 * \brief return 1 if `n` is negative infinity.
 *
 *****************************************************************************/

#include "../../../incl/libft.h"

int	is_neginf(double n)
{
	if (n == -1.0 / 0.0)
		return (1);
	return (0);
}
