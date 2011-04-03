//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 21 15:38:36 2007 by ROOT version 4.04/02g
// from TTree T/An example of a ROOT tree
// found on file: Event.root
//////////////////////////////////////////////////////////

#ifndef Planes_h
#define Planes_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
const Int_t kMaxHits = 39;  //!!!! mayby it should change depending on given tree 

class Planes {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   TH1F *Hits_Plane; 
   TH1F *nPlanesPerEvent;
   TH1F*	   myHisto;
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          EvtHdr_fUniqueID;
   UInt_t          EvtHdr_fBits;
   Int_t           EvtHdr_size;
   Int_t           EvtHdr_decoding;
   Int_t           EvtHdr_id;
   Int_t           EvtHdr_seqNr;
   Int_t           EvtHdr_date;
   Int_t           EvtHdr_time;
   Int_t           EvtHdr_year;
   Int_t           EvtHdr_month;
   Int_t           EvtHdr_day;
   Int_t           EvtHdr_hour;
   Int_t           EvtHdr_minute;
   Int_t           EvtHdr_second;
   Int_t           EvtHdr_pad;
   Int_t           EvtHdr_dataSize;
   Int_t           EvtHdr_paddedSize;
   Int_t           kMaxMult;
   Int_t           kMaxChannelNr;
   UInt_t          subEvtId;
   Int_t           errors_per_event;
   Int_t           referenceChannel;
   Int_t           referenceTime;
   Int_t           totalNHits;
   Int_t           Hits_;
   UInt_t          Hits_fUniqueID[kMaxHits];   //[Hits_]
   UInt_t          Hits_fBits[kMaxHits];   //[Hits_]
   Int_t           Hits_channel[kMaxHits];   //[Hits_]
   Int_t           Hits_TDC[kMaxHits];   //[Hits_]
   Int_t           Hits_nHits[kMaxHits];   //[Hits_]
   Int_t           Hits_time1[kMaxHits];   //[Hits_]
   Int_t           Hits_width1[kMaxHits];   //[Hits_]
   Int_t           Hits_time2[kMaxHits];   //[Hits_]
   Int_t           Hits_width2[kMaxHits];   //[Hits_]
   Int_t           Hits_time3[kMaxHits];   //[Hits_]
   Int_t           Hits_width3[kMaxHits];   //[Hits_]
   Int_t           Hits_time4[kMaxHits];   //[Hits_]
   Int_t           Hits_width4[kMaxHits];   //[Hits_]
   Int_t           Hits_width_wk[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime1[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime1[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime2[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime2[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime3[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime3[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime4[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime4[kMaxHits];   //[Hits_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_EvtHdr_fUniqueID;   //!
   TBranch        *b_event_EvtHdr_fBits;   //!
   TBranch        *b_event_EvtHdr_size;   //!
   TBranch        *b_event_EvtHdr_decoding;   //!
   TBranch        *b_event_EvtHdr_id;   //!
   TBranch        *b_event_EvtHdr_seqNr;   //!
   TBranch        *b_event_EvtHdr_date;   //!
   TBranch        *b_event_EvtHdr_time;   //!
   TBranch        *b_event_EvtHdr_year;   //!
   TBranch        *b_event_EvtHdr_month;   //!
   TBranch        *b_event_EvtHdr_day;   //!
   TBranch        *b_event_EvtHdr_hour;   //!
   TBranch        *b_event_EvtHdr_minute;   //!
   TBranch        *b_event_EvtHdr_second;   //!
   TBranch        *b_event_EvtHdr_pad;   //!
   TBranch        *b_event_EvtHdr_dataSize;   //!
   TBranch        *b_event_EvtHdr_paddedSize;   //!
   TBranch        *b_event_kMaxMult;   //!
   TBranch        *b_event_kMaxChannelNr;   //!
   TBranch        *b_event_subEvtId;   //!
   TBranch        *b_event_errors_per_event;   //!
   TBranch        *b_event_referenceChannel;   //!
   TBranch        *b_event_referenceTime;   //!
   TBranch        *b_event_totalNHits;   //!
   TBranch        *b_event_Hits_;   //!
   TBranch        *b_Hits_fUniqueID;   //!
   TBranch        *b_Hits_fBits;   //!
   TBranch        *b_Hits_channel;   //!
   TBranch        *b_Hits_TDC;   //!
   TBranch        *b_Hits_nHits;   //!
   TBranch        *b_Hits_time1;   //!
   TBranch        *b_Hits_width1;   //!
   TBranch        *b_Hits_time2;   //!
   TBranch        *b_Hits_width2;   //!
   TBranch        *b_Hits_time3;   //!
   TBranch        *b_Hits_width3;   //!
   TBranch        *b_Hits_time4;   //!
   TBranch        *b_Hits_width4;   //!
   TBranch        *b_Hits_width_wk;   //!
   TBranch        *b_Hits_leadTime1;   //!
   TBranch        *b_Hits_trailTime1;   //!
   TBranch        *b_Hits_leadTime2;   //!
   TBranch        *b_Hits_trailTime2;   //!
   TBranch        *b_Hits_leadTime3;   //!
   TBranch        *b_Hits_trailTime3;   //!
   TBranch        *b_Hits_leadTime4;   //!
   TBranch        *b_Hits_trailTime4;   //!

   Planes(TTree *tree=0);
   virtual ~Planes();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   
   /*wk added 20.04.07*/
private
   void ClearLeaves();	// not all leaves but chosen
   /*end wk*/
};

#endif

#ifdef Planes_cxx
Planes::Planes(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Event.root");
      if (!f) {
         f = new TFile("Event.root");
      }
      tree = (TTree*)gDirectory->Get("T");

   }
   Init(tree);
}

Planes::~Planes()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Planes::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Planes::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Planes::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID",&fUniqueID);
   fChain->SetBranchAddress("fBits",&fBits);
   fChain->SetBranchAddress("EvtHdr.fUniqueID",&EvtHdr_fUniqueID);
   fChain->SetBranchAddress("EvtHdr.fBits",&EvtHdr_fBits);
   fChain->SetBranchAddress("EvtHdr.size",&EvtHdr_size);
   fChain->SetBranchAddress("EvtHdr.decoding",&EvtHdr_decoding);
   fChain->SetBranchAddress("EvtHdr.id",&EvtHdr_id);
   fChain->SetBranchAddress("EvtHdr.seqNr",&EvtHdr_seqNr);
   fChain->SetBranchAddress("EvtHdr.date",&EvtHdr_date);
   fChain->SetBranchAddress("EvtHdr.time",&EvtHdr_time);
   fChain->SetBranchAddress("EvtHdr.year",&EvtHdr_year);
   fChain->SetBranchAddress("EvtHdr.month",&EvtHdr_month);
   fChain->SetBranchAddress("EvtHdr.day",&EvtHdr_day);
   fChain->SetBranchAddress("EvtHdr.hour",&EvtHdr_hour);
   fChain->SetBranchAddress("EvtHdr.minute",&EvtHdr_minute);
   fChain->SetBranchAddress("EvtHdr.second",&EvtHdr_second);
   fChain->SetBranchAddress("EvtHdr.pad",&EvtHdr_pad);
   fChain->SetBranchAddress("EvtHdr.dataSize",&EvtHdr_dataSize);
   fChain->SetBranchAddress("EvtHdr.paddedSize",&EvtHdr_paddedSize);
   fChain->SetBranchAddress("kMaxMult",&kMaxMult);
   fChain->SetBranchAddress("kMaxChannelNr",&kMaxChannelNr);
   fChain->SetBranchAddress("subEvtId",&subEvtId);
   fChain->SetBranchAddress("errors_per_event",&errors_per_event);
   fChain->SetBranchAddress("referenceChannel",&referenceChannel);
   fChain->SetBranchAddress("referenceTime",&referenceTime);
   fChain->SetBranchAddress("totalNHits",&totalNHits);
   fChain->SetBranchAddress("Hits",&Hits_);
   fChain->SetBranchAddress("Hits.fUniqueID",Hits_fUniqueID);
   fChain->SetBranchAddress("Hits.fBits",Hits_fBits);
   fChain->SetBranchAddress("Hits.channel",Hits_channel);
   fChain->SetBranchAddress("Hits.TDC",Hits_TDC);
   fChain->SetBranchAddress("Hits.nHits",Hits_nHits);
   fChain->SetBranchAddress("Hits.time1",Hits_time1);
   fChain->SetBranchAddress("Hits.width1",Hits_width1);
   fChain->SetBranchAddress("Hits.time2",Hits_time2);
   fChain->SetBranchAddress("Hits.width2",Hits_width2);
   fChain->SetBranchAddress("Hits.time3",Hits_time3);
   fChain->SetBranchAddress("Hits.width3",Hits_width3);
   fChain->SetBranchAddress("Hits.time4",Hits_time4);
   fChain->SetBranchAddress("Hits.width4",Hits_width4);
   fChain->SetBranchAddress("Hits.width_wk",Hits_width_wk);
   fChain->SetBranchAddress("Hits.leadTime1",Hits_leadTime1);
   fChain->SetBranchAddress("Hits.trailTime1",Hits_trailTime1);
   fChain->SetBranchAddress("Hits.leadTime2",Hits_leadTime2);
   fChain->SetBranchAddress("Hits.trailTime2",Hits_trailTime2);
   fChain->SetBranchAddress("Hits.leadTime3",Hits_leadTime3);
   fChain->SetBranchAddress("Hits.trailTime3",Hits_trailTime3);
   fChain->SetBranchAddress("Hits.leadTime4",Hits_leadTime4);
   fChain->SetBranchAddress("Hits.trailTime4",Hits_trailTime4);
   Notify();
}

Bool_t Planes::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_event_fUniqueID = fChain->GetBranch("fUniqueID");
   b_event_fBits = fChain->GetBranch("fBits");
   b_event_EvtHdr_fUniqueID = fChain->GetBranch("EvtHdr.fUniqueID");
   b_event_EvtHdr_fBits = fChain->GetBranch("EvtHdr.fBits");
   b_event_EvtHdr_size = fChain->GetBranch("EvtHdr.size");
   b_event_EvtHdr_decoding = fChain->GetBranch("EvtHdr.decoding");
   b_event_EvtHdr_id = fChain->GetBranch("EvtHdr.id");
   b_event_EvtHdr_seqNr = fChain->GetBranch("EvtHdr.seqNr");
   b_event_EvtHdr_date = fChain->GetBranch("EvtHdr.date");
   b_event_EvtHdr_time = fChain->GetBranch("EvtHdr.time");
   b_event_EvtHdr_year = fChain->GetBranch("EvtHdr.year");
   b_event_EvtHdr_month = fChain->GetBranch("EvtHdr.month");
   b_event_EvtHdr_day = fChain->GetBranch("EvtHdr.day");
   b_event_EvtHdr_hour = fChain->GetBranch("EvtHdr.hour");
   b_event_EvtHdr_minute = fChain->GetBranch("EvtHdr.minute");
   b_event_EvtHdr_second = fChain->GetBranch("EvtHdr.second");
   b_event_EvtHdr_pad = fChain->GetBranch("EvtHdr.pad");
   b_event_EvtHdr_dataSize = fChain->GetBranch("EvtHdr.dataSize");
   b_event_EvtHdr_paddedSize = fChain->GetBranch("EvtHdr.paddedSize");
   b_event_kMaxMult = fChain->GetBranch("kMaxMult");
   b_event_kMaxChannelNr = fChain->GetBranch("kMaxChannelNr");
   b_event_subEvtId = fChain->GetBranch("subEvtId");
   b_event_errors_per_event = fChain->GetBranch("errors_per_event");
   b_event_referenceChannel = fChain->GetBranch("referenceChannel");
   b_event_referenceTime = fChain->GetBranch("referenceTime");
   b_event_totalNHits = fChain->GetBranch("totalNHits");
   b_event_Hits_ = fChain->GetBranch("Hits");
   b_Hits_fUniqueID = fChain->GetBranch("Hits.fUniqueID");
   b_Hits_fBits = fChain->GetBranch("Hits.fBits");
   b_Hits_channel = fChain->GetBranch("Hits.channel");
   b_Hits_TDC = fChain->GetBranch("Hits.TDC");
   b_Hits_nHits = fChain->GetBranch("Hits.nHits");
   b_Hits_time1 = fChain->GetBranch("Hits.time1");
   b_Hits_width1 = fChain->GetBranch("Hits.width1");
   b_Hits_time2 = fChain->GetBranch("Hits.time2");
   b_Hits_width2 = fChain->GetBranch("Hits.width2");
   b_Hits_time3 = fChain->GetBranch("Hits.time3");
   b_Hits_width3 = fChain->GetBranch("Hits.width3");
   b_Hits_time4 = fChain->GetBranch("Hits.time4");
   b_Hits_width4 = fChain->GetBranch("Hits.width4");
   b_Hits_width_wk = fChain->GetBranch("Hits.width_wk");
   b_Hits_leadTime1 = fChain->GetBranch("Hits.leadTime1");
   b_Hits_trailTime1 = fChain->GetBranch("Hits.trailTime1");
   b_Hits_leadTime2 = fChain->GetBranch("Hits.leadTime2");
   b_Hits_trailTime2 = fChain->GetBranch("Hits.trailTime2");
   b_Hits_leadTime3 = fChain->GetBranch("Hits.leadTime3");
   b_Hits_trailTime3 = fChain->GetBranch("Hits.trailTime3");
   b_Hits_leadTime4 = fChain->GetBranch("Hits.leadTime4");
   b_Hits_trailTime4 = fChain->GetBranch("Hits.trailTime4");

   return kTRUE;
}

void Planes::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Planes::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

#endif // #ifdef Planes_cxx
