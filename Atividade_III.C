#include "TH1.h"
#include <iostream>
#include "TMath.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include <TF1NormSum.h>


using namespace std;


void ex15(){
    
    TCanvas *c1 = new TCanvas("c1", "Problema 15", 400, 90, 600, 500);

    // Criação e preenchimento do histograma com o gerador gaussiano aleatório.
    TH1D *h1 = new TH1D("h1", "histograma;var. ale#acute{a}toria;frequ#hat{e}ncia",50,-5,5);
    h1->FillRandom("gaus",1000);
    
    // Criação da função gaussiana para o fit.        
    TF1 *ga = new TF1("ga","gaus"); 

    // Armazenamendo do Fit, em que S significa armazenar o fit em TFitResultPr e M melhora
    // o resultado do Fit utilizando o algoritmo IMPROVE do TMinuit.
    TFitResultPtr fit = h1->Fit(ga,"S M");
    fit->Print();
    
    // Guarda a matriz de correlação no objeto mtx.
    TMatrixDSym mtx = fit->GetCorrelationMatrix();

    // Obtêm o resultado do Chi quadrado, a média e o desvio padrão, respectivamente.
    double xi2 = fit->Chi2();
    double med = fit->Parameter(1);
    double sig = fit->Parameter(2);

    cout << "A média e o desvio padrão são, respectivamente " << med << " e " << sig << "." << endl;

    cout << "O teste de Chi quadrado é " << xi2 << endl;  

    mtx.Print();    
   
    /* Outra maneira de pegar a média e o desvio padrão seria diretamente através da função
    gaussiana:
    double med, sig;
    med = ga->GetParameter(1); // Pega a média da função gaus.
    sig = ga->GetParameter(2); // Pega o desvio padrão da função gaus.*/

}

void ex16(){
    
    TFile *file = new TFile("DimuonM.root", "RECREATE");
    TTree *tree = new TTree("tremu", "Dados do dimuon_2-5 GeV.csv");

    tree->ReadFile("dimuon_2-5GeV2.csv","Massa/D,Q1/I,Q2/I",',');

    // Criação do histograma
    TH1D *h1 = new TH1D("h1", "histograma; massa invariante (GeV); frequ#hat{e}ncia ",60, 2, 5);
    
    double massa;
    int q1, q2;
    
    tree->SetBranchAddress("Massa", &massa);
    tree->SetBranchAddress("Q1", &q1);
    tree->SetBranchAddress("Q2", &q2);

    int n = tree->GetEntries();

    for (unsigned i = 0; i!=n; i++){
        tree->GetEntry(i);
        if (q1*q2 == -1)  h1->Fill(massa);
       
    }

    TF1 *exp1 = new TF1("exp1", "expo",2., 5);
    exp1->SetParameter(0, 580);
    exp1->SetParameter(1,  -1.01172e+00);
    
    TF1 *ga = new TF1("ga", "gaus", 2, 5);
    ga->SetParameter(0,44.3499) ;
    ga->SetParameter(1,2.96950);
    ga->SetParameter(2,0.256882);
         
    TF1 *sum = new TF1("sum", "[0]*TMath::Gaus(x,[1],[2]) + [3]*TMath::Exp([4]*x)",2.,5.);
    sum->SetParameters(44.3499, 2.96950, 0.256882, 580, -1.01172);
    //TF1 *sum = new TF1("sum", "ga+exp1",2.,5.);

    TFitResultPtr fit = h1->Fit(sum,"S M");  
    TMatrixDSym mtx = fit->GetCorrelationMatrix();
    TMatrixDSym cov = fit->GetCovarianceMatrix();
    double xi2 = fit->Chi2();
    double med = fit->Parameter(1);
    double sig = fit->Parameter(2);
    mtx.Print();   
    file->Write();
    const double *p = fit->GetErrors();
    double ne = ga->Integral(2.,5.);
    TMatrixDSym covPeak = cov.GetSub(0,2,0,2); 
    
    double err = ga->IntegralError(2.,5.,covPeak.GetMatrixArray())/h1->GetBinWidth(1);

    cout << "O número de pico de eventos é: " << ne << endl;
    cout << "O erro é: " << err << endl;
    //file->Close();
    
}

void ex17(){

    TFile *file = new TFile("DimuonM.root", "RECREATE");
    TTree *tree = new TTree("tremu", "Dados do dimuon_2-5 GeV.csv");

    tree->ReadFile("dimuon_2-5GeV2.csv","Massa/D,Q1/I,Q2/I",',');

    // Criação do histograma
    TH1D *h1 = new TH1D("h1", "histograma; massa invariante (GeV); frequ#hat{e}ncia ",60, 2, 5);
    
    double massa;
    int q1, q2;
    
    tree->SetBranchAddress("Massa", &massa);
    tree->SetBranchAddress("Q1", &q1);
    tree->SetBranchAddress("Q2", &q2);

    int n = tree->GetEntries();

    for (int i = 0; i!=n; i++){
        tree->GetEntry(i);
        if (q1*q2 == -1)  h1->Fill(massa);
       
    }
    h1->Draw();
}