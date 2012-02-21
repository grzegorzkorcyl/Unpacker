// File: hldevent_wk.cc
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified:
// 

#include "hldevent_wk.h"
#include "TError.h"
#include <iostream>
#include <iomanip> 
#include <unistd.h>

//______________________________________________________________________________
//   HldEvent
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

ClassImp(HldEvent)

// const Int_t kMaxSubEvtId = 999; not used anymore

//______________________________________________________________________________
Bool_t HldEvent::setFile(const Text_t *name)
    {
    if (access(name, F_OK) != 0)
	{
	Error("HldEvent::setFile()", "Error during access of file %s !", name);
	exit(EXIT_FAILURE);
	}

    stat(name, &status);
    if (file)
	{
	((ifstream*) file)->open(name);
	if (!((ifstream*) file)->is_open())
	    {
	    Error("HldEvent::setFile()", "Error during opening file %s !", name);
	    exit(EXIT_FAILURE);
	    }
	if (!((ifstream*) file)->good())
	    {
	    Error("HldEvent::setFile()",
		    "Error flags discovered in stream of file %s !", name);
	    exit(EXIT_FAILURE);
	    }

	}
    else
	{
	file = new std::ifstream(name);
	if (!((ifstream*) file)->is_open())
	    {
	    Error("HldEvent::setFile()", "Error during opening file %s !", name);
	    exit(EXIT_FAILURE);
	    }
	if (!((ifstream*) file)->good())
	    {
	    Error("HldEvent::setFile()",
		    "Error flags discovered in stream of file %s !", name);
	    exit(EXIT_FAILURE);
	    }
	}
    return kTRUE;
    }

//______________________________________________________________________________
Bool_t HldEvent::read()
    {
    if (file)
	{
	if (file->eof())
	    {
	    return kFALSE;
	    }
	if (!((ifstream*) file)->good())
	    {
	    Error("HldEvent::read()",
		    "Error flags discovered in input stream before read!");
	    exit(1);
	    }

	if (pData)
	    {
	    delete[] pData;
	    pData = 0;
	    }
	if (file->read((char *) (pHdr), getHdrSize()))
	    {
	    if (isSwapped())
		swapHdr();
	    if (getSize() > getHdrSize())
		{

#warning "Hardcoded maximum event size is 1000000"
		if (getDataLen() > 1000000)
		    return kFALSE;
		/*wk: co z tym dalej
		 size_t filesize    =(size_t)status.st_size;
		 size_t expectedsize=((size_t)((ifstream*)file)->tellg())+getPaddedSize();
		 if(expectedsize>filesize)
		 {
		 Error("HldEvent::read()",
		 "Could not read enough bytes from file! \n File pointer + padded Size = %i bytes, file size = %i bytes !",
		 expectedsize , filesize);
		 return kFALSE;
		 }
		 */
		pData = new UInt4[getDataLen()];
		if (file->read((char*) (pData), getDataSize()))
		    file->ignore(getPaddedSize() - getSize());
		}
	    }

	if (!((ifstream*) file)->good())
	    {
	    if (!file->eof())
		{
		Error("HldEvent::read()",
			"Error flags discovered in input stream after read!");
		}
	    return kFALSE;
	    }
	else
	    {
	    return kTRUE;
	    }

	}
    return kFALSE;
    }

//______________________________________________________________________________
Bool_t HldEvent::readSubEvt(size_t i)
    {
    UInt4* p;
    if (i)
	p = subEvt[i - 1].getPaddedEnd();
    else
	p = pData;
    if (p < getPaddedEnd())
	subEvt[i] = HldSubEvent(p);
    else
	return kFALSE;
    return kTRUE;
    }

