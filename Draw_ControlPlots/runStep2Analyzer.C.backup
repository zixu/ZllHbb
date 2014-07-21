//void fianl_step();
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>
#include <TROOT.h>
#include <iostream>
#include <TGraph.h>
#include <TMath.h>
#include <map>
#include "fstream"
#include <TLegend.h>


void runStep2Analyzer() {
    gROOT->LoadMacro("METzCalculator.cc+");
    gROOT->LoadMacro("Step2Analyzer.C+");
    gROOT->LoadMacro("tdrstyle.C");
    setTDRStyle(); //plotting style

    
	TString path="../histos/";
	Double_t lumi=19624;


/*
	//signal
	runStep2Analyzer_signle(1,             lumi, path, "Step2_ZHiggs0P_M-125p6_8TeV-JHUGenV4-private_local");

	//backgrounds
//	runStep2Analyzer_signle(234,           lumi, path, "DiJetPt_TTJets_Merged");
	runStep2Analyzer_signle(234,           lumi, path, "DiJetPt_TT_8TeV-mcatnlo");
	runStep2Analyzer_signle(2950.0 * 1.188,lumi, path, "DiJetPt_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball");
//	runStep2Analyzer_signle(1.,            lumi, path, "DiJetPt_DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball");
//	runStep2Analyzer_signle(1.,            lumi, path, "DiJetPt_DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball");
//	runStep2Analyzer_signle(1.,            lumi, path, "DiJetPt_DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph");
//	runStep2Analyzer_signle(1.,            lumi, path, "DiJetPt_DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph");
//	runStep2Analyzer_signle(1.,            lumi, path, "DiJetPt_DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph");
//	runStep2Analyzer_signle(1.,            lumi, path, "DiJetPt_DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph");
	runStep2Analyzer_signle(5.9,           lumi, path, "DiJetPt_ZZ_TuneZ2star_8TeV_pythia6_tauola");
	runStep2Analyzer_signle(18.3,          lumi, path, "DiJetPt_WZ_TuneZ2star_8TeV_pythia6_tauola");
	runStep2Analyzer_signle(43,            lumi, path, "DiJetPt_WW_TuneZ2star_8TeV_pythia6_tauola");
	runStep2Analyzer_signle(3.19,          lumi, path, "DiJetPt_T_s-channel_TuneZ2star_8TeV-powheg-tauola");
	runStep2Analyzer_signle(41.92,         lumi, path, "DiJetPt_T_t-channel_TuneZ2star_8TeV-powheg-tauola");
	runStep2Analyzer_signle(7.87,          lumi, path, "DiJetPt_T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola");
	runStep2Analyzer_signle(1.44,          lumi, path, "DiJetPt_Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola");
	runStep2Analyzer_signle(22.65,         lumi, path, "DiJetPt_Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola");
	runStep2Analyzer_signle(7.87,          lumi, path, "DiJetPt_Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola");
*/
	//data
	runStep2Analyzer_signle(1,             lumi, path, "DiJetPt_SingleMuRun2012", 1);


}

void runStep2Analyzer_signle( Double_t xs, Double_t lumi,TString path, TString samplename, bool isData=0) 
{

	// mkdir plots fold accoding time
	TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
	dir.ReplaceAll("runStep2Analyzer.C","");
	dir.ReplaceAll("/./","/");
	TDatime dt;

	char* plot_Dir_DateTime=Form("%sPlots/%i_%i_%i/%s_%i",dir.Data(), dt.GetYear(), dt.GetMonth(), dt.GetDay(), samplename.Data(), dt.GetTime());
	cout<<plot_Dir_DateTime<<endl;
	gSystem->mkdir(plot_Dir_DateTime, 1);

	//TFile *file1=new TFile("/home/wangq/CMS/whbb/ben/lhe/"+samplename+".root");
	TFile *file1=new TFile(path+samplename+".root");

	TTree *tree1=(TTree*) file1->Get("tree");
	if(tree1){

		Step2Analyzer* analyzor = new Step2Analyzer(tree1, plot_Dir_DateTime);
		analyzor->Loop(samplename, xs, lumi, isData );

	}else{
		cout<<"Error! Coundn't find a tree!!!"<<endl;
	}
	/*    TFile *fout =new TFile("hist.root","recreate");
		  fout->mkdir("VHbb");
		  fout->cd("VHbb");
		  fout->Write();
		  fout->Close();
		  */
}
