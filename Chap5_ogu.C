#include <iostream>
#include <string>
#include <vector>
#include "TF1.h"

void verblum1(){
    TF1 *gra = new TF1("graf", "x*TMath::Power((10-x),3)/20000*4",0,10);
    gra->SetTitle("Func#tilde{a}o de verossimilhanca");
    gra->GetXaxis()->SetTitle("x (qt de bolas azuis na caixa)");
    gra->GetYaxis()->SetTitle("L");
    gra->Draw();
    gra->SaveAs("./Vero.jpeg");
}

void verblum2(){
    TF1 *gra = new TF1("graf", "TMath::Power(x,3)*TMath::Power((10-x),8)/5.0505051e+08",0,10);
    gra->SetTitle("Func#tilde{a}o de verossimilhanca");
    gra->GetXaxis()->SetTitle("x (qt de bolas azuis na caixa)");
    gra->GetYaxis()->SetTitle("L");
    gra->Draw();
}