//______________________________________________________________________________
Bool_t HldEvent::execute()
    {
    if (read())
	{
	//czyszczenie
	for (size_t idx = 0; idx < lastSubEvtIdx; idx++)
	    *subEvtTable[idx].p = 0;

	for (size_t i = 0; i < maxSubEvts && readSubEvt(i); i++)
	    { // loop subevts
	    Bool_t unpacked = kFALSE;

	    for (size_t idx = 0; idx < lastSubEvtIdx; idx++)
		{ // loop unpackers
		// gk 09.12.11
		//if (subEvt[i].getId() == subEvtTable[idx].id)
		if (kTRUE) 
		    {
		    subEvt[i].swapData();
		    *subEvtTable[idx].p = subEvt + i;
		    //        cout << "pass a pointer to subevt to its unpacker" << endl;
		    unpacked = kTRUE;
		    }
		}
	    if (isWritable && !unpacked)
		{
		// to assure that the swapData() can work
		if (((subEvt[i].getWordSize()) == 1)
			|| ((subEvt[i].getWordSize()) == 2)
			|| ((subEvt[i].getWordSize()) == 4))
		    {
		    subEvt[i].swapData();
		    }
		else
		    Warning("execute", "Corrupted SubEvent, SubId %x",
			    subEvt[i].getId());
		}

	    } //end loop subevts

	//wk added
	if (pSubEvt)
	    {
	    decode();
	    }
	//end wk added
	return kTRUE;
	}
    else
	return kFALSE;

    }

//______________________________________________________________________________
Bool_t HldEvent::swap()
    {
    //only swapping correctly the header
    if (read())
	{
	return kTRUE;
	}
    else
	{
	return kFALSE;
	}
    }

//from HldBase
//______________________________________________________________________________
void HldEvent::swap2(UShort_t* ptr, const size_t len) const
    {
    for (size_t i = 0; i < len; ++i)
	{
	UShort_t tmp = ptr[i];
	UChar_t* t = (UChar_t*) &tmp;
	UChar_t* p = (UChar_t*) &ptr[i];
	p[0] = t[1];
	p[1] = t[0];
	}
    }

//______________________________________________________________________________
void HldEvent::swap4(UInt4* p, const size_t len) const
    {
    UInt4 tmp;
    UInt1* d;
    UInt1* const s = (UInt1*) &tmp;
    for (size_t i = 0; i < len; i++)
	{
	d = (UInt1*) (p + i);
	tmp = p[i];
	d[0] = s[3];
	d[1] = s[2];
	d[2] = s[1];
	d[3] = s[0];
	}
    }

//end HldBase

//from HldEvt
//______________________________________________________________________________
Int_t HldEvent::appendSubEvtIdx()
    {
    subEvtTable[lastSubEvtIdx].id = getSubEvtId();
    subEvtTable[lastSubEvtIdx].p = getpSubEvt();
    if (lastSubEvtIdx == maxSubEvtIdx - 1)
	{
	printf("\nMax. nb of unpackers (%d) exceeded!\n\n", maxSubEvtIdx);
	return 0;
	}
    else
	return ++lastSubEvtIdx;
    }

//end HldEvt


//wk from testunpacker --unpacker classes

//______________________________________________________________________________
void HldEvent::clearAll(void)
    {
    for (Int_t i = 0; i < fpgasNum * 128; i++)
	{
	for (Int_t k = 0; k < kMaxMult; k++)
	    {
	    LeadingTime[i][k] = -1000000;
	    WidthTime[i][k] = -1000000;
	    TrailingTime[i][k] = -1000000;
	    trbADC[i][k] = -1;
	    }
	LeadingMult[i] = 0;
	WidthMult[i] = 0;
	TrailingMult[i] = 0;
	SpikesCtr[i] = 0;
	}
    errors_per_event = 0;
    }

//______________________________________________________________________________
Bool_t HldEvent::fill_lead(Int_t ch, Int_t time)
    {
      
    Int_t leadMult = LeadingMult[ch];
    Int_t trailMult = TrailingMult[ch];
    
    if(leadMult - trailMult == 0) {
      LeadingMult[ch]++;
      if (leadMult < kMaxMult)  {
	      LeadingTime[ch][leadMult] = time;
	  }
      return ((leadMult + 1) <= kMaxMult);

    }
    else {
      LeadingTime[ch][leadMult - 1] = time;
      SpikesCtr[ch]++;
    }
    
    }

