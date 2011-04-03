// File: unpacker_wk.h
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified:

#ifndef UNPACKER_WK_H
#define UNPACKER_WK_H

/////////////////////////////////////////////////////////////////////
//   Unpacker
//
// Event is a class used for creating the root tree.
// It contains the information unpacked from hld files.
// It's specific for "802" SubEvents (from Hodo like detectors)
/////////////////////////////////////////////////////////////////////

//#include <TROOT.h>
//#include <TChain.h>
#include <TTree.h>  //wk think about
#include <TFile.h>  //wk think about
#include <TObject.h>  //wk think about
#include "hldevent_wk.h"

enum EDsState {kDsOk=0,kDsEndFile=1,kDsEndData=2,kDsError=3};

class Unpacker: public TObject
{

public:

 Unpacker() 
 {
   fEventNr=0;
   pEvent=0;
   pRootFile=0;
 }

 Unpacker(const char* name,Int_t subEvtId){
  // cout<<"KONSTRUKTOR UNPACKER"<<endl;
  pEvent= new HldEvent(name,subEvtId); 
  fEventNr=0;
 }
 
 ~Unpacker() {
  if(pEvent)	delete pEvent;
 //wk to check 
 //if(pRootFile)	delete pRootFile;
 }

 //to set the root output file
 Bool_t setRootFile(const char* filename="test.root");
 
 // EDsState skipEvents(Int_t nEv);
//  EDsState getNextEvent(Bool_t doUnpack=kTRUE)=0;
 Bool_t eventLoop(Int_t NbEvt=50000,Int_t startEvt=0);

//hope it's not necessary 
 HldEvent* getpEvent(void) {return pEvent;}
 // Bool_t init(); 
 
// void setMaxEventPerFile(Int_t n) {fEventLimit = n; } 
//wk!!!! temporary public !!!
 HldEvent* pEvent; //Current event read from file
protected:

 Int_t fEventNr;   //Event Counter
 Int_t fEventLimit; //Maximum event number per file 
 TFile* pRootFile; // pointer to TFile with the output tree
 
public:
 ClassDef(Unpacker,1);
};

#endif /* !UNPACKER_WK_H */

