/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:28 by avoronko          #+#    #+#             */
/*   Updated: 2023/05/17 17:09:10 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	diff;

	diff = 0;
	while (!diff && (*s1 || *s2))
		diff = (unsigned char) *s1++ - (unsigned char) *s2++;
	return (diff);
}
