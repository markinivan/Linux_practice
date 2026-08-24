#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <utility>
#include <iomanip>

int number_len(int number);

int utf8_char_len(unsigned char c);

class WC {
private:
  bool c_flag;
  bool m_flag;
  bool l_flag;
  bool w_flag;
  bool validity_flag;
  std::vector<std::string> files;
public:
  WC();
  WC(bool c,  bool m, bool l, bool w, bool val, std::vector<std::string> files_input);
  WC(const WC& copy);
  
  void wc_parse(int size, char** arguments);
  
  void wc_main();
  
  void wc_res_print(std::vector<std::pair<std::vector<int>, std::string>> output_table);
  
};
