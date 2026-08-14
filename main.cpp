#include <fstream>
#include <iostream>
#include <string>

struct Flags {
  bool c;
  bool m;
  bool l;
  bool w;
};
int wc_main(){
  std::ifstream file("./test.txt");
  
  if (!file.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        return 1;
    }
    
    std::string line;
    int line_counter = 0, byte_counter = 0, word_counter = 0;
    bool last_spase, empty_line;
    while (std::getline(file, line)) {
      line_counter++;
      last_spase = 1;
      empty_line = 1;
      for (char c : line) {
        byte_counter++;
        if (c != ' ' && c != '\t') {
          //first_sym = 1;
        }
        if (c == ' ' || c =='\t' && last_spase == 0) {
          word_counter++;
          last_spase = 1;
        } else if (c != ' ') {
          last_spase = 0;
          empty_line = 0;
        }
      }
      printf("\n%s %b %b\n", line, empty_line, last_spase);
      if (empty_line == 0 && last_spase == 0) {
        word_counter++;
      }
    }
    byte_counter += line_counter;
    file.close();
    printf("\n%d %d %d\n", line_counter,  word_counter, byte_counter);
    return 0;
}

int main(){
  wc_main();
  return 0;
}
