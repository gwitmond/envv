#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* env replacement with proper! argument parsing.

 * Good: #!/usr/bin/make -f
 * this works as expected

 * Bad: #!/usr/bin/env make -f
 * Gives error: /usr/bin/env: ‘make -f’: No such file or directory
 * This is because coreutils-env does not split the input on spaces.

 * We do! It's so simple. :-)

 * Copyright 2018, Guido Witmond.
 * License: MIT.
 */

void main(int argc, char **argv) {
  if (argc == 1) {
    printf("Missing command. Usage: %s <command> ... <args>\n", *argv);
    exit(1);
  }

  if (argc >= 256) {
      printf("Too many parameters. Only 256 allowed.\n");
    }

  char *args[256];
  uint ind = 0;

  // tokenise the command and params that linux places in argv[1]
  char *tok;
  char *pos;
  char *string = argv[1];
  while (tok = strtok_r(string, " ", &pos)) {
    args[ind++] = tok;
    if (ind == 256) {
      printf("Too many parameters. Only 256 allowed.\n");
    }
    string = NULL;
  }

  // add the script (argv[2]) and its arguments (argv[3+])
  char **param = &argv[2];
  while (*param) {
    args[ind++] = *param;
    param++;
  }
  args[ind] = NULL;

  execvp(args[0], args);
}
