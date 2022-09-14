#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>

//ft_split
//ft_strjoin
//ft_strstr
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
//ft_substr

#endif