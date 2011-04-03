
void Create()
{
TFile* f=new TFile("Event.root");
TCanvas* c1=new TCanvas("ct","ct",0,0,600,600);

TH1F *hityNaZdarzenie= new TH1F("hityNaZdarzenie","Liczba hitow na zdarzenie",50,0,50);
TH1F *hityNaKanal= new TH1F("hityNaKanal","Liczba hitow na kanal",10,0,10);
TH1F* kanaly=new TH1F("kanaly","Liczba zliczen w funkcji numeru kanalu",64,64,128);


TH1F* czasDryfu=new TH1F("czasDryfu","Czas dryfu",3000,0,3000);
TH1F* czasDryfu1=new TH1F("czasDryfu1","Czas dryfu dla 1 plaszczyzny",3000,0,3000);
TH1F* czasDryfu2=new TH1F("czasDryfu2","Czas dryfu dla 2 plaszczyzny",3000,0,3000);
TH1F* czasDryfu3=new TH1F("czasDryfu3","Czas dryfu dla 3 plaszczyzny",3000,0,3000);
TH1F* czasDryfu4=new TH1F("czasDryfu4","Czas dryfu dla 4 plaszczyzny",3000,0,3000);


//T->Draw("channel >>kanaly","channel!=127&&channel!=95");
T->Project("hityNaZdarzenie","totalNHits","channel!=127&&channel!=95");
T->Project("hityNaKanal","nHits","channel!=127&&channel!=95");
T->Project("kanaly","channel","channel!=127&&channel!=95");


T->Project("czasDryfu","referenceTime-time1","channel!=127&&channel!=95&&time1>0&&referenceTime>0");
T->Project("czasDryfu1","referenceTime-time1","channel!=127&&channel!=95&&time1>0&&referenceTime>0&&channel>63&&channel<80");
T->Project("czasDryfu2","referenceTime-time1","channel!=127&&channel!=95&&time1>0&&referenceTime>0&&channel>95&&channel<112");
T->Project("czasDryfu3","referenceTime-time1","channel!=127&&channel!=95&&time1>0&&referenceTime>0&&channel>=80&&channel<95");
T->Project("czasDryfu4","referenceTime-time1","channel!=127&&channel!=95&&time1>0&&referenceTime>0&&channel>=112&&channel<127");

ct->Divide(2,2);
ct->cd(1);
czasDryfu1->Draw();
ct->cd(2);
czasDryfu2->Draw();
ct->cd(3);
czasDryfu3->Draw();
ct->cd(4);
czasDryfu4->Draw();
}
