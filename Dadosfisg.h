#include <TCanvas.h>
#include <TH1I.h>
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"

void Primtre(){
        
    TFile *dados = new TFile("Q1.root","RECREATE");
    TTree *tree = new TTree("mree","data from csv file");
    
    tree->ReadFile("DadosFisGeral2001_2.csv","idade/I,massa/D,altura/D",',');
        
    int idade;   
    double massa, altura;

    TH1I *h_idade = new TH1I("idade", "Histograma de idade", 25,15.,40.);
    TH1D *h_altura = new TH1D("altura", "Histograma de altura", 17,158.,192.);
    TH1D *h_massa = new TH1D("massa", "Histograma de massa", 20,50.,130.);
    
    tree->SetBranchAddress("idade", &idade);
    tree->SetBranchAddress("altura", &altura);
    tree->SetBranchAddress("massa", &massa);
    
   
    auto n = tree->GetEntries();
    
    for (auto i = 0; i != n; ++i){
        tree->GetEntry(i);
        h_idade->Fill(idade);
        h_altura->Fill(altura);
        h_massa->Fill(massa);
    }
    TCanvas *c_massa = new TCanvas("massa","Massa",400,500);
    TCanvas *c_idade = new TCanvas("idade","idade",400,500);
    TCanvas *c_altura = new TCanvas("altura","altura",400,500);

    c_idade->cd();
    h_idade->Draw();
        
    c_altura->cd();
    h_altura->Draw();
    
    c_massa->cd();
    h_massa->Draw();
    //c_massa->update();
}

//Função que plota os diagramas de dispersão.
void dispersao(){
    
    int idade;
    double massa, altura;

    TFile *dados = new TFile("Q1.root"); //Carrega o file;
    TTree *tree = new TTree("mree","data from csv file"); //Pega a tree que está dentro do file;

    tree->ReadFile("DadosFisGeral2001_2.csv","idade/I,massa/D,altura/D",',');
    
    tree->SetBranchAddress("massa", &massa);
    tree->SetBranchAddress("idade", &idade);
    tree->SetBranchAddress("altura", &altura); 

    int n = tree->GetEntries();

    int id[n]; //Array para guardar as idades.
    int ma[n], al[n]; //Array para guardar as massas e as idades.

    //rotina para prencher os arrays

    for (auto i = 0; i != n; i++){
        tree->GetEntry(i);
        id[i] = idade;
        ma[i] = massa;
        al[i] = altura;
    }

    // Cria um canvas para cada gráfico de dispersão
    TCanvas *cg1 = new TCanvas("Dispersão 1","Diagrama de dispersao 1",700,500);
    TCanvas *cg2 = new TCanvas("Dispersão 2", "Diagrama de dispersao 2",700,500);
    TCanvas *cg3 = new TCanvas("Dispesão 3","Diagrama de dispersao 3",700,500);

    // Cria o gráfico para a dispersão da altura e idade.
    TGraph *grafico1 = new TGraph(n, id, al);
    
    // Deixando o gráfico mais agradável.
    grafico1->SetTitle("Altura x idade");
    grafico1->GetXaxis()->SetTitle("idade (anos)");
    grafico1->GetYaxis()->SetTitle("altura (cm)");
    grafico1->SetMarkerStyle(20);
    grafico1->SetMarkerSize(0.9);
    grafico1->SetMarkerColor(1);

    // Cria o gráfico para a dispersão da altura e idade.
    TGraph *grafico2 = new TGraph(n, id, ma);

    // Deixand o gráfico mais agradável.
    grafico2->SetTitle("Massa x idade");
    grafico2->GetXaxis()->SetTitle("idade (anos)");
    grafico2->GetYaxis()->SetTitle("Massa (kg)");
    grafico2->SetMarkerStyle(20);
    grafico2->SetMarkerSize(0.9);
    grafico2->SetMarkerColor(1);

    // Cria o gráfico para a dispersão da altura e massa.
    TGraph *grafico3 = new TGraph(n, ma, al);

    // Deixand o gráfico mais agradável.
    grafico3->SetTitle("Altura x massa");
    grafico3->GetXaxis()->SetTitle("Massa (anos)");
    grafico3->GetYaxis()->SetTitle("Altura (kg)");
    grafico3->SetMarkerStyle(20);
    grafico3->SetMarkerSize(0.9);
    grafico3->SetMarkerColor(1);

    //Seleciona o canvas 1 e desenha o diagrama de dispersão da altura e idade.
    cg1->cd();
    grafico1->Draw("AP"); 

    //Seleciona o canvas 2 e desenha o diagrama de dispersão da altura e idade.
    cg2->cd();
    grafico2->Draw("AP"); 

    //Seleciona o canvas 3 e desenha o diagrama de dispersão da altura e massa.
    cg3->cd();
    grafico3->Draw("AP"); 
}

