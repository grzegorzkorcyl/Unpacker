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

const Int_t kMaxSubEvtId = 999;

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
	for (size_t idx = 0; idx < lastSubEvtIdx; idx++)
	    *subEvtTable[idx].p = 0;
	for (size_t i = 0; i < maxSubEvts && readSubEvt(i); i++)
	    { // loop subevts
	    Bool_t unpacked = kFALSE;
	    for (size_t idx = 0; idx < lastSubEvtIdx; idx++)
		{ // loop unpackers
		if (subEvt[i].getId() == subEvtTable[idx].id)
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
    for (Int_t i = 0; i < 128; i++)
	{
	for (Int_t k = 0; k < kMaxMult; k++)
	    {
	    LeadingTime[i][k] = -1000000;
	    TrailingTime[i][k] = -1000000;
	    trbADC[i][k] = -1;
	    }
	LeadingMult[i] = 0;
	TrailingMult[i] = 0;
	}
    errors_per_event = 0;
    }

//______________________________________________________________________________
Bool_t HldEvent::fill_lead(Int_t ch, Int_t time)
    {

    //wk added 02.02.07
    Int_t trailMult = TrailingMult[ch]; //Trailing Multiplicity
    Int_t leadMult = LeadingMult[ch]; //Leading Multiplicity


    LeadingMult[ch]++;

    if (leadMult < kMaxMult)
	{
	if (leadMult <= trailMult + 1)
	    {
	    LeadingTime[ch][leadMult] = time;
	    }
	else
	    {
	    return kFALSE;
	    }
	}
    return ((leadMult + 1) <= kMaxMult);

    ///////////////////////////////////////////
    // Stores the given time in the next data element
    // and sets the multiplicity.
    // Return false if kMaxMult hits are already stored.
    ///////////////////////////////////////////

    /*
     if( trbLeadingMult[ch]<kMaxMult){
     trbLeadingTime[ch][trbLeadingMult[ch]]=time;
     }
     //wk added
     cout<< "zwiekszamy multiplicity dla kanalu: "<<ch<<endl;
     trbLeadingMult[ch]++;
     cout<< "multiplicity wynosi: "<<trbLeadingMult[ch]<<endl;
     return(trbLeadingMult[ch]<=kMaxMult);
     */

    }

//______________________________________________________________________________
Bool_t HldEvent::fill_trail(Int_t ch, Int_t time)
    {

    //wk added 02.02.07
    Int_t trailMult = TrailingMult[ch]; //Trailing Multiplicity
    Int_t leadMult = LeadingMult[ch]; //Leading Multiplicity

    TrailingMult[ch]++;

    if (trailMult < kMaxMult)
	{
	if (trailMult <= leadMult + 1)
	    {
	    TrailingTime[ch][trailMult] = time;
	    //ADC cannot be set here
	    }
	else
	    {
	    return kFALSE;
	    }
	}

    return ((trailMult + 1) <= kMaxMult);

    ///////////////////////////////////////////
    // Calculates the time between trailing and LAST(!) leading hit.
    // No other check if its really the right one,
    // i am depending on the TDC to deliver the right order
    // Return kFALSE if no leading yet or more than kMaxMult Hits
    ///////////////////////////////////////////
    /*
     Int_t m;// Leading Multiplicity
     m=trbLeadingMult[ch];
     //wk added
     cout<< "multiplicity dla kanalu: "<<ch<<"wynosi "<<trbLeadingMult[ch]<<endl;
     if(m==0) {//wk added
     cout<<" jestem w fill_trail leading multiplicity =0"<<endl;
     return kFALSE;
     }

     if( m<=kMaxMult){
     if( trbTrailingMult[ch]!=m){
     trbTrailingTime[ch][m-1]=time;
     trbADC[ch][m-1] = time - trbLeadingTime[ch][m-1];
     }else{ //wk added
     cout <<"Mamy juz to zbocze opadajace ??"<<endl;
     return kFALSE;// In this case we already have one trailing
     }
     }
     trbTrailingMult[ch]=m;

     return(trbTrailingMult[ch]<=kMaxMult);
     */

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
    /*   UInt_t nEvt        = 0;   //Evt SeqNumber
     Int_t nEvId       = 0;    //Evt Id */

    Int_t TdcId;
    Int_t nCountTDC = 0;
    //   Int_t nCountTDCHeader = 0;
    //   Int_t nCountTDCTrailer = 0;

    UInt_t nEvtNr;

    UInt_t nSizeCounter = 0;
    UInt_t nTdcEvtId = 0;
    //   Int_t nTdcBunchId = -1;
    UInt_t TdcDataLen = 0;

    UInt_t uBlockSize = 0;

    //wk getData z hldbase.h
    UInt_t* data = pSubEvt->getData();
    UInt_t* end = pSubEvt->getEnd();
    //cout << "data: " << *data << " ,end: " << *end<<" ,getDataSize: "<< endl;

    //wk tutaj jest sedno
    /*wk  nEvt = gHades->getCurrentEvent()->getHeader()->getEventSeqNumber();

     //////////////////////////////////////////////////////////
     //   debugFlag1 is used only                            //
     // for special cases                                    //
     // if set to 1:                                         //
     // actual EVENT ID is overwritten                       //
     // by value 1, that means event will be treated as      //
     // normal data                                          //
     //////////////////////////////////////////////////////////
     if(debugFlag1 > 0){
     gHades->getCurrentEvent()->getHeader()->setId(1);
     }
     nEvId = gHades->getCurrentEvent()->getHeader()->getId();

     if((debugFlag > 0 )&& (!quietMode)){
     cout<<endl;
     cout<<"--TRB SubEvent: EvtNb= "<<nEvt<<" --- Evnt Id= "<<nEvId<<endl;
     cout<<"--debugFlag = "<<debugFlag<<endl;
     cout<<"--debugFlag1 = "<<debugFlag1<<endl;
     cout<<"--quietMode = "<<quietMode<<endl;
     if(quietMode==0) cout<<"--quietMode0 = "<<quietMode<<endl;
     if(quietMode>0) cout<<"--quietMode1 = "<<quietMode<<endl;
     //Loop over all data in this subevt

     cout<<hex<<"data word: "<<*data<<dec<<endl;
     cout<<hex<<"data word: ---SUBEVENT HEADER: "<<*data<<dec<<endl;
     }
     */
    // first word in subevent contains info about subevent size 0xbeef_6a_20 (magic,EvtId,length)
    // should be used for checking the subevent.

#if DEBUG_LEVEL>4
    if(!quietMode)printf("=== Unpacker start SubEvtId: %d\n===Header: %X  Nr:%d  Len:%d\n",subEvtId,*data>>16,nEvtNr,uBlockSize);
#endif

    if ((*data & 0xFFFF0000) == 0xBE010000)
	{
	//wk   if(!quietMode)Error("TRB unpack","TRB Buffer overflow, Data truncated. No lethal error, but please report if error is persistend!!!");
	return (kFALSE);
	}
    // BEEF has been replaced ny BE00 before the Beamtime, I only need it for
    // analysis of test files ... remove after Beamtime
    if ((*data & 0xFFFF0000) != 0xBEEF0000 && (*data & 0xFFFF0000)
	    != 0xBE000000)
	{
	//wk  if(!quietMode)Error("TRB unpack","NO $BEEF FOUND!!!");
	//      exit();
	}
    uBlockSize = *data & 0xFF;
    nEvtNr = (*data >> 8) & 0xFF;

    if (nEvtNr != (UInt_t) pSubEvt->getTrigNr())
	{
	/*wk       if(!quietMode){
	 Error("TRB unpack","TRB EvtNr!=pSubEvt->getTrigNr() ********* Event Mixing *********");
	 printf("=== %d != %d \n",nEvtNr,(UInt_t)pSubEvt->getTrigNr());
	 }
	 */
	return (kFALSE);
	}

    //   if(uBlockSize<10){
#warning "Change value to 10 if all TRBs have 4 TDCs after beamtime may06"
    if (uBlockSize < 8)
	{
	if (!quietMode)
	    printf(
		    "Error in TRB unpack: Suspicious length (too small for header/trailer of tdcs) %d , might be a overflow!\n",
		    uBlockSize);
	}

    nSizeCounter++;// First one already processed
    /*
     while ( ++data<end && *data!=0x0 )
     {
     UInt_t dataword;
     dataword=*data;//[ii];
     cout<<"jestwhile ";
     nSizeCounter++;
     if(dataword==0xDEADFACE){
     #if DEBUG_LEVEL>4
     if(!quietMode)printf("TRB unpack: Found DEADFACE -> break %08X %08X\n",data,end);
     #endif
     break;
     }
     */
    while (*data != 0x0 && ++data < end)
	{
	++data; // omijanmoie 2. headera
	UInt_t dataword;
	dataword = *data;//[ii];
	nSizeCounter++;

	if (dataword == 0xDEADFACE)
	    {
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("TRB unpack: Found DEADFACE -> break %08X %08X\n",data,end);
#endif
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
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("TRB unpack: Found GLOBAL Header $%08X\n",dataword);
#endif
	    /*wk
	     if(!quietMode)Info("TRB unpack","Global Header not expected!");
	     break;
	     }
	     case 1:{// Group Trailer
	     #if DEBUG_LEVEL>4
	     if(!quietMode)printf("TRB unpack: Found GLOBAL Trailer $%08X\n",dataword);
	     #endif

	     if(!quietMode)Info("TRB unpack","Global Trailer not expected!");
	     break;
	     */
	    }
	case 2:
	    {// TDC Header
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("TRB unpack: Found TDC %d Header $%04X $%04X\n",TdcId,(dataword>>12)&0xFFF,dataword&0xFFF);
#endif

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
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("nTdcEvtId: %06X   dataword:  %06X  nEvtNr: %02X\n" , nTdcEvtId ,((dataword>>12)&0xFFF),nEvtNr);
#endif
	    nTdcEvtId = (dataword >> 12) & 0xFFF;

	    TdcDataLen = 1;
	    break;
	    }
	case 3:
	    {// TDC Trailer
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("TRB unpack: Found TDC %d Trailer $%04X $%04X\n",TdcId,(dataword>>12)&0xFFF,dataword&0xFFF);
#endif
	    if (TdcDataLen != (dataword & 0xFFF))
		{
		//wk     if(!quietMode)Error("TRB unpack","TdcDataLen!= length in Trailer!");
		if (!quietMode)
		    printf("TRB unpack: TdcDataLen %d != %d ", TdcDataLen,
			    dataword & 0xFFF);
		}
	    TdcDataLen = 0;
	    if (nTdcEvtId != ((dataword >> 12) & 0xFFF))
		{
		//wk        if(!quietMode)Error("TRB unpack","TDC Header and Trailer have different EventIds");
		//               exit();
		//               return(kFALSE);
		}
	    nCountTDC++;
	    break;
	    }
	case 4:
	    {// TDC DATA Leading

#if DEBUG_LEVEL>4
	    if(!quietMode)printf("TRB unpack: Found TDC %d Lead Data $%08X\n",TdcId,dataword);
#endif
	    Int_t nData, nChannel;
	    nChannel = (dataword >> 19) & 0x1f; // decode channel
	    nChannel += TdcId * 32;
	    nData = dataword & 0x7ffff; // decode 19bit data
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("(Chan,Data) %3d, %d\n",nChannel,nData);
#endif

	    // this is for SINGLE LEADING/TRAILING EDGE measurements only!!!
	    //wk added wypelniane lead
	    if (!fill_lead(nChannel, nData))
		{
		//   cout<< "Leading without Trailing or Too many Hits"<<endl;
		}
	    break;
	    }
	case 5:
	    {// TDC DATA Trailing
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("TRB unpack: Found TDC %d Trail Data $%08X\n",TdcId,dataword);
#endif
	    Int_t nData, nChannel;
	    nChannel = (dataword >> 19) & 0x1f; // decode channel
	    nChannel += TdcId * 32;
	    nData = dataword & 0x7ffff; // decode 19bit data
#if DEBUG_LEVEL>4
	    if(!quietMode)printf("(Chan,Data) %3d, %d\n",nChannel,nData);
#endif
	    // this is for SINGLE LEADING/TRAILING EDGE measurements only!!!
	    if (!fill_trail(nChannel, nData))
		{

		//	cout <<"Trailing without Leading or Too many Hits"<<endl;
		}
	    break;
	    }
	case 6:
	    {// TDC ERROR
	    incErrorNr();
	    if ((dataword & 0x7FFF) == 0x1000)
		{// special case for non fatal errors
		//wk     if(!quietMode)Info("TRB unpack","TDC Event Size Limit exceeded!\n");
		if (!quietMode)
		    printf("(TDC %d Error Event Size Limit: $%08X)\n", TdcId,
			    dataword);
		}
	    else
		{
		//wk     if(!quietMode)Info("TRB unpack","Found TDC Error(s)!\n");
		if (!quietMode)
		    printf("TDC %d Error $%04X ($%08X)\n", TdcId, dataword
			    & 0x7FFF, dataword);
		if (!quietMode)
		    PrintTdcError(dataword & 0x7FFF);
		}
	    break;
	    }
	case 7:
	    {// Debug Info
	    //wk      if(!quietMode)Error("TRB unpack","Found DEBUG Info");
	    if (!quietMode)
		printf("TRB unpack: TDC %d: Found Debug Info $%08X", TdcId,
			dataword);
	    break;
	    }
	default:
	    {// not defined!
	    //wk       if(!quietMode)Error("TRB unpack","Found UNDEFINED data");
	    if (!quietMode)
		printf("TRB unpack: TDC %d: Found undefined $%08X", TdcId,
			dataword);
	    break;
	    }
	    }
	}

    if (nCountTDC != 4)
	{
	if (nCountTDC < 4)
	    {
#warning "Comment this in after may06 beamtime"
	    //         Error("TRB unpack","TDC count <4 -> TDC data missing!!!");
	    }
	else
	    {
	    //wk    if(!quietMode)Error("TRB unpack","TDC count >4 -> additional TDC data!!!");
	    }
	}

    if (uBlockSize != nSizeCounter)
	{
	//wk   if(!quietMode)Error("TRB unpack","Blocksize!=Counted words!!!");
	}
#if DEBUG_LEVEL>4
    if(!quietMode)printf("==== Unpacker end (%d)\n",subEvtId);
#endif

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

    if ((channel < kMaxChannelNr) && (mult < kMaxMult))
	return LeadingTime[channel][mult];
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
//end 

