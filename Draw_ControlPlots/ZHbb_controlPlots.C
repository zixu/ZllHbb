#include "TH1D.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "stdio.h"
#include "THStack.h"
#include "TLegend.h"
#include <fstream>
#include "iostream"
#include "vector"

using namespace std;

TH1D* GetHist(TString var_name, TString fileName, Double_t rescale=1., Int_t fillcolor=1, Int_t linecolor=1);
TH1D* GetHist(TString var_name, vector<TString> filesName, vector<Double_t> rescales, Int_t fillcolor=1, Int_t linecolor=1);

void ZHbb_controlPlots(){
    TString varName[9] = {"costheta1","costheta2","costhetastar","phi","phi1","rapidityVH",
        "mVH","Higgs_mass","Z_mass"};

	//TString path= "./Plots/2014_7_19/";
	TString path= "./Plots/2014_7_21/";

	//draw opt
	//Int_t linecolor[]
	Double_t signal_rescale=50;
	Double_t ttbar_rescale=32852589/27519328.0000;
	Double_t DY_rescale=30459503/28640004.0000;
	vector<Double_t> singleTop_rescale; 
	singleTop_rescale.push_back(259961/259923.5000);
	singleTop_rescale.push_back(3758227/3144815.0000);
	singleTop_rescale.push_back(497658/498080.5938);
	singleTop_rescale.push_back(139974/140163.6406);
	singleTop_rescale.push_back(1935072/1933425.6250);
	singleTop_rescale.push_back(493460/493595.9062);
	vector<Double_t> VV_rescale; //ZZ, WZ, WW
	VV_rescale.push_back(9799908/9809065.0000);
	VV_rescale.push_back(10000283/10008316.0000);
	VV_rescale.push_back(10000431/10007584.0000);

    for(int i = 0; i < 9; i++){
		//signal
        TH1D* hist_signal  = GetHist(varName[i], path+"Step2_ZHiggs0P_M-125p6_8TeV-JHUGenV4-private_histresult.root",signal_rescale, -1);
		//TTbar
        TH1D* hist_TTbar  = GetHist(varName[i], path+"DiJetPt_TT_8TeV-mcatnlo_histresult.root",ttbar_rescale, 7 );
		//DY
        TH1D* hist_DY  = GetHist(varName[i], path+"DiJetPt_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_histresult.root",DY_rescale, 6 );
		//ZZ, WZ, WW
		vector<TString> dibosons_file;
		dibosons_file.push_back(path+"DiJetPt_ZZ_TuneZ2star_8TeV_pythia6_tauola_histresult.root");
		dibosons_file.push_back(path+"DiJetPt_WZ_TuneZ2star_8TeV_pythia6_tauola_histresult.root");
		dibosons_file.push_back(path+"DiJetPt_WW_TuneZ2star_8TeV_pythia6_tauola_histresult.root");
        TH1D* hist_VV = GetHist(varName[i], dibosons_file, VV_rescale, 5);
		//Single Top
		vector<TString> singleTops_file;
		singleTops_file.push_back(path+"DiJetPt_T_s-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root"); 
		singleTops_file.push_back(path+"DiJetPt_T_t-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root"); 
		singleTops_file.push_back(path+"DiJetPt_T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_histresult.root"); 
		singleTops_file.push_back(path+"DiJetPt_Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root"); 
		singleTops_file.push_back(path+"DiJetPt_Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root"); 
		singleTops_file.push_back(path+"DiJetPt_Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_histresult.root"); 
        TH1D* hist_singleTop = GetHist(varName[i], singleTops_file, singleTop_rescale,3 );

		//data: muon 2012run
        TH1D* hist_data = GetHist(varName[i], path+"DiJetPt_SingleMuRun2012_histresult.root" );


        THStack * hist_total_bks = new THStack("hist_total_bks","hist_total_bks");  //      --Qun Wang @ 2014-07-15
        



        hist_total_bks->Add(hist_TTbar);
        hist_total_bks->Add(hist_VV);
        hist_total_bks->Add(hist_singleTop);
        hist_total_bks->Add(hist_DY);

		//Draw plots
		TCanvas* c1 = new TCanvas("c1","c1", 800, 600);

        hist_data ->SetStats(kFALSE);
        hist_data ->GetXaxis()->SetTitle(varName[i]);
        hist_data ->GetXaxis()->CenterTitle();
		Double_t tmp_max_data_y=hist_data->GetMaximum();
        hist_data->SetMarkerStyle(20);
		hist_data->GetYaxis()->SetRangeUser(1,1.2*tmp_max_data_y );
		hist_data->Draw("PE");

		hist_total_bks->Draw("histsame");

		hist_data ->Draw("PEsame");

		hist_signal ->Scale(5e1);
		hist_signal->SetLineWidth(3);
		hist_signal->SetLineStyle(2);
		//hist_signal->SetFillColor(0);
		hist_signal -> Draw("SAME");
		// hist_data ->Draw("PE");

		TLegend * leg = new TLegend(.89,.7,.99,.9);
		leg->SetFillColor(0);
		leg->AddEntry(hist_signal,"Signal","l");
		leg->AddEntry(hist_TTbar,"TT");
		leg->AddEntry(hist_DY,"DY");
		leg->AddEntry(hist_VV,"VV");
		//leg->AddEntry(hist_11,"WZ");
		//leg->AddEntry(hist_12,"WW");
		leg->AddEntry(hist_singleTop,"SingleT");
		leg->AddEntry(hist_data,"Data");
		leg->Draw();
		c1->SaveAs(Form("figures_ControlPlot_%s.png",varName[i].Data()));
		c1->SetLogy();
		c1->SaveAs(Form("figures_ControlPlot_%s_logY.png",varName[i].Data()));

		delete c1;
		delete hist_signal;
		delete hist_TTbar;
		delete hist_DY;
		delete hist_VV;
		delete hist_singleTop;
		delete hist_data;
		delete hist_total_bks; 
	}
}


TH1D* GetHist_fromTree(char* var_name, TString fileName, double histMin, double histMax){

	int nbins = 25;
	TH1D* hist = new TH1D("hist","",nbins, histMin, histMax);

	TFile* infile = new TFile(fileName.Data(),"R"); 
	TTree * t1 = (TTree*)infile->Get("tree");
	float var;
	t1->SetBranchAddress(var_name,&var);

	int nentries = t1->GetEntries();

	for(int ientry = 0; ientry < nentries; ientry++){

		t1->GetEntry(ientry);
		hist->Fill(var);
	}

	return hist;

}
TH1D* GetHist(TString var_name, TString fileName, Double_t rescale,  Int_t fillcolor, Int_t linecolor){
	TFile* infile = new TFile(fileName.Data(),"R"); 
	TH1D* hist = (TH1D*)infile->Get( TString("hist_"+var_name).Data() ) ;
	if(fillcolor>=0) hist->SetFillColor(fillcolor);
	if(linecolor>=0) hist->SetLineColor(linecolor);
	//hist->Draw();
	return hist;
}

TH1D* GetHist(TString var_name, vector<TString> filesName, vector<Double_t> rescales, Int_t fillcolor, Int_t linecolor){
	TH1D* hist=  GetHist(var_name, filesName[0], rescales[0], fillcolor, linecolor);
	for(Int_t i=1;i<Int_t(filesName.size());i++ ){
		TH1D* hist_tmp=  GetHist(var_name, filesName[i], rescales[i], fillcolor, linecolor);
		(*hist)=(*hist)+(*hist_tmp);
	}
	hist->SetFillColor(fillcolor);
	hist->SetLineColor(linecolor);
	hist->Draw();
	return hist;
}

