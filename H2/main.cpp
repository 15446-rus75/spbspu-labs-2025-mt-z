#include <iostream>
#include <string>

#include <unistd.h>

#include "message.hpp"

int main()
{
  using namespace abramov;

  int pipe_fds[2];
  if (pipe(pipe_fds) < 0)
  {
    std::cerr << "Pipe creation failed" << '\n';
    return 2;
  }

  pid_t pid = fork();
  if (pid < 0)
  {
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    std::cerr << "Fork failed" << '\n';
    return 2;
  }
  else if (pid == 0)
  {
    close(pipe_fds[1]);
    char cmsg[1024] = {};
    if (getMessage(pipe_fds[0], cmsg) < 0)
    {
      std::cerr << "Failed to get msg" << '\n';
      return 2;
    }
    close(pipe_fds[0]);
    std::cout << cmsg << '\n';
    return 0;
  }
  else
  {
    std::string msg;
    if (!std::getline(std::cin, msg))
    {
      std::cerr << "Invalid string" << '\n';
      return 1;
    }

    close(pipe_fds[0]);
    if (sendMessage(pipe_fds[1], msg.c_str(), msg.size()) < 0)
    {
      std::cerr << "Failed to send msg" << '\n';
      return 2;
    }
    close(pipe_fds[1]);
    return 0;
  }
}
