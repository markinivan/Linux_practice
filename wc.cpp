#include "wc.h"

int number_len(int number) {
  if (number == 0) {
    return 1;
  }
  int res = 0;
  while (number > 0) {
    res+=1;
    number /= 10;
  }
  return res;
}

int utf8_char_len(unsigned char c) {
    if (c < 0x80 || (c & 0xC0) == 0x80) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

WC::WC() : c_flag(false), m_flag(false), l_flag(false), w_flag(false), validity_flag(false), files(std::vector<std::string>{}){}
WC::WC(bool c,  bool m, bool l, bool w, bool val, std::vector<std::string> files_input) : c_flag(c), m_flag(m), l_flag(l), w_flag(w), validity_flag(val), files(files_input) {}
WC::WC(const WC& copy) : c_flag(copy.c_flag), m_flag(copy.m_flag), l_flag(copy.l_flag), w_flag(copy.w_flag), validity_flag(copy.validity_flag), files(copy.files) {}
  
void WC::wc_parse(int size, char** arguments){
  for (int i = 0; i < size;i++) {
    std::string frag = arguments[i];
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
  if (this->l_flag == 0 && this->c_flag == 0 && this->w_flag == 0 && this->m_flag == 0) {
    this->l_flag = 1;
    this->w_flag = 1;
    this->m_flag = 1;
  }
}

void WC::wc_main(){

  std::vector<std::pair<std::vector<int>, std::string>> output_table;
  int all_line_counter = 0, all_byte_counter = 0, all_word_counter = 0, all_symbol_counter = 0;

  for (int i = 0; i < (int)(this->files.size());i++) {
    std::ifstream file(this->files[i]);
    std::pair<std::vector<int>, std::string> result;
    result.second = this->files[i];
    if ( !file.is_open()) {
          result.first = {-1, -1, -1, -1};
          output_table.push_back(result);
          continue;
      }
      
      std::string line;
      int line_counter = 0, byte_counter = 0, word_counter = 0, symbol_counter = 0;
      bool last_spase, empty_line;
      while (std::getline(file, line)) {
        line_counter++;
        last_spase = 1;
        empty_line = 1;
        for (char c : line) {
          byte_counter++;
          symbol_counter -= (utf8_char_len(c) - 2);
          if ((c == ' ' || c =='\t') && last_spase == 0) {
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
      symbol_counter += line_counter;
      file.close();
      result.first = {line_counter, word_counter, symbol_counter, byte_counter};
      all_line_counter += line_counter;
      all_byte_counter += byte_counter;
      all_word_counter += word_counter;
      all_symbol_counter += symbol_counter;
      output_table.push_back(result);
    }
    if (output_table.size() > 1) {
      std::pair<std::vector<int>, std::string> summary;
      summary.first = {all_line_counter, all_word_counter, all_symbol_counter, all_byte_counter};
      summary.second = "итого";
      output_table.push_back(summary);
    }
    wc_res_print(output_table);
}
 
void WC::wc_res_print(std::vector<std::pair<std::vector<int>, std::string>> output_table) {    
  int max_chars = -1;
  for (int i = 0; i < (int)(output_table.size());i++) {
      int len = number_len((output_table[i].first)[0]);
      max_chars = max_chars > len ? max_chars : len;
      len = number_len((output_table[i].first)[1]);
      max_chars = max_chars > len ? max_chars : len;
      len = number_len((output_table[i].first)[2]);
      max_chars = max_chars > len ? max_chars : len;
      len = number_len((output_table[i].first)[3]);
      max_chars = max_chars > len ? max_chars : len;
  }
  
  for (int i = 0; i < (int)(output_table.size());i++) {
    if ((output_table[i].first)[0] == -1 && (output_table[i].first)[1] == -1 && (output_table[i].first)[2] == -1 && (output_table[i].first)[3] == -1) {
      std::cout << "wc: " << output_table[i].second << ": Нет такого файла или каталога\n";
    } else {
      if (this->l_flag == 1) {
          std::cout << std::setw(max_chars) << (output_table[i].first)[0] << " ";
        }
      if (this->w_flag == 1) {
          std::cout << std::setw(max_chars) << (output_table[i].first)[1] << " ";
        }
      if (this->c_flag == 1) {
          std::cout << std::setw(max_chars) << (output_table[i].first)[2] << " ";
        }
      if (this->m_flag == 1) {
          std::cout << std::setw(max_chars) << (output_table[i].first)[3] << " ";
        }
    std::cout << output_table[i].second << "\n";
    }
  }
}
