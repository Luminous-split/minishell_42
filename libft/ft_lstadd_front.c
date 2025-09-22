/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:05:24 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 21:59:20 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
void    print_list(t_list *lst)
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
    t_list  *head = NULL;
    t_list  *node1 = ft_lstnew("Node 1");
    t_list  *node2 = ft_lstnew("Node 2");
    t_list  *node3 = ft_lstnew("Node 3");

    ft_lstadd_front(&head, node1);
    ft_lstadd_front(&head, node2);
    ft_lstadd_front(&head, node3);

    print_list(head); // Should print: Node 3 -> Node 2 -> Node 1 -> NULL

    // Free the list
    t_list *tmp;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }

    return (0);
}
*/
