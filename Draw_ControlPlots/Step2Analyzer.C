#define Step2Analyzer_cxx
#include "Step2Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


using namespace std;



void Step2Analyzer::Loop(TString samplename, Double_t xs, Double_t lumi, Double_t num_entrise, bool isData)
{
	if (fChain == 0) return;

	//output root file
	TFile rootfout(PlotDir+"/../"+samplename+"_histresult.root","recreate");

	TTree tree("tree","tree");
	float  costheta1,costheta2,phi,costhetastar,phi1,mVH,rapidityVH;
	float  Z_mass,Z_eta,Z_pt;
	float  Higgs_mass,Higgs_eta,Higgs_pt;
	float  lep0_eta,lep0_pt,lep1_eta,lep1_pt;
	float  Bjet0_eta,Bjet0_pt,Bjet1_eta,Bjet1_pt;
	double  Reweight;	
	tree.Branch("costheta1",   &costheta1,   "costheta1/F");
	tree.Branch("costheta2",   &costheta2,   "costheta2/F");
	tree.Branch("phi",         &phi,         "phi/F");
	tree.Branch("costhetastar",&costhetastar,"costhetastar/F");
	tree.Branch("phi1",        &phi1,        "phi1/F");
	tree.Branch("mVH",         &mVH,         "mVH/F");
	tree.Branch("rapidityVH",  &rapidityVH,  "rapidityVH/F");
	tree.Branch("Higgs_mass",  &Higgs_mass,  "Higgs_mass/F");
	tree.Branch("Higgs_eta",   &Higgs_eta,       "Higgs_eta/F");
	tree.Branch("Higgs_pt",    &Higgs_pt,        "Higgs_pt/F");
	tree.Branch("Z_mass",      &Z_mass,      "Z_mass/F");
	tree.Branch("Z_eta",       &Z_eta,       "Z_eta/F");
	tree.Branch("Z_pt",        &Z_pt,        "Z_pt/F");
	tree.Branch("lep0_eta",    &lep0_eta,    "lep0_eta/F");   //        --Qun Wang @ 2014-07-15
	tree.Branch("lep0_pt",     &lep0_pt,     "lep0_pt/F");
	tree.Branch("lep1_eta",    &lep1_eta,    "lep1_eta/F");
	tree.Branch("lep1_pt",     &lep1_pt,     "lep1_pt/F");
	tree.Branch("Bjet0_eta",   &Bjet0_eta,   "Bjet0_eta/F");
	tree.Branch("Bjet0_pt",    &Bjet0_pt,    "Bjet0_pt/F");
	tree.Branch("Bjet1_pt",    &Bjet1_pt,    "Bjet1_pt/F");
	tree.Branch("Bjet1_eta",   &Bjet0_eta,   "Bjet1_eta/F");
	tree.Branch("Reweight",    &Reweight,    "Reweight/D");

	TH1D   hist_Higgs_mass("hist_Higgs_mass","hist_Higgs_mass",50,0,300);
	TH1D    hist_Higgs_eta("hist_Higgs_eta","hist_Higgs_eta",50,-6,6);
	TH1D     hist_Higgs_pt("hist_Higgs_pt","hist_Higgs_pt",50,0,1000);
	TH1D       hist_Z_mass("hist_Z_mass","hist_Z_mass",50,0,160);
	TH1D        hist_Z_eta("hist_Z_eta","hist_Z_eta",50,-6,6);
	TH1D         hist_Z_pt("hist_Z_pt","hist_Z_pt",50,0,1000);
	TH1D    hist_costheta1("hist_costheta1","hist_costheta1",50,-1.2,1.2); 
	TH1D    hist_costheta2("hist_costheta2","hist_costheta2",50,-1.2,1.2);
	TH1D          hist_phi("hist_phi","hist_phi",50,-4,4);
	TH1D hist_costhetastar("hist_costhetastar","hist_costhetastar",50,-1.2,1.2);
	TH1D         hist_phi1("hist_phi1","hist_phi1",50,-4,4);
	TH1D          hist_mVH("hist_mVH","hist_mVH",50,-10,1000);
	TH1D   hist_rapidityVH("hist_rapidityVH","hist_rapidityVH",50,-4,4);
	TH1D     hist_lep0_eta("hist_lep0_eta","hist_lep0_eta",50,-6,6);   //       --Qun Wang @ 2014-07-15
	TH1D      hist_lep0_pt("hist_lep0_pt","hist_lep0_pt",50,0,800);
	TH1D     hist_lep1_eta("hist_lep1_eta","hist_lep1_eta",50,-6,6);
	TH1D      hist_lep1_pt("hist_lep1_pt","hist_lep1_pt",50,0,800);
	TH1D    hist_Bjet0_eta("hist_Bjet0_eta","hist_Bjet0_eta",50,-6,6);
	TH1D     hist_Bjet0_pt("hist_Bjet0_pt","hist_Bjet0_pt",50,0,800);
	TH1D    hist_Bjet1_eta("hist_Bjet1_eta","hist_Bjet1_eta",50,-6,6);
	TH1D     hist_Bjet1_pt("hist_Bjet1_pt","hist_Bjet1_pt",50,0,800);
	TH1D     hist_Reweight("hist_Reweight","hist_Reweight",1,0,1);

	//the 4-vect of Hbb, Wlv/Zll
	TLorentzVector bjet0;
	TLorentzVector bjet1;
	TLorentzVector chargelep;
	TLorentzVector chargelep2;
	TString lep_type;
	TLorentzVector met;
	TLorentzVector neutrino;
	TLorentzVector wlep;
	TLorentzVector zlep;
	TLorentzVector zstar;


	Long64_t nentries = fChain->GetEntriesFast();
	//nentries=100000;//for quickly test
	Long64_t nbytes = 0, nb = 0;

	//MC sample reweight
	cout<<"nentries="<<nentries<<endl;
	Double_t reweight=xs*lumi/num_entrise;
	reweight=reweight*fChain->GetEntriesFast()/nentries;
	cout<<"reweight="<<reweight<<endl;
	hist_Reweight.SetBinContent(1,reweight);
	ofstream outfile(PlotDir+"/"+samplename+"test.txt");	
	outfile << "AOD level event number: "<<num_entrise << endl;
	outfile << "    total event number: "<<nentries << endl;
	outfile << "         cross-section: "<< xs<<endl;
	outfile << "                  lumi: "<< lumi<<endl;
	outfile << "          event weight: "<<reweight << endl;
	outfile.close();

	if(isData){
		reweight=  Double_t(fChain->GetEntriesFast())/Double_t(nentries); 
		cout<<" Data reweight= "<<reweight<<endl;
	}

	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		if(jentry%100000==0) cout<<"jentry="<<jentry<<"  "<<Double_t(jentry)/nentries*100.0<<"\% done"<<endl;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if (Cut(ientry) < 0) continue;//pre-selection

		//Get the 4-vect of Hbb, Wlv/Zll
		bjet0.SetPtEtaPhiE(hJet_pt[0],hJet_eta[0], hJet_phi[0],hJet_e[0]);
		bjet1.SetPtEtaPhiE(hJet_pt[1],hJet_eta[1], hJet_phi[1],hJet_e[1]);

		if(vLepton_mass[0]<-1 || vLepton_mass[1]<-1){
			cout<<"Error! Lep mass is nega="<<vLepton_mass[0]<<", "<<vLepton_mass[1]<<endl;
			cout<<"nvlep=" <<nvlep<<endl;
			cout<<"nhJets=" <<nhJets<<endl;

			BREAK();
		}

		chargelep.SetPtEtaPhiM(vLepton_pt[0], vLepton_eta[0], vLepton_phi[0], vLepton_mass[0]);
		chargelep2.SetPtEtaPhiM(vLepton_pt[1], vLepton_eta[1], vLepton_phi[1], vLepton_mass[1]);

		//cout<<"vlepton_type0    "<<vLepton_type[0]<<endl; //cout<<"vlepton_type1    "<<vLepton_type[1]<<endl;
		if(vLepton_type[0]==11){ lep_type="electron";
			//cout<<"vlepton_type0    "<<vLepton_type[0]<<endl;
			//cout<<"vLepton_charge0   "<<vLepton_charge[0]<<endl;
		}  //		--Qun Wang @ 2014-06-18
		else{
			if(vLepton_type[0]==13){ lep_type="muon";
				//cout<<"vlepton_type0    "<<vLepton_type[0]<<endl;
				//cout<<"vLepton_charge0   "<<vLepton_charge[0]<<endl;
			} else{
				cout<<"Error! Unknow Lep="<<vLepton_type[0];
				BREAK();
			}
		}

		hist_Higgs_mass.Fill(H.mass, reweight);
		hist_Higgs_eta. Fill(H.eta, reweight);   //      --Qun Wang @ 2014-07-15
		hist_Higgs_pt.  Fill(H.pt, reweight);
		hist_Bjet0_eta. Fill(hJet_eta[0], reweight);
		hist_Bjet0_pt.  Fill(hJet_pt[0], reweight);
		hist_Bjet1_eta. Fill(hJet_eta[1], reweight);
		hist_Bjet1_pt.  Fill(hJet_pt[1], reweight);
		hist_Z_mass.    Fill(V.mass, reweight);
		hist_Z_eta.     Fill(V.eta, reweight);
		hist_Z_pt.      Fill(V.pt, reweight);

		//zstar = -10;
		//        wlep=chargelep+neutrino;
		//if((vLepton_type[0]==11 && vLepton_type[1]==-11) || (vLepton_type[0]==-11 && vLepton_type[1]==11) || (vLepton_type[0]==13 && vLepton_type[1]==-13) || (vLepton_type[0]==-13 && vLepton_type[1]==13))  zlep=chargelep+chargelep2;
		/*if(vLepton_type[1]==vLepton_type[0]&&vLepton_charge[0]!=vLepton_charge[1])  zlep=chargelep+chargelep2; //          --Qun Wang @ 2014-06-24
		  if(zlep.M()>80&&zlep.M()<100)   
		  {   
		  hist_Z_mass.Fill(zlep.M(), reweight);
		  hist_Z_eta.Fill(zlep.Eta(), reweight);
		  hist_Z_pt.Fill(zlep.Pt(), reweight);
		  }
		  Higgs_mass = higgs.M();
		  Z_mass = zlep.M();
		  */

		//I assume you have the following four four-vectors:
		//fs_f0 is the four-vector of the fermion particle
		//fs_f1 is the four-vector of the fermion ***anti***-particle
		//fs_b0 is the four-vector of the b jet with the higher pT 
		//fs_b1 is the four-vector of the b jet with the lower pT
		//(Note: we use pT since we don't know which b jet is the particle or anti particle)
		TLorentzVector fs_f0;
		TLorentzVector fs_f1;
		TLorentzVector fs_b0;
		TLorentzVector fs_b1;

		//2 b-jets
		fs_b0=bjet0;
		fs_b1=bjet1;

		if(bjet0.Pt() <bjet1.Pt()){
			cout<<"strange: bjet0 pT < bjet1 pT"<<endl;
			BREAK();
			fs_b0=bjet1;	fs_b1=bjet0;
		}

		// 2 lep
		if(vLepton_charge[0]>0) {
			fs_f0=chargelep;
			fs_f1=chargelep2;
		}else{
			fs_f0=chargelep2;
			fs_f1=chargelep;
		}

		hist_lep0_eta.Fill(chargelep.Eta(), reweight);
		hist_lep0_pt.Fill(chargelep.Pt(), reweight);
		hist_lep1_eta.Fill(chargelep2.Eta(), reweight);
		hist_lep1_pt.Fill(chargelep2.Pt(), reweight);

		TLorentzVector p4_Vff = fs_f0 + fs_f1; //Four-vector of V that decays to two fermions
		TLorentzVector p4_Hbb = fs_b0 + fs_b1; //Four-vector of H
		TLorentzVector p4_VH = p4_Vff + p4_Hbb; //Four-vector of off-shell V that decays to VH

		Double_t a_costheta1, a_costheta2, a_costhetastar, a_Phi, a_Phi1;
		computeAngles( p4_VH, p4_Vff, fs_f0, fs_f1, p4_Hbb, fs_b0, fs_b1,
					a_costheta1, a_costheta2, a_Phi, a_costhetastar, a_Phi1); 
		//remap to convention of arXiv:1309.4819
		/*        float costheta1 = (float) a_costheta1;
				  float costheta2 = (float) a_costhetastar;
				  float phi = (float) a_Phi1;
				  float costhetastar = TMath::Abs( (float) a_costheta2);
				  float phi1 = (float) a_Phi;
				  float mVH = (float) p4_VH.M();
				  float rapidityVH = (float) p4_VH.Rapidity();
				  *///        tree.Fill();
		//remap to convention of arXiv:1309.4819
		//costheta1 = (float) a_costheta1;
		//costheta2 = (float) a_costhetastar;
		costheta1 = (float) a_costhetastar;
		costheta2 = (float) a_costheta1;
		phi = (float) a_Phi1;
		costhetastar = TMath::Abs( (float) a_costheta2);
		phi1 = (float) a_Phi;
		mVH = (float) p4_VH.M();
		rapidityVH = (float) p4_VH.Rapidity();


		hist_costheta1.Fill(costheta1, reweight); 
		hist_costheta2.Fill(costheta2, reweight);
		hist_phi.Fill(phi, reweight);
		hist_costhetastar.Fill(costhetastar, reweight);
		hist_phi1.Fill(phi1, reweight);
		hist_mVH.Fill(mVH, reweight);
		hist_rapidityVH.Fill(rapidityVH, reweight);

		//tree.Fill();
	}

	Draw_and_Save(PlotDir, hist_Higgs_mass);
	Draw_and_Save(PlotDir, hist_Higgs_eta);
	Draw_and_Save(PlotDir, hist_Higgs_pt);
	Draw_and_Save(PlotDir, hist_Z_mass);
	Draw_and_Save(PlotDir, hist_Z_eta);
	Draw_and_Save(PlotDir, hist_Z_pt);
	Draw_and_Save(PlotDir,    hist_costheta1);
	Draw_and_Save(PlotDir,    hist_costheta2);
	Draw_and_Save(PlotDir,          hist_phi);
	Draw_and_Save(PlotDir, hist_costhetastar);
	Draw_and_Save(PlotDir,         hist_phi1);
	Draw_and_Save(PlotDir,          hist_mVH);
	Draw_and_Save(PlotDir,   hist_rapidityVH);
	Draw_and_Save(PlotDir, hist_lep0_eta);
	Draw_and_Save(PlotDir, hist_lep0_pt);
	Draw_and_Save(PlotDir, hist_lep1_eta);
	Draw_and_Save(PlotDir, hist_lep1_pt);
	Draw_and_Save(PlotDir, hist_Reweight);
	Draw_and_Save(PlotDir, hist_Bjet0_eta);
	Draw_and_Save(PlotDir, hist_Bjet0_pt);
	Draw_and_Save(PlotDir, hist_Bjet1_eta);
	Draw_and_Save(PlotDir, hist_Bjet1_pt);

	hist_costheta1.Write();
	hist_costheta2.Write();
	hist_phi.Write();
	hist_costhetastar.Write();
	hist_phi1.Write();
	hist_mVH.Write();
	hist_rapidityVH.Write();
	hist_Higgs_mass.Write();
	hist_Higgs_pt.Write();
	hist_Higgs_eta.Write();
	hist_Z_mass.Write();
	hist_Z_pt.Write();
	hist_Z_eta.Write();

	//tree.Write();



}

