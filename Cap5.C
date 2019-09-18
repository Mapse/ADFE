#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMath.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include <iostream>

using namespace std;

void prob2(){
    
    TFile *file = new TFile("pendulo.root", "RECREATE");
    TTree *tree = new TTree("tree", "tree");

    tree->ReadFile("pendulo.dat","T/D", ',');
    int n = tree->GetEntries();

    double T;
    tree->SetBranchAddress("T",&T);
    double media, err, errmedia, errerr = 0;

    for (unsigned i = 0; i != n; ++i){
        tree->GetEntry(i);
        media += T/n;
    }

    for (unsigned i = 0; i != n; ++i){
        tree->GetEntry(i);
        err += pow((T-media),2)/(n-1);
    }

    err = sqrt(err);
    errmedia = err/sqrt(n);
    errerr = errmedia/sqrt(2*n);

    cout << "Média: " << media << " Erro da medida: " << err << " Erro da média: " << errmedia << " Erro do erro da média: " << errerr << endl;

    file->Write();
    file->Close();    
}

void prob3(){
    
    const unsigned n = 6;
    double ddp[n] = {1.44, 1.48, 1.42, 1.44, 1.50, 1.46};
    
    double media, err, errmedia, errerr = 0;

    for (unsigned i = 0; i != n; ++i){
        media += ddp[i]/n;
    }

    for (unsigned i = 0; i != n; ++i){
        err += pow((ddp[i]-media),2)/(n-1);
    }

    err = sqrt(err);
    errmedia = err/sqrt(n);
    errerr = errmedia/sqrt(2*n);

    cout << "Média: " << media << " Erro da medida: " << err << " Erro da média: " << errmedia << " Erro do erro da média: " << errerr << endl;


}

void prob5(){
    const unsigned n = 5;
    double d[n] = {4.9, 6.7, 7.3, 8.1, 9.2};
    double e[n] = {0.07, 0.18, 0.30, 0.45, 0.69};
    double mede, medd, sige, sigd;
    
    for (unsigned i = 0; i!=n; i++){
        d[i] = log(d[i]);
        e[i] = log(e[i]);
        mede+= e[i]/n;
        medd+= d[i]/n;
    }
    
    for (unsigned i = 0; i!=n; i++){
        sige+= pow((e[i]-mede),2)/(n-1);
        sigd+= pow((d[i]-medd),2)/(n-1);
        
    }
    
    cout << "média da energia: " << mede << "desvio da energia: " << sige;
    cout << "média da depressão: " << mede << "desvio da depressão: " << sige;
    TGraph *g = new TGraph(n, e, d);
     
    g->Draw("AP");
    
}
