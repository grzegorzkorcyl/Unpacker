// File: documentation.C
// 
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 17.10.06
//
// Macro creates the htlm documentation for classes: Unpacker, Event, HldEvent,
// HldSubEvent and Hit
// usage: .L documentation.C
// 	   documentation();

void documentation()
{
 THtml html;
 gSystem->Load("libunpacker_wk.so");
 html.MakeClass("Hit");
 html.MakeClass("EventHdr");
 html.MakeClass("Event");
 html.MakeClass("HldSubEvent");
 html.MakeClass("HldEvent");
 html.MakeClass("Unpacker");
}
