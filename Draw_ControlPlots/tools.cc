/*
 * =====================================================================================
 * 
 *       Filename:  tools.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  08/07/13 02:04:15 CDT
 *       Revision:  none
 *       Compiler:  gcc, root
 * 
 *         Author:  Zijun Xu, xuzijun123@gmail.com
 *        Company:  School of Physics, Peking Univ.
 * 
 * =====================================================================================
 */

#include "tools.h"

void print_p4(fastjet::PseudoJet tmpJ, std::string tmpName,bool extra_info){
	if(extra_info){ 
		std::cout<<tmpName<<" PseudoJet(pt,eta,phi,E,m,pdgID,charge)=("<<tmpJ.pt()<<","<<tmpJ.eta()<<","<<tmpJ.phi()<<","<<tmpJ.E()<<","<<tmpJ.m()<<","<<tmpJ.user_info<PseudoJetUserInfo>().pdg_id()<<","<<tmpJ.user_info<PseudoJetUserInfo>().charge()<<")"<<std::endl;
	}else{
		std::cout<<tmpName<<" PseudoJet(pt,eta,phi,E,m)=("<<tmpJ.pt()<<","<<tmpJ.eta()<<","<<tmpJ.phi()<<","<<tmpJ.E()<<","<<tmpJ.m()<<")"<<std::endl;
	}
}

void BREAK(std::string info){ 
	std::cout<<info<<std::endl<<"Enter a char to continue..."<<std::endl;
	char tmp;std::cin>>tmp;
}

Bool_t isMatching( fastjet::PseudoJet j1, fastjet::PseudoJet j2, Double_t deltaR){
	Double_t eta1=j1.eta();
	Double_t eta2=j2.eta();
	Double_t phi1=j1.phi();
	Double_t phi2=j2.phi();
	Double_t tmpR=TMath::Sqrt( (eta1-eta2)*(eta1-eta2) + (phi1-phi2)*(phi1-phi2) );
	if (tmpR<deltaR)return 1;
	else return 0;
}

