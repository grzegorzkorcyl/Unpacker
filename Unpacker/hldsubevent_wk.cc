// File: hldsubevent.cc
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified

#include "hldsubevent_wk.h"
#include <iostream> 
#include <iomanip>
#include <stdlib.h>

//______________________________________________________________________________
//   HldSubEvent
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

ClassImp(HldSubEvent)

	
//______________________________________________________________________________
void HldSubEvent::swapData() {
    if (wasSwapped()) {
	switch (getWordSize()) {
	case 4:
	    swap4((UInt_t*) getData(), getDataLen());
	    break;
	case 2:
	    swap2((UShort_t*) getData(), getDataLen());
	    break;
	case 1:
	    break;
	default:
	    cerr << "Word Size of " << getWordSize()
		 << " not supported" << endl;
	    exit(1);
	}
        resetSwapFlag();   // make sure, subevent is not swapped a second time
    }
} 

//______________________________________________________________________________
Bool_t HldSubEvent::scanIt(void) {
//Checks the subevent for corruption. Returns kTRUE if correct.
  Bool_t r=kTRUE;
  
  if (getId()>699 || getId()<1) {
    r=kFALSE;
    printf("SubEvent corrupted\n");
  }
  return r;
}

//______________________________________________________________________________
void HldSubEvent::dumpIt(FILE* output) const{

  fprintf(output,"===========================================================\n");
  fprintf(output,"SubEvent: Id:%8i Size:%8i Decoding:%8i \n",  
	  getId(),
	  getSize(), 
	  getDecoding()); 
  fprintf(output,"TrigNr:%8i\n", getTrigNr()); 
  fprintf(output,"===========================================================\n");
 
  UInt_t *data;
  data= getData();
  for(UInt_t i=0;i<getDataSize()/sizeof(UInt_t);i++){
    if(i % 4 == 0 ){ // newline with offset 
     fprintf(output,"\n0x%08x:", (char *) data - (char *) getData());
    }
    fprintf(output,"  0x%08x", data[i]);
  }

  fprintf(output,"\n");
  fprintf(output,"\n");
}

//______________________________________________________________________________
void HldSubEvent::swap2(UShort_t* ptr, const size_t len) const {
    for (size_t i = 0; i < len; ++i) {
        UShort_t tmp = ptr[i];
        UChar_t* t = (UChar_t*) &tmp;
        UChar_t* p = (UChar_t*) &ptr[i];
        p[0] = t[1];
        p[1] = t[0];
    }
}

//______________________________________________________________________________
void HldSubEvent::swap4(UInt4* p, const size_t len) const {
  UInt4 tmp;
  UInt1* d;
  UInt1* const s = (UInt1*) &tmp;
  for (size_t i = 0; i < len; i++) {
    d = (UInt1*) (p + i);
    tmp = p[i];
    d[0] = s[3];
    d[1] = s[2];
    d[2] = s[1];
    d[3] = s[0];
  }
}

