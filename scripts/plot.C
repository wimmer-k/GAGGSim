void plot(){
 gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TChain *ch = new TChain("str");
  for(int i=0;i<10;i++)
    ch->Add(Form("/mnt/raid/gamma/gagg/NoWrap_2MeV_10k_%d.root",i));
  //ch->Add("test.root");

  TH1F* h[6];
  TH2F* g[5];
  ch->Draw("edep>>hdep(250,0,2500)");
  h[0] = (TH1F*)gROOT->FindObject("hdep");
  h[0]->SetName("h0");
  ch->Draw("nphotons>>hpho(750,0,15000)");
  h[1] = (TH1F*)gROOT->FindObject("hpho");
  h[1]->SetName("h1");

  ch->Draw("pfirst.Z()>>hzf(60,-30,-30)");
  h[2] = (TH1F*)gROOT->FindObject("hzf");
  h[2]->SetName("h2");
  ch->Draw("paverage.Z()>>hza(60,-30,-30)");
  h[3] = (TH1F*)gROOT->FindObject("hza");
  h[3]->SetName("h3");
  ch->Draw("pmax.Z()>>hzm(60,-30,-30)");
  h[4] = (TH1F*)gROOT->FindObject("hzm");
  h[4]->SetName("h4");

  ch->Draw("nphotons>>hphog(750,0,15000)","paverage.Z()>0");
  h[5] = (TH1F*)gROOT->FindObject("hphog");
  h[5]->SetName("h5");

  ch->Draw("nphotons:edep>>hne(125,0,2500,375,0,15000)");
  g[0] = (TH2F*)gROOT->FindObject("hne");
  g[0]->SetName("g0");

  ch->Draw("nphotons:pfirst.Z()>>hnzf(60,-30,-30,375,0,15000)");
  g[1] = (TH2F*)gROOT->FindObject("hnzf");
  g[1]->SetName("g1");

  ch->Draw("nphotons:paverage.Z()>>hnza(60,-30,-30,375,0,15000)");
  g[2] = (TH2F*)gROOT->FindObject("hnza");
  g[2]->SetName("g2");

  ch->Draw("nphotons:pmax.Z()>>hnzm(60,-30,-30,375,0,15000)");
  g[3] = (TH2F*)gROOT->FindObject("hnzm");
  g[3]->SetName("g3");

  // ch->Draw("nphotons:pfirst.Z()>>hnzf(60,-30,-30,375,0,15000)");
  // g[1] = (TH2F*)gROOT->FindObject("hnzf");
  // g[1]->SetName("g1");

  
  TCanvas *c = new TCanvas("c","c",700,400);
  c->cd();
  TPad *pad; 
  pad = new TPad("p0","p0",0,0,1,1);
  pad->SetTopMargin(0.01);
  pad->SetLeftMargin(0.11);
  pad->SetBottomMargin(0.145);
  pad->SetRightMargin(0.04);
  pad->Draw();
  pad->cd();
  
  for(int i=0;i<5;i++){
    h[i]->GetYaxis()->SetTitleSize(0.05);
    h[i]->GetYaxis()->SetTitleOffset(1.0);
    h[i]->GetYaxis()->SetLabelSize(0.04);
    h[i]->GetYaxis()->SetTitle("counts");
    h[i]->GetXaxis()->SetTitleSize(0.06);
    h[i]->GetXaxis()->SetTitleOffset(0.9);
    h[i]->GetXaxis()->SetLabelSize(0.05);
  }
  h[0]->GetXaxis()->SetTitle("E_{dep}");
  h[1]->GetXaxis()->SetTitle("N_{phot}");
  h[2]->GetXaxis()->SetTitle("z_{first}");
  h[3]->GetXaxis()->SetTitle("z_{average}");
  h[4]->GetXaxis()->SetTitle("z_{max}");

  for(int i=0;i<4;i++){
    g[i]->GetYaxis()->SetTitleSize(0.05);
    g[i]->GetYaxis()->SetTitleOffset(1.0);
    g[i]->GetYaxis()->SetLabelSize(0.04);
    g[i]->GetXaxis()->SetTitleSize(0.06);
    g[i]->GetXaxis()->SetTitleOffset(0.9);
    g[i]->GetXaxis()->SetLabelSize(0.05);
    g[i]->GetZaxis()->SetTitleSize(0.05);
    g[i]->GetZaxis()->SetTitleOffset(1.0);
    g[i]->GetZaxis()->SetLabelSize(0.04);
    g[i]->GetZaxis()->SetTitle("counts");
    g[i]->GetYaxis()->SetTitle("N_{phot}");
  }
  g[0]->GetXaxis()->SetTitle("E_{dep}");
  g[1]->GetXaxis()->SetTitle("z_{first}");
  g[2]->GetXaxis()->SetTitle("z_{average}");
  g[3]->GetXaxis()->SetTitle("z_{max}");

  h[0]->GetYaxis()->SetRangeUser(0,31000);
  h[0]->Draw();
  c->SaveAs("edep.pdf");
  h[0]->GetYaxis()->UnZoom();
  pad->SetLogy();
  h[0]->Draw();
  c->SaveAs("edep_log.pdf");
  pad->SetLogy(0);
  h[1]->GetYaxis()->SetRangeUser(0,1550);
  h[1]->Draw();
  c->SaveAs("npho.pdf");
  h[1]->GetYaxis()->SetRangeUser(1,2000);
  pad->SetLogy();
  h[1]->Draw();
  c->SaveAs("npho_log.pdf");
  pad->SetLogy(0);
  h[2]->Draw();
  h[2]->GetYaxis()->SetRangeUser(1,3000);
  h[3]->Draw("same");
  h[4]->Draw("same");
  h[3]->SetLineColor(2);
  h[4]->SetLineColor(3);
  TLegend *le;
  le= new TLegend(0.35,0.77,0.96,0.975);
  le->AddEntry(h[2],"Z position, first interaction","L");
  le->AddEntry(h[3],"Z position, average","L");
  le->AddEntry(h[4],"Z position, highest deposition","L");
  le->SetTextSize(0.06);
  le->SetFillColor(0);
  le->SetBorderSize(0);
  le->Draw();
  c->SaveAs("positionz.pdf");
  h[5]->Draw();
  c->SaveAs("npho_gated.pdf");
  h[5]->Draw();
  h[5]->SetLineColor(3);
  h[1]->Draw("same");
  le= new TLegend(0.17,0.77,0.54,0.975);
  le->AddEntry(h[1],"all events","L");
  le->AddEntry(h[5],"Z average > 0","L");
   le->SetTextSize(0.06);
  le->SetFillColor(0);
  le->SetBorderSize(1);
  le->Draw();
  c->SaveAs("npho_gated_super.pdf");

  
  pad->SetRightMargin(0.14);
  
  g[0]->Draw("colz");
  c->SaveAs("npho_edep.pdf");
  g[0]->GetZaxis()->SetRangeUser(0,220);
  g[0]->Draw("colz");
  c->SaveAs("npho_edep.pdf");
  g[1]->Draw("colz");
  c->SaveAs("npho_zfirst.pdf");
  g[2]->Draw("colz");
  c->SaveAs("npho_zaverage.pdf");
  g[3]->Draw("colz");
  c->SaveAs("npho_zmax.pdf");

}
void plot_jul22(){
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TChain *ch = new TChain("str");
  for(int i=0;i<10;i++)
    ch->Add(Form("/mnt/raid/gamma/gagg/GAGG_2MeV_10kevts_%d.root",i));

  TH1F* h[2];
  TH2F* g;
  ch->Draw("edep>>hdep(250,0,2500)");
  h[0] = (TH1F*)gROOT->FindObject("hdep");
  h[0]->SetName("h0");
  ch->Draw("npho>>hpho(750,0,15000)");
  h[1] = (TH1F*)gROOT->FindObject("hpho");
  h[1]->SetName("h1");

  ch->Draw("npho:edep>>h2d(125,0,2500,375,0,15000)");
  g = (TH2F*)gROOT->FindObject("h2d");
  g->SetName("g");
 
  TCanvas *c = new TCanvas("c","c",700,400);
  c->cd();
  TPad *pad; 
  pad = new TPad("p0","p0",0,0,1,1);
  pad->SetTopMargin(0.01);
  pad->SetLeftMargin(0.11);
  pad->SetBottomMargin(0.145);
  pad->SetRightMargin(0.04);
  pad->Draw();
  pad->cd();
  

  h[0]->GetYaxis()->SetTitleSize(0.05);
  h[0]->GetYaxis()->SetTitleOffset(1.0);
  h[0]->GetYaxis()->SetLabelSize(0.04);
  h[0]->GetYaxis()->SetTitle("counts");
  h[0]->GetXaxis()->SetTitleSize(0.06);
  h[0]->GetXaxis()->SetTitleOffset(0.9);
  h[0]->GetXaxis()->SetLabelSize(0.05);
  h[0]->GetXaxis()->SetTitle("E_{dep}");

  h[1]->GetYaxis()->SetTitleSize(0.05);
  h[1]->GetYaxis()->SetTitleOffset(1.0);
  h[1]->GetYaxis()->SetLabelSize(0.04);
  h[1]->GetYaxis()->SetTitle("counts");
  h[1]->GetXaxis()->SetTitleSize(0.06);
  h[1]->GetXaxis()->SetTitleOffset(0.9);
  h[1]->GetXaxis()->SetLabelSize(0.05);
  h[1]->GetXaxis()->SetTitle("N_{phot}");

  g->GetYaxis()->SetTitleSize(0.05);
  g->GetYaxis()->SetTitleOffset(1.0);
  g->GetYaxis()->SetLabelSize(0.04);
  g->GetYaxis()->SetTitle("N_{phot}");
  g->GetXaxis()->SetTitleSize(0.06);
  g->GetXaxis()->SetTitleOffset(0.9);
  g->GetXaxis()->SetLabelSize(0.05);
  g->GetXaxis()->SetTitle("E_{dep}");
  g->GetZaxis()->SetTitleSize(0.05);
  g->GetZaxis()->SetTitleOffset(1.0);
  g->GetZaxis()->SetLabelSize(0.04);
  g->GetZaxis()->SetTitle("counts");
 
 
  h[0]->GetYaxis()->SetRangeUser(0,31000);
  h[0]->Draw();
  c->SaveAs("edep.pdf");
  h[0]->GetYaxis()->UnZoom();
  pad->SetLogy();
  h[0]->Draw();
  c->SaveAs("edep_log.pdf");
  pad->SetLogy(0);
  h[1]->GetYaxis()->SetRangeUser(0,1550);
  h[1]->Draw();
  c->SaveAs("npho.pdf");
  h[1]->GetYaxis()->SetRangeUser(1,2000);
  pad->SetLogy();
  h[1]->Draw();
  c->SaveAs("npho_log.pdf");

  pad->SetRightMargin(0.14);
  pad->SetLogy(0);
  g->Draw("colz");
  c->SaveAs("versus.pdf");
  g->GetZaxis()->SetRangeUser(0,2200);
  g->Draw("colz");
  c->SaveAs("versus_zoom.pdf");
}
