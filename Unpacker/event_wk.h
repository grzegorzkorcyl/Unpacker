// File: event_wk.h 
//  
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified:

#ifndef EVENT_WK_H
#define EVENT_WK_H

/////////////////////////////////////////////////////////////////////
// Event 
//
// Event is a class used for creating the root tree.
// It contains the information unpacked from hld files.
// It's specific for SubEvents from Hodo like detectors
// Class is based on HHodoRaw class
/////////////////////////////////////////////////////////////////////

#include <TObject.h>
#include <TBuffer.h>
#include <TClonesArray.h>
#include "eventhdr_wk.h"

//wk temporary
#include <iostream>
using namespace std;


typedef UInt_t UInt4;
typedef UChar_t UInt1;

class HldEvent;
class Hit;

class Event :public TObject
{
 
 public:

 Event();
 Event(const HldEvent& HldEvt, Int_t refCh);
 virtual ~Event();
 
 protected:
 
 EventHdr EvtHdr;   //contains data from event header 
 
 //wk added 03.02.07 not necessary (??)
  const Int_t kMaxMult; //Maximum number of multiplicity
  const Int_t kMaxChannelNr; 
 //wk end
 
 //data from subEvent
 UInt_t subEvtId;   //Id of subEvent according to HLD format
 //wk 18.01. added
 public:
 //Int_t trbLeadingTime[128][10];
 //Int_t trbTrailingTime[128][10];
 private:
 
//wk 03.02.07 Int_t trbADC[128][10];
 //Int_t trbLeadingMult[128];
 //Int_t trbTrailingMult[128];
 
 Int_t errors_per_event;   // number of TDC errors per event
 Int_t referenceChannel;   // reference channel
 Int_t referenceTime;   // reference time from indicated channel if it is used
 
 Int_t totalNHits; // total number of hits per one event
 TClonesArray* Hits; //array with all hits
 static TClonesArray* gHits;
 
 public:
	 
 Int_t getEvtSize()  { return EvtHdr.getSize(); }
 Int_t getEvtDecoding()  { return EvtHdr.getDecoding(); }
 Int_t getEvtId()  { return EvtHdr.getId(); }
 Int_t getEvtSeqNr()  { return EvtHdr.getSeqNr(); }
 Int_t getEvtDate()  { return EvtHdr.getDate(); }
 Int_t getEvtTime()  { return EvtHdr.getTime(); }
 Int_t getEvtYear()  { return EvtHdr.getYear(); }  
 Int_t getEvtMonth()  { return EvtHdr.getMonth(); }
 Int_t getEvtDay()  { return EvtHdr.getDay(); }  
 Int_t getEvtHour()  { return EvtHdr.getHour(); } 
 Int_t getEvtMinute()  { return EvtHdr.getMinute(); } 
 Int_t getEvtSecond()  { return EvtHdr.getSecond(); }
 //wk! read in README:Int_t getRunNr() { return EvtHdr.getRunNr(); }
 Int_t getEvtPad()  { return EvtHdr.getPad(); }
 Int_t getEvtDataSize() { return EvtHdr.getDataSize();} 
 Int_t getEvtPaddedSize() { return EvtHdr.getPaddedSize(); } 
 Int_t getSubEvtId() { return subEvtId; }
 Int_t getReferenceTime() {return referenceTime; }
 Int_t getReferenceChannel() {return referenceChannel; }
 Int_t getErrors_per_event() {return errors_per_event; }
 TClonesArray* getHits(){return gHits;}
  
 void setErrors_per_event(Int_t e) { errors_per_event=e; }
 /*
 void setSize(Int_t s=0)  { size=s; } 
 void setDecoding(Int_t d=0)  { decoding=d; }
 void setId(Int_t i=0)  { id=i; }
 void setSeqNr(Int_t se=0)  { seqNr=se; }
 void setDate(Int_t d=0)  { date=d; }
 void setTime(Int_t t=0)  { time=t; }
 void setYear(Int_t y=0)  { year=y; }  
 void setMonth(Int_t m=0)  { month=m; }
 void setDay(Int_t d=0)  { day=d; }  
 void setHour(Int_t h=0)  { hour=h; } 
 void setMinute(Int_t m=0)  { minute=m; } 
 void setSecond(Int_t s=0)  { second=s; }
 //wk! read in README: void setRunNr(Int_t r=0)  { runNr=r; }
 void setPad(Int_t p=0)  { pad=p; }
 void setDataSize(Int_t ds=0) { dataSize=ds;} 
 void setPaddedSize(Int_t ps=0) { paddedSize=ps; } 
 */
 void setReferenceChannel(Int_t c) { referenceChannel=c; }
 void setReferenceTime(Int_t t) { referenceTime=t; }
 void setSubEvtId(Int_t sb=0) { subEvtId=sb; }
 
 Hit* addHit(); 
 Bool_t fill(const HldEvent&);
 void clearAll(void);

 public:
 ClassDef(Event,1);
};

#endif /* !EVENT_WK_H */
