// File: unpacker_wk.cc
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified: 19.05.07
// 

#include "unpacker_wk.h"
//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include "htrbbaseunpacker.h"
//#include "htrblookup.h"
//#include "hdebug.h"
//#include "hades.h"
//#include "hevent.h"
//#include "hldsubevt.h"
//#include "heventheader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "hldevent_wk.h" 
#include "event_wk.h"

//______________________________________________________________________________
//   Unpacker
//
//
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

ClassImp(Unpacker)

//______________________________________________________________________________
Unpacker::Unpacker() 
{
   EventNr=0;
   pEvent=0;
   pRootFile=0;
   subEvtId=0;
   fpga_code=0;
   refCh = -1;
}

//______________________________________________________________________________
//gk change to accept multiple fpga_codes
//Unpacker::Unpacker(const char* name,Int_t nEvt /*=50000*/,Int_t subEvtId /*=802*/,Int_t refChannel/*=95*/, Int_t fpga_code/*=65535*/)
//Unpacker::Unpacker(const char* name,Int_t nEvt /*=50000*/,Int_t subEvtId /*=802*/,Int_t refChannel/*=95*/, const char* fpga_code/*=65535*/)
// Unpacker::Unpacker(const char* name,Int_t nEvt /*=50000*/,const char* subEvtId /*=802*/,Int_t refChannel/*=95*/, const char* fpga_code/*=65535*/)
// //if nEvt is equal 0 there will be no processing -> one can use eventLoop()
// {
//   
//   /*stringstream Name(name);
//   string Tmp,NoWhite;
//   //it strips all whitespaces from name
//   while(!Name.eof())
//   {
// 	  Tmp.clear();
// 	  Name>>skipws >>Tmp;
// 	  NoWhite+=Tmp;
//   }
//   */
//   refCh = -1;
//   refCh = refChannel;
//   this->subEvtId= HexStrToInt(subEvtId);	
//   setInputFile(name);
//   EventNr=0;
//   pEvent= new HldEvent(inputFile.c_str(), HexStrToInt(subEvtId), fpga_code); 
//   pRootFile=0;
// //  this->fpga_code=fpga_code;
//  if(nEvt>0)
//   {
//     eventLoop(nEvt);
//   }
//   cout<<"Reference channel is set in the event_wk.cc in the  Event::clearAll()"<<endl;
// 
// }

Unpacker::Unpacker(const char* name,Int_t nEvt, const char* subEvtId, Int_t refChannel, const char* fpga_code, Int_t min, Int_t max)
{
  refCh = -1;
  refCh = refChannel;
  this->subEvtId= HexStrToInt(subEvtId);	
  setInputFile(name);
  EventNr=0;
  pEvent= new HldEvent(inputFile.c_str(), HexStrToInt(subEvtId), fpga_code, min, max); 
  pRootFile=0;
//  this->fpga_code=fpga_code;
 if(nEvt>0)
  {
    eventLoop(nEvt);
  }
  cout<<"Reference channel is set in the event_wk.cc in the  Event::clearAll()"<<endl;
}

//______________________________________________________________________________
Unpacker::~Unpacker() 
{
  if(pEvent)	delete pEvent;
 //wk 28.05 
 if(pRootFile)	delete pRootFile;
}

//______________________________________________________________________________
Bool_t Unpacker::setRootFile(const char* filename/*="test.root" */)
{
  if(pRootFile)
  {
	  delete pRootFile;
	  pRootFile=new TFile(filename,"RECREATE");	  
  }
  else	pRootFile=new TFile(filename,"RECREATE");	  

return kTRUE;
}
 
//______________________________________________________________________________
string Unpacker::setInputFile(const char* filename)
{
   stringstream Name(filename);
   string Tmp,NoWhite;
   //it strips all whitespaces from name
   while(!Name.eof())
   {
 	Tmp.clear();
 	Name>>skipws >>Tmp;
 	NoWhite+=Tmp;
   }
  inputFile=NoWhite;  
   return inputFile;
}
	
