// File: eventhdr_wk.cc
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 17.10.06
// Modified:

#include "eventhdr_wk.h"
#include "hldevent_wk.h"

//______________________________________________________________________________
//   EventHdr  
//
//
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

ClassImp(EventHdr)


//______________________________________________________________________________
void EventHdr::clearAll()
//
{	
  size=0;
  decoding=0;
  id=0;
  seqNr=0;
  date=0;
  time=0;
  year=0;
  month=0;
  day=0;
  hour=0;
  minute=0;
  second=0;
 //wk! read in README: runNr=0;
  pad=0;
  dataSize=0;
  paddedSize=0;

}

//______________________________________________________________________________
Bool_t EventHdr::fill(const HldEvent& HldEvt)
//what about some error's check
{

 setSize(HldEvt.getSize());
 setDecoding(HldEvt.getDecoding());
 setId(HldEvt.getId()); 
 setSeqNr(HldEvt.getSeqNr());
 setDate(HldEvt.getDate());
 setTime(HldEvt.getTime());
 setYear(HldEvt.getYear());
 setMonth(HldEvt.getMonth());
 setDay(HldEvt.getDay());
 setHour(HldEvt.getHour());
 setMinute(HldEvt.getMinute());
 setSecond(HldEvt.getSecond());
 //wk! read in README:setRunNr(static_cast<Int_t> (HldEvt.getRunNr())); 
 setPad(HldEvt.getPad());
 setDataSize(HldEvt.getDataSize());
 setPaddedSize(HldEvt.getPaddedSize());
 
 return kTRUE;
}
/*
//______________________________________________________________________________
void EventHdr::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventHdr.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b >> size;
      R__b >> decoding;
      R__b >> id;
      R__b >> seqNr;
      R__b >> date;
      R__b >> time;
      R__b >> year;
      R__b >> month;
      R__b >> day;
      R__b >> hour;
      R__b >> minute;
      R__b >> second;
      R__b >> pad;
      R__b >> dataSize;
      R__b >> paddedSize;
      R__b.CheckByteCount(R__s, R__c, EventHdr::IsA());
   } else {
      R__c = R__b.WriteVersion(EventHdr::IsA(), kTRUE);
      R__b << size;
      R__b << decoding;
      R__b << id;
      R__b << seqNr;
      R__b << date;
      R__b << time;
      R__b << year;
      R__b << month;
      R__b << day;
      R__b << hour;
      R__b << minute;
      R__b << second;
      R__b << pad;
      R__b << dataSize;
      R__b << paddedSize;
      R__b.SetByteCount(R__c, kTRUE);
   }
}
*/
