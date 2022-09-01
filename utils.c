#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*dupstr;
	int		i;

	dupstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dupstr)
		return (0);
	i = 0;
	while (s1[i])
	{
		dupstr[i] = s1[i];
		i++;
	}
	dupstr[i] = 0;
	return (dupstr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*search_ptr;
	size_t	i;

	search_ptr = (char *)haystack;
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && *search_ptr)
	{
		if (ft_strncmp(search_ptr, needle, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) <= len)
				return (search_ptr);
		}
		search_ptr++;
		i++;
	}
	return (0);
}