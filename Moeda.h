#ifndef MOEDA_H
#define MOEDA_H


#include "TFile.h"
#include <TCanvas.h>
#include "TGraph.h"
#include <cstdlib> //utiliza o random do c++


// rotina que determina o número de caras
int moeda(int N){
    int i = 0;
    int cara = 0;
    while (i <= N) {
        if (rand() %2) cara++; //rand() %2 retornas números 0 ou 1
        i++ ;
        
    }
    return cara;
}

//rotina que cria a tree para armazenar o número de jogadas e a dispersão associada.
void retorna(int jog = 1000){
    int n_jog, disp; //variáveis número de jogadas e dispersão
    TFile *file = new TFile("Distcara.root", "RECREATE"); //Cria o arquivo Distcara.
    TTree *tree = new TTree("mtree","distribut"); //Cria a tree para armazenar os dados.
    TBranch *brj = tree->Branch("jog", &n_jog); //Cria o ramo que armazena o número de jogadas.
    TBranch *brd = tree->Branch("disp", &disp); //Cria o ramo que armazena a dispersão.
    
    //for para o preenchimento da tree
    for (int i = 2; i <= jog; i = i+2){//armazenamos de duas em duas jogadas
        n_jog = i;
        disp = moeda(n_jog) - n_jog/2; //Calcula a dispersão.
        tree->Fill(); //preenche a ttree
    }
    file->Write();
    file->Close();
}

//rotina para criar o gráfico de dispersão.
void grafdisp(){
    int n_jog, disp;
    TFile *file = new TFile("Distcara.root"); //Lê o arquivo file.
    TTree *tree = (TTree*) file->Get("mtree"); //Pega a tree que está dentro do file para utilizar os dados.
    
    //Associa as variáveis da tree às variáveis criadas aqui.
    tree->SetBranchAddress("jog", &n_jog); 
    tree->SetBranchAddress("disp", &disp);
    
    int n = tree->GetEntries();//Tamanho da tree.
    int x[n], y[n]; //Cria os arrays para a plotagem do gráfico.

    for (auto i = 0; i < n; i++){
        tree->GetEntry(i); //toma a entra i da tree para jogar nas arrays.
        x[i] = n_jog;
        y[i] = disp;
        
    }
    TCanvas *cm = new TCanvas("c1", "Joga a moeda", 600, 500);
    TGraph *grafico = new TGraph(n, x, y); //Plota o gŕafico
    
    cm->cd();
    grafico->SetTitle("Dispers#tilde{a}o x N#circ de jogadas");
    grafico->GetXaxis()->SetTitle("N#circ de jogadas");
    grafico->GetYaxis()->SetTitle("Dispers#tilde{a}o");
    grafico->SetLineColor(2);
    grafico->SetLineWidth(1);
    grafico->GetXaxis()->SetRangeUser(0.,n*2);
    grafico->Draw();

    file->Close();
    

}

#endif