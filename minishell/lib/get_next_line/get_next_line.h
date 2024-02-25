/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:26:45 by beddinao          #+#    #+#             */
/*   Updated: 2024/01/01 03:51:54 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# if BUFFER_SIZE >= 2147483646 || BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <unistd.h>
# include <stdlib.h>

char			*get_next_line(int fd);
char			*re_tighten(char *str, int st, int end, int con);
char			*re_tightenthem(char *str_1, char *str_2, int end, int end_2);
void			*re_clean(void *b, size_t i, size_t len);
void			*re_doit(size_t len);
int				is_divided(char *str, int st, int size);

#endif
