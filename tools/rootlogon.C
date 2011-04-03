{

gSystem->Load("libGraf");
gSystem->Load("/local/tools/root/unpacker_dirc/libunpacker_wk.so");
printf("Witajcie dobrzy ludzie\n"); 
gROOT->ProcessLine(".L makeTdcHistos.C");
//	   gROOT->ProcessLine(".L analysis.C");
//	   gROOT->ProcessLine(".L DriftTime.C");
//	   gROOT->ProcessLine(".L Planes.C");
}
