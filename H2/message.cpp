#include "message.hpp"
#include <unistd.h>

ssize_t abramov::sendMessage(int fd, const char *cstr, size_t count)
{
  size_t k = count;
  size_t bytes = 0;
  while (bytes < sizeof(k))
  {
    if (ssize_t ret = write(fd, reinterpret_cast< const char* >(&k) + bytes, sizeof(k) - bytes); ret <= 0)
    {
      return -1;
    }
    else
    {
      bytes += ret;
    }
  }

  bytes = 0;
  while (bytes < count)
  {
    if (ssize_t ret = write(fd, cstr + bytes, count - bytes); ret <= 0)
    {
      return -1;
    }
    else
    {
      bytes += ret;
    }
  }
  return bytes + sizeof(k);
}

ssize_t abramov::getMessage(int fd, char **msgptr)
{
  size_t count;
  size_t bytes = 0;
  while (bytes < sizeof(count))
  {
    if (ssize_t ret = read(fd, reinterpret_cast< char* >(&count) + bytes, sizeof(count) - bytes); ret <= 0)
    {
      return -1;
    }
    else
    {
      bytes += ret;
    }
  }

  char *buf = new char[count + 1];
  bytes = 0;
  while (bytes < count)
  {
    if (ssize_t ret = read(fd, buf + bytes, count - bytes); ret <= 0)
    {
      delete[] buf;
      return -1;
    }
    else
    {
      bytes += ret;
    }
  }
  buf[count] = '\0';
  *msgptr = buf;
  return bytes + sizeof(count);
}
