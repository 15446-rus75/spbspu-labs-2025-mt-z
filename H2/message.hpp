#ifndef MESSAGE_HPP
#define MESSAGE_HPP

namespace abramov
{
  ssize_t sendMessage(int fd, const char *cstr, size_t count);
  ssize_t getMessage(int fd, char *buf);
}

#endif
