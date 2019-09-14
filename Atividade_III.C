#include "TH1.h"
#include <iostream>
#include "TMath.h"
#include "TRandom.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFitResult.h"

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