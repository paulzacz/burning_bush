#include <iostream>
#include <cstdlib>
#include <string>

#include "hardware_interface/aiousb_wrapper.h"
#include "fifo/pipe.h"

void terminate(unsigned long result=0);

std::string get_fifo_path();
void make_fifo(std::string path);

int main(int /*argc*/, char **/*argv*/) {
  BurningBush::HardwareInterface::AiousbWrapper interface;

  int zone;
  bool status;
  BurningBush::Fifo::Pipe pipe;
  while(pipe.get_command(zone, status)) {
    std::cout << "Zone " << zone << (status ? " on" : " off") << std::endl;
  }

  // if(argc < 2) {
  //   std::cerr << "Usage: " << argv[0] << " ZONE {0|1}";
  // }
  // interface.set_zone(atoi(argv[1]), atoi(argv[2]));

  return 0;
}

std::string get_fifo_path() {
  const char* env_path = std::getenv("BURNING_BUSH_ROOT");
  if(env_path == NULL) {
    std::cerr << "Run \"source .env\"";
    exit(1);
  }
  std::string fifo_path = env_path;
  fifo_path += "/exec/fifo";

  return fifo_path;
}
