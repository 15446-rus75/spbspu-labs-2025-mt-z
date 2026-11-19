#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstddef>
#include <sys/types.h>

namespace abramov
{
  ssize_t sendMessage(int fd, const char *cstr, size_t count);
  ssize_t getMessage(int fd, char **msgptr);
}

#endif
