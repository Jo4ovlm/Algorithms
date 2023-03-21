#include <iostream>
#include <iomanip>
#include <cstdlib>

// Código por Ahmad Reiano Wahab e João Vitor Loch Martins

using namespace std;

typedef struct Nodo
{
    string nome;
    int cod, Qestoque, Qvendida;
    float preco;
    struct Nodo *proximo;
} Produto;

void cadastro(Produto **umproduto)
{
    Produto *p, *paux;
    bool igual;
    p = new Produto;
    if(p==NULL)
    {
        cout<<"Sem memoria disponivel";
        system("pause");
        return;
    }
    cin.ignore();
    cout<<"Informe o nome do produto"<<endl;
    getline(cin,p->nome);
    paux = *umproduto;
    while(paux != NULL)
    {
        if(paux ->nome == p->nome)
        {
            cout<<"Produto ja existente"<<endl;
            system("pause");
            delete p;
            return;
        }
        paux = paux->proximo;
    }
    do
    {
        cout<<"Informe a quantidade em estoque"<<endl;
        cin>>p->Qestoque;
    }
    while(p->Qestoque <= 0);
    do
    {
        cout<<"Informe o preco do produto"<<endl;
        cin>>p->preco;
    }
    while(p->preco <= 0.0);
    p->Qvendida = 0;
    p->cod = rand()%100 + 1;
    do
    {
        igual = false;
        paux = *umproduto;
        while(paux != NULL)
        {
            if(p->cod == paux->cod)
            {
                p->cod = rand()%100 + 1;
                igual = true;
            }
            paux = paux->proximo;
        }
    }
    while(igual == true);
    cout<<"Cadastro confirmado! Codigo do produto: "<<p->cod<<endl;
    system("pause");
    p->proximo = *umproduto;
    *umproduto = p;
}



void vender(Produto *umproduto)
{
    Produto *p = umproduto;
    int codigo, vendido;
    cout<<"Informe o codigo do produto a ser vendido: ";
    cin>>codigo;
    while(p != NULL)
    {
        if(p->cod == codigo)
        {
            do{cout<<"Informe a quantidade que sera vendida: ";
            cin>>vendido;}while(vendido <= 0);
            if(vendido > (p->Qestoque - p->Qvendida))
            {
                cout<<"Desculpe! Disponivel no estoque somente: "<<(p->Qestoque - p->Qvendida)<<endl;
                system("pause");
                return;
            }
            else
            {
                p->Qvendida += vendido;
                cout<<"Venda concluida!"<<endl;
                system("pause");
                return;
            }
        }
        p = p->proximo;
    }
    cout<<"Produto não encontrado!"<<endl;
    system("pause");
    return;
}

void procura(Produto *umproduto)
{
    Produto *p = umproduto;
    int codigo;
    cout<<"Que produto voce quer procurar: "<<endl;
    cin>>codigo;
    while(p != NULL)
    {
        if(codigo == p->cod)
        {
            cout<<"Nome: "<<p->nome<<endl<<"Codigo: "<<p->cod<<endl<<"Preco: "<<p->preco<<endl<<"Estoque: "<<p->Qestoque<<" /Vendidos: "<<p->Qvendida<<endl;
            system("pause");
            return;
        }
        p = p->proximo;
    }
    cout<<"Produto nao encontrado"<<endl;
    system("pause");
}

