#include "wc.h"

int main(int argc, char* argv[]){
  WC obj;
  obj.wc_parse(argc-1, argv+1);
  obj.wc_main();
  return 0;
}