TLorentzVector getNeutrino(TLorentzVector chargelep, TLorentzVector met, TString lep_type, Int_t diffMode)//diffMode: different neutrino vz 
{
	TLorentzVector p4_neutrino;
	METzCalculator metzcal;
	metzcal.SetMET(met);
	metzcal.SetLepton(chargelep);
	if(lep_type=="electron" || lep_type=="muon") metzcal.SetLeptonType(lep_type.Data());
	else cout<<"Error! Unknow Lep="<<lep_type.Data();
	Double_t pzNu1=metzcal.Calculate(diffMode);
	//Double_t pzNu2=metzcal.getOther();

	Double_t energy=TMath::Sqrt(met.E()*met.E()+pzNu1*pzNu1);
	p4_neutrino.SetPxPyPzE(met.Px(), met.Py(), pzNu1, energy);

	//if(metzcal.IsComplex())p4_neutrino.SetPxPyPzE(0.,0.,0.,-10);
	return p4_neutrino;

}


void Draw_and_Save(TString plotDir, TH1D h1, char* addtional_info){
	TCanvas *c1 = new TCanvas(Form("c1_%s",h1.GetTitle()),Form("c1_%s",h1.GetTitle()),200,10,600,600);
	c1->cd();
	h1.Draw();
	if( addtional_info){
		TLatex tl;
		tl.SetTextSize(0.04 ); tl.SetTextAlign(13);
		tl.DrawLatex(h1.GetXaxis()->GetXmin()*0.9+h1.GetXaxis()->GetXmax()*0.1, h1.GetMinimum()*0.1 +h1.GetMaximum()*0.9,addtional_info);
	};
	//c1->Write();
	c1->Print(Form("%s/%s.png",plotDir.Data(), h1.GetTitle()));
	delete c1;
}

