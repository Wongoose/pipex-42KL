// #include "pipex.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*dupstr;
// 	int		i;

// 	dupstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
// 	if (!dupstr)
// 		return (0);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		dupstr[i] = s1[i];
// 		i++;
// 	}
// 	dupstr[i] = 0;
// 	return (dupstr);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	if (n == 0)
// 		return (0);
// 	i = 0;
// 	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && i < n - 1)
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	char	*search_ptr;
// 	size_t	i;

// 	search_ptr = (char *)haystack;
// 	i = 0;
// 	if (!*needle)
// 		return ((char *)haystack);
// 	while (i < len && *search_ptr)
// 	{
// 		if (ft_strncmp(search_ptr, needle, ft_strlen(needle)) == 0)
// 		{
// 			if (i + ft_strlen(needle) <= len)
// 				return (search_ptr);
// 		}
// 		search_ptr++;
// 		i++;
// 	}
// 	return (0);
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;
// 	size_t	srclen;

// 	i = 0;
// 	srclen = ft_strlen(src);
// 	if (dstsize == 0)
// 		return (srclen);
// 	while (i < dstsize - 1 && src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	if (i < dstsize)
// 		dst[i] = 0;
// 	return (srclen);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substr;

// 	if (!s)
// 		return (0);
// 	if (start > ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s))
// 		return (ft_strdup(s));
// 	substr = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!substr)
// 		return (0);
// 	ft_strlcpy(substr, &s[start], len + 1);
// 	return (substr);
// }

// static size_t	count_words(char const *s, char c)
// {
// 	size_t	words;

// 	words = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 			words++;
// 		while (*s != c && *s)
// 			s++;
// 	}
// 	return (words);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**splitstr;
// 	size_t	start;
// 	size_t	end;
// 	size_t	i;

// 	splitstr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
// 	if (!s || !splitstr)
// 		return (0);
// 	start = 0;
// 	end = 0;
// 	i = 0;
// 	while (i < count_words(s, c))
// 	{
// 		while (s[start] == c)
// 			start++;
// 		end = start;
// 		while (s[end] != c && s[end])
// 			end++;
// 		splitstr[i] = ft_substr(s, start, end - start);
// 		start = end;
// 		i++;
// 	}
// 	splitstr[i] = 0;
// 	return (splitstr);
// }

// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;
// 	size_t	dstlen;
// 	size_t	srclen;

// 	i = 0;
// 	dstlen = ft_strlen(dst);
// 	srclen = ft_strlen(src);
// 	if (dstsize <= dstlen)
// 		return (srclen + dstsize);
// 	while (i < dstsize - dstlen - 1 && src[i])
// 	{
// 		dst[i + dstlen] = src[i];
// 		i++;
// 	}
// 	dst[i + dstlen] = 0;
// 	return (srclen + dstlen);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*newstr;
// 	size_t	total_len;

// 	if (!s1 || !s2)
// 		return (0);
// 	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	newstr = (char *)malloc(sizeof(char) * total_len);
// 	if (!newstr)
// 		return (0);
// 	ft_strlcat(newstr, s1, total_len);
// 	ft_strlcat(newstr, s2, total_len);
// 	return (newstr);
// }