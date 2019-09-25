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

void crystb(){
    // Cria a crystalball com ranges de -5 a 5.
    TF1 * cr = new TF1("cr", "crystalball", -5, 5);
    // Define os parâmetros: o primeiro é o ponto máximo da função(ymax), 
    //o segundo é o ponto central (ymax=f(xcent)),
    //o terceiro é a largura (ver direito ainda),
    //o quarto é a altura da calda inicial
    // o quinto eu não sei
    cr->SetParameters(1, 0, 1, 2, 5); 
    cr->Draw();
}

int main(){
    //Criando o histograma para preenchimento.
    TH1F *h1 = new TH1F("hshow", "h1;mass (GeV);counts",60,0,8);
    const int N = 16;
    // Inserindo dados para formar uma distribuição gausiana.
    int v[N] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7};
    for (int i = 0; i!=N; ++i){ // For para preencher o histograma
        h1->Fill(v[i]);
    }
    // Definição da função gausiana para fitar os dados do histograma
    TF1 * ga = new TF1("f1", "[0]*TMath::Gaus(x, [1], [2])", 0, 8);
    ga->SetParameter(0,1);
    ga->SetParameter(1,4.2);
    ga->SetParameter(2, 1.2);

   // h1->Fit(ga);
    TF1 *fitfun = h1->GetFunction("hshow");
    //fitfun->GetParameter(2);
    //h1->Draw();
    TFitResultPtr r = h1->Fit(ga,"S");
    
    
}