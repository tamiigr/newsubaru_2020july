#ifndef READ
#define READ

#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"

class tree_ana
{
private:
	std::string file;
	double r_mean;
	double c_mean;

	//Parameters
	ULong64_t abs;
	UShort_t pha;
	UShort_t ch;
	UShort_t laser_on;

	TFile *t_file;
	TTree *t1;
	TLegend *lg;
	std::vector<TH1F *> his;
	std::vector<TCanvas *> cx;
	std::vector<std::string> name;

	// accessor
public:
	tree_ana(const char *t_file);
	~tree_ana();
	void get();
	void set();
	void eventloop();
	void get_mean();
	void save();
};
#endif
