#include "avaliacao.hpp"

/*
    Efolio B - Avaliacao
*/
Avaliacao::Avaliacao(int nota, tipoAluno_EN t, modoAvaliacao_EN m, double s, double ef[], double p, double ex) {
    notaFinal = nota;
    tipoAluno = t;
    modoAvaliacao = m;
    somaEfolio = s;
    for(int i = 0; i < 3; i++)
        efolio[i] = ef[i];
    pfolio = p;
    exame = ex;
}

Avaliacao::Avaliacao() {}

Avaliacao::~Avaliacao() {}

void Avaliacao::finalizarAvaliacao() {
    if(modoAvaliacao != Indeciso || tipoAluno == Novo) {
        if(tipoAluno == Melhoria) 
            tipoAluno = Aprovado;
        if(tipoAluno == Novo)
            tipoAluno = Repetente;

        // Atribuir um novo maximo na soma de efolios caso existir
        somaEfolio = (somarEfolios() > somaEfolio ? somarEfolios() : somaEfolio);
    
        resetAvaliacaoTemp();
    }
}

void Avaliacao::resetAvaliacaoTemp() {
    for(int i = 0; i < 3; i++)
        efolio[i] = -1;

    pfolio = -1;
    exame = -1;
    modoAvaliacao = Indeciso;
}

double Avaliacao::somarEfolios() {
    double soma = 0;

    for(int i = 0; i < 3; i++) {
        if(efolio[i] != -1)  // para o caso de haver nao avaliados
            soma += efolio[i];
    }
            
    return soma;
}

void Avaliacao::manterNotasEfolios() {
    efolio[0] = somaEfolio;
    efolio[1] = 0;
    efolio[2] = 0;
}
