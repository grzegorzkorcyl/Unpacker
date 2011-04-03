#define Planes_cxx
#include "Planes.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Planes::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L Planes.C
//      Root > Planes t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  
//wk 
TH1F *Hits_Plane= new TH1F("Hits_Plane","Hits_Plane",4,1,5);
TH1F *nPlanesPerEvent= new TH1F("nPlanesPerEvent","nPlanesPerEvent",5,0,5);
TH1F *hityNaZdarzenie= new TH1F("hityNaZdarzenie","Liczba hitow na zdarzenie",50,0,50);

Int_t channel;
Int_t Planes[4]={0,0,0,0};
Int_t nPlanes=0;
Int_t totHits=0;
Int_t channels[128];
Char_t test;

for(Int_t i=0; i<128; i++)
{
 channels[i]=0;	
}

//end wk
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Int_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //nb = b_Hits_channel->GetEntry(jentry);   nbytes += nb;  //wczytuje tylko jedna galaz--> powinno przyspieszyc
      
     // cout<< "Zdarzenie: "<<jentry<<endl;
     // cin >> test;
     
      if(totalNHits==0)	continue; 	//liczba trafien zero odpowiada pustemu naglowkowi
      
      for(Int_t i=0; i<kMaxHits; i++)
      {    
         channel=Hits_channel[i];    
	     
	      if(channel>0)		//zmienic to potem bo co z kanalem 0
	      {
		      	channels[channel]=1;
	      }
	      
//	      cout<<"kanal:"<<channel<<endl;
	      
	      if((channel>=64)&&(channel<=79))
	      {
				      Hits_Plane->Fill(1); //plaszczyzna pierwsza
	      			      Planes[0]=1;
				       
	      }
	      if((channel>=80)&&(channel<95))
	      {
				      Hits_Plane->Fill(3); //plaszczyzna trzecia
				      Planes[2]=1;
	      }
	      if((channel>=96)&&(channel<=111))
	      {
				      Hits_Plane->Fill(2); //plaszczyzna druga
	      			      Planes[1]=1;
	      }
	      if((channel>=112)&&(channel<=126)) 
	      {
				      Hits_Plane->Fill(4); //plaszczyzna czwarta
				      Planes[3]=1;
	      }
      }
     
      ClearLeaves();      
      
      for(Int_t i=0; i<128; i++)	//zmienic zeby uwzglednic kanal 0
      {
         if((i!=127)&&(i!=95))
	 { 
	    totHits+=channels[i];
	 }	 
	 channels[i]=0;	
      }
      
  //    cout <<"Liczba hitow w tym zdarzeniu:"<<totHits <<endl;
      hityNaZdarzenie->Fill(totHits);
      totHits=0;
      
	      for(Int_t k=0;k<4;k++)
	      {
		     nPlanes+=Planes[k];
		     Planes[k]=0;	//for next event
	      }
	      nPlanesPerEvent->Fill(nPlanes);
	      nPlanes=0; 
      // if (Cut(ientry) < 0) continue;
   
   } /*for*/
   
   //nPlanesPerEvent->Draw();
 //  Hits_Plane->Draw();
}


void Planes::ClearLeaves()
//private function it zeroes given arrays
{
   for(Int_t i=0; i<kMaxHits; i++)
   {
      Hits_channel[i]=0;
   }
}

void Planes::EventDisplay(int everyN)
//everyN it will show every N-th event
{
   
   Int_t channels[128];
   Char_t test;
   Int_t channel;
   
   for(Int_t i=0; i<128; i++){
      channels[i]=0;	
   }
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Int_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      //nb = fChain->GetEntry(jentry);   nbytes += nb;
      nb = b_Hits_channel->GetEntry(jentry);   nbytes += nb;  //wczytuje tylko jedna galaz--> powinno przyspieszyc
      
      for(Int_t i=0; i<kMaxHits; i++){    
         channel=Hits_channel[i];    
	    if(channel>0)		//zmienic to potem bo co z kanalem 0
	    {
	       channels[channel]=1;
	    }
      }
      if(!(jentry%everyN))
      {
	 cout <<"Event number: "<< jentry << endl;     
         cout<<" p1>>"; 
	 for(Int_t i=64; i<80; i++){
            if(channels[i]==1)
	    	cout<<" x ";
	    else
    		cout<<"   ";
	 //   if(!((i+1)%16))
         }
	 cout<<endl;
         cout<<" p2>>"; 
	 for(Int_t i=96; i<112; i++){
            if(channels[i]==1)
	    	cout<<" x ";
	    else
    		cout<<"   ";
	  //  if(!((i+1)%16))
         }
		cout<<endl;
         cout<<" p3>>"; 
	 for(Int_t i=80; i<96; i++){
            if(channels[i]==1)
	    	cout<<" x ";
	    else
    		cout<<"   ";
	  //  if(!((i+1)%16))
         }
	 cout<<endl;
         cout<<" p4>>"; 
	 for(Int_t i=112; i<128; i++){
            if(channels[i]==1)
	    	cout<<" x ";
	    else
    		cout<<"   ";
	 //   if(!((i+1)%16))
	//	cout<<endl;
         }
	 cout<<endl;
	 cin>>test;
	 if(test=='q')
		 return;
      }      
      
      ClearLeaves();   
      for(Int_t i=0; i<128; i++){
         channels[i]=0;	//zerowanie tablicy
      }
      
   }
}
