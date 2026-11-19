#include <iostream>
#include <string>

#include <unistd.h>

int main()
{
  std::string msg;
  if (!(std::cin >> msg))
  {
    std::cerr << "Invalid string" << '\n';
    return 1;
  }
  std::cout << msg << '\n';

  int pipe_fds[2];
  if (!pipe(pipe_fds) < 0)
  {
    std::cerr << "Pipe creation failed" << '\n';
    return 2;
  }

  pid_t pid = fork();
  if (pid < 0)
  {
    std::cerr << "Fork failed" << '\n';
    return 2;
  }
  else if (pid == 0)
  {
    getMessage();
  }
  else
  {
    sendMessage();
  }
}
