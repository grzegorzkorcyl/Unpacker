// File: hit_wk.h 
//  
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified:

#ifndef HIT_WK_H
#define HIT_WK_H

/////////////////////////////////////////////////////////////////////
// Hit 
//
// 
// 
// 
// 
/////////////////////////////////////////////////////////////////////

#include <TObject.h>
#include <TBuffer.h>


class Hit:public TObject
{
 public:

 Hit()
 {
    clear();
 }
//wk temporary
 Hit(Int_t ch,Int_t tdc)
 {
	 setChannel(ch);
	 setTDC(tdc);   
 }
 
/* 
 Hit(const Hit& hit)
 {
	 
	
 }
 */
 
 protected:
  
 Int_t channel;	//channel number
 Int_t TDC;		//TDC number from 0-3
 Int_t nHits;    // number of hits
 Int_t time1;    // tdc time of 1st hit
 Int_t width1;   // width of 1st hit
 Int_t time2;    // tdc time of 2nd hit
 Int_t width2;   // width of 2nd hit
 Int_t time3;    // tdc time of 3rd hit
 Int_t width3;   // width of 3rd hit
 Int_t time4;    // tdc time of 4th hit
 Int_t width4;   // width of 4th hit

 public:
 
 void setChannel(Int_t c) {channel=c;}
 void setTDC(Int_t t) {TDC=t;}
 void setNHits(Int_t h) { nHits=h; }
 void setTime1(Int_t t) { time1=t; } 
 void setWidth1(Int_t w){ width1=w; }
 void setTime2(Int_t t) { time2=t; }
 void setWidth2(Int_t w) { width2=w;}
 void setTime3(Int_t t)  { time3=t;}
 void setWidth3(Int_t w) { width3=w; }
 void setTime4(Int_t t)  { time4; }
 void setWidth4(Int_t w) { width4=w; }
  
 Int_t getChannel() { return channel;}
 Int_t getTDC() { return TDC;}
 Int_t getNHits() { return nHits; }
 Int_t getTime1() { return time1; } 
 Int_t getWidth1(){ return width1; }
 Int_t getTime2() { return time2; }
 Int_t getWidth2(){ return width2;}
 Int_t getTime3() { return time3;}
 Int_t getWidth3() { return width3;}
 Int_t getTime4() { return time4;}
 Int_t getWidth4() { return width4;}

  
 //wk from HHodoRaw
 
 Int_t getTime(const Int_t n) const;
 Int_t getWidth(const Int_t n) const;
 void getTimeAndWidth(const Int_t,Int_t&,Int_t&);
 void setModule(Int_t m) {1;} //module=m;
 void setMult(Int_t mu) { 1; } //nHits=mu;
 void setAddress(const Int_t m,const Int_t f) {
 }
 Bool_t fillTimeAndWidth(const Int_t,const Int_t);
 Bool_t fill_lead(const Int_t time);
 Bool_t fill_trail(const Int_t time);
 //wk end from HHodoRaw
 
 void clear(void);

 public:
 ClassDef(Hit,1); //changed from 1  
};

#endif /* !HIT_WK_H */
