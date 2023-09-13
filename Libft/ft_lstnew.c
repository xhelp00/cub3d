/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:03 by nroth             #+#    #+#             */
/*   Updated: 2023/01/14 16:32:04 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list_item;

	list_item = ft_calloc(1, sizeof(t_list));
	if (!list_item)
		return (NULL);
	list_item->content = content;
	list_item->next = NULL;
	return (list_item);
}