//______________________________________________________________________________
Bool_t HldEvent::fill_width(Int_t ch, Int_t time)
    {

    //hk added
    Int_t widMult = WidthMult[ch]; //width Multiplicity
    Int_t leadMult = LeadingMult[ch]; //Leading Multiplicity

    WidthMult[ch]++;

    if (widMult < kMaxMult)
	{
	if (widMult <= leadMult + 1)
	    {
	    WidthTime[ch][widMult] = time;
	    }
	else
	    {
	    return kFALSE;
	    }
	}

    return ((widMult + 1) <= kMaxMult);
    }

//______________________________________________________________________________
Bool_t HldEvent::fill_trail(Int_t ch, Int_t time)
    {

    Int_t trailMult = TrailingMult[ch]; //Trailing Multiplicity
    Int_t leadMult = LeadingMult[ch]; //Leading Multiplicity

    if (trailMult < kMaxMult)
	{
	if (leadMult - trailMult == 1)
	    {
	      TrailingMult[ch]++;
	      TrailingTime[ch][trailMult] = time;
	    }
	else
	    {
	      SpikesCtr[ch]++;
	      
	    return kFALSE;
	    }
	}

    return ((trailMult + 1) <= kMaxMult);
    
    }

//______________________________________________________________________________
void HldEvent::PrintTdcError(UInt_t e)
    {
    Char_t *e_str[15] =
	{
		"Hit lost in group 0 from read-out FIFO overflow",
		"Hit lost in group 0 from L1 buffer overflow",
		"Hit error have been detected in group 0",
		"Hit lost in group 1 from read-out FIFO overflow",
		"Hit lost in group 1 from L1 buffer overflow",
		"Hit error have been detected in group 1",
		"Hit lost in group 2 from read-out FIFO overflow",
		"Hit lost in group 2 from L1 buffer overflow",
		"Hit error have been detected in group 2",
		"Hit lost in group 3 from read-out FIFO overflow",
		"Hit lost in group 3 from L1 buffer overflow",
		"Hit error have been detected in group 3",
		"Hits rejected because of programmed event size limit",
		"Event lost (trigger FIFO overflow)",
		"Internal fatal chip error has been detected"
	};

    if (e == 0)
	return;// No Error

    cout << "=== TRB/TDC Error analysis:" << endl;
    for (Int_t i = 0; i < 15; i++)
	{
	if (e & 0x1)
	    {
	    cout << e_str[i] << endl;
	    }
	e >>= 1;
	}
    cout << "===" << endl;
    }