void exclui(Produto **umproduto)
{
    Produto *p, *pant = NULL;
    int codigo;
    char sn;
    p = *umproduto;
    cout<<"Informe o codigo do produto a ser excluido: "<<endl;
    cin>>codigo;
    if(p != NULL)
    {
        if(p->cod == codigo)
        {
            do
            {
                cout<<"Produto a ser excluido:"<<endl<<"Nome:"<<p->nome<<endl<<"Codigo: "<<p->cod<<endl<<"Preço: R$"<<p->preco<<endl<<"Estoque: "<<p->Qestoque<<" Vendidos: "<<p->Qvendida<<endl;
                cout<<"Confirmar exclusao?: S/N"<<endl;
                cin>>sn;
            }
            while(sn != 's' and sn != 'n');
            if(sn == 's')
            {
                *umproduto = p->proximo;
                delete p;
                cout<<"Item excluido com sucesso!"<<endl;
                system("pause");
                return;
            }
            else
            {
                cout<<"Exclusao cancelada"<<endl;
                system("pause");
                return;
            }
        }
        pant = *umproduto;
        p = p->proximo;
        while(p != NULL and p->cod != codigo)
        {
            pant = p;
            p=p->proximo;
        }
        if(p != NULL)
        {
            do
            {
                cout<<"Produto a ser excluido:"<<endl<<"Nome:"<<p->nome<<endl<<"Codigo: "<<p->cod<<endl<<"Preço: R$"<<p->preco<<endl<<"Estoque: "<<p->Qestoque<<" Vendidos: "<<p->Qvendida<<endl;
                cout<<"Confirmar exclusao?: S/N"<<endl;
                cin>>sn;
            }
            while(sn != 's' and sn != 'n');
            if(sn == 's')
            {
                pant->proximo = p->proximo;
                delete p;
                cout<<"Item excluido com sucesso!"<<endl;
                system("pause");
                return;
            }
            else
            {
                cout<<"Exclusao cancelada"<<endl;
                system("pause");
                return;
            }
        }
    }
    cout<<"Produto nao encontrado!"<<endl;
    system("pause");
}


void relatorio(Produto *umproduto)
{
    Produto *p = umproduto;
    cout<<"    Nome | codigo | preco | estoque | vendidos:"<<endl;
    while(p != NULL)
    {
        cout<<setw(9)<<p->nome<<"|"<<setw(8)<<p->cod<<"|"<<setw(7)<<p->preco<<"|"<<setw(9)<<p->Qestoque<<"|"<<setw(9)<<p->Qvendida<<endl;
        p = p->proximo;
    }
    system("pause");
}

void relatorioV(Produto *umproduto)
{
    Produto *p = umproduto;
    cout<<"codigo | vendidos | preco  | R$ total:"<<endl;
    while(p != NULL)
    {
        cout<<setw(7)<<p->cod<<"|"<<setw(10)<<p->Qvendida<<"|"<<setw(7)<<p->preco<<" | R$"<<(p->preco * p->Qvendida)<<endl;
        p = p->proximo;
    }
    system("pause");
}

void destroilista(Produto **umproduto)
{
    Produto *p;
    while(*umproduto != NULL)
    {
        p = *umproduto;
        *umproduto = (*umproduto)->proximo;
        delete p;
    }
}

int main()
{
    srand(time(NULL));
    Produto *umproduto = NULL;
    int opcao;
    do
    {
        system("cls");
        cout<<"O que voce deseja fazer?"<<endl;
        cout<<"1 - Cadastrar produto"<<endl;
        cout<<"2 - Vender Produto"<<endl;
        cout<<"3 - Procurar produto"<<endl;
        cout<<"4 - Excluir produto"<<endl;
        cout<<"5 - Relatorio de estoque"<<endl;
        cout<<"6 - Relatorio de vendas"<<endl;
        cout<<"0 - Sair"<<endl;
        cin>>opcao;
        switch(opcao)
        {
        case 1:
            system("cls");
            cadastro(&umproduto);
            break;
        case 2:
            system("cls");
            vender(umproduto);
            break;
        case 3:
            system("cls");
            procura(umproduto);
            break;
        case 4:
            system("cls");
            exclui(&umproduto);
            break;
        case 5:
            system("cls");
            relatorio(umproduto);
            break;
        case 6:
            system("cls");
            relatorioV(umproduto);
            break;
        case 0:
            destroilista(&umproduto);
        }



    }
    while(opcao != 0);

}


