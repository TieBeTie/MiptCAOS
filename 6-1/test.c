#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



struct Kek {
  int value;
  uint32_t next;
};

int main(){
  Kek kek = { -10, 16 }, kek1 = { 24, 0 }, kek2 = { 13, 8 };

//
//  std::ofstream ostr("kek", std::ios_base::binary);
//  ostr << kek;
  int file = open("kek", O_RDWR);
  write(file, &kek, 8);
  write(file, &kek1,8);
  write(file, &kek2,8);
  return 0;
}