//______________________________________________________________________________
Int_t HldEvent::decode(void)
{
  clearAll();

  Int_t TdcId;
  Int_t nCountTDC = 0;
  UInt_t nEvtNr;

  UInt_t nSizeCounter = 0;
  UInt_t nTdcEvtId = 0;
  UInt_t TdcDataLen = 0;
  UInt_t uBlockSize = 0;
  
  UInt_t subeventFound = false;

  //wk getData z hldbase.h
  UInt_t* data = pSubEvt->getData();
  UInt_t* end = pSubEvt->getEnd();

  Int_t currentFpga = -1;

  // gk 02.12.10
  // skip the first 32b. word which is hub header
  //data++;

  if((*data & 0xFFFF0000) == 0xBE010000)
  {
    return (kFALSE);
  }

  uBlockSize = *data & 0xFF;
  nEvtNr = (*data >> 8) & 0xFF;

  nSizeCounter++;// First one already processed
  
  
  bool foundLeadingEdge = false;

  bool printDebug = false;
  
  while (data < end)
  {
    UInt_t dataword;
    dataword = *data;//[ii];
    nSizeCounter++;
    UInt_t* endOfSubevent;
    

    
    if (fullSetup == true) {
      // gk 09.12.11
      //gk find if the subevent is the one from endpoints list, skip others
      if (subeventFound == false) {
	      currentFpga = -1;
	      // loop over registered endpoint addresses
	      for(int i = 0; i < fpgasNum; i++) {
		//cerr<<"FPGA: "<<i<<" "<<fpgasAddr[i]<<endl;
		      // found a matching one
		      if (((*data) & 0xffff) == fpgasAddr[i]) {
			      endOfSubevent = data + (((*data) & 0xffff0000) >> 16) + 1;
			      data++;
			      subeventFound = true;
			      currentFpga = i;
			      
			      if(!quietMode) printf("Subevent found on fpga %d\n", currentFpga);
			      
			      break;
		      }
	      }

	      // if none matches, skip to the next subevent
	      if (currentFpga == -1) {
		      data += (((*data) & 0xffff0000) >> 16) + 1;
	      }
	      continue;
      }
	
    }
    // in case of single trb setup
    else {
      
      
    // gk 20.12.10
    // fpgaAddr is a number used to select the source of data (given fpga) - set in constructor
    //65535
    
      if((((*data) & 0xffff) != fpgaAddr) && (subeventFound == false)) {
	data += ((*data) & 0xffff0000) >> 16;
	data++;
	continue;
      }
      else if((((*data) & 0xffff) == 65535) && (subeventFound == false)) {
	end = data + (((*data) & 0xffff0000) >> 16) + 1;
	subeventFound = true;
	data++;
	continue;
      }   
	  
	  subeventFound = true;
	  currentFpga = 0;
    }

    // process data in case subevent is found
    if (subeventFound == true) {

    if(dataword == 0xDEADFACE)
    {
      break;
    }

    TdcId = (dataword >> 24) & 0xF;// might be wrong for TRB board
    TdcId = nCountTDC;

    if (TdcDataLen > 0)
      TdcDataLen++;
    switch (dataword >> 28)
    {// Raw TDC Data
      case 0:
      {// Group Header
      // gk reset tdc  counter for each TRB board
nCountTDC = 0;
      }
      case 2:
      {// TDC Header
      

	if(!quietMode)
	  printf("TRB unpack: Found TDC %d Header $%04X $%04X\n",TdcId,(dataword>>12)&0xFFF,dataword&0xFFF);

	if (nCountTDC > 0 && nTdcEvtId != ((dataword >> 12) & 0xFFF))
	{
	//wk    if(!quietMode)Error("TRB unpack","TDCs have different EventIds ******* Event Mixing *******");
	  if (!quietMode)
	    printf("nTdcEvtId: %06X   dataword:  %06X  nEvtNr: %02X\n",
	  nTdcEvtId, ((dataword >> 12) & 0xFFF), nEvtNr);
	//               exit();
	//               return(kFALSE);
	}
	if (nEvtNr != ((dataword >> 12) & 0xFF))
	{
      //wk    if(!quietMode)Error("TRB unpack","TDC EventIds != Main EventId ******* Event Mixing *******");
	if (!quietMode)
	  printf("nTdcEvtId: %06X   dataword:  %06X  nEvtNr: %02X\n",
	nTdcEvtId, ((dataword >> 12) & 0xFFF), nEvtNr);
	//               exit();
	//               return(kFALSE);
	}
	if(!quietMode)
	  printf("nTdcEvtId: %06X   dataword:  %06X  nEvtNr: %02X\n" , nTdcEvtId ,((dataword>>12)&0xFFF),nEvtNr);
	nTdcEvtId = (dataword >> 12) & 0xFFF;

	TdcDataLen = 1;
	break;
      }
      case 3:
      {// TDC Trailer
	
	if(!quietMode)
	  printf("TRB unpack: Found TDC %d Trailer $%04X $%04X\n",TdcId,(dataword>>12)&0xFFF,dataword&0xFFF);
	
	if (TdcDataLen != (dataword & 0xFFF))
	{
	  if (!quietMode)
	    printf("TRB unpack: TdcDataLen %d != %d ", TdcDataLen, dataword & 0xFFF);
	}
	TdcDataLen = 0;
	nCountTDC++;
	break;
      }
      
      case 4:
      {// TDC DATA Leading and width

	if(!quietMode)
	      printf("TRB unpack: Found TDC %d Lead Data $%08X\n",TdcId,dataword);
	
	// gk 13.02.12 added support for VHR mode
	if(VHR == false) {
	  Int_t nData, nChannel, nWidth;
	  nChannel = (dataword >> 19) & 0x1f; // decode channel
	  
	  nChannel += (TdcId * 32) + (currentFpga * 128);
	  nData = dataword & 0x7ffff; // decode 19bit data
	  
	  if(!quietMode)
	    printf("(Chan,Data) %3d, %d\n",nChannel,nData);
	  
	  // gk in case the search window is defined
	  if (nData >= minWindow && nData <= maxWindow && minWindow != -100000) {
	    fill_lead(nChannel, nData);
	    //foundLeadingEdge = true;
	  }
	  // operate without search window
	  else if(minWindow == -100000) {
	    fill_lead(nChannel, nData);
	    //foundLeadingEdge = true;
	  }
	}
	else {  // VHR decoding
	  Int_t nData, nChannel, nTDC;
	  nChannel  = (dataword >> 21) & 0x7;
	  nTDC      = (dataword >> 24) & 0xf;
	  nChannel += (nTDC * 32) + (currentFpga * 128);
	  nData     = ((dataword & 0x7ffff) << 2) | ((dataword >> 19) & 0x3);
	  
	  if (!quietMode)
	    printf("VHR(Chan,Data) %3d, %d\n",nChannel,nData);
	    
	  fill_lead(nChannel, nData);
	  //foundLeadingEdge = true;
	}
	//}
	break;
      }
      case 5:
      {// TDC DATA Trailing
      
        if(!quietMode)
	    printf("TRB unpack: Found TDC %d Trail Data $%08X\n",TdcId,dataword);   if(!quietMode) printf("FPGA code: %s amount: %d\n", fpgaAddr, fpgasNum);
	
	// gk 13.02.12 added support for VHR mode
	if (VHR == false) {
	  Int_t nData, nChannel;
	  nChannel = (dataword >> 19) & 0x1f; // decode channel

	  //shift by tdc number and endpoint number
	  nChannel += (TdcId * 32) + (currentFpga * 128);
	  
	  nData = dataword & 0x7ffff; // decode 19bit data
	  
	  if(!quietMode)
	    printf("(Chan,Data) %3d, %d\n",nChannel,nData);
	  
	  // this is for SINGLE LEADING/TRAILING EDGE measurements only!!!
	  //if (foundLeadingEdge == true) {
	    fill_trail(nChannel, nData);
	  //  foundLeadingEdge = false;
	  //} else {
	  // if(!quietMode) printf("!!!Rejecting that trail edge \n");
	  //}
	}
	else {
	  Int_t nData, nChannel, nTDC;
	  nChannel  = (dataword >> 21) & 0x7;
	  nTDC      = (dataword >> 24) & 0xf;
	  nChannel += (nTDC * 32) + (currentFpga * 128);
	  nData     = ((dataword & 0x7ffff) << 2) | ((dataword >> 19) & 0x3);
	  
	  if (!quietMode)
	    printf("VHR(Chan,Data) %3d, %d\n",nChannel,nData);
	    
	  fill_trail(nChannel, nData);
	  //foundLeadingEdge = false;
	}
	break;
      }
      case 6:
      {// TDC ERROR
      
      
	printDebug = true;
      
	incErrorNr();
	if ((dataword & 0x7FFF) == 0x1000)
	{// special case for non fatal errors
	//wk     if(!quietMode)Info("TRB unpack","TDC Event Size Limit exceeded!\n");
	if (!quietMode)
	  printf("(TDC %d Error Event Size Limit: $%08X)\n", TdcId, dataword);
	}
	else
	{
	  //wk     if(!quietMode)Info("TRB unpack","Found TDC Error(s)!\n");
	  if (!quietMode)
	    printf("TDC %d Error $%04X ($%08X)\n", TdcId, dataword & 0x7FFF, dataword);
	  if (!quietMode)
	    PrintTdcError(dataword & 0x7FFF);
	}
	break;
      }
      case 7:
      {// Debug Info
      //wk      if(!quietMode)Error("TRB unpack","Found DEBUG Info");
	if (!quietMode)
	  printf("TRB unpack: TDC %d: Found Debug Info $%08X", TdcId, dataword);
	break;
      }
      default:
      {// not defined!
	//wk       if(!quietMode)Error("TRB unpack","Found UNDEFINED data");
	if (!quietMode)
	  printf("TRB unpack: TDC %d: Found undefined $%08X", TdcId, dataword);
	break;
      }
  }

	}  //  end of if(subeventFound == true)


  ++data;

  	// reset flag when the end of subevent is reached
	if (data == endOfSubevent) {
		subeventFound = false;
	}

  }
  
  if(!quietMode)printf("==== Unpacker end (%d)\n",subEvtId);
  
  
  //if (LeadingMult[31] == 0 || LeadingMult[63] == 0 || LeadingMult[95] == 0 || LeadingMult[127] == 0) {
  if(LeadingMult[31] != TrailingMult[31] || LeadingMult[63] != TrailingMult[63] || LeadingMult[95] != TrailingMult[95]) {
      if(!quietMode) printf("%d, %d, %d, %d, %d, %d \n", LeadingMult[31], TrailingMult[31], LeadingMult[63], TrailingMult[63], LeadingMult[95],  TrailingMult[95]);
      printDebug = true;
  }
  
  
  if(!quietMode && printDebug == true) {
    data = pSubEvt->getData();
    UInt_t *start = data;
    while (data < end)
    {
      UInt_t dataword;
      dataword = *data;
      
      printf("%08x\t", dataword);
      
      if (((data - start) % 4 == 3) && (data != start)) printf("\n");
      
      data++;
    }
    
    printf("\n============================ END OF EVENT ======================================\n\n");
  }
  
  return (kTRUE);
}

