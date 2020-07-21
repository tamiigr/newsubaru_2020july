#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "TH1F.h"
#include "TFile.h"

const int bin_min = 0;
const int bin_max = 4096 * 2;
const int bin_num = 4096 * 2;
const int num_ch = 8;

//Sprint function
std::vector<std::string> split(std::string &input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (getline(stream, field, delimiter))
	{
		result.push_back(field);
	}
	return result;
}

//main
int main(int argc, char *argv[])
{
	if (!(argc == 2))
	{
		std::cout << "The argumet is : input CSV file " << std::endl;
		exit(1);
	}
	std::ifstream data;
	std::string filename(argv[1]);
	data.open(filename.c_str(), std::ios_base::in);
	std::string outname = filename;
#if 0
	data.open(filename.c_str(), std::ios_base::in);
	std::string outname = filename;
	//erase .csv
	outname.resize(outname.length() - 4);
	outname.erase(outname.begin() + 0, outname.begin() + 4);
#endif
	//Making histogram
	std::vector<TH1F *> his;
	his.assign(num_ch, 0x0);

	for (int i = 0; i < num_ch; i++)
	{
		//if your compiler is more than g++11
		//you can use std::to_string();
		char temp[10];
		sprintf(temp, "%d", i + 1);

		his[i] = new TH1F(("h" + outname + "_" + temp).c_str(), ("h" + outname + "_" + temp).c_str(), bin_num, bin_min, bin_max);
	}
	std::string line;
	//CSV file read
	while (getline(data, line))
	{
		std::vector<std::string> channels = split(line, ',');
		//std::cout << channels[0] << " : " << channels[1] << " : " << channels[2] << std::endl;
		//Set bin content and bin error
		his[atoi(channels[1].c_str()) - 1]->Fill(atoi(channels[2].c_str()));
	}
	//Make root file
	TFile *tout = new TFile((outname + ".root").c_str(), "RECREATE");
	tout->cd();
	for (int i = 0; i < num_ch; i++)
		his[i]->Write();
	tout->Close();
	return 0;
}
