#ifndef CURSO
#define CURSO

#include "aluno.hpp"
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Curso {
    private:
        // Poderia por nome do curso, mas apenas programei para as funcionalidades do efolio.
        list<Aluno> listaAluno;
        list<Aluno>::iterator iteratorAluno;
        /*
            Lista de UC's predefinidas para LEI
        */
        list<Uc> listaUc;
        list<Uc>::iterator iteratorUc;

    public:
        // Construtores e Desconstrutor
        Curso();
        virtual ~Curso();
        
        /*
            Funcoes remetentes a Lista de Alunos
        */
        int existeAluno(int );
        int existeAluno(int, int );
        int existeUc(int );
        void listarUcsCurso();
        void listarAlunos();
        void listarAlunos(int );
        void adicionarAluno(int );
        void inscricaoUc(int, int, int, tipoAluno_EN, modoAvaliacao_EN, double, double[], double, double);
        void inscricaoUc(int, int );
        void listarUcAprovadaAluno(int );
        void estatisticaAluno(int );
        void estatisticaUc(int );

        // Getters
        string getNomeAluno(int );
        Uc* getUc(int );
        string getNomeUc(int );

        /*
            Funcoes iniciais na abertura e fecho do programa.
            Le varios ficheiros na abertura.
            Guarda varios ficheiros na saida.
        */
        void carregarListaUc();
        void carregarListaAluno();
        void carregarListaInscricoes();
        void guardarListaAluno();
        void guardarListaInscricoes();
        void guardarListaUc(); // Adicionado para poder alterar o numero e valor dos efolios
        void despedida();

        /*
            Varios menus
        */
        void menuNovoAluno();
        void menuInscricaoUc();
        void menuConsultaAluno();
        void menuConsultaUc();

        /*
            Efolio B - Funcoes Avaliacao
        */
        void avaliacaoAluno(int , int );
        void alterarCriteriosAvaliacao(int, int, int, int);
        int existeAlunoPorAprovar(int );

        /*
            Efolio B - Menus Avaliacao
        */
        void finalizarAvaliacoes();
        void alterarCriteriosAvaliacao();
        void menuAdicionarNota();
        void menuAvaliacoes();
};

#endif