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
    double errin[n] = {0.061, 0.045, 0.055, 0.049, 0.043};
    double mede, medd, sige, sigd, cov;
    
    for (unsigned i = 0; i!=n; i++){
        d[i] = log(d[i]);
        e[i] = log(e[i]);
        mede+= e[i]/n;
        medd+= d[i]/n;
    }
    
    for (unsigned i = 0; i!=n; i++){
        sige+= pow((e[i]-mede),2)/n;
        sigd+= pow((d[i]-medd),2)/n;
        cov+= (e[i]-mede)*(d[i]-medd)/n;
        
    }
    sige = sqrt(sige);
    
    double a,b = 0;
    a = cov/pow(sige,2);
    b = medd - a* mede; 
    double ey=0;
    
    for (unsigned i = 0; i!=n; i++){
        ey += pow((d[i]-(a*e[i]+b)),2)/(n-2);
        
    }
    ey += sqrt(ey);

    double siga = ey/(sige*sqrt(n));
    
    double sigmas;   
    for (unsigned i = 0; i!=n; i++){
        sigmas+= 1/errin[i];
        
    }

    cout << a << endl;
    TGraph *g = new TGraph(n, e, d);
     
    g->Draw("AP");
    
}
