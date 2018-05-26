/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:12:46 by fmadura           #+#    #+#             */
/*   Updated: 2017/11/20 18:28:35 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		count;
	char	*nstr;

	if (s == NULL)
		return (NULL);
	if ((nstr = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	count = 0;
	while (len > (size_t)count && s[start + count])
	{
		nstr[count] = s[start + count];
		count++;
	}
	nstr[count] = '\0';
	return (nstr);
}
