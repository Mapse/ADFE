#include "TF1.h"
#include "TH1.h"
#include <iostream>
#include "TMath.h"
using namespace std;



// Função gausiana para valores x, com parâmetros [0] (multiplica toda a função), [1] (desvio padrão) e [2] (média)
void gausian(){
    TF1 * ga = new TF1("f1", "[0]*TMath::Gaus(x, [1], [2])", 0, 8.4);
    ga->SetParameter(0,1);
    ga->SetParameter(1,4.2);
    ga->SetParameter(2, 1.2);
    ga->Draw();
}