
#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	pozitie;
	size_t	pozitiecurenta;
	char	*str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	pozitie = start;
	pozitiecurenta = 0;
	while (s[pozitie] && pozitiecurenta < len)
	{
		str[pozitiecurenta++] = s[pozitie++];
	}
	str[pozitiecurenta] = '\0';
	return (str);
}

int	ft_strlen(const char *str)
{
	const char	*s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		s++;
	return (s - str);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	pozitie;
	size_t	lungime;
	char	*str;

	if (!s)
		return (NULL);
	lungime = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (lungime + 1));
	if (str == NULL)
		return (NULL);
	pozitie = 0;
	while (pozitie < lungime)
	{
		str[pozitie] = s[pozitie];
		pozitie++;
	}
	str[pozitie] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	p1;
	size_t	p2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	p1 = 0;
	while (s1[p1] != '\0')
	{
		str[p1] = s1[p1];
		p1++;
	}
	p2 = 0;
	while (s2[p2] != '\0')
	{
		str[p1 + p2] = s2[p2];
		p2++;
	}
	str[p1 + p2] = '\0';
	return (str);
}
