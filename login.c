#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int check_secret(const char *password, int pwLen) {
  if (pwLen == -1) {
    printf("problem reading password.txt\n");
    return 0;
  } else {
    const char *pw = "superSecretPassword";
    return (pwLen == strlen(pw)) && (memcmp(password, pw, pwLen) == 0);
  }
}

int check_secret1(const char *password, int pwLen) {
  return check_secret(password, pwLen);
}

#ifdef _WIN32
extern char **_environ;
#define environ _environ
static char * sh = "C:\\Windows\\System32\\cmd.exe";
#else
extern char **environ;
static char * sh = "/bin/sh";
#endif

void success(){
  char *argv[2] = {sh, NULL};
  puts("successful login!\n");
  execve(sh, argv, environ);
}

void failure(){
  puts("wrong password\n");
}

int login(){
  char password[48];
  int fd = open("password.txt", O_RDONLY);
  printf("enter your password:\n");
  int pwLen = read(fd, password, 1000);
  close(fd);
  return check_secret1(password, pwLen);
}

int main(){
  int res = login();
  if (res) {
    success();
  } else {
    failure();
  }

  puts("exiting in main\n");
  return 0;
}