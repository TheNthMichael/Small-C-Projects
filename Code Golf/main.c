#include <stdio.h> 
int ic(char* a){int r=0;while (*a){r*=10;r+=((*a)-'0');a++;}return r;}
int main(int argc, char* argv[]){(argc<2)?exit(0):printf("");int l = ic(argv[1]),e=0; for(int i = 2; i < l; i++) { for (int j = 2; j <= i / 2; j++) { if (i % j == 0) { e = 1; break; } }e ? printf("") : printf("%d\n", i); e = 0; } }
