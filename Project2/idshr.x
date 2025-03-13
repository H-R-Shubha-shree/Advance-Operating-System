/*
 * idshr.x: remote database access protocol
 */
/* preprocessor directives */

struct node {
  float value;
  struct node * next;
};

/* structure definitions, no enumerations needed */
struct parameters {
  int n;
  int m;
  int s1;
};

/* program definition, no union or typdef definitions needed */
program RDBPROG { /* could manage multiple servers */
        version RDBVERS {
                double GETLOAD() = 1;
				double SUMQROOT_GPU(parameters) = 2 ;
				double SUMQROOT_LST(node) = 3;
        } = 1;
} = 0x20000001;  /* program number ranges established by ONC */