//______________________________________________________________________________
Bool_t Unpacker::setpEvent(Int_t Id)
//Id is the subevent id 
{
   if(inputFile.empty())
   {
      return kFALSE;
   }
   subEvtId=Id;
//   pEvent= new HldEvent(inputFile.c_str(),Id,fpga_code);
   return kTRUE;
	
}


/*wk: from hldfilesource*/
/*
EDsState Unpacker::getNextEvent(Bool_t doUnpack) {
  // loops over the event files in the runtime database
  // Tries to read a new event from the LMD file and put the info into the
  // HEvent structure:

  if(isDumped) {
    if (dumpEvt()==kDsError) {
      if (getNextFile()==kFALSE) return kDsEndData;
      else return kDsEndFile;
    }
    return kDsOk;
  }

  if (isScanned) {
    if (scanEvt()==kDsError) {
      if (getNextFile()==kFALSE) return kDsEndData;
      else return kDsEndFile;
    }
    return kDsOk;
  }

  fEventNr++;

  if ( !((HldFilEvt*)fReadEvent)->execute() || !(fEventNr<fEventLimit)) {
    //End of current file
    fEventNr = 0;
    if (getNextFile()==kFALSE) return kDsEndData;
    else return kDsEndFile;
  }

  if(doUnpack){
    decodeHeader((*fEventAddr)->getHeader());
    iter->Reset();
    HldUnpack *unpacker;
    while ( (unpacker=(HldUnpack *)iter->Next())!=NULL) {
      if (!unpacker->execute()) return kDsError;
    }
  }
  return kDsOk;
}
*/

//______________________________________________________________________________
Bool_t Unpacker::eventLoop(Int_t nbEvt,Int_t startEv)
//Loop over all events, data written to the root tree
{
   if(pEvent==0)
   {
	   cout<<"Error: no pEvent set"<<endl;
	   return kFALSE;
   }
   else
   {
      if(!pRootFile)
      {
	 char* t = new char[(inputFile + ".root").length() + 1];
	 strcpy(t, (inputFile + ".root").c_str());
         setRootFile(t);
      }
//  TFile hfile("Event.root","RECREATE");
      TTree *tree = new TTree("T","An example of a ROOT tree");
      tree->SetAutoSave(1000000000); //autosave when 1 GB written
      Event* event=0;
      Int_t split = 2;
      Int_t bsize = 64000;
      cout<< "We create the tree"<<endl;
      tree->Branch("event","Event", &event, bsize,split);
// if(tree->GetBranchStatus("event")==kTRUE)	cout<<"aktywny"<<endl;
//  cout<<"to zwraca Branch(): "<<test<<endl;	  

      for(Int_t i=0; i< nbEvt; i++)
      {    
	  //cerr<<i<<endl;
         if(!(pEvent->execute()))
         {
	    cout<<"END OF FILE"<<endl;
	    cout<<"Number of Events: "<<EventNr<<endl;
	    break;
         }
	 //cerr<<"Un ref ch: "<<refCh<<endl;
         event= new Event(*pEvent, refCh);
	 //event->setReferenceChannel(refCh);
	 //cerr<<"Un get ref ch: "<<event->getReferenceChannel()<<endl;
	 
	 //cerr<<event->getReferenceChannel()<<" | "<<refCh<<endl;
         //cout<<"Event number: "<<i <<endl;   
   //cout<<"Leading time: "<<event->trbLeadingTime[3][0]<<endl;
   //cout<<"Trailing time: "<<event->trbTrailingTime[3][0]<<endl;
   
  //  cout<<"Reference Time" << event->getReferenceTime()<<endl;
         tree->Fill();   
         delete event;
         EventNr++;
      }
 //else return kFALSE;
      pRootFile->Write();
 //wk 28.05 hfile.Write();
 //hfile.Close();
      delete tree;
      return kTRUE;
   }
}