//////////////////////////////////
//// P A P E R 4 - V E C T O R D E F I N I T I O N O F P H I A N D P H I 1
//////////////////////////////////
void computeAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4M11, TLorentzVector thep4M12, TLorentzVector thep4Z2, TLorentzVector thep4M21, TLorentzVector thep4M22, double& costheta1, double& costheta2, double& Phi, double& costhetastar, double& Phi1){

	///////////////////////////////////////////////
	// check for z1/z2 convention, redefine all 4 vectors with convention
	///////////////////////////////////////////////
	TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;
	p4H = thep4H;

	p4Z1 = thep4Z1; p4M11 = thep4M11; p4M12 = thep4M12;
	p4Z2 = thep4Z2; p4M21 = thep4M21; p4M22 = thep4M22;
	//// costhetastar
	TVector3 boostX = -(thep4H.BoostVector());
	TLorentzVector thep4Z1inXFrame( p4Z1 );
	TLorentzVector thep4Z2inXFrame( p4Z2 );	
	thep4Z1inXFrame.Boost( boostX );
	thep4Z2inXFrame.Boost( boostX );
	TVector3 theZ1X_p3 = TVector3( thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z() );
	TVector3 theZ2X_p3 = TVector3( thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z() );
	costhetastar = theZ1X_p3.CosTheta();

	//// --------------------------- costheta1
	TVector3 boostV1 = -(thep4Z1.BoostVector());
	TLorentzVector p4M11_BV1( p4M11 );
	TLorentzVector p4M12_BV1( p4M12 );	
	TLorentzVector p4M21_BV1( p4M21 );
	TLorentzVector p4M22_BV1( p4M22 );
	p4M11_BV1.Boost( boostV1 );
	p4M12_BV1.Boost( boostV1 );
	p4M21_BV1.Boost( boostV1 );
	p4M22_BV1.Boost( boostV1 );

	TLorentzVector p4V2_BV1 = p4M21_BV1 + p4M22_BV1;
	//// costheta1
	costheta1 = -p4V2_BV1.Vect().Dot( p4M11_BV1.Vect() )/p4V2_BV1.Vect().Mag()/p4M11_BV1.Vect().Mag();

	//// --------------------------- costheta2
	TVector3 boostV2 = -(thep4Z2.BoostVector());
	TLorentzVector p4M11_BV2( p4M11 );
	TLorentzVector p4M12_BV2( p4M12 );	
	TLorentzVector p4M21_BV2( p4M21 );
	TLorentzVector p4M22_BV2( p4M22 );
	p4M11_BV2.Boost( boostV2 );
	p4M12_BV2.Boost( boostV2 );
	p4M21_BV2.Boost( boostV2 );
	p4M22_BV2.Boost( boostV2 );

	TLorentzVector p4V1_BV2 = p4M11_BV2 + p4M12_BV2;
	//// costheta2
	costheta2 = -p4V1_BV2.Vect().Dot( p4M21_BV2.Vect() )/p4V1_BV2.Vect().Mag()/p4M21_BV2.Vect().Mag();

	//// --------------------------- Phi and Phi1
	// TVector3 boostX = -(thep4H.BoostVector());
	TLorentzVector p4M11_BX( p4M11 );
	TLorentzVector p4M12_BX( p4M12 );	
	TLorentzVector p4M21_BX( p4M21 );
	TLorentzVector p4M22_BX( p4M22 );	

	p4M11_BX.Boost( boostX );
	p4M12_BX.Boost( boostX );
	p4M21_BX.Boost( boostX );
	p4M22_BX.Boost( boostX );

	TVector3 tmp1 = p4M11_BX.Vect().Cross( p4M12_BX.Vect() );
	TVector3 tmp2 = p4M21_BX.Vect().Cross( p4M22_BX.Vect() );

	TVector3 normal1_BX( tmp1.X()/tmp1.Mag(), tmp1.Y()/tmp1.Mag(), tmp1.Z()/tmp1.Mag() );
	TVector3 normal2_BX( tmp2.X()/tmp2.Mag(), tmp2.Y()/tmp2.Mag(), tmp2.Z()/tmp2.Mag() );

	//// Phi
	TLorentzVector p4Z1_BX = p4M11_BX + p4M12_BX;
	double tmpSgnPhi = p4Z1_BX.Vect().Dot( normal1_BX.Cross( normal2_BX) );
	double sgnPhi = tmpSgnPhi/fabs(tmpSgnPhi);
	Phi = sgnPhi * acos( -1.*normal1_BX.Dot( normal2_BX) );


	//////////////

	TVector3 beamAxis(0,0,1);
	TVector3 tmp3 = (p4M11_BX + p4M12_BX).Vect();

	TVector3 p3V1_BX( tmp3.X()/tmp3.Mag(), tmp3.Y()/tmp3.Mag(), tmp3.Z()/tmp3.Mag() );
	TVector3 tmp4 = beamAxis.Cross( p3V1_BX );
	TVector3 normalSC_BX( tmp4.X()/tmp4.Mag(), tmp4.Y()/tmp4.Mag(), tmp4.Z()/tmp4.Mag() );

	//// Phi1
	double tmpSgnPhi1 = p4Z1_BX.Vect().Dot( normal1_BX.Cross( normalSC_BX) );
	double sgnPhi1 = tmpSgnPhi1/fabs(tmpSgnPhi1);
	Phi1 = sgnPhi1 * acos( normal1_BX.Dot( normalSC_BX) );

	// std::cout << "extractAngles: " << std::endl;
	// std::cout << "costhetastar = " << costhetastar << ", costheta1 = " << costheta1 << ", costheta2 = " << costheta2 << std::endl;
	// std::cout << "Phi = " << Phi << ", Phi1 = " << Phi1 << std::endl;

}
