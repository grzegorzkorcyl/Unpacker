// File: event_wk.cc
//
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 12.10.06
// Modified: 17.01.07 Wojciech Krzemien

#include "hit_wk.h"
#include "event_wk.h"
#include "hldevent_wk.h"

//______________________________________________________________________________
//   Event  
//
//
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

ClassImp(Event)

TClonesArray *Event::gHits = 0;

//______________________________________________________________________________
Event::Event() :
    kMaxMult(10), kMaxChannelNr(128)
// Create an Event object.
// When the constructor is invoked for the first time, the class static
// variable gHits is 0 and the TClonesArray gHits is created.
    {
    if (!gHits)
	gHits = new TClonesArray("Hit", 1000);
    Hits = gHits;
    clearAll();

    }

//______________________________________________________________________________
Event::Event(const HldEvent& HldEvt) :
    kMaxMult(HldEvt.getkMaxMult()), kMaxChannelNr(HldEvt.getkMaxChannelNr())
    {
    if (!gHits)
	gHits = new TClonesArray("Hit", 1000);
    Hits = gHits;
    clearAll();
    fill(HldEvt);
    }

//______________________________________________________________________________
Event::~Event()
    {
    clearAll();
    }

//______________________________________________________________________________
void Event::clearAll()
//
    {
    Hits->Clear();
    totalNHits = 0;
    errors_per_event = 0;
    setReferenceChannel(127);
    setReferenceTime(-100000);
    EvtHdr.clearAll();

    /* for(Int_t i=0; i<kMaxChannelNr; i++){
     for(Int_t k=0; k<10; k++){
     trbLeadingTime[i][k]  = -1000000;
     trbTrailingTime[i][k] = -1000000;
     }
     trbLeadingMult[i]=0;
     trbTrailingMult[i]=0;
     }*/

    }

//______________________________________________________________________________
Bool_t Event::fill(const HldEvent& HldEvt)
//what about some error's check
    {
    Hit* pCurrentHit;
    EvtHdr.fill(HldEvt);
    setSubEvtId(HldEvt.getSubEvtId());

    Int_t leadTime;
    Int_t widTime;
    Int_t trailTime;
    Int_t leadMult;

    /*
     for(Int_t i=0; i<kMaxChannelNr; i++){
     for(Int_t k=0; k<10; k++){
     trbLeadingTime[i][k]  = HldEvt.getLeadingTime(i,k);
     trbTrailingTime[i][k] = HldEvt.getTrailingTime(i,k);
     }
     trbLeadingMult[i]=HldEvt.getLeadingMult(i);
     trbTrailingMult[i]=HldEvt.getTrailingMult(i);
     }
     */
    for (Int_t i = 0; i < kMaxChannelNr; i++)
	{
	leadMult = HldEvt.getLeadingMult(i);

	if (leadMult < 1)
	    continue; //Leading Time data for this channel does not exist
	//wk to set
	pCurrentHit = addHit();
	pCurrentHit->setChannel(i);
	pCurrentHit->setTDC(i); //wk !!!change it
	//end wk
	// fill time info for channel: TDC, channel
	// Do it only for firs 4 hits (HHodoRaw can handle 4 hits)
	for (Int_t chmult = 0; (chmult < leadMult && chmult < 4); chmult++)
	    {
	    leadTime = HldEvt.getLeadingTime(i, chmult);
	    trailTime = HldEvt.getTrailingTime(i, chmult);
	    widTime = HldEvt.getWidthTime(i, chmult);
	    //moze powinno sie sprawdzac czy lead i trail sa ustawione
	    // pCurrentHit->fillTimeAndWidth(leadTime, leadTime - trailTime);
	    pCurrentHit->fillTimeAndWidth(leadTime, widTime);
	    //wk 14.03 zmienic zeby wypelniana to tylko jedna fkcja roboczo:
	    if (chmult == 0)
		{
		pCurrentHit->setLeadTime1(leadTime);
		pCurrentHit->setTrailTime1(trailTime);
		}
	    //end wk 14.03
	    //pCurrentHit->fillTimeAndWidth(trbLeadingTime[ i ][ chmult ],0/* wk: trbADC [ i ][ chmult ]*/) ;
	    //line added 17.01.07
	    //pCurrentHit->setWidth(trbLeadingTime[i][0],trbTrailingTime[i][0]);
	    pCurrentHit->setWidth(leadTime, trailTime);
	    }//for

	//wk added
	//cout <<"leading time"<<HldEvt.getLeadingTime(i,1)<<endl;
	//cout <<"trailing time"<<HldEvt.getTrailingTime(i,1)<<endl;
	//cout <<"roznica"<<HldEvt.getLeadingTime(i,1)-HldEvt.getTrailingTime(i,1)<<endl;
	//if(trbTrailingTime[i][0]==-1000000 && trbLeadingTime[i][0]!=-1000000)
	//	cout<<"Trailing nieustawiony dla kanalu: "<<i<<endl;
	//wk end

	//wk it has no effect is it ok?  if(trbLeadingMult[i]  > 4) pCurrentHit->setMult(trbLeadingMult[i]);

	}// for(Int_t i=0; i<128; i++)

    //wk if is set to use reference time -add it !!!!
    //cout <<"trbLeadingTime[getReferenceChannel()][0]: " <<trbLeadingTime[getReferenceChannel()][0]<<endl;
    setReferenceTime(HldEvt.getLeadingTime(getReferenceChannel(), 0));
    setErrors_per_event(HldEvt.errors_per_event);

    return kTRUE;
    //wk from HHodoRaw
    }

//______________________________________________________________________________
Hit *Event::addHit()
    {
    TClonesArray& hits = *Hits;
    Hit *hit = new (hits[totalNHits++]) Hit();
    return hit;
    }

