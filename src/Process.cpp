#include "SoftwareCore/Process.hpp"

#ifdef __linux__
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static char* argv0_str = NULL;

std::string argv0(void)
{
	int fd, result;
	size_t len, max;
	char* str,* tmp;
	ssize_t n;

	/* Already known? */
	str = __sync_fetch_and_or(&argv0_str, (char*)0);
	if (str)
	{
		return (const char*)str;
	}

	/* Open /proc/self/cmdline. */
	do
	{
		fd = open("/proc/self/cmdline", O_RDONLY);
	} while (fd == -1 && errno == EINTR);
	if (fd == -1)
	{
		return nullptr;
	}

	str = NULL;
	len = max = 0;

	while (1)
	{
		/* Make sure there is room in the buffer. */
		if (len >= max)
		{
			max = (len | 1023) + 1025;
			tmp = (char*)realloc(str, max);
			if (!tmp)
			{
				free(str);
				do
				{
					result = close(fd);
				} while (result == -1 && errno == EINTR);
				errno = ENOMEM;
				return nullptr;
			}
			str = tmp;
		}

		n = read(fd, str + len, max - len);

		if (n > (ssize_t)0)
		{
			len += n; /* Read n more chars. */
		}
		else
		{
			if (n == (ssize_t)0)
			{
				break; /* All read. */
			}

			else
			{
				if (n != (ssize_t)-1 || errno != EINTR)
				{
					/* Error. */
					const int err = (n == (ssize_t)-1) ? errno : EIO;
					free(str);
					do
					{
						result = close(fd);
					} while (result == -1 && errno == EINTR);
					errno = err;
					return nullptr;
				}
			}
		}
	}

	/* Close. */
	do
	{
		result = close(fd);
	} while (result == -1 && errno == EINTR);
	if (result == -1)
	{
		const int err = errno;
		free(str);
		errno = err;
		return nullptr;
	}

	/* Nothing? */
	if (len < 1)
	{
		free(str);
		errno = ENOENT;
		return nullptr;
	}

	/* Let's be paranoid: the kernel says the last char
	 * must be '\0'. Let's make sure. */
	str[len - 1] = '\0';

	/* Then, we only pick the first string. */
	len = strlen(str);

	/* Optimize. */
	max = len + 1;
	tmp = (char*)realloc(str, max);
	if (!tmp)
	{
		free(str);
		errno = ENOMEM;
		return nullptr;
	}

	/* Replace current argv0_str. */
	if (__sync_bool_compare_and_swap(&argv0_str, (char*)0, str))
	{
		return (const char*)str;
	}

	/* Oops. Another thread already did this work. */
	free(str);

	/* Return what the other thread did. */
	return (const char*)__sync_fetch_and_or(&argv0_str, (char*)0);
}
#endif

Core::Process::Process()
{
#ifdef _WIN32
	runtimePath = std::filesystem::path(__argv[0]);
#else
	runtimePath = std::filesystem::path(argv0());
#endif
}

std::filesystem::path Core::Process::GetRuntimePath() const
{
	return runtimePath;
}
