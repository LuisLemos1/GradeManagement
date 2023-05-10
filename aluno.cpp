#include "aluno.hpp"

/*
    Criar um objeto dado apenas o numero de aluno.
    Pede por um nome.
    Aloca atributos ao objeto.
*/
Aluno::Aluno(int numeroMatricula){
    string nomeAluno;    

    do {
        cout << "\n\tNome(Primeiro e Ultimo): ";
        cin.clear();
        cin.sync();
        getline(cin, nomeAluno);

        if(nomeAluno.length() < 2)
            cout << "\n\t\tPor favor insira um nome valido! Pelo menos dois caracters.\n";
    } while(nomeAluno.length() < 2);

    nome = nomeAluno;
    numero = numeroMatricula;
}

/*
    Criar um objeto dado o numero e nome de aluno.
    Aloca atributos ao objeto.
*/
Aluno::Aluno(int a, string b) {
    numero = a;
    nome = b;
}

Aluno::~Aluno() {}

/* 
    Varias funcoes de manipulacao da lista de Uc's do aluno 
*/
void Aluno::removerUltimaUc() { // Utilizada para remover duplicado no ultimo objeto das listas ao carrega-las
    listaUc.pop_back();
} 

void Aluno::updateLista(Uc* novaUc, int notaFinal, tipoAluno_EN tipoAluno, modoAvaliacao_EN modoAvaliacao, double somaEfolio, double efolio[3], double pfolio, double exame) {
    listaUc.push_back(Uc(novaUc->getCodigo(), novaUc->getECTS(), novaUc->getNome(), novaUc->getNrEfolios(), novaUc->getEfolioA(), novaUc->getEfolioB(), novaUc->getEfolioC(), notaFinal, tipoAluno, modoAvaliacao, somaEfolio, efolio, pfolio, exame));
}

void Aluno::updateLista(Uc* novaUc) { //Updated
    
    // Verificar se existe, actualizar nota se existir!
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(iteratorUc->getCodigo() == novaUc->getCodigo()) {
            cout << "\n\tUc ja existente na lista!";
            delete novaUc;
            return;
        }
    }
    
    // Adicionar na lista caso nao esteja
    if(iteratorUc == listaUc.end())
        listaUc.push_back(Uc(novaUc->getCodigo(), novaUc->getECTS(), novaUc->getNome(), novaUc->getNrEfolios(), novaUc->getEfolioA(), novaUc->getEfolioB()));

    cout << "\n\tUc Adicionado com sucesso!";
    delete novaUc;
}

void Aluno::listarUcAprovada() {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if((iteratorUc->getAvaliacao()).getNotaFinal() >= 10) {
            cout << "\t" << setw(46) << iteratorUc->getNome() << "\t" << iteratorUc->getECTS() << "\t" << (iteratorUc->getAvaliacao()).getNotaFinal() << "\n";
        }
    }
}

int Aluno::existeUcAprovadaLista(int codigo) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(iteratorUc->getCodigo() == codigo && (iteratorUc->getAvaliacao()).getNotaFinal() >= 10) {
            return 1;
        }
    }
    return 0;
}

/*
    Funcoes de Calculo
*/
double Aluno::calcularMedia() { // Corrigido o calculo da media - tem em conta o numero de ECTS por UC
    int totalECTS = 0;
    double totalNotaECTS = 0; // Somatorio da multiplicacao das notas por ECTS

    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if((iteratorUc->getAvaliacao()).getNotaFinal() >= 10){
            totalNotaECTS += ((iteratorUc->getAvaliacao()).getNotaFinal()) * iteratorUc->getECTS();
            totalECTS += iteratorUc->getECTS();
        } 
    }

    if(totalNotaECTS == 0) 
        return 0;
    else 
        return totalNotaECTS / totalECTS;
}

int Aluno::somaECTS() {
    int soma = 0;

    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if((iteratorUc->getAvaliacao()).getNotaFinal() >= 10) soma += iteratorUc->getECTS();
    }

    return soma;
}

int Aluno::contarUc() {
    int soma = 0;

    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if((iteratorUc->getAvaliacao()).getNotaFinal() >= 10) soma ++;
    }

    return soma;
}

double Aluno::getNotaUc(int codigoUc) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(iteratorUc->getCodigo() == codigoUc) {
            return (iteratorUc->getAvaliacao()).getNotaFinal();
            break;
        }
    }
    return 0;
}

/*
    Efolio B - Avaliacoes
*/
int Aluno::contemUc(int codigoUc) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(iteratorUc->getCodigo() == codigoUc)
            return 1;
    }
    return 0;
}

int Aluno::contemUcPorAprovar(int codigoUc) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(iteratorUc->getCodigo() == codigoUc && ((iteratorUc->getAvaliacao()).getModoAvaliacao() != Indeciso || (iteratorUc->getAvaliacao()).getTipoAluno() == Novo))
            return 1;
    }
    return 0;
}

void Aluno::avaliacaoUc(int codigoUc) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(iteratorUc->getCodigo() == codigoUc) {
            iteratorUc->avaliacaoUc();
            break;
        }
    }
}

void Aluno::finalizarAvaliacoes() {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        iteratorUc->finalizarAvaliacao();
    }
}