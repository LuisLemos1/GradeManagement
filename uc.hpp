//Header Guards
#ifndef UC
#define UC

#include "avaliacao.hpp"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Uc{
    private:
        int codigo;
        int ects;
        string nome;
        // int ano; // removido -> informacao nunca utilizada
        // int semestre; // removido -> informacao nunca utilizada
        int nrEfolios; // adicionado
        int efolioA; // adicionado
        int efolioB; // adicionado
        int efolioC; // adicionado
        Avaliacao avaliacao;

    public:
        /*
            Construtores e Descontrutor
        */
        Uc(int, int, string, int, int, int); 
        Uc(int, int, string, int, int, int, int, int, tipoAluno_EN, modoAvaliacao_EN, double, double[], double, double);
        Uc();
        virtual ~Uc();

        /*
            Efolio B - Avaliacoes
        */
        void finalizarAvaliacao() { avaliacao.finalizarAvaliacao(); };

        void avaliacaoEfolioA();
        void avaliacaoEfolioB();
        void avaliacaoEfolioC();
        void avaliacaoPfolio();
        void avaliacaoPfolioRecurso();
        void avaliacaoExame();
        void avaliacaoExameRecurso();

        /* 
            Efolio B - Menus
        */
        void menuAvaliacaoIndeciso();
        void menuAvaliacaoContinua();
        void menuAvaliacaoExame();
        void avaliacaoUc();

        /*
            Setters e Getters
        */
        void setCodigo(int cod) { codigo = cod; };
        void setECTS(int e) { ects = e; };
        void setNome(string n) { nome = n; };
        void setNrEfolios(int n) { nrEfolios = n; };
        void setEfolioA(int n) { efolioA = n; };
        void setEfolioB(int n) { efolioB = n; };
        void setEfolioC(int n) { efolioC = n; };
        int getCodigo() { return codigo; };
        int getECTS() { return ects; };
        string getNome() { return nome; };
        Avaliacao getAvaliacao() { return avaliacao; };
        int getNrEfolios() { return nrEfolios; };
        int getEfolioA() { return efolioA; };
        int getEfolioB() { return efolioB; };
        int getEfolioC() { return efolioC; };
};

#endif