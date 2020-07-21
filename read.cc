#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "read.h"

const int calc_range = 2000;
#define DEBUG 0

tree_ana::tree_ana(const char *t_file)
{
	file = std::string(t_file);
	//make histrgam vector
	his.assign(3, 0x0);
	cx.assign(2, 0x0);
	//histgram title
	std::vector<std::string> name = {"h_true", "h_bg", "h_subtracted"};
	for (int i = 0; i < name.size(); i++)
	{
		//Create histgram
		his[i] = new TH1F(name[i].c_str(), name[i].c_str(), 3000, 0, 3000);
	}
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
tree_ana::~tree_ana()
{
	for (int i = 0; i < his.size(); i++)
		delete his[i];
	for (int i = 0; i < cx.size(); i++)
		delete cx[i];
	delete t_file;
	delete lg;
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
void tree_ana::get()
{
	std::cout << "Read file name : " << file << std::endl;
	if (!(t_file = TFile::Open(file.c_str())))
	{
		std::cerr << "No_file" << file << "\r";
		exit(0);
	}
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
void tree_ana::set()
{
	get();
	t1 = (TTree *)t_file->Get("tr");
#if DEBUG
	std::cout << "Reading OK" << std::endl;
#endif
	t1->SetBranchAddress("abs", &abs);
	t1->SetBranchAddress("pha", &pha);
	t1->SetBranchAddress("ch", &ch);
	t1->SetBranchAddress("laser_on", &laser_on);
#if DEBUG
	std::cout << "setting Branching address OK" << std::endl;
#endif
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
void tree_ana::eventloop()
{
	int N_max = t1->GetEntries();
	//Main loop
	for (int i = 0; i < N_max; i++)
	{
		t1->GetEntry(i);
		//select laser on condition
		if (laser_on == 1 && ch == 7)
			his[0]->Fill(pha);
		//select laser off condition
		if (laser_on == 0 && ch == 7)
			his[1]->Fill(pha);
	}
	//subtraction laser off is 4 times less than laser on
	his[1]->Scale(4);
	his[2]->Add(his[0], his[1], 1, -1);
	t_file->Close();
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
void tree_ana::get_mean()
{
	double sum_1(0), sum_2(0);
	//Analysis
	his[2]->GetXaxis()->SetRangeUser(0, calc_range);
	r_mean = his[2]->GetMean();
	for (int i = 0; i < calc_range; i++)
	{
		int bin_v = his[2]->GetBinContent(i);
		sum_1 += bin_v * i;
		sum_2 += bin_v;
	}
	c_mean = sum_1 / sum_2;
	std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << std::endl;
	std::cout << "Mean value(ch) using root class : " << r_mean << std::endl;
	std::cout << "Mean value(ch) calculation : " << c_mean << std::endl;
	std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << std::endl;
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
void tree_ana::save()
{
	//erase .root
	file.resize(file.length() - 5);
	//output root file
	t_file = TFile::Open((file + "_his.root").c_str(), "RECREATE");
	for (int i = 0; i < his.size(); i++)
	{
		his[i]->SetLineWidth(2);
		his[i]->SetTitle("");
		his[i]->GetXaxis()->SetRangeUser(0, calc_range);
	}
	cx[0] = new TCanvas("Comparison", "Comparison", 500, 400);
	cx[0]->cd();
	his[0]->SetLineColor(1);
	his[1]->SetLineColor(2);
	his[0]->Draw();
	his[1]->Draw("HIST same");

	lg = new TLegend(0.4, 0.70, 0.90, 0.90);
	lg->SetHeader("Mean channel value ", "c");
	//Set digit of double
	// double --> stringstream --> string --> char
	std::stringstream st;
	st << std::fixed << std::setprecision(2) << r_mean;
	//stringstream to string
	std::string temp = st.str();
	lg->AddEntry((TObject *)0, ("Mean value root :" + temp).c_str(), "");
	//stringstream initialization
	st.str("");
	st << std::fixed << std::setprecision(2) << c_mean;
	temp = st.str();
	lg->AddEntry((TObject *)0, ("Mean value clc. :" + temp).c_str(), "");

	lg->SetTextFont(132);
	lg->SetTextSize(0.04);
	cx[1] = new TCanvas("Subtracted", "Subtracted", 500, 400);
	cx[1]->cd();
	his[2]->SetStats(0);
	his[2]->SetLineColor(1);
	his[2]->Draw("HIST");
	lg->Draw();
#if DEBUG
	std::cout << "Legend check OK" << std::endl;
#endif
	for (int i = 0; i < his.size(); i++)
	{
		his[i]->Write();
	}
	cx[0]->Write();
	cx[1]->Write();
	t_file->Close();
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
//		Main function		//
//+-+-+-+-+-+-+-+-+-+-+-+-+-//
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[1] << "Root file analyzed by nai_laser_on_off.cc " << std::endl;
		return 1;
	}
	if (DEBUG == 1)
	{
		std::cout << "Debag mode " << std::endl;
	}
	tree_ana ana(argv[1]);
	ana.set();
	ana.eventloop();
	ana.get_mean();
	ana.save();
	return 0;
}
