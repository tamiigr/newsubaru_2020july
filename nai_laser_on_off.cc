#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

unsigned short SwapShort(unsigned short datum) {
  unsigned short temp = 0;
  temp = (datum&0x00ff);
  return (temp<<8) + (datum>>8);
}

struct apu8208 {
  unsigned short abs_3;
  unsigned short abs_2;
  unsigned short abs_1;
  unsigned short pha;
  unsigned short ch;
};

int main(int argc, char* argv[]){
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " input_file [output_root_name]" << std::endl;
    return 1;
  }
  
  TString output_file_name;
  if (argc == 2) {
    output_file_name = argv[1];
    output_file_name += ".root";
  }else{
    output_file_name = argv[2];
  }

  std::cout << "Input filename  : " << argv[1] << std::endl;
  std::cout << "Output filename : " << output_file_name << std::endl;
  
  TFile *output_file = new TFile(output_file_name.Data(), "recreate");
  TTree *tree = new TTree("tr", "tr");
  /*tree->SetAutoFlush(0);*/

  ULong64_t abs;
  UShort_t  pha;
  UShort_t  ch;
  UShort_t  laser_on = 1;
  tree->Branch("abs",&abs);
  tree->Branch("pha",&pha);
  tree->Branch("ch",&ch);
  tree->Branch("laser_on",&laser_on);

  std::ifstream ifs(argv[1], std::ios::in | std::ios::binary);
  apu8208 event;
  unsigned long ievent = 0;
  unsigned long cur_pos = 0;
  
  std::cout << "Size of a single event: " << sizeof(event)  << " bytes"<< std::endl;
  std::cout << std::hex << std::setfill('0');
  while (!ifs.eof()) {
    ievent++;
    cur_pos = ifs.tellg();
    /*if (ievent > 1e6){
      break;
      }*/
    if (ievent%100000==0){
      std::cout << "Event: 0x" << std::setw(16) << ievent
    		<< ", Position: 0x"    << std::setw(16) << cur_pos
    		<< " (" << std::dec << cur_pos << ") bytes"
    		<< std::hex << std::endl;
    }
    
    ifs.read((char*)&event,  sizeof(event));
    abs = (((ULong64_t)SwapShort(event.abs_3)) << 32) + ((ULong64_t)SwapShort(event.abs_2) << 16) + SwapShort(event.abs_1);
    pha   = SwapShort(event.pha);
    ch    = SwapShort(event.ch);
    if (ch == 1) {
      laser_on = 1;
    }
    if (ch == 2) {
      laser_on = 0;
    }
    tree->Fill();
  }
  ifs.close();
  output_file->Write();
  output_file->Close();
  return 0;
}
