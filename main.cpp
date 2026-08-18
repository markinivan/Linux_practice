#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

class WC {
private:
  bool c_flag;
  bool m_flag;
  bool l_flag;
  bool w_flag;
  bool validity_flag;
  std::vector<std::string> files;
public:
  WC() : c_flag(false), m_flag(false), l_flag(false), w_flag(false), validity_flag(false), files(std::vector<std::string>{}){}
  WC(bool c,  bool m, bool l, bool w, bool val, std::vector<std::string> files_input) : c_flag(c), m_flag(m), l_flag(l), w_flag(w), validity_flag(val), files(files_input) {}
  WC(const WC& copy) : c_flag(copy.c_flag), m_flag(copy.m_flag), l_flag(copy.l_flag), w_flag(copy.w_flag), validity_flag(copy.validity_flag), files(copy.files) {}
  
  void wc_parse(int size, char* arguments[]){
    for (int i = 0; i < size;i++) {
      std::string frag = frag;
      if (frag.find('.') != std::string::npos) {
        files.push_back(frag);
      } else {
        if (frag.find('c') != std::string::npos) {
          this->c_flag = 1;
        }
        if (frag.find('m') != std::string::npos) {
          this->m_flag = 1;
        }
        if (frag.find('l') != std::string::npos) {
          this->l_flag = 1;
        }
        if (frag.find('w') != std::string::npos) {
          this->w_flag = 1;
        }
        }
    }
  }
  
  void wc_main(){
    std::ifstream file(this->files[0]);
  
    if ( !file.is_open()) {
          std::cout << "Нет такого файла или каталога: " << this->files[0] << std::endl;
          return;
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
          if (c == ' ' || c =='\t' && last_spase == 0) {
            word_counter++;
            last_spase = 1;
          } else if (c != ' ') {
            last_spase = 0;
            empty_line = 0;
          }
        }
        if (empty_line == 0 && last_spase == 0) {
          word_counter++;
        }
      }
      byte_counter += line_counter;
      file.close();
      wc_res_print(line_counter, word_counter, byte_counter, -1, this->files[0]);
  }
  
  void wc_res_print(int lines, int words, int bytes, int symbols, std::string filepath) {
    std::cout << lines << "   " << words << "   " << bytes << "   " << symbols << "   " << filepath << "\n";
  }
  
};
int main(int argc, char* argv[]){
  std::vector<std::string> input = {"./test.txt"};
  WC obj(false,false,false,false,true,input);
  obj.wc_main();
  return 0;
}
