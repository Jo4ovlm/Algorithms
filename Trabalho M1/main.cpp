#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;
#define TMAX 50

typedef struct
{
    int dia, mes, ano;
} DMA;

typedef struct
{
    string titulo, autor, isbn;
    int Qestoque, Qdisponivel;
} Livro;

typedef struct
{
    string matricula, isbn, cod;
    DMA data;
} Emprestimo;

string lerIsbn()
{
    string isbn;
    system("cls");
    cin.ignore();
    cout<<"Informe o ISBN do livro"<<endl;
    getline(cin,isbn);
    return isbn;
}

void zeraData(DMA &data)
{
    data.dia = 0;
    data.mes = 0;
    data.ano = 0;
}

void lerData(DMA &data)
{
    do
    {
        cout<<"Dia: ";
        cin>>data.dia;
    }
    while(data.dia > 31 or data.dia <1);
    do
    {
        cout<<"Mes: ";
        cin>>data.mes;
    }
    while(data.mes > 12 or data.mes <1);
    do
    {
        cout<<"Ano: ";
        cin>>data.ano;
    }
    while(data.ano < 2022);
}

void printaData(DMA data)
{
    cout<<setw(2)<<data.dia<<"/"<<setw(2)<<data.mes<<"/"<<setw(4)<<data.ano;
}

void ordenaAcervo(int nl, Livro titulos[]){
    for(int i=0; i<nl-1; i++){
        int minimo = i;
        for (int j=i+1; j<nl; j++)
            if (titulos[j].isbn < titulos[minimo].isbn)
            minimo = j;
            Livro x = titulos[i];
            titulos[i] = titulos[minimo];
            titulos[minimo] = x;
}
}

void novotitulo(int &nl, Livro titulos[])
{
    int i=nl,j;
    string isbn;
    isbn = lerIsbn();
    for(j=0; j<nl; j++){
        if(isbn == titulos[j].isbn)
        {
            cout<<"Titulo já cadastrado!"<<endl;
            system("pause");
            return;
        }
    }
    titulos[i].isbn = isbn;
    cout<<"Informe o titulo do livro"<<endl;
    getline(cin,titulos[i].titulo);
    cout<<"Informe o autor do livro"<<endl;
    getline(cin,titulos[i].autor);
    do
    {
        cout<<"Informe a quantidade no estoque"<<endl;
        cin>>titulos[i].Qestoque;
    }
    while(titulos[i].Qestoque <= 0);
    titulos[i].Qdisponivel = titulos[i].Qestoque;
    system("cls");
    cout<<"Cadastro realizado!"<<endl;
    nl++;
    ordenaAcervo(nl, titulos);
    system("pause");
}

void consultalivro(int nl, Livro titulos[])
{
    int i;
    string isbn;
    isbn = lerIsbn();
    for(i=0; i<nl; i++)
    {
        if(isbn == titulos[i].isbn)
        {
            cout<<"Titulo do livro: "<<titulos[i].titulo<<endl;
            cout<<"Autor do livro: "<<titulos[i].autor<<endl;
            cout<<"Quantidade no estoque: "<<titulos[i].Qestoque<<endl;
            cout<<"Quantidade disp para emprestimo: "<<titulos[i].Qdisponivel<<endl;
            system("pause");
            return;
        }
        }
        cout<<"Livro nao encontrado"<<endl;
        system("pause");
        return;
}

void emprestimo(int nl, int &ne, Livro titulos[], Emprestimo emprest[])
{
    string isbn, cod;
    bool igual;
    int i;
    isbn = lerIsbn();
    for(i = 0; i<nl; i++)
    {
        if(isbn == titulos[i].isbn)
        {
            if(titulos[i].Qdisponivel == 0)
            {
                system("cls");
                cout<<"Desculpe! Nao temos unidades disponiveis para emprestimo"<<endl;
                system("pause");
                return;
            }
            emprest[ne].isbn = isbn;
            cout<<"Informe o numero da matricula de quem esta pegando"<<endl;
            getline(cin, emprest[ne].matricula);
            cout<<"Informe a data de entrega"<<endl;
            lerData(emprest[ne].data);
            cin.ignore();
            do{
                cout<<"Informe o codigo do emprestimo"<<endl;
                getline(cin,cod);
                for(int k=0;k<ne;k++){
                    igual = false;
                    if(emprest[k].cod == cod){
                        cout<<"Codigo ja utilizado!"<<endl;
                        igual = true;
                    }
                }
            }while(igual == true);
            emprest[ne].cod = cod;
            cout<<"Emprestimo Realizado! Codigo: "<<emprest[ne].cod<<endl;
            ne++;
            system("pause");
            titulos[i].Qdisponivel -= 1;
            return;
        }
    }
            system("cls");
            cout<<"Titulo nao encontrado"<<endl;
            system("pause");
            return;
}


