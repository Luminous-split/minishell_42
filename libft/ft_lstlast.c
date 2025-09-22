/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:06:23 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:02:13 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main(void)
{
    t_list *node1 = ft_lstnew(strdup("first"));
    t_list *node2 = ft_lstnew(strdup("second"));
    t_list *node3 = ft_lstnew(strdup("last"));
    node1->next = node2;
    node2->next = node3;
    printf("Full list:\n");
    print_list(node1);
    t_list *last = ft_lstlast(node1);
    if (last)
        printf("Last node content: %s\n", (char *)last->content);
    else
        printf("List is empty.\n");
    t_list *tmp;
    while (node1)
    {
        tmp = node1->next;
        free(node1->content);
        free(node1);
        node1 = tmp;
    }
    return (0);
}
*/
