#include<string>


//================================================
// calcSeparation()
//================================================
float calcSep(TH1F* sig, TH1F* bkg) {
 
  float Separation = 0;
  for(int i=1; i<= sig->GetNbinsX(); i++){

    float y_sig = sig->GetBinContent(i);
    float y_bkg = bkg->GetBinContent(i);

    if((y_sig + y_bkg) != 0){
      Separation += (y_sig - y_bkg)*(y_sig - y_bkg)/(y_sig + y_bkg);}
  }

  Separation = 0.5*Separation;

  return Separation;

}


void MVAljets()
{
//   In a ROOT session, you can do:
//      Root > .L MVAljets.C
//      Root > MVAljets t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch




TChain * fChain[2];
fChain[0]=new TChain("nominal");
fChain[1]=new TChain("nominal");
fChain[0]->Add("/afs/cern.ch/work/m/mmantoan/public/LJETS_4bI/nomin/341270/output.root");
fChain[0]->Add("/afs/cern.ch/work/m/mmantoan/public/LJETS_4bI/nomin/341271/output.root");
fChain[0]->Add("/afs/cern.ch/work/m/mmantoan/public/LJETS_4bI/nomin/341177/output.root");
fChain[1]->Add("/afs/cern.ch/work/m/mmantoan/public/LJETS_4bI/nomin/410000/output.root");

std::cout<<":-D"<<std::endl;

fChain[0]->SetBranchStatus("*",0);
fChain[1]->SetBranchStatus("*",0);
fChain[0]->SetBranchStatus("Norm_total",1);
fChain[1]->SetBranchStatus("Norm_total",1);


    std::string n, min, max, bin;



Int_t region[9][2][2]; TBranch *b_region[9][2][2]; Float_t Norm_Lumi[2]; TBranch *b_Norm_Lumi[2];


fChain[0]->SetBranchAddress("Norm_total", &Norm_Lumi[0], &b_Norm_Lumi[0]);
fChain[1]->SetBranchAddress("Norm_total", &Norm_Lumi[1], &b_Norm_Lumi[1]);


Int_t j=0;
ifstream input;
input.open("list.txt");
  std::string line;
Int_t nvar=0;
  while (getline(input,line)) {


    istringstream linestream(line);
    getline(linestream, n, '|');
    getline(linestream, bin, '|');
    getline(linestream, min, '|');
    getline(linestream, max);


nvar++;
}
input.close();

vector<string> nn (nvar);

vector<string> regio (9);

Float_t var[nvar][2];
TBranch *b_var[nvar][2];
Int_t preproflags[nvar];
input.open("list.txt");

Float_t maxx[nvar];
Float_t minn[nvar];
Int_t binn[nvar];



Int_t k=0;

 while (getline(input,line)) {


       istringstream linestream(line);
    getline(linestream, n, '|');
    getline(linestream, bin, '|');
    getline(linestream, min, '|');
    getline(linestream, max);
  
//std::cout<<"Matteo check "<<n.c_str()<<std::endl;

fChain[0]->SetBranchStatus(n.c_str(),1);
fChain[1]->SetBranchStatus(n.c_str(),1);
fChain[0]->SetBranchAddress(n.c_str(), &var[k][0], &b_var[k][0]);
fChain[1]->SetBranchAddress(n.c_str(), &var[k][1], &b_var[k][1]);


 minn[k]=std::atof(min.c_str());
 maxx[k]=std::atof(max.c_str());
binn[k]= std::stoi(bin.c_str());



nn[k]=n;

//std::cout<<n<<std::endl;

//std::cout<<c_varnames[k]<<std::endl;
k++;

}

input.close();













 TH1F* h[9][nvar][2];


std::string ejets;
std::string mujets;

for(Int_t i=0; i<9; i++){

if(i==0){regio[0]="4jex2bex";}
if(i==1){regio[1]="4jex3bex";}
if(i==2){regio[2]="4jex4bex";}
if(i==3){regio[3]="5jex2bex";}
if(i==4){regio[4]="5jex3bex";}
if(i==5){regio[5]="5jex4bin";}
if(i==6){regio[6]="6jin2bex";}
if(i==7){regio[7]="6jin3bex";}
if(i==8){regio[8]="6jin4bin";}


ejets="e_jets_"+regio[i];
mujets="mu_jets_"+regio[i];

fChain[0]->SetBranchStatus(ejets.c_str(),1);
fChain[1]->SetBranchStatus(ejets.c_str(),1);
fChain[0]->SetBranchStatus(mujets.c_str(),1);
fChain[1]->SetBranchStatus(mujets.c_str(),1);

fChain[0]->SetBranchAddress(ejets.c_str(), &region[i][0][0], &b_region[i][0][0]);
fChain[0]->SetBranchAddress(mujets.c_str(), &region[i][1][0], &b_region[i][1][0]);
fChain[1]->SetBranchAddress(ejets.c_str(), &region[i][0][1], &b_region[i][0][1]);
fChain[1]->SetBranchAddress(mujets.c_str(), &region[i][1][1], &b_region[i][1][1]);


for (Int_t j=0; j<nvar; j++){
 h[i][j][0] = new TH1F((nn[j]+"_"+regio[i]+"_sig").c_str(),"",binn[j],minn[j],maxx[j]); 
 h[i][j][1] = new TH1F((nn[j]+"_"+regio[i]+"_back").c_str(),"",binn[j],minn[j],maxx[j]); 
}

}

input.close();


  









for(Int_t i=0; i<2; i++){

   Int_t nentries = fChain[i]->GetEntries();

   Long64_t nbytes = 0, nby = 0;
   for (Int_t jentry=0; jentry<nentries;jentry++) {
  
      fChain[i]->GetEvent(jentry);  nbytes += nby;

if(jentry % 100000==0){
std::cout << "Reading Event " <<jentry<<" of "<< nentries<<std::endl;
}


for(Int_t s=0; s<9; s++){

if( (region[s][0][i]==1 || region[s][1][i]==1)) {


for(j=0; j<nvar; j++){
//std::cout<<var[j][i]<<std::endl;

if(nn[j]=="Mbb_MindR"||nn[j]=="Mjj_MaxPt"||nn[j]=="pT_jet5"||nn[j]=="Mjj_MindR"||nn[j]=="Mbb_MaxM"||nn[j]=="Mjjj_MaxPt"||nn[j]=="HhadT_jets"||nn[j]=="Mbj_MaxPt"||nn[j]=="Mbj_MindR"||nn[j]=="Mbb_MaxPt"||nn[j]=="pTuu_MindR"||nn[j]=="Muu_MindR"||nn[j]=="MHiggs"||nn[j]=="Mjj_MinM"||nn[j]=="Mjj_HiggsMass"||nn[j]=="HT_all"||nn[j]=="pT_jet3"||nn[j]=="pT_jet1"||nn[j]=="pT_jet2"||nn[j]=="pT_jet4"||nn[j]=="pT_lep1"||nn[j]=="pT_bJet1"||nn[j]=="met_met"||nn[j]=="pT_bjet1"||nn[j]=="pT_bjet2"||nn[j]=="pT_bjet3"||nn[j]=="pT_bjet4"||nn[j]=="Mbb_avg"||nn[j]=="Mbj_avg"||nn[j]=="Mbj_MaxM"||nn[j]=="Mjj_avg"||nn[j]=="Mjj_MaxM"||nn[j]=="Muu_avg"||nn[j]=="Muu_MaxM"||nn[j]=="Muu_MaxPt"||nn[j]=="pTbb_avg"||nn[j]=="pTbb_MaxM"||nn[j]=="pTbb_MaxPt"||nn[j]=="pTbb_MindR"||nn[j]=="pTbj_avg"||nn[j]=="pTbj_MaxM"||nn[j]=="pTbj_MaxPt"||nn[j]=="pTbj_MindR"||nn[j]=="pTjj_avg"||nn[j]=="pTjj_MaxM"||nn[j]=="pTjj_MaxPt"||nn[j]=="pTjj_MindR"||nn[j]=="pTuu_avg"||nn[j]=="pTuu_MindR"||nn[j]=="pTuu_MaxM"||nn[j]=="pTuu_MaxPt"){
h[s][j][i]->Fill(var[j][i]/1000.,Norm_Lumi[i]);}

else h[s][j][i]->Fill(var[j][i],Norm_Lumi[i]);



}
//histofill



}

}
}
}

















TH1F* hdiv[9][nvar];
float sep[9][nvar];

bool ok[9][nvar];
for(Int_t i=0;i<9;i++){
for(Int_t j=0;j<nvar;j++){
ok[i][j]=false;

}
}



TPaveText* paves[9][nvar]; 
TPaveText* paves2[nvar]; 
char titles[9*nvar];
char titles2[nvar];

for(Int_t i=0;i<9;i++){
for(Int_t j=0;j<nvar;j++){
paves[i][j]= new TPaveText(0.65, 0.65, 0.85, 0.75,"NDC");
paves2[j]= new TPaveText(0.15, 0.7, 0.4, 0.85,"NDC");
 //TH1F *hdiv[i][j] = h[i][j][0]->Clone();  hdiv[i][j]->Divide(h[i][j][1]);  
for(Int_t k=0;k<2;k++){
std::cout<<nn[j]<<""<<h[i][j][k]->Integral()<<std::endl;//adding to check integral is 0 or not. 
if(h[i][j][k]->Integral()!=0){
h[i][j][k]->Scale(1./h[i][j][k]->Integral());
hdiv[i][j]=(TH1F*) h[i][j][0]->Clone("");  hdiv[i][j]->Divide(h[i][j][1]); hdiv[i][j]->SetLineColor(kBlack);
if(nn[j]=="Mbb_MindR"||nn[j]=="Mjj_MaxPt"||nn[j]=="pT_jet5"||nn[j]=="Mjj_MindR"||nn[j]=="Mbb_MaxM"||nn[j]=="Mjjj_MaxPt"||nn[j]=="HhadT_jets"||nn[j]=="Mbj_MaxPt"||nn[j]=="Mbj_MindR"||nn[j]=="Mbb_MaxPt"||nn[j]=="pTuu_MindR"||nn[j]=="Muu_MindR"||nn[j]=="MHiggs"||nn[j]=="Mjj_MinM"||nn[j]=="Mjj_HiggsMass"||nn[j]=="HT_all"||nn[j]=="pT_jet3"||nn[j]=="pT_jet1"||nn[j]=="pT_jet2"||nn[j]=="pT_jet4"||nn[j]=="pT_lep1"||nn[j]=="pT_bJet1"||nn[j]=="met_met"||nn[j]=="pT_bjet1"||nn[j]=="pT_bjet2"||nn[j]=="pT_bjet3"||nn[j]=="pT_bjet4"||nn[j]=="Mbb_avg"||nn[j]=="Mbj_avg"||nn[j]=="Mbj_MaxM"||nn[j]=="Mjj_avg"||nn[j]=="Mjj_MaxM"||nn[j]=="Muu_avg"||nn[j]=="Muu_MaxM"||nn[j]=="Muu_MaxPt"||nn[j]=="pTbb_avg"||nn[j]=="pTbb_MaxM"||nn[j]=="pTbb_MaxPt"||nn[j]=="pTbb_MindR"||nn[j]=="pTbj_avg"||nn[j]=="pTbj_MaxM"||nn[j]=="pTbj_MaxPt"||nn[j]=="pTbj_MindR"||nn[j]=="pTjj_avg"||nn[j]=="pTjj_MaxM"||nn[j]=="pTjj_MaxPt"||nn[j]=="pTjj_MindR"||nn[j]=="pTuu_avg"||nn[j]=="pTuu_MindR"||nn[j]=="pTuu_MaxM"||nn[j]=="pTuu_MaxPt"){
hdiv[i][j]->GetXaxis()->SetTitle("GeV");
}
ok[i][j]=true;
//sep[i][j]=calcSep(h[i][j][0],h[i][j][1]);

//sprintf(titles,"Sep = %.2f %%",sep[i][j]*100);
//paves[i][j]->AddText(titles.c_str());

}


}
}
}




for(Int_t i=0;i<9;i++){
for(Int_t j=0;j<nvar;j++){
//cout<<i<<" "<<j<<" "<<calcSep(h[i][j][0],h[i][j][1])<<endl;
sep[i][j]=calcSep(h[i][j][0],h[i][j][1]);

sprintf(titles,"Sep = %.2f %%",sep[i][j]*100);

paves[i][j]->AddText(titles);
 paves[i][j]->SetFillColor(0);
}
}

 
for(Int_t j=0;j<nvar;j++){
paves2[j]->AddText(nn[j].c_str());
 paves2[j]->SetFillColor(0);
}

 TLegend* leg = new TLegend(0.6, 0.8, 0.9, 0.9);
 leg->AddEntry(h[0][0][0], "ttH", "l"); 
 leg->AddEntry(h[0][0][1], "ttbar", "l"); 

for(Int_t i=0;i<9;i++){ 
for(Int_t j=0;j<nvar;j++){
for(Int_t k=0;k<2;k++){
if (k==1){h[i][j][k]->SetLineColor(kBlue);}
if (k==0){h[i][j][k]->SetLineColor(kRed);}


}
}
}


TLine* l = new TLine(); 
  l->SetLineStyle(2); 
   
gStyle->SetOptStat(0);


string name;
TCanvas *a[9][nvar];


gStyle->SetCanvasColor(-1); 
gStyle->SetPadColor(-1); 
gStyle->SetFrameFillColor(-1); 
gStyle->SetHistFillColor(-1); 
gStyle->SetTitleFillColor(-1); 
gStyle->SetFillColor(-1); 
gStyle->SetFillStyle(4000); 
gStyle->SetStatStyle(0); 
gStyle->SetTitleStyle(0); 
gStyle->SetCanvasBorderSize(0); 
gStyle->SetFrameBorderSize(0); 
gStyle->SetLegendBorderSize(0); 
gStyle->SetStatBorderSize(0); 
gStyle->SetTitleBorderSize(0);




for(Int_t i=0;i<9;i++){
for(Int_t j=0;j<nvar;j++){
name=regio[i]+"/"+nn[j]+".png";

a[i][j]=new TCanvas(name.c_str(), name.c_str(), 500, 500);
TPad *pad1 = new TPad("pad1","",0,0.2,1,1);
 TPad *pad2 = new TPad("pad2","",0,0.05,1,0.3);
pad1->Draw();
   pad2->Draw();
if(ok[i][j]==true){

cout<<name<<endl;
//a[i][j]->cd(1);
pad1->cd();
gPad->SetTicky(2);
h[i][j][0]->SetMaximum(2*h[i][j][0]->GetMaximum());
h[i][j][0]->Draw("HISTEE");
h[i][j][1]->Draw("HISTEsame");
paves[i][j]->Draw("same");
 paves2[j]->Draw("same");
leg->Draw();
//a[i][j]->cd(2);
pad2->cd();
gPad->SetTicky(2);
hdiv[i][j]->Draw("E");
hdiv[i][j]->GetXaxis()->SetTitleOffset(0.9);
hdiv[i][j]->GetXaxis()->SetTitleSize(0.15);
hdiv[i][j]->GetXaxis()->SetLabelSize(0.1);
hdiv[i][j]->GetYaxis()->SetLabelSize(0.1);


hdiv[i][j]->GetYaxis()->SetRangeUser(0.2,2.5);
hdiv[i][j]->GetYaxis()->SetNdivisions(5);
//hdiv[i][j]->GetXaxis()->SetTitleOffset(1.3);
l->DrawLine(hdiv[i][j]->GetXaxis()->GetXmin(), 1., hdiv[i][j]->GetXaxis()->GetXmax(), 1.);



//cout<<name<<endl;
a[i][j]->SaveAs(name.c_str());
}

}
}











}