void devolve(int nl, int ne, Livro titulos[], Emprestimo emprest[])
{
    string codigo;
    cin.ignore();
    cout<<"Informe o codigo do emprestimo"<<endl;
    getline(cin,codigo);
    for(int i=0; i<ne; i++)
    {
        if(emprest[i].cod == codigo)
        {
            for(int j=0; j<nl; j++)
            {
                if(titulos[j].isbn == emprest[i].isbn)
                {
                    titulos[j].Qdisponivel += 1;
                    emprest[i].matricula = "-1";
                }
            }
            system("cls");
            cout<<"Devoluçao concluida!"<<endl;
            return;
        }
    }
            system("cls");
            cout<<"Codigo nao encontrado"<<endl;
            system("pause");
            return;
}

void excluir(int &nl, Livro titulos[])
{
    string isbn;
    isbn = lerIsbn();
    for(int i=0; i<nl; i++)
    {
        if(titulos[i].isbn == isbn)
        {
            titulos[i] = titulos[nl-1];
            titulos[nl-1].autor = " ";
            titulos[nl-1].isbn = " ";
            titulos[nl-1].Qdisponivel = 0;
            titulos[nl-1].Qestoque = 0;
            titulos[nl-1].titulo = " ";
            nl--;
            cout<<"Exclusao concluida!"<<endl;
            system("pause");
            return;
        }
    }
        cout<<"Livro nao encontrado, verifique o ISBN"<<endl;
        system("pause");
        return;
}

void relatorio1(int nl, Livro titulos[])
{
    cout<<"     ISBN    |"<<"    Titulo     |"<<"     Autor     |"<<" Estq. | Disp."<<endl;
    for(int i=0; i<nl; i++)
    {
        cout<<titulos[i].isbn<<"|"<<setw(15)<<titulos[i].titulo<<"|"<<setw(15)<<titulos[i].autor;
        cout<<"| "<<setw(6)<<titulos[i].Qestoque<<"| "<<setw(6)<<titulos[i].Qdisponivel<<endl;
    }
    system("pause");
}

void relatorio2(int ne, Emprestimo emprest[])
{
    int i;
    cout<<"     ISBN    |"<<"Matricula |"<<"  Entrega  |"<<"Codigo"<<endl;
    for(i=0; i<ne; i++)
    {
        if(emprest[i].matricula != "-1"){
        cout<<emprest[i].isbn<<"|"<<setw(11)<<emprest[i].matricula<<"|";
        printaData(emprest[i].data);
        cout<<"|"<<setw(7)<<emprest[i].cod<<endl;}
    }
    system("pause");
}

void menu(Livro titulos[], Emprestimo emprest[])
{
    int opcao, nl=0, ne=0;
    do
    {
        system("cls");
        cout<<"Selecione uma operacao:"<<endl;
        cout<<"1 - Incluir um novo titulo"<<endl;
        cout<<"2 - Consultar titulo"<<endl;
        cout<<"3 - Emprestimo"<<endl;
        cout<<"4 - Devolucao"<<endl;
        cout<<"5 - Excluir um livro"<<endl;
        cout<<"6 - Relatorio dos livros"<<endl;
        cout<<"7 - Relatorio dos emprestimos"<<endl;
        cout<<"0 - Sair"<<endl;
        cin>>opcao;
        switch(opcao)
        {
        case 1:
            system("cls");
            novotitulo( nl, titulos);
            break;
        case 2:
            system("cls");
            consultalivro(nl, titulos);
            break;
        case 3:
            system("cls");
            emprestimo(nl, ne, titulos, emprest);
            break;
        case 4:
            system("cls");
            devolve(nl, ne, titulos, emprest);
            break;
        case 5:
            system("cls");
            excluir(nl, titulos);
            break;
        case 6:
            system("cls");
            relatorio1(nl, titulos);
            break;
        case 7:
            system("cls");
            relatorio2(ne, emprest);
            break;
        }
    }
    while(opcao != 0);
}

int main()
{
    Livro titulos[TMAX];
    Emprestimo emprest[TMAX];
    menu(titulos, emprest);
    system("cls");
    cout<<"Codigo por Joao Vitor Loch Martins e Ahmad Reiano Wahab"<<endl;
    return 0;
}
