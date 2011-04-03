// File: hldsubevent_wk.h
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified:

#ifndef HLDSUBEVENT_WK_H
#define HLDSUBEVENT_WK_H

/////////////////////////////////////////////////////////////////////
//HldSubEvent
//
// Class based on HldSubEvt and HldBase from Hydra
/////////////////////////////////////////////////////////////////////

#include <TObject.h>
#include <stdio.h>

typedef UInt_t UInt4;
typedef UChar_t UInt1;

class HldSubEvent :public TObject
{
public:
  HldSubEvent(): pData(0),swapped(0) { pHdr = 0; }
  HldSubEvent(UInt4* p) {
    pHdr = p; pData = pHdr + getHdrLen();
       if ((swapped = isSwapped()) !=0){
            swapHdr();
        }
  }
  
  size_t getWordSize() const { return 1 <<  (((SubEvtHdr*)pHdr)->decoding >> 16 & 0xf); }
  int getTrigNr() const { return (((SubEvtHdr*)pHdr)->trigNr)& 0xff; }
  int getUnMaskedTrigNr() const { return ((SubEvtHdr*)pHdr)->trigNr; }
  size_t getDataLen() const { return getDataSize()/getWordSize(); }
  void swapData();
  void dumpIt(FILE *output=stderr) const;
  Bool_t scanIt(void);
  size_t getSize() const { return ((SubEvtHdr*)pHdr)->size; }
  UInt4 getId() const { return ((SubEvtHdr*)pHdr)->id & 0x7fffffff; }
  UInt4 getDecoding() const { return ((SubEvtHdr*)pHdr)->decoding; }
  UInt_t getErrorBit(void) {return ((((SubEvtHdr*)pHdr)->id) >> 31) & 0x1;};
  UInt4* getHeader() const { return pHdr; }
  UInt4* getData() const { return pData; }
  size_t getDataSize() const { return getSize() - getHdrSize(); }
  size_t getPaddedSize() const { return align8(getSize()); }
  UInt4* getEnd() const { return pData + getDataSize()/4; }
  UInt4* getPaddedEnd() const { return pData + getDataPaddedSize()/4; }

private:
  
  struct SubEvtHdr {
    UInt4 size;
    UInt4 decoding;
    UInt4 id;
    UInt4 trigNr;
  };
  
  UInt4* pHdr;
  UInt4* pData;
  Bool_t swapped;
  Bool_t wasSwapped() const { return swapped; }
  void resetSwapFlag() {swapped=0;}
  size_t getHdrLen() const { return getHdrSize()/4; }
  size_t getDataPaddedSize() const { return align8(getDataSize()); }
  Bool_t isSwapped() const { return byte(1, getDecoding()); }
  void swapHdr() { swap4(pHdr, getHdrLen()); }
  int byte(int b, UInt4 i) const { return (i >> 32 - 8*b & 0xff); }
  size_t align8(const size_t i) const { return 8*size_t( (i - 1)/8 + 1 ); }
  void swap4(UInt_t* p, const size_t len) const;
  void swap2(UShort_t* p, const size_t len) const;
  size_t getHdrSize() const { return sizeof(SubEvtHdr); }

public:
  ClassDef(HldSubEvent,0)
};

#endif /* !HLDSUBEVENT_WK_H */      





