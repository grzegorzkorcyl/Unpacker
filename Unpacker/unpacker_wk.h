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
#include <TTree.h> 
#include <TFile.h>  
#include <TObject.h> 
#include <string>
#include "hldevent_wk.h"

using namespace std;

enum EDsState {kDsOk=0,kDsEndFile=1,kDsEndData=2,kDsError=3};

class Unpacker: public TObject
{

public:

 Unpacker(); 
 //fpga_code - used to select the source of data
 // gk
 // fpgaCode defines the endpoint addresses that that generates wanted subevents
 // the order of endpoints then defines the channel mapping on histogram
 //Unpacker(const char* name,Int_t nEvt=50000,Int_t subEvtId=803,Int_t referenceChannel=95,Int_t fpga_code=65535);
 //Unpacker(const char* name,Int_t nEvt=50000,Int_t subEvtId=803,Int_t referenceChannel=95, const char* fpga_code = "");
//  Unpacker(const char* name,Int_t nEvt=50000,const char* subEvtId="",Int_t referenceChannel=95, const char* fpga_code = ""); 
 //gk second constructor gives the possibility to set the search window instead of collecting all hits
 Unpacker(const char* name,Int_t nEvt=50000,const char* subEvtId="",Int_t referenceChannel=95, const char* fpga_code = "", Int_t min = -100000, Int_t max = -100000);
 ~Unpacker();
 
 
 // gk helper function
UInt_t HexStrToInt(const char* str) {
	UInt_t t;
	std::stringstream s;
	s << std::hex << str;
	s >> t;
	return t;
 }

 Bool_t setRootFile(const char* filename="test.root"); //to set the root output file
 string setInputFile(const char* filename); //to set the hld input file
 // EDsState skipEvents(Int_t nEv);
// EDsState getNextEvent(Bool_t doUnpack=kTRUE)=0;
// void setMaxEventPerFile(Int_t n) {fEventLimit = n; } 
 Bool_t eventLoop(Int_t NbEvt=50000,Int_t startEvt=0);
 // Bool_t init(); 
 Bool_t setpEvent(Int_t subId);	 //it sets pEvent by reading hld file
 HldEvent* getpEvent(void) {return pEvent;}
 Int_t getEventNr() { return EventNr; } 
 Int_t getEventLimit() { return EventLimit; }
 
 
 protected:
 void setpEvent(HldEvent* evt) { pEvent=evt; }
 HldEvent* pEvent; //Current event read from file
 Int_t EventNr;   //Event Counter
 Int_t EventLimit; //Maximum event number per file 
 Int_t subEvtId;
 TFile* pRootFile; // pointer to TFile with the output tree
 string inputFile; //wk 28.05
 Int_t fpga_code; // address of the data source (e.g. given fpga ) decoded from hld file 
 Int_t refCh;
 
public:
 ClassDef(Unpacker,1);
};

#endif /* !UNPACKER_WK_H */

