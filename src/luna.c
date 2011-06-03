
//
// luna.c
//
// Copyright (c) 2011 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdlib.h>
#include <string.h>
#include "luna.h"
#include "lexer.h"

/*
 * Output usage information.
 */

void
usage() {
  fprintf(stderr, 
    "\n  Usage: luna [options]"
    "\n"
    "\n  Options:"
    "\n"
    "\n    -h, --help      output help information"
    "\n    -V, --version   output luna version"
    "\n"
    "\n"
    );
  exit(1);
}

/*
 * Output luna version.
 */

void
version() {
  printf("%s\n", LUNA_VERSION);
  exit(0);
}

/*
 * Parse arguments.
 */

void
parse_args(int argc, const char **argv) {
  const char *arg;
  for (int i = 0; i < argc; ++i) {
    arg = argv[i];
    if (0 == strcmp(arg, "-h") || 0 == strcmp(arg, "--help"))
      usage();
    else if (0 == strcmp(arg, "-V") || 0 == strcmp(arg, "--version"))
      version();
    else if ('-' == arg[0]) {
      fprintf(stderr, "unknown flag %s\n", arg);
      exit(1);
    }
  }
}

/*
 * Parse arguments and scan from stdin (for now).
 */

int
main(int argc, const char **argv){
  parse_args(argc, argv);
  luna_lexer_t lex;
  luna_lexer_init(&lex, stdin, "stdin");

  while (luna_lexer_next(&lex)) {
    luna_token_inspect(&lex.tok);
  }

  if (lex.tok.type != LUNA_TOKEN_EOS) {
    fprintf(stderr
      , "luna(%s:%d): SyntaxError %s\n"
      , lex.filename
      , lex.lineno
      , lex.error);
  }

  return 0;
}