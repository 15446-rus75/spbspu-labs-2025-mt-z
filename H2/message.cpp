#include "message.hpp"

ssize_t abramov::sendMessage(int fd, const char *cstr, size_t count)
{
  size_t k = count;
  if (write(fd, &k, sizeof(k)) < 0)
  {
    return -1;
  }

  size_t bytes = 0;
  while (bytes < count)
  {
    if (int ret = write(fd, cstr, count - bytes); ret < 0)
    {
      return -1;
    }
    else
    {
      bytes += ret;
    }
  }
  return bytes;
}

ssize_t abramov::getMessage(int fd, char *buf)
{
  size_t count;
  if (read(fd, &count, sizeof(count) < 0)
  {
    return -1;
  }

  size_t bytes = 0;
  while (bytes < count)
  {
    if (int ret = read(fd, cstr, count - bytes); ret < 0)
    {
      return -1;
    }
    else
    {
      bytes += ret;
    }
  }
  return bytes;
}