//wk from HldUnpack
//______________________________________________________________________________
HldEvent::HPP const HldEvent::getpSubEvt(void)
    {
    //Return a pointer to the subevent read by this unpacker
    return &pSubEvt;
    }

/*wk void TestHldEvent::setCategory(HCategory *aCat) {
 //Sets the category where the unpacked data go to.
 pRawCat=aCat;
 }
 */
//end from HldUnpack


//end from testunpacker

//wk added 04.02.07
Int_t HldEvent::getLeadingTime(Int_t channel, Int_t mult) const
//______________________________________________________________________________
    {
    if ((channel < kMaxChannelNr) && (mult < kMaxMult)) {
	return LeadingTime[channel][mult];
	
    }
    return -1; //channel or multiplicity out of range
    }

Int_t HldEvent::getWidthTime(Int_t channel, Int_t mult) const
//______________________________________________________________________________
    {

    if ((channel < kMaxChannelNr) && (mult < kMaxMult))
	return WidthTime[channel][mult];
    return -1; //channel or multiplicity out of range
    }

Int_t HldEvent::getTrailingTime(Int_t channel, Int_t mult) const
//______________________________________________________________________________
    {

    if ((channel < kMaxChannelNr) && (mult < kMaxMult))
	return TrailingTime[channel][mult];
    return -1; //channel or multiplicity out of range
    }

Int_t HldEvent::getLeadingMult(Int_t channel) const
//______________________________________________________________________________
    {

    if (channel < kMaxChannelNr)
	return LeadingMult[channel];
    return -1; //channel out of range
    }

Int_t HldEvent::getTrailingMult(Int_t channel) const
//______________________________________________________________________________
    {

    if (channel < kMaxChannelNr)
	return TrailingMult[channel];
    return -1; //channel out of range
    }
    
Int_t HldEvent::getSpikesCtr(Int_t channel) const
//______________________________________________________________________________
    {

    if (channel < kMaxChannelNr)
	return SpikesCtr[channel];
    return -1; //channel out of range
    }
//end

