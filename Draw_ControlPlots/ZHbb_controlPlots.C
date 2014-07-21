#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "stdio.h"
#include "THStack.h"
#include "TLegend.h"
#include <fstream>

using namespace std;

TH1F* GetHist(char* var_name, char* fileName, double histMin, double histMax);

void ZHbb_controlPlots(){
    //Draw_variable(costheta1);
    //Draw_variable(costheta2);
    //Draw_variable(costhetastar);
    //Draw_variable(phi);
    //Draw_variable(phi1);
    //Draw_variable(mVH);
    //Draw_variable(rapidityVH);
    //Draw_variable(Higgs_mass);
    //Draw_variable(Zstar_mass);
    //Draw_variable(Z_mass);

    /*    char* varName[9] = {"costheta1","costheta2","costhetastar","phi","phi1","rapidityVH",
          "mVH","Higgs_mass","Z_mass"};
          double histMin[9] = {-1.0, -1.0, 0., -4., -4., 
          -4., -10., 0., 80.};
          double histMax[9] = {1., 1., 1., 4., 4., 
          4.,1500., 300., 110.};
          *///    std::cout<<"test"<<std::endl;

    char* varName[9] = {"costheta1","costheta2","costhetastar","phi","phi1","rapidityVH",
        "mVH","Higgs_mass","Z_mass"};
    double histMin[9] = {-1.0, -1.0, 0., -4., -4., 
        -4., -10., 0., 80.};
    double histMax[9] = {1., 1., 1., 4., 4., 
        4.,1500., 300., 110.};



    for(int i = 0; i < 9; i++){

        //TString path = "/home/wangq/CMS/whbb/plot_from_controlregion/"; 
        //    TH1F* hist_1  = GetHist(varName[i], path+"Step2_ZHiggs0P_M-125p6_8TeV-JHUGenV4-private_histresult.root",             histMin[i], histMax[i] );
        //    TH1F* hist_2  = GetHist(varName[i], path+"DiJetPt_DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_histresult.root",        histMin[i], histMax[i] );
        //    TH1F* hist_3  = GetHist(varName[i], path+"DiJetPt_TT_8TeV-mcatnlo_histresult.root",                                  histMin[i], histMax[i] );
        //    TH1F* hist_4  = GetHist(varName[i], path+"DiJetPt_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_1  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/Step2_ZHiggs0P_M-125p6_8TeV-JHUGenV4-private_histresult.root",             histMin[i], histMax[i] );
        TH1F* hist_2  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_TT_8TeV-mcatnlo_histresult.root",                                  histMin[i], histMax[i] );
        TH1F* hist_3  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_histresult.root",        histMin[i], histMax[i] );
        TH1F* hist_4  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_5  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_6  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_7  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_8  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_9  = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_10 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_ZZ_TuneZ2star_8TeV_pythia6_tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_11 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_WZ_TuneZ2star_8TeV_pythia6_tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_12 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_WW_TuneZ2star_8TeV_pythia6_tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_13 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_T_s-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_14 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_T_t-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_15 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_16 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_17 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_18 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_histresult.root", histMin[i], histMax[i] );
        TH1F* hist_19 = GetHist(varName[i], "/home/wangq/CMS/whbb/plot_from_controlregion/2014_7_17/DiJetPt_DataZmm_histresult.root", histMin[i], histMax[i] );
        //    TH1F* hist_11 = GetHist(varName[i], "", histMin[i], histMax[i] );




        THStack * hs = new THStack("hs","hs");  //      --Qun Wang @ 2014-07-15
        THStack * hDY = new THStack("hDY","hDY"); 
        TCanvas* c1 = new TCanvas("c1","");
        //if(i<6) {        // --Qun Wang @ 2014-07-08
        //    hist_1 -> Scale(1./hist_1->Integral());
        hist_1 -> Scale(1.*0.000302073);
        hist_2 -> Scale(1.*2.60217e-06);
        hist_3 -> Scale(1.*0.000402992);
        hist_4 -> Scale(1.*0.0173155);
        hist_5 -> Scale(1.*9.2728e-06);
        hist_6 -> Scale(1.*2.5171e-05);
        hist_7 -> Scale(1.*1.757e-05);
        hist_8 -> Scale(1.*1.7368e-05);
        hist_9 -> Scale(1.*3.47431e-06);
        hist_10 -> Scale(1.*7.00183e-05);
        hist_11 -> Scale(1.*0.000190763);
        hist_12 -> Scale(1.*0.000393356);
        hist_13 -> Scale(1.*0.00133049);
        hist_14 -> Scale(1.*0.00156868);
        hist_15 -> Scale(1.*0.000828297);
        hist_16 -> Scale(1.*0.001125);
        hist_17 -> Scale(1.*0.00133907);
        hist_18 -> Scale(1.*0.000833082);
        //hist_19 -> Scale(1.*1.661e-06);




        // }

        // hist_1 ->SetLineColor(2);
        // hist_2 ->SetLineColor(4);
        // hist_3 ->SetLineColor(6);
        // hist_4 ->SetLineColor(9);
        // hist_5 ->SetLineColor(1);
        // hist_6 ->SetLineColor(50);
        // hist_7 ->SetLineColor(40);
        // hist_8 ->SetLineColor(31);
        hist_1 ->SetFillColor(2);
        hist_2 ->SetFillColor(4);
        hist_3 ->SetFillColor(6);
        hist_4 ->SetFillColor(6);
        hist_5 ->SetFillColor(6);
        hist_6 ->SetFillColor(6);
        hist_7 ->SetFillColor(6);
        hist_8 ->SetFillColor(6);
        hist_9 ->SetFillColor(6);
        hist_10 ->SetFillColor(5);
        hist_11 ->SetFillColor(49);
        hist_12 ->SetFillColor(31);
        hist_13 ->SetFillColor(3);
        hist_14 ->SetFillColor(3);
        hist_15 ->SetFillColor(3);
        hist_16 ->SetFillColor(1);
        hist_17 ->SetFillColor(1);
        hist_18 ->SetFillColor(1);
        hist_19 ->SetFillColor(41);
        hist_1 ->SetLineColor(2);
        hist_2 ->SetLineColor(4);
        hist_3 ->SetLineColor(6);
        hist_4 ->SetLineColor(6);
        hist_5 ->SetLineColor(6);
        hist_6 ->SetLineColor(6);
        hist_7 ->SetLineColor(6);
        hist_8 ->SetLineColor(6);
        hist_9 ->SetLineColor(6);
        hist_10 ->SetLineColor(5);
        hist_11 ->SetLineColor(49);
        hist_12 ->SetLineColor(31);
        hist_13 ->SetLineColor(3);
        hist_14 ->SetLineColor(3);
        hist_15 ->SetLineColor(3);
        hist_16 ->SetLineColor(1);
        hist_17 ->SetLineColor(1);
        hist_18 ->SetLineColor(1);
        hist_19 ->SetLineColor(41);
        hist_1 ->SetStats(kFALSE);
        hist_1 ->GetXaxis()->SetTitle(varName[i]);
        hist_1->GetXaxis()->CenterTitle();
        hist_19->SetMarkerStyle(20);
        c1->SetLogy();
        hs->Draw("hist");
        //  hist_19 ->Draw("PEsame");
        // hist_19 ->Draw("PE");
        // hs->Draw("histsame");
        // hist_1 -> Draw();  //         --Qun Wang @ 2014-07-15
        // hist_2 -> Draw("same");
        // hist_3 -> Draw("same");
        // hist_4 -> Draw("same");

        hs->Add(hist_1);
        hs->Add(hist_2);
        hs->Add(hist_10);
        hs->Add(hist_11);
        hs->Add(hist_12);
        hs->Add(hist_13);
        hs->Add(hist_14);
        hs->Add(hist_15);
        hs->Add(hist_16);
        hs->Add(hist_17);
        hs->Add(hist_18);
        hs->Add(hist_3);
        //hs->Add(hist_4);
        hs->Add(hist_5);
        hs->Add(hist_6);
        hs->Add(hist_7);
        hs->Add(hist_8);
        hs->Add(hist_9);
        hs->Add(hist_4);
        /*    hs->Add(hist_10);
              hs->Add(hist_11);
              hs->Add(hist_12);
              hs->Add(hist_13);
              hs->Add(hist_14);
              hs->Add(hist_15);
              hs->Add(hist_16);
              hs->Add(hist_17);
              hs->Add(hist_18);
              */    //hs->Add(hDY);
        //    hs->Draw();
        // hs->Draw("same");


        //    if(i==3) hist_1->GetYaxis()->SetRangeUser(0,0.09);
        //    if(i==5) hist_1->GetYaxis()->SetRangeUser(0,0.15);
        //    if(i==6) hist_1->GetYaxis()->SetRangeUser(0,1800.);
        //    if(i==7) hist_1->GetYaxis()->SetRangeUser(0,0.28);
        //    if(i==8) hist_1->GetYaxis()->SetRangeUser(0,9000.);
        //std::cout<<"againtest"<<endl; 
        TLegend * leg = new TLegend(.1,.7,.3,.9);
        leg->SetFillColor(0);
        leg->AddEntry(hist_1,"MC sample");
        leg->AddEntry(hist_2,"TT");
        leg->AddEntry(hist_3,"DYJet");
        leg->AddEntry(hist_10,"ZZ");
        leg->AddEntry(hist_11,"WZ");
        leg->AddEntry(hist_12,"WW");
        leg->AddEntry(hist_13,"T");
        leg->AddEntry(hist_16,"Tbar");
        leg->AddEntry(hist_19,"Data");
        leg->Draw();
        //c1->SaveAs(Form("figures/%s.pdf",varName[i]));
        c1->SaveAs(Form("figures_ControlR/%s.png",varName[i]));
        //c1->SaveAs(Form("figures/%s.eps",varName[i]));

        delete c1;
        delete hist_1;
        delete hist_2;
        delete hist_3;
        delete hist_4;
        delete hist_5;
        delete hist_6;
        delete hist_7;
        delete hist_8;
        delete hist_9;
        delete hist_10;
        delete hist_11;
        delete hist_12;
        delete hist_13;
        delete hist_14;
        delete hist_15;
        delete hist_16;
        delete hist_17;
        delete hist_18;
        delete hist_19;
        delete hs;  //      --Qun Wang @ 2014-07-15
    }



}

TH1F* GetHist(char* var_name, char* fileName, double histMin, double histMax){

    int nbins = 25;
    TH1F* hist = new TH1F("hist","",nbins, histMin, histMax);

    TFile* infile = new TFile(fileName,"R"); 
    TTree * t1 = (TTree*)infile->Get("tree");
    float var;
    t1->SetBranchAddress(var_name,&var);

    int nentries = t1->GetEntries();

    for(int ientry = 0; ientry < nentries; ientry++){

        //if(ientry%500==0)  
        //  std::cout << "entry " << ientry << 
        //      " of entries " << nentries << std::endl;

        t1->GetEntry(ientry);
        hist->Fill(var);
    }

    return hist;

}

