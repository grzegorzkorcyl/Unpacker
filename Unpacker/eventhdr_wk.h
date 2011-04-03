// File: eventhdr_wk.h 
//  
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 17.10.06
// Modified:

#ifndef EVENTHDR_WK_H
#define EVENTHDR_WK_H

/////////////////////////////////////////////////////////////////////
// EventHdr 
//
//
/////////////////////////////////////////////////////////////////////

#include <TObject.h>
#include <TBuffer.h>
//wk typedef UInt_t UInt4;
//wk typedef UChar_t UInt1;

class HldEvent;

class EventHdr:public TObject
{
 public:

 EventHdr()
 {
	 clearAll();
 }
 
 
 EventHdr(const HldEvent& HldEvt)
 {
	 clearAll();
	 fill(HldEvt);
 }
 
 protected:
 //information from event header
 Int_t size; //size_t
 Int_t decoding;
 Int_t id;
 Int_t seqNr;
 Int_t date;
 Int_t time;
 Int_t year;
 Int_t month;
 Int_t day;
 Int_t hour;
 Int_t minute;
 Int_t second;
//wk! read in README: Int_t runNr;
 Int_t pad;
 Int_t dataSize; 
 Int_t paddedSize; 

 public:
	 
 Int_t getSize()  { return size; }
 Int_t getDecoding()  { return decoding; }
 Int_t getId()  { return id; }
 Int_t getSeqNr()  { return seqNr; }
 Int_t getDate()  { return date; }
 Int_t getTime()  { return time; }
 Int_t getYear()  { return year; }  
 Int_t getMonth()  { return month; }
 Int_t getDay()  { return day; }  
 Int_t getHour()  { return hour; } 
 Int_t getMinute()  { return minute; } 
 Int_t getSecond()  { return second; }
 //wk! read in README:Int_t getRunNr() { return runNr; }
 Int_t getPad()  { return pad; }
 Int_t getDataSize() { return dataSize;} 
 Int_t getPaddedSize() { return paddedSize; } 

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
 
 Bool_t fill(const HldEvent&);
 void clearAll(void);

 public:
 ClassDef(EventHdr,1);
};

#endif /* !EVENTHDR_WK_H */
