// File: hit_wk.cc
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified: Wojciech Krzemien 17.01.07


#include "hit_wk.h"
#include <iostream>
//______________________________________________________________________________
//   Hit  
//
//
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

ClassImp(Hit)


//______________________________________________________________________________
void Hit::clear()
//
{
 channel=-1;
 TDC=-1;
 
 nHits=0;  
//  time1=0; 
//  width1=0;
//  time2=0; 
//  width2=0;
//  time3=0;
//  width3=0;
//  time4=0;
//  width4=0;
 width_wk=0;
 trailTime1=0;
 leadTime1=0;
 trailTime2=0;
 leadTime2=0;
 trailTime3=0;
 leadTime3=0;
 trailTime4=0;
 leadTime4=0;
}

//wk from HHodoRaw

//______________________________________________________________________________
Int_t Hit::getTime(const Int_t n) const {
   // Returns the time of the nth hit (1<=n<=4)
   switch (n) {
//       case 1: return time1;
//       case 2: return time2;
//       case 3: return time3;
//       case 4: return time4;
      default:
        //wk Error("getTime()","hit number: %i out of range [1,4]",n);
	 return -1;
   }
}

//______________________________________________________________________________
Int_t Hit::getWidth(const Int_t n) const {
  // Returns the width of the nth hit (1<=n<=4)
   switch (n) {
//       case 1: return width1;
//       case 2: return width2;
//       case 3: return width3;
//       case 4: return width4;
      default:
      //    Error("getWidth()","hit number: %i out of range [1,4]",n);
         return -1;
   }
}

//______________________________________________________________________________
void Hit::getTimeAndWidth(const Int_t n, Int_t& time, Int_t& width ) {
   // Returns the time and width of the nth hit (1<=n<=4)
   switch (n) {
//       case 1:
//          time=time1;
//          width=width1;
//          return;
//       case 2:
//          time=time2;
//          width=width2;
//          return;
//       case 3:
//          time=time3;
//          width=width3;
//          return;
//       case 4:
//          time=time4;
//          width=width4;
//          return;
      default:
         //Error("getTime()","hit number: %i out of range [1,4]",n);
	 time=width=-1;
	 return;
   }
}

//______________________________________________________________________________
Bool_t Hit::fillTimeAndWidth(const Int_t time,const Int_t width) {
  
  // Stores the given time and width in the next data element time* and width*
  // and sets the multiplicity.
  // Return kFALSE if 4 hits are already stored.
  
  //cerr<<"bla"<<endl;
//   switch (nHits) {
//      case 0:
// //         time1 = time;
// //         width1 = width;
//         nHits++;
//         break;
//      case 1:
// //         time2 = time;
// //         width2 = width;
//         nHits++;
//         break;
//      case 2:
// //         time3 = time;
// //         width3 = width;
//         nHits++;
//         break;
//      case 3:
// //         time4 = time;
// //         width4 = width;
//         nHits++;
//         break;
//     default:
//        if( nHits>=4) nHits++;// continue counting Hits ...
// 	break;
//        //return kFALSE;
//   }
  return kTRUE;
 
}

//______________________________________________________________________________
Bool_t Hit::fill_lead(const Int_t time) {
  // Stores the given time in the next data element time*
  // and sets the multiplicity.
  // Return kFALSE if 4 hits are already stored. 
  
  cerr<<"Fill_lead"<<endl;
  
  /*switch (nHits) {
    case 0:
//       time1 = time;
      nHits++;
      break;
    case 1:
//       time2 = time;
      nHits++;
      break;
    case 2:
//       time3 = time;
      nHits++;
      break;
    case 3:
//       time4 = time;
      nHits++;
      break;
		default:
			if( nHits>=4) nHits++;// continue counting Hits ...
      break;
      //return kFALSE;
  }*/
  return kTRUE;
}

//______________________________________________________________________________
Bool_t Hit::fill_trail(const Int_t time) {
  // Calculates the time between trailing and LAST(!) leading hit.
  // No other check if its really the right one,
	// i am depending on the TDC to deliver the right order
  // Return kFALSE if no leading yet or more than 4 Hits 
  switch (nHits) {
    case 0:
			// no Leading
      return kFALSE;
//     case 1:
//       width1 = time-time1;
//       break;
//     case 2:
//       width2 = time-time2;
//       break;
//     case 3:
//       width3 = time-time3;
//       break;
//     case 4:
//       width4 = time-time4;
//       break;
		default:
      return kFALSE;
  }
  return kTRUE;
}

//wk end from HHodoRaw

//______________________________________________________________________________
Bool_t Hit::setTDC(Int_t t)
{
    TDC = t / 32;
	  
//     if((t>=0) &&(t<=31))
// 	TDC=0;		      	
//     else if((t>=32) && (t<=63))
//       	TDC=1;
//     else if ((t>=64) && (t<=95))
//         TDC=2;
//     else if((t>=96) && (t<=127))
//         TDC=3;
//     else
//         return kFALSE;
    
  return kTRUE;
  }

