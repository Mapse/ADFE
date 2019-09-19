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
    // Valores de depressão e de energia.
    double d[n] = {4.9, 6.7, 7.3, 8.1, 9.2};
    double e[n] = {0.07, 0.18, 0.30, 0.45, 0.69};
    // Erro propagado para o logaritmo da depressão. *Ver o cálculo no relatório.
    double errin[n] = {0.061, 0.045, 0.055, 0.049, 0.043};
    // Variáveis: média da energia e da depressão, desvio da energia e da depressão e covariância.
    double mede, medd, sige, sigd, cov = 0;
    
    // Cálculo das médias da energia e da depressão.
    for (unsigned i = 0; i!=n; i++){
        d[i] = log(d[i]);
        e[i] = log(e[i]);
        mede+= e[i]/n;
        medd+= d[i]/n;
    }
    
    // Cálculo da desvio da energia, da depressão e da covariância.
    for (unsigned i = 0; i!=n; i++){
        sige+= pow((e[i]-mede),2)/n;
        sigd+= pow((d[i]-medd),2)/n;
        cov+= (e[i]-mede)*(d[i]-medd)/n;        
    }
    sige = sqrt(sige);
    
    // Cálculo dos parâmetros da reta de ajuste.
    double a,b = 0;
    a = cov/pow(sige,2);
    b = medd - a* mede; 

    // Cálculo dos desvios combinados.
    double sigmas = 0;  
    for (unsigned i = 0; i!=n; i++){
        sigmas+= 1/pow(errin[i],2);
        
    }
    sigmas = 1/pow(sigmas,0.5);

    // Cálculo do desvio do parâmetro a.
    double siga = 0;
    siga = sigmas/sige;

    // Cálculo da média quadrática da energia.
    double equadmed = 0;
    for (unsigned i = 0; i!=n; i++){
        equadmed += (pow(e[i],2))/n;        
    }

    // Cálculo do desvio do parâmetro b.
    double sigb = 0;
    sigb = siga*sqrt(equadmed);

    cout << "a: " << a << " sigma a: " << siga << "\n" << endl;
    cout << "b: " << b << " sigma b: " << sigb << endl;

    // Gráfico da função.
    TGraph *g = new TGraph(n, e, d);
    g->SetMarkerStyle(21);
    g->Draw("AP");
    
}
