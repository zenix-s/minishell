/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:01:06 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 17:25:16 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include "structs.h"
# include <stdlib.h>

t_token		*ft_lstnew(void *content);
int			newcmp(const char *s1, const char *s2);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, unsigned int n);
t_token		*ft_lstlast(t_token *lst);
char		*ft_strdup(char *src);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_lstsize(t_env_token *lst);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
int			ft_strrint(const char *s, int c);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strduptrim(char *src);
int			ft_strcat(char *dest, const char *src);
int			ft_strcpy(char *dest, const char *src);
char		*ft_strndup(const char *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			lstsizetoken(t_token *lst);
uint64_t	is_string_in_array(const char *str, const char *arr[]);
int			ft_super_strcat(char **dest, const char *src);
char		**delete_string_on_array(char *arr[], int pos);
char		**insert_string_on_array(char *arr[], char *str, int pos);
t_bool		string_is_null_or_whitespace(const char *str);
t_bool		is_space(char c);
uint64_t	get_array_string_size(char **array);
t_bool		ft_isdigit(int c);
t_bool		is_string_numeric(const char *str);

#endif
